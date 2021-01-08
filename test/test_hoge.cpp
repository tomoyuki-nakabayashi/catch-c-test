#include <catch.hpp>
#include <hoge.h>

TEST_CASE("test fuga") {
    REQUIRE(fuga() == 42);
}
