#include "data_struct.h"
#include <iostream>
#include <vector>

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

	this->root->color = BLACK;
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


//���������
int lcs_length(char* A, char* B, int lenA, int lenB)
{
	int c[8][7] = {};
	for (int i = 0; i <= lenA; ++i)
	{
		c[i][0] = 0;
	}

	for (int j = 0; j <= lenB; ++j)
	{
		c[0][j] = 0;
	}

	for (int i = 1; i <= lenA; ++i)
	{
		for (int j = 1; j <= lenB; ++j)
		{
			if (A[i-1] == B[j-1])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if(c[i-1][j]>=c[i][j-1])
			{
				c[i][j] = c[i - 1][j];
			}
			else
			{
				c[i][j] = c[i][j - 1];
			}
		}
	}

	int k = lenA, m = lenB;
	while (k>0 && m>0)
	{
		if (c[k][m] == c[k-1][m])
		{
			--k;
		}
		else if(c[k][m]==c[k][m-1])
		{
			--m;
		}
		else
		{
			--m;
			--k;
			std::cout << A[k];
		}
	}


	std::cout << "lcs:" << c[lenA][lenB]<<std::endl;
	return c[lenA-1][lenB-1];
}

void test_lcs()
{
	char A[] = { 'A','B','C', 'B', 'D', 'A','B' };
	char B[] = { 'B','D','C', 'A', 'B', 'A' };

	lcs_length(A, B, 7, 6);
}

//�����������ӡ���Ŷ������ĸ��ڵ�����
void optimal_bst_print_root(std::vector<std::vector<int>> root,int start, int end)
{
	if (start > end)
		return;

	if (start == end) //û��������
	{
		std::cout << " " << start;
		return;
	}
	int index = root[start][end];
	std::cout << " " << index;
	optimal_bst_print_root(root, start, index - 1);
	optimal_bst_print_root(root, index + 1, end);
}

/**
*���Ŷ���������
*����ֵΪ���ڵ��б�
**/
std::vector<std::vector<int>> optimal_bst(int* p, int* q, int n)
{
	std::vector<std::vector<int>> e; //��������
	std::vector<std::vector<int>> w; //�����ܸ���
	std::vector<std::vector<int>> root; //����root�ڵ�

	for (int i = 0; i < n+1; ++i)
	{
		e.push_back(std::vector<int>(n));
		w.push_back(std::vector<int>(n));
		root.push_back(std::vector<int>(n));
		for (int j = 0; j < n; ++j)
		{
			e[i].push_back(0);
			w[i].push_back(0);
			root[i].push_back(0);
		}
	}

	//��ʼ��[i,i-1]��ʽ,ֻ��һ��d[i-1]
	for (int i = 1; i <= n; ++i)
	{
		e[i][i-1] = q[i-1];
		w[i][i-1] = q[i-1];
	}

	//i��1��n+1,j��0��n
	for (int k = 1; k <= n; ++k)
	{
		for (int i = 1; i <= n - k + 1; ++i)
		{
			int j = i + k - 1;
			e[i][j] = -1;
			w[i][j] = w[i][j - 1] + p[j] + q[j]; //��һ��Ҳ����Ҫ

			for (int r = i; r < j; ++r) //Ѱ��[i,j]��root�ڵ�k
			{				
				int t = e[i][r - 1] + e[r + 1][j] + w[i][j];  //��һ���ǹؼ����������ǽڵ�k��������������ֻ�ͼ���w[i][j]�ĸ��ʣ�
				if (e[i][j] < 0 || t < e[i][j])
				{
					e[i][j] = t;
					root[i][j] = r;

					std::cout <<r << " for " << i << ":" << j << std::endl;
				}
			}
		}
	}

	optimal_bst_print_root(root, 1, n);
	return root;
}

void test_optimal_bst()
{
	int p[] = { 0,4,6,8,2,10,12,14 };
	int q[] = { 6,6,6,6,5,5,5,5 };

	optimal_bst(p, q, 7);
}

int distance(int a[2], int b[2])
{
	return (a[0] - b[0])*(a[0] - b[0]) + (a[1] - b[1])*(a[1] - b[1]);
}

