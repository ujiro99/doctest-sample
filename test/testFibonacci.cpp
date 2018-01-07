#include <unistd.h>
#include <vector>
#include "doctest.h"

// テスト対象
#include "fibonacci.cpp"

int g_out   = 0;
bool g_done = false;

TEST_SUITE("fibonacci.cpp") {
    int inout[3][2] = {{0, 0}, {5, 5}, {10, 55}};

    TEST_CASE("RecursiveFibonacci") {
        for (auto &i : inout) {
            int in  = i[0];
            int out = i[1];
            CAPTURE(in);
            Fibonacci *fib = new RecursiveFibonacci();

            int ret = fib->calc(in);
            CHECK_EQ(ret, out);
        }
    }

    TEST_CASE("MemorizeFibonacci") {
        for (auto &i : inout) {
            int in  = i[0];
            int out = i[1];
            CAPTURE(in);

            Fibonacci *fib = new MemorizeFibonacci();

            int ret = fib->calc(in);
            CHECK_EQ(ret, out);
        }
    }

    TEST_CASE("DPFibonacci") {
        for (auto &i : inout) {
            int in  = i[0];
            int out = i[1];
            CAPTURE(in);
            Fibonacci *fib = new DPFibonacci();

            int ret = fib->calc(in);
            CHECK_EQ(ret, out);
        }
    }

    TEST_CASE("AsyncDPFibonacci") {
        for (auto &i : inout) {
            int in = i[0];
            g_out  = i[1];
            CAPTURE(in);

            AsyncDPFibonacci *fib = new AsyncDPFibonacci();

            fib->onExecuted = [](ExecutedData data) {
                CHECK_EQ(data.result, g_out);
                g_done = true;
            };

            g_done = false;
            fib->calc(in);
            while (!g_done) {
                usleep(1000);
            }
        }
    }
}
