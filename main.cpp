#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

struct Data {
	long a;

#ifdef FIX_FALSE_SHARING
  long padding[7]; // seemingly useless variables, yet they solve the false sharing problem
#endif

	long b; // sits on the same L1 cache line as the "a" member
	
	Data() : a(0l), b(0l) {
		
	}
};

long nb_iter = 100000000l; // global and not const to prevent the compiler from optimizing out the loop in work()

void work(long &e) {
  while(e<nb_iter)
  {
    e++;
  }
}

int main() {
	const auto tic = high_resolution_clock::now();
    
	Data d;
	std::thread t1(work, ref(d.a));
	std::thread t2(work, ref(d.b));

	t1.join();
	t2.join();
	const auto toc = high_resolution_clock::now();
	const std::chrono::duration<double, std::milli> elapsed = toc - tic;
	
	cout << "a = " << d.a << endl;
	cout << "b = " << d.b << endl;
	cout << "Computation time: " << elapsed.count() << "ms" << endl;
	
	return 0;
}
