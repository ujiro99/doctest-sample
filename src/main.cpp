/**
 * @file main.cpp
 * @brief 一番最初に実行される関数を定義する.
 */

#include <vector>
#include "counter.hpp"
#include "fibonacci.hpp"

using namespace std;

/**
 * main関数.
 * @param[in] argc コマンドライン引数の数
 * @param[in] argv コマンドライン引数文字列配列のポインタ
 * @retval 正常終了: 0
 * @retval 異常終了: 1
 */
int main(int argc, char const *argv[]) {
    Fibonacci *r_fib = new RecursiveFibonacci();
    Fibonacci *m_fib = new MemorizeFibonacci();
    Fibonacci *d_fib = new DPFibonacci();

    Counter *counter = new Counter();

    vector<Fibonacci *> fib(3);
    fib[0] = r_fib;
    fib[1] = m_fib;
    fib[2] = d_fib;

    for (unsigned int i = 0; i < fib.size(); i++) {
        counter->setFibonacci(fib[i]);
        counter->calcTime(30);
    }
    return 0;
}
