#pragma once
#include "fibonacci.hpp"

/**
 * 計算時間を測定するクラス.
 */
class Counter {
  public:
    /** コンストラクタ. */
    Counter();

    /**
     * フィボナッチ数を計算するオブジェクトを登録する.
     * @param[in] fib フィボナッチ数を計算するオブジェクト
     */
    void setFibonacci(Fibonacci *fib);

    /**
     * 計算時間を測定し、stdoutへ出力する.
     * @param[in] x 指定する値
     */
    void calcTime(int x);

    /**
     * 非同期で計算時間を測定し、stdoutへ出力する.
     * @param[in] x 指定する値
     */
    void calcTimeAsync(int x);

  private:
    /**
     * 測定対象のフィボナッチ数計算オブジェクト.
     */
    Fibonacci *t_fib;
};
