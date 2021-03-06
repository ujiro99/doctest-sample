/**
 * @file counter.cpp
 * @brief フィボナッチ数の計算時間を記録するクラスの定義を記載する.
 */
#include "counter.hpp"
#include <iostream>

using namespace std;

Counter::Counter() {
    t_fib = NULL;
}

void Counter::setFibonacci(Fibonacci *fib) {
    t_fib = fib;
}

void Counter::calcTime(int x) {
    if (t_fib == NULL) {
        cout << "[error] Fibonacci is not initialized." << endl;
        return;
    }

    clock_t start = clock();
    int ret       = t_fib->calc(x);

    cout << t_fib->name << "\t";
    cout << ret << "\t";
    cout << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
}

void Counter::calcTimeAsync(int x) {
    if (t_fib == NULL) {
        cout << "[error] Fibonacci is not initialized." << endl;
        return;
    }

    t_fib->onExecuted = [](ExecutedData data) {
        cout << data.name << "\t";
        cout << data.result << "\t";
        cout << (double)(clock() - data.start) / CLOCKS_PER_SEC << endl;
    };

    t_fib->calc(x);
}
