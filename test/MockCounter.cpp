#include "MockCounter.hpp"
#include "counter.hpp"

ICounter *MockCounter::mock  = nullptr;
bool MockCounter::mockEnable = false;

MockCounter::MockCounter() {
    counter = new Counter();
}

MockCounter::~MockCounter() {
    delete counter;
}

void MockCounter::setFibonacci(Fibonacci *fib) {
    if (mockEnable) {
        mock->setFibonacci(fib);
    } else {
        counter->setFibonacci(fib);
    }
}

void MockCounter::calcTime(int x) {
    if (mockEnable) {
        mock->calcTime(x);
    } else {
        counter->calcTime(x);
    }
}
