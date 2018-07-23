#include "data_struct.h"
#include "iostream"

void ListStack::push(int x)
{
	listNode* node = new listNode(x);

	node->next = this->top; //��node����һ��ָ��ǰջ������
	this->top = node; //��node��Ϊջ������
}

int ListStack::pop()
{
	if (this->top == nullptr)
	{
		std::cout << "empty stack" << std::endl;
		return -1;
	}

	listNode* node = this->top;
	this->top = this->top->next; //ջ��ָ����һ��
	int n = node->data;

	free(node); //�ǵ��ͷŵ�
	return n;
}

void ListQueue::enqueue(int x)
{
	listNode* node = new listNode(x);

	if (this->tail == nullptr) //β��Ϊ�� ����һ��
	{
		this->head = node;
		this->tail = node;
	}
	else
	{
		this->tail->next = node; //��Ϊ�ս���ǰβ������һ��ָ��node
		this->tail = node; //��node����Ϊ����β
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
	if (this->head == this->tail) //���˵��ֻ��1��Ԫ��
	{
		this->head = nullptr;
		this->tail = nullptr;
	}
	else
	{
		this->head = this->head->next; //ͷ������
	}
	int n = node->data;
	free(node);
	return n;
}

//�������
void SearchTree::inorder_tree_walk(TreeNode* node)
{
	if (node != nullptr)
	{
		inorder_tree_walk(node->left);
		printf("%d\n", node->data);
		inorder_tree_walk(node->right);
	}
}

//�������
void SearchTree::preorder_tree_walk(TreeNode* node)
{
	if (node != nullptr)
	{
		printf("%d\n", node->data);
		preorder_tree_walk(node->left);
		preorder_tree_walk(node->right);
	}
}

//�������
void SearchTree::postorder_tree_walk(TreeNode* node)
{
	if (node != nullptr)
	{
		postorder_tree_walk(node->left);
		postorder_tree_walk(node->right);
		printf("%d\n", node->data);
	}
}

//��������������(�ݹ�)
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

//��������������(����)
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

//������������С�ؼ���
TreeNode* SearchTree::tree_minnum(TreeNode* node)
{
	if (node == nullptr)
		return node;
	while (node->left != nullptr)
	{

		node = node->left; //�������ӽڵ�
	}

	return node;
}

//�������������ؼ���
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

//Ѱ�Һ��
TreeNode* SearchTree::tree_successor(TreeNode* node)
{
	if (node == nullptr)
		return nullptr;

	//�������������ֱ���ҵ�����������С�ؼ��ּ���
	if (node->right != nullptr)
		return tree_minnum(node->right);

	//û��������,������Դ,ֱ���ҵ��ڵ������Ϊ���ȸ��ڵ�����ӽڵ㣬������ȵĸ��ڵ�Ϊ���
	TreeNode* p = node->parent;
	while (p != nullptr)
	{
		if (p->left == node)
			return p;

		node = p;
		p = p->parent;
	}

	return nullptr; //û�к��(Ϊ���ҽڵ�)
}

//Ѱ��ǰ��
TreeNode* SearchTree::tree_predecessor(TreeNode* node)
{
	if (node == nullptr)
		return nullptr;

	
	//���������������Ѱ�������������ؼ���
	if (node->left != nullptr)
	{
		return tree_maxnum(node->left);
	}

	//û��������,���ϻ���,ֱ��Ϊ���ڵ��������Ϊֹ,��ø��ڵ�Ϊǰ��
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
*��������������
*node Ϊroot�ڵ�
*x ����ֵ
*/
void SearchTree::tree_insert(int x)
{
	TreeNode* in = new TreeNode();
	in->data = x;
	in->left = nullptr;
	in->right = nullptr;
	in->parent = nullptr;

	TreeNode* t = nullptr; //Ѱ�Ҳ���ڵ�ĸ��ڵ�
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
		//T.root = in ������Ѳ���ڵ���Ϊ���ڵ�
	}
	else if(t->data>x)
	{
		t->left = in;
	}
	else
	{
		t->right = in;
	}

	//����֮��δҶ�ӽڵ�,�������֮��ΪҶ�ӽڵ��������Σ�
}

//�ڵ��滻 x�ڵ��滻y�ڵ�
void SearchTree::tree_translate(TreeNode* x, TreeNode* y)
{
	if (y==nullptr)
		return;

	if (y->parent == nullptr) //û�и��ڵ㣬˵��Ϊ���ڵ�
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
*�ڵ�ɾ��
*Ҫɾ���Ľڵ�
*/
void SearchTree::tree_delete(TreeNode* node)
{
	//û�����ӽڵ�,��ֱ�������ӽڵ��滻����
	if (node->left == nullptr)
	{
		tree_translate(node->right, node);
	}
	else if(node->right==nullptr) //û�����ӽڵ�,ֱ�������ӽڵ��滻
	{
		tree_translate(node->left, node);
	}
	else //�����ӽڵ㶼��
	{
		TreeNode* y = tree_minnum(node->right); //Ѱ�ҽڵ�ĺ��(��Ϊnode�����ӽڵ�,��̾�Ϊ��������С�ؼ���)
		if (y->parent != node) //��̽ڵ㲻��node���ӽڵ�,���ں�̱ض�û������������Ѱ�Һ�̵Ĺ����֪��,�����y��y������������,���Ұ�node����������Ϊy��������
		{
			tree_translate(y->right, y);
			y->right = node->right;
			y->right->parent = y;
		}

		//�滻���y��node,���Ұ�node����������Ϊy��������(���yΪnode�����ӽڵ㲻�ô�������������������Ѿ������洦����)
		tree_translate(y, node); 
		y->left = node->left;
		y->left->parent = y;
	}
}


void RBTree::tree_left_rotate(RBTreeNode* node)
{
	//���ӽڵ㲻Ϊ��
	if (node->right == nullptr)
		return;

	RBTreeNode* y = node->right;
	node->right = y->left; //node�����ӽڵ��Ϊ���ӽڵ�����ӽڵ�
	if (y->left != nullptr)
	{
		y->left->parent = node; //��node�����ӽڵ�����ӽڵ�ĸ��ڵ��Ϊnode
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
	//���ӽڵ㲻Ϊ��
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
		RBTreeNode* y = nullptr; //Ѱ����ڵ�
		if (p->parent->left == p) //������
		{
			y = p->parent->right;
		}
		else
		{
			y = p->parent->left;
		}

		if (y->color == RED) //��ڵ�Ϊ��ɫ
		{
			p->color = BLACK;
			y->color = BLACK;
			p->parent->color = RED;
			node = p->parent;
		}
		else if (node == node->parent->right)//�ڵ�Ϊ���ӽڵ㣬����ת��Ϊ���ӽڵ�
		{
			node = node->parent;
			tree_left_rotate(node);
		}
		else
		{
			node->parent->color = BLACK; //���ڵ�����Ϊ��ɫ
			node->parent->parent->color = RED; //�ϲ�����Ϊ��ɫ
			tree_right_rotate(node->parent->parent); //����
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
	if (node->left == nullptr) //���ӽڵ�Ϊ��
	{
		x = node->right;
		tree_transplant(node->right, node);
	}
	else if(node->right==nullptr) //���ӽڵ�Ϊ��
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