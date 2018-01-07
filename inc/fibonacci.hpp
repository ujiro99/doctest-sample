#pragma once
#include <future>
#include <iostream>

typedef struct _ExecutedData {
    const char *name;
    clock_t start;
    int result;
} ExecutedData;
typedef void (*Executed)(ExecutedData);

/**
 * フィボナッチ数を計算する基底クラス.
 */
class Fibonacci {
  public:
    /** デストラクタ. */
    virtual ~Fibonacci(){};

    const char *name    = "";      /**< 計算方法の名称  */
    Executed onExecuted = nullptr; /**< 計算完了時のコールバック */
    ExecutedData data   = {};      /**< 計算完了コールバックで渡されるデータ */

    /**
     * 指定した整数値までのフィボナッチ数を計算する.
     * @param[in] x 指定する値
     * @return フィボナッチ数
     */
    virtual int calc(int x) = 0;
};

/**
 * 再帰を使って計算するクラス.
 */
class RecursiveFibonacci : public Fibonacci {
  public:
    /** コンストラクタ. */
    RecursiveFibonacci();
    /** デストラクタ. */
    ~RecursiveFibonacci();

    int calc(int x);
};

/**
 * メモ化を使って計算するクラス.
 */
class MemorizeFibonacci : public Fibonacci {
  public:
    /** コンストラクタ. */
    MemorizeFibonacci();
    /** デストラクタ. */
    ~MemorizeFibonacci();

    int calc(int x);

  private:
    int memo[10000] = {0}; /**< メモ化した値を格納する変数. */
};

/**
 * 動的計画法を使って計算するクラス.
 */
class DPFibonacci : public Fibonacci {
  public:
    /** コンストラクタ. */
    DPFibonacci();
    /** デストラクタ. */
    ~DPFibonacci();

    int calc(int x);
};

/**
 * 非同期で動的計画法を使って計算するクラス.
 */
class AsyncDPFibonacci : public Fibonacci {
  public:
    /** コンストラクタ. */
    AsyncDPFibonacci();
    /** デストラクタ. */
    ~AsyncDPFibonacci();

    /**
     * 非同期で指定した整数値までのフィボナッチ数を計算する.
     * 計算結果は onExecuted で通知される.
     *
     * @param[in] x 指定する値
     * @return 常に0を返す
     */
    int calc(int x);

    /*
     * calc()の実行完了を待つ.
     */
    void wait();

  private:
    void execCalc(int x);
    class std::thread t;
};
