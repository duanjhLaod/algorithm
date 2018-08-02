#pragma once
#include "stdio.h"

#define LEFT(i)  i==0?1:(i<<1);
#define RIGHT(i) i==0?2:(i<<1)+1;
#define PATENT(i) i>>1;

void test_minEatingSpeed();
void test_findMaximumXOR();

//��С��
template<class T> class MinHeap
{
public:

	int current_index=-1; //��ǰ��СԪ����������������

	MinHeap();
	MinHeap(const size_t size);
	~MinHeap();


	T get_min() const; //��ȡ��СԪ��
	size_t get_heap_size() const; //��ȡheapsize
	int compare(const T& t1, const T& t2); //�Ƚ�

	void insert_e(const T& e); //����
	void delete_min(); //ɾ����СԪ��
	void min_heapfiy(const size_t index); //��С������
	void swap(size_t s1, size_t s2);
	
private:
	T *heap;
	size_t heap_size;	
};


struct SortNode
{

public:
	int num;
	SortNode* next;

	SortNode(int v, SortNode& n)
	{
		num = v;
		next = &n;
	}

	int &operator-(SortNode & node)
	{
		int v = this->num - node.num;
		return v;
	}
};