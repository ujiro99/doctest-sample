#include "fibonacci.hpp"

/**
 * 計算時間を測定するクラス.
 */
class Counter {
  public:
    /**
     * フィボナッチ数を計算するオブジェクトを登録する.
     * @param fib[in] フィボナッチ数を計算するオブジェクト
     */
    void setFibonacci(Fibonacci *fib);

    /**
     * 計算時間を測定し、stdoutへ出力する.
     * @param x[in] 指定する値
     */
    void calcTime(int x);

  private:
    /**
     * 測定対象のフィボナッチ数計算オブジェクト.
     */
    Fibonacci *t_fib;
};
