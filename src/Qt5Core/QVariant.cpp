#include "QVariant.hpp"

#include "QChar.hpp"
#include "QString.hpp"
#include "../algorithm.hpp"
#include "../convert/string.hpp"
#include "../convert/numeric.hpp"

#include <unordered_map>
#include <QStringList>

std::unordered_map<int, std::function<void(lua_State* const, const QVariant&)>>& qvariant_push_handler()
{
    static std::unordered_map<int, std::function<void(lua_State* const, const QVariant&)>> _rv;
    return _rv;
}

std::unordered_map<int, std::function<void(QVariant&, const lua::index&)>>& qvariant_store_handler()
{
    static std::unordered_map<int, std::function<void(QVariant&, const lua::index&)>> _rv;
    return _rv;
}

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

void lua::set_qvariant_push_handler(const int type, const std::function<void(lua_State* const, const QVariant&)>& handler)
{
    qvariant_push_handler()[type] = handler;
}

void lua::set_qvariant_store_handler(const int type, const std::function<void(QVariant&, const lua::index&)>& handler)
{
    qvariant_store_handler()[type] = handler;
}

void lua::push_qvariant(lua_State* const state, const QVariant& value)
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
        {
            lua::push(state, value.toInt());
            break;
        }
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
            auto converter = qvariant_push_handler().find(value.userType());
            if (converter != qvariant_push_handler().end()) {
                converter->second(state, value);
            } else {
                throw std::logic_error(std::string("No handler exists to push QVariant type: ") + value.typeName());
            }
        }
    }
}

void lua::store_qvariant(QVariant& destination, lua_State* const state, const int pos)
{
    lua::index source(state, pos);
    switch (destination.userType()) {
        case QVariant::Invalid:
            throw lua::error("A QVariant must have a valid type");
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
            for (unsigned int i = 1; i <= length; ++i) {
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
            auto converter = qvariant_store_handler().find(destination.userType());
            if (converter != qvariant_store_handler().end()) {
                converter->second(destination, source);
            } else {
                throw std::logic_error(std::string("No QVariant handler exists to store type: ") + destination.typeName());
            }
        }
    }
}
