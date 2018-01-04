#include <iostream>
#include <sstream>
#include "doctest.h"

// テスト対象
#include "counter.cpp"

TEST_SUITE("counter") {
    TEST_CASE("calcTime") {
        SUBCASE("shows error message.") {
            std::stringbuf buf;
            std::streambuf* prev = std::cout.rdbuf(&buf);

            Counter* c = new Counter();
            c->setFibonacci(NULL);
            c->calcTime(1);

            std::cout.rdbuf(prev);
            CHECK_EQ("[error] Fibonacci is not initialized.\n", buf.str());

            delete c;
            delete prev;
        }
    }
}
