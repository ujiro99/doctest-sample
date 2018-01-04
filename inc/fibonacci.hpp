#pragma once

/**
 * フィボナッチ数を計算する基底クラス.
 */
class Fibonacci {
  public:
    /** デストラクタ. */
    virtual ~Fibonacci(){};

    const char *name = ""; /**< 計算方法の名称  */

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
