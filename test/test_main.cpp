#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#define main _old_main
#include "main.cpp"
#include "counter.cpp"
#include "fibonacci.cpp"

TEST_CASE("main") {
    CHECK(_old_main(0, 0) == 0);
}
