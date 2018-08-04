#include "sort/sort.h"
#include "data_struct/data_struct.h"
#include "iostream"
#include "algorithm/Dijkstra.h"

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

	system("pause");
}