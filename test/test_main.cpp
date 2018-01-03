#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "main.cpp"

TEST_CASE("main") {
    CHECK(main(0, 0) == 0);
}
