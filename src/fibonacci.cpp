/**
 * @file fibonacci.cpp
 * @brief フィボナッチ数を計算するクラスの定義を記載する.
 */
#include "fibonacci.hpp"
#include <future>

RecursiveFibonacci::RecursiveFibonacci() {
    name = "Recursive";
}

RecursiveFibonacci::~RecursiveFibonacci() {}

int RecursiveFibonacci::calc(int x) {
    if (x == 0) {
        return 0;
    } else if (x == 1) {
        return 1;
    } else {
        return calc(x - 1) + calc(x - 2);
    }
}

MemorizeFibonacci::MemorizeFibonacci() {
    name = "Memorize";
}

MemorizeFibonacci::~MemorizeFibonacci() {}

int MemorizeFibonacci::calc(int x) {
    if (x == 0) {
        return 0;
    } else if (x == 1) {
        return 1;
    } else if (memo[x] != 0) {
        return memo[x];
    }
    memo[x] = calc(x - 1) + calc(x - 2);
    return memo[x];
}

DPFibonacci::DPFibonacci() {
    name = "Dynamic ";
}

DPFibonacci::~DPFibonacci() {}

int DPFibonacci::calc(int x) {
    int dp[1000] = {0, 1};
    for (int i = 2; i < x; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[x];
}

AsyncDPFibonacci::AsyncDPFibonacci() {
    name = "Async   ";
}

AsyncDPFibonacci::~AsyncDPFibonacci() {}

int AsyncDPFibonacci::calc(int x) {
    int ret;
    DPFibonacci *f = new DPFibonacci();

    // execute async
    auto t = std::thread([f, &x, &ret] { ret = f->calc(x); });
    t.join();

    delete f;
    return ret;
}
