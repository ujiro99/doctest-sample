#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stdexcept>
#include "MockCounter.hpp"
#include "doctest.h"
#include "fakeit.hpp"
#include "fibonacci.cpp"

using namespace fakeit;

// Counterをモック化
#define Counter MockCounter
// doctest.hもmainを生成するため、本番mainは名前を変える
#define main main_production
#include "main.cpp"
#undef Counter
#undef main

TEST_SUITE("main.cpp") {
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
    TEST_CASE("returns 0 if error argv") {
        CHECK(main_production(1, NULL) == 0);
    }
    TEST_CASE("exception on Counter::setFibonacci.") {
        Mock<ICounter> mock;
        MockCounter::mockEnable = true;
        MockCounter::mock       = &mock.get();
        When(Method(mock, setFibonacci)).Throw(std::exception());
        CHECK_THROWS(main_production(1, NULL));
    }
}
