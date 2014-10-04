#define BOOST_TEST_MODULE luacxx_without_conversions
#define LUACXX_EXCLUDE_NUMERIC_CONVERSION
#include "main.hpp"

#include "thread.hpp"
#include "stack.hpp"
#include "algorithm.hpp"
#include "load.hpp"

BOOST_AUTO_TEST_CASE(luacxx_without_conversions)
{
    auto env = lua::create();

    env["foo"] = 42;
    BOOST_CHECK(!env["foo"].type().number());
    BOOST_CHECK(env["foo"].type().userdata());

    // Is const char* conversion implicit?
    env["bar"] = "notime";
    BOOST_CHECK(!env["bar"].type().string());
    BOOST_CHECK(env["bar"].type().userdata());

    env["baz"] = true;
    BOOST_CHECK(!env["baz"].type().boolean());
    BOOST_CHECK(env["baz"].type().userdata());
    lua::push(env["baz"]);
}
