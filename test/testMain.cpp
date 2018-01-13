#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stdexcept>
#include "doctest.h"
#include "fakeit.hpp"
#include "mock/mockCounter.hpp"

using namespace fakeit;

// Counterをモック化
#define Counter MockCounter
// doctest.hもmainを生成するため、本番mainは名前を変える
#define main main_production
#include "main.cpp"
#undef Counter
#undef main

struct Fixture {
    Fixture() {
        // setup
        MockCounter::mockEnable = true;
    }
    ~Fixture() {
        // tear down
        MockCounter::mockEnable = false;
        delete MockCounter::useMock;
    }
};

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

    TEST_CASE_FIXTURE(Fixture, "exception on Counter::setFibonacci.") {
        Mock<ICounter> mock;
        MockCounter::useMock = new bool[1]{true};
        MockCounter::mock    = &mock.get();
        When(Method(mock, setFibonacci)).Throw(std::exception());

        CHECK_THROWS(main_production(1, NULL));
    }

    TEST_CASE_FIXTURE(Fixture, "exception on Counter::calcTime.") {
        Mock<ICounter> mock;
        MockCounter::useMock = new bool[2]{false, true};
        MockCounter::mock    = &mock.get();
        When(Method(mock, calcTime)).Throw(std::exception());

        CHECK_THROWS(main_production(1, NULL));
    }
}
