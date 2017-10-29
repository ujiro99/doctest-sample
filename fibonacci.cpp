#include <iostream>
#include <vector>

using namespace std;

class Fibonacci{
public:
	const char* name = "";
	virtual int calc(int x) = 0;
};

class RecursiveFibonacci:public Fibonacci{
public:
    RecursiveFibonacci()
    {
        name = "Recursive";
    }

    virtual int calc(int x){
        if(x == 0){
            return 0;
        }else if(x == 1){
            return 1;
        }else{
            return calc(x - 1) + calc(x - 2);
        }
    }
};

class MemorizeFibonacci:public Fibonacci{
	int memo[10000] = {0};
public:
    MemorizeFibonacci()
    {
        name = "Memorize";
    }

    virtual int calc(int x){
        if(x == 0){
            return 0;
        }else if(x == 1){
            return 1;
        }else if(memo[x] != 0){
            return memo[x];
        }
        memo[x] = calc(x-1) + calc(x-2);
    }
};

class DPFibonacci:public Fibonacci{
public:
    DPFibonacci()
    {
        name = "Dynamic ";
    }

    virtual int calc(int x){
        int dp[1000] = {0};
        dp[0] = 0;
        dp[1] = 1;
        for(int i = 2; i < x; i++){
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[x];
    }
};

class TimeFibonatti{
public:
	void setFibonacci(Fibonacci *fib){
		t_fib = fib;
	}

	void calcTime(int x){
		clock_t start = clock();
		t_fib->calc(x);
		cout << t_fib->name << "\t";
		cout << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
	}
private:
	Fibonacci *t_fib;
};

int main(int argc, char const *argv[]){
	Fibonacci *r_fib = new RecursiveFibonacci();
	Fibonacci *m_fib = new MemorizeFibonacci();
	Fibonacci *dp_fib = new DPFibonacci();

	TimeFibonatti *t_fib = new TimeFibonatti();

	vector<Fibonacci*> fib(3);
	fib[0] = r_fib;
    fib[1] = m_fib;
    fib[2] = dp_fib;

	for(int i = 0; i < fib.size(); i++){
		t_fib->setFibonacci(fib[i]);
		t_fib->calcTime(30);
	}
	return 0;
}
