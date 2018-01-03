#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#define main _old_main

#include "main.cpp"

#undef main
#define test_main main

TEST_CASE("main") {
    CHECK(main(0, 0) == 0);
}
