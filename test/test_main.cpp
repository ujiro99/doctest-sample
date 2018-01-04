#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// doctestもmainを生成するため、本番mainは名前を変える
#define main main_production

// テスト対象
#include "fibonacci.cpp"
#include "main.cpp"

TEST_SUITE("main") {
    TEST_CASE("returns 0") {
        CHECK(main_production(0, NULL) == 0);
    }
    TEST_CASE("returns 0 if error argc") {
        const char* argv[] = {"param0", "param1", "param2"};
        CHECK(main_production(-1, argv) == 0);
    }
    TEST_CASE("returns 0 if error argv") {
        CHECK(main_production(1, NULL) == 0);
    }
}
