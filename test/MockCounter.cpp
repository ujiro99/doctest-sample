#include "MockCounter.hpp"
#include "counter.hpp"

ICounter *MockCounter::mock  = nullptr;
bool MockCounter::mockEnable = false;
bool *MockCounter::useMock   = nullptr;

MockCounter::MockCounter() {
    counter   = new Counter();
    callCount = 0;
}

MockCounter::~MockCounter() {
    delete counter;
}

void MockCounter::setFibonacci(Fibonacci *fib) {
    if (mockEnable && useMock[callCount]) {
        mock->setFibonacci(fib);
    } else {
        counter->setFibonacci(fib);
    }
    callCount++;
}

void MockCounter::calcTime(int x) {
    if (mockEnable && useMock[callCount]) {
        mock->calcTime(x);
    } else {
        counter->calcTime(x);
    }
    callCount++;
}
