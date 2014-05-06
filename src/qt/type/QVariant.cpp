#include "qt/type/QVariant.hpp"
#include "qt/type/QChar.hpp"
#include "qt/type/QString.hpp"
#include "algorithm.hpp"

#include <unordered_map>
#include <QStringList>

namespace std {
    template<>
    class hash<QVariant::Type>
    {
    public:
        size_t operator()(const QVariant::Type& value) const
        {
            return static_cast<int>(value);
        }
    };
}

namespace {
static std::unordered_map<int, std::function<void(lua::state* const, const QVariant&)>> qvariant_push_handler;
static std::unordered_map<int, std::function<void(QVariant&, const lua::index&)>> qvariant_store_handler;
}

void lua::push_qvariant(lua::state* const state, const QVariant& value)
{
    switch (value.userType()) {
        case QVariant::Invalid:
            lua::push(state, lua::value::nil);
            break;
        case QVariant::Bool:
            lua::push(state, value.toBool());
            break;
        case QVariant::Char:
            lua::push(state, value.toChar());
            break;
        case QVariant::Int:
            lua::push(state, value.toInt());
            break;
        case QVariant::Double:
        case QVariant::UInt:
            lua::push(state, value.toDouble());
            break;
        case QVariant::String:
            lua::push(state, value.toString());
            break;
        case QVariant::Hash:
        {
            auto hash = value.toHash();

            auto table = lua::push(state, lua::value::table);
            for (auto i = hash.begin(); i != hash.end(); ++i) {
                lua::table::set(table, i.key(), i.value());
            }

            break;
        }
        case QVariant::StringList:
        {
            auto list = value.toStringList();

            auto table = lua::push(state, lua::value::table);
            for (int i = 0; i < list.size(); ++i) {
                lua::table::set(table, i + 1, list[i]);
            }

            break;
        }
        default:
        {
            auto converter = qvariant_push_handler.find(value.userType());
            if (converter != qvariant_push_handler.end()) {
                converter->second(state, value);
            } else {
                throw std::logic_error(std::string("QVariant type not supported: ") + value.typeName());
            }
        }
    }
}

void lua::store_qvariant(QVariant& destination, const lua::index& source)
{
    switch (destination.userType()) {
        case QVariant::Invalid:
            destination.clear();
            break;
        case QVariant::Bool:
            destination.setValue(lua::get<bool>(source));
            break;
        case QVariant::Char:
            destination.setValue(lua::get<char>(source));
            break;
        case QVariant::Int:
        case QVariant::UInt:
            destination.setValue(lua::get<int>(source));
            break;
        case QVariant::Double:
            destination.setValue(lua::get<double>(source));
            break;
        case QVariant::String:
            destination.setValue(lua::get<QString>(source));
            break;
        case QVariant::StringList:
        {
            auto state = source.state();
            QStringList items;

            auto length = lua_rawlen(state, source.pos());
            for (int i = 1; i <= length; ++i) {
                lua::push(state, i);
                lua_gettable(state, source.pos());
                items << lua::get<QString>(state, -1);
                lua_pop(state, 1);
            }

            destination.setValue(items);
            break;
        }
        case QVariant::Hash:
        {
            QHash<QString, QVariant> hash;

            auto state = source.state();

            lua::push(state, lua::value::nil);
            while (lua_next(state, source.pos()) != 0) {
                auto key = lua::get<QString>(state, -2);
                auto value = lua::get<QVariant>(state, -1);

                hash[key] = value;

                lua_pop(state, 1);
            }

            destination.setValue(hash);
            break;
        }
        default:
        {
            auto converter = qvariant_store_handler.find(destination.type());
            if (converter != qvariant_store_handler.end()) {
                converter->second(destination, source);
            } else {
                throw std::logic_error(std::string("QVariant type not supported: ") + destination.typeName());
            }
        }
    }
}