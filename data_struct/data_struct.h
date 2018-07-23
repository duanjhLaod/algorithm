#pragma once
#include "stdio.h"

//链表对象
struct listNode
{
public:
	int data; //值
	listNode* next;

	listNode(int x):data(x),next(nullptr){}
};

//单链表栈(LIFO)
class ListStack
{
public:
	listNode * top; //栈顶

	ListStack():top(nullptr){}

	void push(int x); //入栈
	int pop(); //出栈
};


//单链表实现队列(FIFO)
class ListQueue
{
public:
	listNode *head; //队列头
	listNode *tail; //队列尾

	ListQueue() :head(nullptr), tail(nullptr) {}

	void enqueue(int x); //入队列
	int dequeue(); //出队列
};

//二叉树节点
//二叉搜索树性质 （父节点>左子节点， <= 右子节点）
struct TreeNode
{
	int data;
	TreeNode* parent; //父节点
	TreeNode* left; //左子节点
	TreeNode* right; //右子节点
};

class SearchTree
{
public:
	TreeNode* root;

	void inorder_tree_walk(TreeNode* node); //中序
	void preorder_tree_walk(TreeNode* node); //先序
	void postorder_tree_walk(TreeNode* node);//后序
	TreeNode* tree_search(TreeNode* node, int data);
	TreeNode* iterative_tree_search(TreeNode* node, int data);
	TreeNode* tree_minnum(TreeNode* node); //最小关键字
	TreeNode* tree_maxnum(TreeNode* node); //最大关键字
	TreeNode* tree_successor(TreeNode* node); //后驱
	TreeNode* tree_predecessor(TreeNode* node); //前驱
	void tree_insert(int x); //插入
	void tree_translate(TreeNode* x, TreeNode* y); //替换（不会替换子节点）
	void tree_delete(TreeNode* node); //删除
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
	RBTreeNode* parent; //父节点
	RBTreeNode* left; //左子节点
	RBTreeNode* right; //右子节点
};

//红黑树
class RBTree
{
public:
	RBTreeNode * root;

	//哨兵nil

	void tree_left_rotate(RBTreeNode* node); //左旋
	void tree_right_rotate(RBTreeNode* node); //右旋
	void tree_insert_fixup(RBTreeNode* node); //插入修正
	void tree_insert(RBTreeNode* node); //插入
	void tree_transplant(RBTreeNode* u, RBTreeNode* v); //将u替换v
	void tree_delete(RBTreeNode* node); //删除节点
};