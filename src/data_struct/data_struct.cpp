#include "data_struct.h"
#include "iostream"

void ListStack::push(int x)
{
	listNode* node = new listNode(x);

	node->next = this->top; //将node的下一个指向当前栈顶对象
	this->top = node; //将node置为栈顶对象
}

int ListStack::pop()
{
	if (this->top == nullptr)
	{
		std::cout << "empty stack" << std::endl;
		return -1;
	}

	listNode* node = this->top;
	this->top = this->top->next; //栈顶指向下一个
	int n = node->data;

	free(node); //记得释放掉
	return n;
}

void ListQueue::enqueue(int x)
{
	listNode* node = new listNode(x);

	if (this->tail == nullptr) //尾部为空 设置一下
	{
		this->head = node;
		this->tail = node;
	}
	else
	{
		this->tail->next = node; //不为空将当前尾部的下一个指向node
		this->tail = node; //将node设置为队伍尾
	}
}

int ListQueue::dequeue()
{
	if (this->head == nullptr)
	{
		std::cout << "empty queue" << std::endl;
		return -1;
	}
	listNode* node = this->head;
	if (this->head == this->tail) //相等说明只有1个元素
	{
		this->head = nullptr;
		this->tail = nullptr;
	}
	else
	{
		this->head = this->head->next; //头部后移
	}
	int n = node->data;
	free(node);
	return n;
}

//中序遍历
void SearchTree::inorder_tree_walk(TreeNode* node)
{
	if (node != nullptr)
	{
		inorder_tree_walk(node->left);
		printf("%d\n", node->data);
		inorder_tree_walk(node->right);
	}
}

//先序遍历
void SearchTree::preorder_tree_walk(TreeNode* node)
{
	if (node != nullptr)
	{
		printf("%d\n", node->data);
		preorder_tree_walk(node->left);
		preorder_tree_walk(node->right);
	}
}

//后序遍历
void SearchTree::postorder_tree_walk(TreeNode* node)
{
	if (node != nullptr)
	{
		postorder_tree_walk(node->left);
		postorder_tree_walk(node->right);
		printf("%d\n", node->data);
	}
}

//二叉搜索树搜索(递归)
TreeNode* SearchTree::tree_search(TreeNode* node, int data)
{
	if (node == nullptr || node->data == data)
		return node;

	if (node->data > data)
	{
		tree_search(node->left, data);
	}
	else
	{
		tree_search(node->right, data);
	}
}

