#pragma once
#include "counter.hpp"
#include "fibonacci.hpp"

class ICounter {
  public:
    virtual ~ICounter()                       = 0;
    virtual void setFibonacci(Fibonacci *fib) = 0;
    virtual void calcTime(int x)              = 0;
    virtual void calcTimeAsync(int x)         = 0;
};

class MockCounter {
  public:
    MockCounter();
    ~MockCounter();
    void setFibonacci(Fibonacci *fib);
    void calcTime(int x);
    void calcTimeAsync(int x);

    // for mock
    static ICounter *mock;
    static bool mockEnable;
    static bool *useMock;

  private:
    // for original
    Counter *counter;
    int callCount;
};
