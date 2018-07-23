#include "sort.h"
#include "iostream"
#include "list"
#include "vector"
#include <iterator>

using namespace std;

template <class T>
int getArrayLength(T& arr)
{
	return sizeof(arr) / sizeof(arr[0]);
}

template<class T>
void prinfArray(T& a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void prinfArray(list<int> a)
{
	for (list<int>::iterator it = a.begin(); it != a.end(); ++it)
	{
		printf("%d ", *it);
	}

	printf("\n");
}

//��������(����)
void insert_sort(int arr[], int size)
{
	printf("size : %d \n", size);
	if (size > 1)
	{
		for (int i = 1; i < size; ++i)
		{
			int key = arr[i];
			int j = i - 1;

			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				j = j - 1;
			}
			
			arr[j + 1] = key;

			printf("sort turn %d:", i);
			for (int i = 0; i < size; ++i)
			{
				printf("%d ", arr[i]);
			}
			printf("\n");
		}
	}
}

//ѡ������
void select_sort(int arr[], int size)
{
	for (int i = 0; i < size-1; ++i)
	{
		for (int j = i+1; j < size; ++j)
		{
			if (arr[i] > arr[j])
			{
				int tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}

		printf("sort turn %d:", i);
		for (int i = 0; i < size; ++i)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
}


//�ϲ�Ԫ��
void mergeUnits(int arr[], int begin, int mid, int end, int temp[])
{
	int i = begin;
	int j = mid + 1;
	int k = begin;
	while (i<=mid && j<=end)
	{
		if (arr[i] > arr[j])
		{
			temp[k++] = arr[j++];
		}
		else
		{
			temp[k++] = arr[i++];
		}
	}

	while (i <= mid)
	{
		temp[k++] = arr[i++];
	}

	while (j <= end)
	{
		temp[k++] = arr[j++];
	}
}

//�鲢����
void merge_sort(int arr[], int begin, int end, int temp[])
{
	if (begin < end)
	{
		int mid = (end + begin) >> 1;
		merge_sort(arr, begin, mid, temp);
		merge_sort(arr, mid + 1, end, temp);
		mergeUnits(arr, begin, mid, end, temp);

		for (int i = begin; i <= end; ++i)
		{
			arr[i] = temp[i];
		}


		printf("sort turn : ");
		for (int i = begin; i <= end; ++i)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
}


/*
*���ֲ���˼�룺1�������С��������2�����ҵ�keyÿ�κ��м����Ƚϣ����keyС��mid
����mid�������鲿�֣����key����mid�������mid�Ҳ�����鲿�֣������ȣ���ֱ�ӷ���mid��
���룺��������-array,�����С-Size,����ֵ-key
���أ����������е���Ӧλ�ã����򷵻�-1
*/
int binary_search(int arr[], int begin, int end, int key)
{
	if (arr == NULL || begin > end)
		return -1;
	int mid = (end+begin) >> 1;

	if (arr[mid] == key)
		return mid;

	if (arr[mid] > key)
	{
		return binary_search(arr, begin, mid-1, key);
	}
	else
	{
		return binary_search(arr, mid+1, end, key);
	}
}

/*
* n�����������򼯺�S��һ������x������S���Ƿ�����������ĺ͸պ�Ϊx
*/
bool search_plusx(int arr[], int begin, int end, int x)
{
	if (arr==NULL || arr[begin] > x/2) //�������ĺͣ���Ϊ���ź���ģ������һ��Ԫ�ش���x��һ�룬��������,û�з���������
		return false;

	int y = x - arr[begin];

	if (binary_search(arr, begin, end, y) > -1)
	{
		return true;
	}

	return search_plusx(arr, begin + 1, end, x);
}

/*
*ð������
*/
void bubble_sort(int arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = size - 1; j >= i + 1; --j)
		{
			if (arr[j-1] > arr[j])
			{
				int temp = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

/*
*���ɷ��������ʽ �Ѷ���ʽ�任�� y = a0 + x(a1 + x(a2 + ... + x(an + xan+1))
*/
int horner(int arr[], int index, int size, int x)
{
	if (index < 0)
		return 0;
	if (index > size -1)
	{
		return arr[index];
	}

	return horner(arr, index + 1, size, x) * x + arr[index];

}

/*
*���ҹ��е�����������
*/
int* find_cross_max_subarray(int arr[], int low, int mid, int high)
{
	if (low >= high)
	{
		int result[] = { low, high, arr[low] };
		return result;
	}

	int lsum = 0;
	int lindex = -1;
	int maxlsum = 0;
	//���
	for (int i = mid; i >= low; --i)
	{
		lsum += arr[i];
		if (lsum > maxlsum)
		{
			maxlsum = lsum;
			lindex = i;
		}
	}
	//�ұ�
	int rsum = 0;
	int rindex = -1;
	int maxrsum = 0;
	for (int j = mid + 1; j <= high; ++j)
	{
		rsum += arr[j];
		if (rsum > maxrsum)
		{
			maxrsum = rsum;
			rindex = j;
		}
	}

	int result[] = { lindex, rindex, (maxlsum + maxrsum) };
	return result;
}

/*
*�������������
* arr ԭ����
* result [low, high, total](��ʼλ����ֹλ, ����) �������
*low high ��λ�͸�λ
*/
int* find_max_subarray(int arr[], int low, int high)
{
	//�ҵ���
	if (low >= high)
	{
		int result[] = { low, high, arr[low] };
		return result;
	}

	int mid = (low + high) >> 1;

	int* _left = find_max_subarray(arr, low, mid); //�����������
	int* _right = find_max_subarray(arr, mid + 1, high); //�����������
	int* _cross = find_cross_max_subarray(arr, low, mid, high); //���е�����������

	if (_left[2] >= _right[2] && _left[2] >= _cross[2])
	{
		return _left;
	}
	else if (_right[2] >= _left[2] && _right[2] >= _cross[2])
	{
		return _right;
	}
	else
		return _cross;
}

void test_find_max_subarray()
{
	int arr[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, -7 };
	int* result = find_max_subarray(arr, 0, getArrayLength(arr) - 1);

	std::cout << "low:" << result[0] << " " << "high:" << result[1] << " " << "total:" << result[2] << std::endl;
}

/*
*����˷�
*/
void square_matrix_multiply(int* a[], int* b[], int* c[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			c[i][j] = 0;
			for (int k = 0; k < n; ++k)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void check_monge_matrix(int** a, int row, int col)
{
	for (int i = 0; i < row-1; ++i)
	{
		for (int j = 0; j < col-1; ++j)
		{
			if (a[i][j] + a[i + 1][j + 1] > a[i + 1][j] + a[i][j + 1])
			{
				printf("error %d:%d", i, j);
			}
		}
	}
}

//��������㷨
void randomize_in_place(int a[], int len)
{
	for (int i = 0; i < len-1; ++i)
	{
		int ran = rand() % (len-i)+i;
		int temp = a[ran];
		a[ran] = a[i];
		a[i] = temp;
	}
}

void swap(int *a, int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}


//���� ���ڵ�����ӽڵ�
void max_heapify(int a[], int index, int len)
{
	int l = LEFT(index);
	int r = RIGHT(index);
	int large = index;
	if (l < len && a[l] > a[index])
	{
		large = l;
	}
	if (r < len && a[r] > a[large])
	{
		large = r;
	}

	if (large != index)
	{
		swap(a, index, large);
		max_heapify(a, large, len);
	}
}

//��������
void build_maxheap(int a[], int len)
{
	int n = len >> 1;
	for (int i = n - 1; i >= 0; --i)
	{
		max_heapify(a, i, len);
	}
}

//������
void heap_sort(int a[], int len)
{
	build_maxheap(a, len);
	int size = len;
	prinfArray(a, len);
	while (size > 1)
	{
		swap(a, 0, size - 1);
		
		--size;
		max_heapify(a, 0, size);
		prinfArray(a, len);
	}
}

template<class T>
MinHeap<T>::MinHeap() :heap(NULL), heap_size(0) {}

template<class T>
MinHeap<T>::MinHeap(const size_t size)
{
	if (heap != NULL)
	{
		delete[] heap;
	}

	heap = new T[size];
	heap_size = 0;
}

template<class T>
MinHeap<T>::~MinHeap()
{
	if (heap != NULL)
	{
		delete[] heap;
	}

	heap_size = 0;
}

template<class T>
size_t MinHeap<T>::get_heap_size() const
{
	return heap_size;
}

template<class T>
T MinHeap<T>::get_min() const
{
	if(heap_size>0)
		return heap[0];

	return T();
}

template<class T>
int MinHeap<T>::compare(const T& t1, const T& t2)
{
	return *t1 - *t2;
}

template<class T>
void MinHeap<T>::swap(size_t s1, size_t s2)
{
	if (s1 < heap_size && s2 < heap_size)
	{
		T temp = heap[s1];
		heap[s1] = heap[s2];
		heap[s2] = temp;
	}
	else
	{
		std::cout << "[ERROR] error swap," << s1 << ":" << s2 << ",heap_size:" << heap_size << std::endl;
	}
}

template<class T>
void MinHeap<T>::insert_e(const T& e)
{
	size_t i, parent;
	T temp;
	++heap_size;
	heap[heap_size - 1] = e;

	i = heap_size - 1;
	parent = PATENT(i);
	while (i>0 && compare(heap[parent], heap[i])>0)
	{
		swap(parent, i);

		i = parent;
		parent = PATENT(i);
	}
}

template<class T>
void MinHeap<T>::delete_min()
{
	if (heap_size > 0)
	{
		swap(0, heap_size - 1); //����һλ�����һλ����
		--heap_size;
		min_heapfiy(0);
	}
}

template<class T>
void MinHeap<T>::min_heapfiy(const size_t index)
{
	size_t l, r, min;
	l = LEFT(index);
	r = RIGHT(index);
	min = index;

	if (l < heap_size && compare(heap[l], heap[min]) < 0)
	{
		min = l;
	}

	if (r < heap_size && compare(heap[r], heap[min]) < 0)
	{
		min = r;
	}

	if (min != index)
	{
		swap(index, min);

		min_heapfiy(min);
	}
}

//��С��k·�鲢����
list<int> minheap_k_merge_sort(int k, list<int> lists[])
{
	MinHeap<list<int>::iterator> minheap(k); //����һ����K��vertor����������С��

	//��ʼ����
	for (int i=0; i<k; ++i)
	{
		minheap.insert_e(lists[i].begin());
		prinfArray(lists[i]);
	}

	list<int>::iterator iter;
	list<int> result;
	while (minheap.get_heap_size()>0)
	{
		//ȡ����С����СԪ�أ�������result���ϣ��ٴ���С����ɾ��
		iter = minheap.get_min();
		result.push_back(*iter);
		minheap.delete_min();		
		++iter;

		//�ж�һ���ǲ�����������һ��Ԫ�أ���һ����Ҫ�Ż�
		//������Կ����Ż�(���õ�����, ֱ��ʹ������ṹ, p->nextΪnull������)
		bool isEnd=false;
		for (int i = 0; i < k; ++i)
		{
			if (iter == lists[i].end()) //��仰������ (STL vector������ָ��Ĵ�������������ʱ�ѳ�ʼ����Ŀǰ�Ĵ����ʼ���ᵼ�������Ϣ�ı䣬���Իᱨ��)
			{
				isEnd = true;
				break;
			}

		}
		if (!isEnd)
		{
			minheap.insert_e(iter);
		}		
	}
	return result;
}

//���ŵĻ����㷨
int quick_sort_partion(int* a, int start, int end)
{
	int x = a[end];
	int i = start - 1;
	for (int j = start; j < end; ++j)
	{
		if (a[j] < x)
		{
			++i;
			swap(a, i, j);
		}
	}

	if ((i + 1) != end)
	{
		swap(a, i + 1, end);
	}

	return i + 1;
}

//���ŵ���������㷨
int quick_sort_random_partion(int* a, int start, int end)
{
	int r = (rand() % (end - start + 1)) + start;
	swap(a, end, r);

	printf("select index:%d\n", r);

	return quick_sort_partion(a, start, end);
}

//��������
void quick_sort(int* a, int len, int start, int end)
{
	if (start < end)
	{
		int p = quick_sort_partion(a, start, end);
		prinfArray(a, len);

		quick_sort(a, len, start, p-1);
		quick_sort(a, len, p+1, end);
	}
}

//�����������
void random_quick_sort(int* a, int len, int start, int end)
{
	if (start < end)
	{
		int p = quick_sort_random_partion(a, start, end);
		prinfArray(a, len);

		random_quick_sort(a, len, start, p - 1);
		random_quick_sort(a, len, p + 1, end);
	}
}

/**
*��������
*a �����������
*b �������
*k ���������Ԫ�ؾ�С��k
*/
void counting_sort(int* a, int* b, int len, int k)
{
	vector<int> c(k);
	for (int i = 0; i < k; ++i)
	{
		c[i] = 0;
	}

	for (int i = 0; i < len; ++i)
	{
		c[a[i]] += 1;
	}

	for (int i = 1; i < k; ++i)
	{
		c[i] += c[i - 1];
	}

	for (int i = len - 1; i >= 0; --i)
	{
		b[c[a[i]]] = a[i];
		c[a[i]] -= 1;
	}
}


//�ҳ�����A�е�iС��Ԫ��
int randomized_select(int* A, int begin, int end, int i)
{
	if (begin == end)
		return A[begin];

	int q = quick_sort_random_partion(A, begin, end);
	int k = q - begin + 1;
	if (i == k)
	{
		return A[q];
	}
	else if(k>i)
	{
		return randomized_select(A, begin, q - 1, i);
	}
	else
	{
		return randomized_select(A, q + 1, end, i - k);
	}

}

//monge�������
void test_check_monge_matrix()
{
	int a[5][4] = { { 37,23,22,32 },{ 21,6,7,10 },{ 53,34,30,31 },{ 32,13,9,6 },{ 43,21,15,8 } };
	int** b = new int*[5];
	for (int i = 0; i < 5; ++i)
	{
		b[i] = new int[4];
	}
	for (int j = 0; j < 5; ++j)
	{
		for (int k = 0; k < 5; ++k)
		{
			b[j][k] = a[j][k];
		}
	}
	check_monge_matrix(b, 5, 4);
}

//���������
void test_heapsort()
{
	int arr[] = { 5,13,2,23,7,16,20,8,4 };
	heap_sort(arr, 9);
}

void test_k_merge_sort()
{
	list<int> v1;
	v1.push_back(25);
	v1.push_back(31);
	v1.push_back(89);
	list<int> v2 = { 26,41,58,90 };
	list<int> v3 = { 41,58, 59, 65, 72 };
	list<int> lists[3] = {v1, v2, v3};

	list<int> rs = minheap_k_merge_sort(3, lists);
	printf("result: ");
	prinfArray(rs);
}

void test_quick_sort()
{
	
	int arr[] = {13,19,9,5,12,8,7,4,21,2,6,11};
	prinfArray(arr, 12);

	printf("normal quick sort:\n");
	quick_sort(arr, 12, 0, 11);

	int arr2[] = { 13,19,9,5,12,8,7,4,21,2,6,11 };
	printf("\nrandom quick sort:\n");
	random_quick_sort(arr2, 12, 0, 11);
}
