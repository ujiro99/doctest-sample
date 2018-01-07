/**
 * @file fibonacci.cpp
 * @brief フィボナッチ数を計算するクラスの定義を記載する.
 */
#include "fibonacci.hpp"
#include <future>
#include <iostream>

using namespace std;

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
    for (int i = 2; i <= x; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[x];
}

AsyncDPFibonacci::AsyncDPFibonacci() {
    name = "Async   ";
}

AsyncDPFibonacci::~AsyncDPFibonacci() {}

void AsyncDPFibonacci::execCalc(int x) {
    if (onExecuted == nullptr) {
        cout << "onExecuted is null" << endl;
        return;
    }

    DPFibonacci *f = new DPFibonacci();

    int ret = f->calc(x);

    delete f;

    data.name   = name;
    data.result = ret;
    onExecuted(data);
}

int AsyncDPFibonacci::calc(int x) {
    data.start = clock();
    // execute async
    t = std::thread(&AsyncDPFibonacci::execCalc, this, x);
    return 0;
}

void AsyncDPFibonacci::wait() {
    t.join();
}
