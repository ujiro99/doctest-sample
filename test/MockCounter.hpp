#pragma once
#include "counter.hpp"
#include "fibonacci.hpp"

class ICounter {
  public:
    virtual void setFibonacci(Fibonacci *fib) = 0;
    virtual void calcTime(int x)              = 0;
};

class MockCounter {
  public:
    MockCounter();
    ~MockCounter();
    void setFibonacci(Fibonacci *fib);
    void calcTime(int x);

    // for mock
    static ICounter *mock;
    static bool mockEnable;

  private:
    // for original
    Counter *counter;
};
