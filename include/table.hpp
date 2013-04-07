#ifndef TABLE_HEADER
#define TABLE_HEADER

#include "LuaStack.hpp"

namespace table {

template <typename Table, typename Value>
void push(Table table, Value value)
{
    LuaStack stack(table.lua());
    stack << table;
    const int len = stack.length();
    stack.set(len + 1, value);
}

} // namespace table

#endif // TABLE_HEADER
