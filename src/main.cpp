#include "sort/sort.h"
#include "data_struct/data_struct.h"
#include "iostream"
#include "algorithm/Dijkstra.h"
#include <thread>
#include <mutex>
#include <condition_variable>


mutex mutex1;
condition_variable condition_var;
bool flag = true;

void th1_func()
{
	std::unique_lock<mutex> unlock(mutex1);
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		condition_var.wait(unlock, [] {return flag; });
		printf("1\n");
		flag = false;
		condition_var.notify_one();
	}

}

void th2_func()
{
	std::unique_lock<mutex> unlock(mutex1);
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		condition_var.wait(unlock, [] {return !flag; });
		printf("2\n");
		flag = true;
		condition_var.notify_one();
	}

}

void test_thread()
{
	std::thread th1(th1_func);
	std::thread th2(th2_func);

	th1.join();
	th2.join();
}


int main()
{
	int const **p1;
	int* const *p2;
	int i = 5;
	int j = 6;

	const int* ptr1 = &i;
	int* const ptr2 = &j;

	p1 = &ptr1;
	p2 = &ptr2;

	//test_lcs();

	//test_optimal_bst();

	clockwisePrint();

	test_thread();
	system("pause");

	return 0;
}