void bitonic_tours_printf(std::vector<std::vector<int>> p, int p1, int p2)
{
	std::cout << p[p1][p2] << " ";
	bitonic_tours_printf(p, p[p1][p2], p2);
}

//˫��ŷ�����������
int bitonic_tours(int points[][2], int len)
{
	if (len == 0)
		return 0;
	if (len == 1)
		return distance(points[0], points[1]);

	//TODO �Ȱ���x����(�ÿ���)

	using namespace std;
	vector<vector<int>> D(len);
	vector<vector<int>> p(len);
	for (int i = 0; i < len; ++i)
	{
		D[i] = vector<int>(len);
		p[i] = vector<int>(len);
	}

	D[0][1] = distance(points[0], points[1]);
	p[0][0] = 0;
	for (int j = 1; j < len; ++j)
	{
		for (int i = 0; i <j-1; ++i)
		{
			D[i][j] = D[i][j - 1] + distance(points[j - 1], points[j]);
		}

		D[j - 1][j] = -1;
		for (int k = 0; k < j-1; ++k)
		{
			int dis = D[k][j] + distance(points[k], points[j - 1]);
			if (D[j - 1][j]<0 || D[j - 1][j]>dis)
			{
				D[j - 1][j] = dis;
				p[j - 1][j] = k;
			}
		}
		
		D[j][j] = -1;
		for (int k = 0; k < j; ++j)
		{
			int dis= D[k][j] + distance(points[k], points[j]);
			if (D[j][j]<0 || D[j][j]>dis)
			{
				D[j][j] = dis;
				p[j][j] = k;
			}
		}
		
	}
}

Trie::Trie()
{
	root = new TrieNode();
	for (int i = 0; i < 26; ++i)
	{
		root->next[i] = NULL;
	}
}

Trie::~Trie()
{
	free(root);
}

int Trie::getIndex(char ch)
{
	int index = ch - 'a';
	if (index >= 26)
		index = -1;

	return index;
}

void Trie::insert(std::string word)
{
	int size = word.size();
	TrieNode* node = root;
	for (int i = 0; i < size; ++i)
	{
		char c = word[i];
		int index = getIndex(c);
		if (index < 0) //���ʷǷ�
			return;
		if (NULL == node->next[index])
		{
			node->next[index] = new TrieNode();
		}

		node = node->next[index];
	}
	node->isWord = true;
}

bool Trie::search(std::string word)
{
	int size = word.size();
	TrieNode* node = root;
	for (int i = 0; i < size; ++i)
	{
		char c = word[i];
		int index = getIndex(c);
		if (index < 0) //���ʷǷ�
			return false;
		if (NULL == node->next[index])
		{
			return false;
		}

		node = node->next[index];
	}

	return node->isWord;
}


bool Trie::startWith(std::string word)
{
	int size = word.size();
	TrieNode* node = root;
	for (int i = 0; i < size; ++i)
	{
		char c = word[i];
		int index = getIndex(c);
		if (index < 0) //���ʷǷ�
			return false;
		if (NULL == node->next[index])
		{
			return false;
		}

		node = node->next[index];
	}

	return true;
}

//˳ʱ���������
void clockwisePrint()
{
	int total = 5;
	int mutix[5][5];
	int n = 5;
	int num = 1;
	int turn = 0;
	while (n>0)
	{
		int start = turn;
		int end = total-turn;

		if (n == 1)
		{
			mutix[start][end - 1] = num;
			break;
		}

		for (int i = start; i < end; ++i)
		{
			mutix[start][i] = num;
			++num;
		}

		for (int j = start + 1; j < end - 1; ++j)
		{
			mutix[j][end - 1] = num;
			++num;
		}

		for (int i = end - 1; i >= start; --i)
		{
			mutix[end - 1][i] = num;
			++num;
		}

		for (int i = end - 2; i > start; --i)
		{
			mutix[i][start] = num;
			++num;
		}

		n -= 2;
		++turn;
	}

	for (int i = 0; i < total; ++i)
	{
		for (int j = 0; j < total; ++j)
		{
			if (mutix[i][j] < 10)
			{
				printf(" %d ", mutix[i][j]);
			}
			else
			{
				printf("%d ", mutix[i][j]);
			}

		}
		printf("\n");
	}
}
