#include <vector>
#include "counter.hpp"
#include "fibonacci.hpp"

using namespace std;

/**
 * main関数.
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
