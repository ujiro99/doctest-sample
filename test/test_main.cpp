#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("main") {
    CHECK(main(0, 0) == 0);
}
