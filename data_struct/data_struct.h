#pragma once
#include "stdio.h"

//�������
struct listNode
{
public:
	int data; //ֵ
	listNode* next;

	listNode(int x):data(x),next(nullptr){}
};

//������ջ(LIFO)
class ListStack
{
public:
	listNode * top; //ջ��

	ListStack():top(nullptr){}

	void push(int x); //��ջ
	int pop(); //��ջ
};


//������ʵ�ֶ���(FIFO)
class ListQueue
{
public:
	listNode *head; //����ͷ
	listNode *tail; //����β

	ListQueue() :head(nullptr), tail(nullptr) {}

	void enqueue(int x); //�����
	int dequeue(); //������
};

//�������ڵ�
//�������������� �����ڵ�>���ӽڵ㣬 <= ���ӽڵ㣩
struct TreeNode
{
	int data;
	TreeNode* parent; //���ڵ�
	TreeNode* left; //���ӽڵ�
	TreeNode* right; //���ӽڵ�
};

class SearchTree
{
public:
	TreeNode* root;

	void inorder_tree_walk(TreeNode* node); //����
	void preorder_tree_walk(TreeNode* node); //����
	void postorder_tree_walk(TreeNode* node);//����
	TreeNode* tree_search(TreeNode* node, int data);
	TreeNode* iterative_tree_search(TreeNode* node, int data);
	TreeNode* tree_minnum(TreeNode* node); //��С�ؼ���
	TreeNode* tree_maxnum(TreeNode* node); //���ؼ���
	TreeNode* tree_successor(TreeNode* node); //����
	TreeNode* tree_predecessor(TreeNode* node); //ǰ��
	void tree_insert(int x); //����
	void tree_translate(TreeNode* x, TreeNode* y); //�滻�������滻�ӽڵ㣩
	void tree_delete(TreeNode* node); //ɾ��
};

enum RBTreeColor
{
	RED,
	BLACK
};

struct RBTreeNode
{
	int data;
	RBTreeColor color;
	RBTreeNode* parent; //���ڵ�
	RBTreeNode* left; //���ӽڵ�
	RBTreeNode* right; //���ӽڵ�
};

//�����
class RBTree
{
public:
	RBTreeNode * root;

	//�ڱ�nil

	void tree_left_rotate(RBTreeNode* node); //����
	void tree_right_rotate(RBTreeNode* node); //����
	void tree_insert_fixup(RBTreeNode* node); //��������
	void tree_insert(RBTreeNode* node); //����
	void tree_transplant(RBTreeNode* u, RBTreeNode* v); //��u�滻v
	void tree_delete(RBTreeNode* node); //ɾ���ڵ�
};