//二叉搜索树搜索(迭代)
TreeNode* SearchTree::iterative_tree_search(TreeNode* node, int data)
{
	while (node!=nullptr)
	{
		if (node->data == data)
			return node;

		if (node->data > data)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	return node;
}

//二叉搜索树最小关键字
TreeNode* SearchTree::tree_minnum(TreeNode* node)
{
	if (node == nullptr)
		return node;
	while (node->left != nullptr)
	{

		node = node->left; //找最左子节点
	}

	return node;
}

//二叉搜索树最大关键字
TreeNode* SearchTree::tree_maxnum(TreeNode* node)
{
	if (node==nullptr)
	{
		return node;
	}
	while (node->right!=nullptr)
	{
		node = node->right;
	}

	return node;
}

//寻找后继
TreeNode* SearchTree::tree_successor(TreeNode* node)
{
	if (node == nullptr)
		return nullptr;

	//如果有右子树，直接找到右子树的最小关键字即可
	if (node->right != nullptr)
		return tree_minnum(node->right);

	//没有右子树,向上溯源,直到找到节点的祖先为祖先父节点的左子节点，则该祖先的父节点为后继
	TreeNode* p = node->parent;
	while (p != nullptr)
	{
		if (p->left == node)
			return p;

		node = p;
		p = p->parent;
	}

	return nullptr; //没有后继(为最右节点)
}

//寻找前驱
TreeNode* SearchTree::tree_predecessor(TreeNode* node)
{
	if (node == nullptr)
		return nullptr;

	
	//如果有左子树，则寻找左子树的最大关键字
	if (node->left != nullptr)
	{
		return tree_maxnum(node->left);
	}

	//没有左子树,往上回溯,直到为父节点的右子树为止,则该父节点为前驱
	TreeNode* p = node->parent;
	while (p != nullptr)
	{
		if (p->right == node)
			return p;

		node = p;
		p = p->parent;
	}
	return nullptr;
}

/*
*二叉搜索树插入
*node 为root节点
*x 插入值
*/
void SearchTree::tree_insert(int x)
{
	TreeNode* in = new TreeNode();
	in->data = x;
	in->left = nullptr;
	in->right = nullptr;
	in->parent = nullptr;

	TreeNode* t = nullptr; //寻找插入节点的父节点
	TreeNode* node = this->root;
	while (node!=nullptr)
	{
		t = node;
		if (t->data > x)
		{
			t = node->left;
		}
		else
		{
			t = node->right;
		}
	}

	in->parent = t; 
	if (t == nullptr)
	{
		//T.root = in 空树则把插入节点做为根节点
	}
	else if(t->data>x)
	{
		t->left = in;
	}
	else
	{
		t->right = in;
	}

	//插入之后未叶子节点,如果插入之后不为叶子节点情况会如何？
}

//节点替换 x节点替换y节点
void SearchTree::tree_translate(TreeNode* x, TreeNode* y)
{
	if (y==nullptr)
		return;

	if (y->parent == nullptr) //没有父节点，说明为根节点
		this->root = x;
	else if(y->parent->left==y)
	{
		y->parent->left = x;
	}
	else
	{
		y->parent->right = x;
	}

	if (x != nullptr)
	{
		x->parent = y->parent;
	}
}

/**
*节点删除
*要删除的节点
*/
void SearchTree::tree_delete(TreeNode* node)
{
	//没有左子节点,则直接用右子节点替换即可
	if (node->left == nullptr)
	{
		tree_translate(node->right, node);
	}
	else if(node->right==nullptr) //没有右子节点,直接用左子节点替换
	{
		tree_translate(node->left, node);
	}
	else //左右子节点都有
	{
		TreeNode* y = tree_minnum(node->right); //寻找节点的后继(因为node有右子节点,后继就为右子树最小关键字)
		if (y->parent != node) //后继节点不是node的子节点,由于后继必定没有左子树（从寻找后继的规则可知）,将后继y于y的右子树互换,并且把node的右子树变为y的右子树
		{
			tree_translate(y->right, y);
			y->right = node->right;
			y->right->parent = y;
		}

		//替换后继y和node,并且把node的左子树变为y的左子树(如果y为node的右子节点不用处理，其他情况下右子树已经在上面处理了)
		tree_translate(y, node); 
		y->left = node->left;
		y->left->parent = y;
	}
}


void RBTree::tree_left_rotate(RBTreeNode* node)
{
	//右子节点不为空
	if (node->right == nullptr)
		return;

	RBTreeNode* y = node->right;
	node->right = y->left; //node的右子节点变为右子节点的左子节点
	if (y->left != nullptr)
	{
		y->left->parent = node; //将node的右子节点的左子节点的父节点变为node
	}

	y->parent = node->parent; //
	if (node->parent == nullptr)
	{
		this->root = y;
	}
	else if(node = node->parent->left)
	{
		node->parent->left = y;
	}
	else
	{
		node->parent->right = y;
	}

	y->left = node;
	node->parent = y;
}

void RBTree::tree_right_rotate(RBTreeNode* node)
{
	//左子节点不为空
	if (node->left == nullptr)
		return;

	RBTreeNode* y = node->left;
	node->left = y->right;
	if (y->right != nullptr)
	{
		y->right->parent = node;
	}

	y->parent = node->parent;
	if (node->parent == nullptr)
	{
		this->root = y;
	}
	else if(node->parent->left==node)
	{
		node->parent->left = y;
	}
	else
	{
		node->parent->right = y;
	}

	y->right = node;
	node->parent = y;
}

void RBTree::tree_insert(RBTreeNode* node)
{
	RBTreeNode* y = nullptr;
	RBTreeNode* x = this->root;
	while (x!=nullptr)
	{
		y = x;
		if (node->data < x->data)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	node->parent = y;
	if (y == nullptr)
	{
		this->root = node;
	}
	else if(node->data<y->data)
	{
		y->left = node;
	}
	else
	{
		y->right = node;
	}

	node->left = nullptr;
	node->right = nullptr;
	node->color = RED;
	this->tree_insert_fixup(node);
}

void RBTree::tree_insert_fixup(RBTreeNode* node)
{
	while (node->parent!=nullptr && node->parent->color==RED)
	{
		RBTreeNode* p = node->parent;
		RBTreeNode* y = nullptr; //寻找叔节点
		if (p->parent->left == p) //左子树
		{
			y = p->parent->right;
		}
		else
		{
			y = p->parent->left;
		}

		if (y->color == RED) //叔节点为红色
		{
			p->color = BLACK;
			y->color = BLACK;
			p->parent->color = RED;
			node = p->parent;
		}
		else if (node == node->parent->right)//节点为右子节点，左旋转变为左子节点
		{
			node = node->parent;
			tree_left_rotate(node);
		}
		else
		{
			node->parent->color = BLACK; //父节点设置为黑色
			node->parent->parent->color = RED; //上层设置为红色
			tree_right_rotate(node->parent->parent); //右旋
		}
	}

	this->root->color == BLACK;
}

void RBTree::tree_transplant(RBTreeNode* u, RBTreeNode* v)
{
	if (v->parent == nullptr)
		this->root = u;
	else if(v->parent->left==v)
	{
		v->parent->left = u;
	}
	else
	{
		v->parent->right = u;
	}
	u->parent = v->parent;
}

void RBTree::tree_delete(RBTreeNode* node)
{
	RBTreeNode* y = node;
	RBTreeColor originalColor = y->color;
	RBTreeNode* x = nullptr;
	if (node->left == nullptr) //左子节点为空
	{
		x = node->right;
		tree_transplant(node->right, node);
	}
	else if(node->right==nullptr) //右子节点为空
	{
		x = node->left;
		tree_transplant(node->left, node);
	}
	else
	{
		y = (RBTreeNode*)this->tree_minnum(node->right);
		originalColor = y->color;
		x = y->right;
		if (y->parent == node)
		{
			x->parent = y;
		}
		else
		{
			tree_transplant(y->right, y);
			y->right = node->right;
			y->right->parent = y;
		}

		tree_transplant(y, node);
		y->left = node->left;
		y->left->parent = y;
		y->color = node->color;
	}

	if (originalColor == BLACK)
	{
		tree_delete_fixup(x);
	}
}

void RBTree::tree_delete_fixup(RBTreeNode* node)
{
	while (node!=this->root && node->color==BLACK)
	{
		if (node == node->parent->left)
		{
			RBTreeNode* y = node->parent->right;
			if (y->color == RED)
			{
				y->color = BLACK;
				y->parent->color = RED;
				this->tree_left_rotate(node->parent);
				y = node->parent->right;
			}

			if (y->left->color == BLACK && y->right->color == BLACK)
			{
				y->color = RED;
				node = node->parent;
			}
			else if(y->right->color==BLACK)
			{
				y->left->color = BLACK;
				y->color = RED;
				this->tree_right_rotate(y);
				y = node->parent->right;
			}
			else
			{
				y->color = node->parent->color;
				node->parent->color = BLACK;
				y->right->color = BLACK;
				this->tree_left_rotate(node->parent);
				node = this->root;
			}
		}
	}
}