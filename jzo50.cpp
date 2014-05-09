#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define MAX 100006
bool TF = false;

struct BinaryTree
{
	int value;
	BinaryTree *left;
	BinaryTree *right;
};

BinaryTree *CreateTree(BinaryTree **root)
{
	BinaryTree *index = NULL;
	int tmp;
	cin >> tmp;
	if (tmp == 0)
		return NULL;
	(*root) = new BinaryTree;
	index = *root;
	index->value = tmp;
	index->left = NULL;
	index->right = NULL;
	CreateTree(&(index->left));
	CreateTree(&(index->right));
	return *root;
}

void DeleteTree(BinaryTree **root)
{
	if ((*root) == NULL)
		return ;
	BinaryTree *index = *root;
	DeleteTree(&(index->left));
	DeleteTree(&(index->right));
	delete index;
}

void PreOrderTraverse(BinaryTree *root)
{
	if (root == NULL)
		return;
	BinaryTree *index = root;
	PreOrderTraverse(index->left);
	cout << index->value << " ";
	PreOrderTraverse(index->right);
}

bool GetNodePath(BinaryTree *root, int value, vector<BinaryTree *> &path)
{
	BinaryTree *index;
	if (root == NULL)
		return false;
	path.push_back(root);
	if (root->value == value)
		return true;
	
	bool found = GetNodePath(root->left, value, path);
	if (found)
		return true;
	else
	{
		found = GetNodePath(root->right, value, path);
		if (found)
			return true;
		else
		{
			path.pop_back();
			return false;
		}
	}
}

BinaryTree *GetLastCommonNode(vector<BinaryTree *> path1, vector<BinaryTree *> path2)
{
	vector<BinaryTree *>::iterator iter1 = path1.begin(), iter2 = path2.begin();
	BinaryTree *last_node = 0;
	if (path1.size() == 0 || path2.size() == 0)
	{
		TF = false;
		return 0;
	}
	while (iter1 != path1.end() && iter2 != path2.end())
	{
		if (*iter1 == *iter2)
		{
			TF = true;
			last_node = *iter1;
		}
		iter1 ++;
		iter2 ++;
	}
	return last_node;
}



BinaryTree* GetLastCommonParent(BinaryTree *root, int num1, int num2)
{
	if (root == NULL)
	{
		TF = false;
		return 0;
	}
	vector<BinaryTree *> path1, path2;
	bool TF1, TF2;
	GetNodePath(root, num1, path1);
	GetNodePath(root, num2, path2);
	return GetLastCommonNode(path1, path2);
}

int main(void)
{
	int n, num1, num2;
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	cin >> n;
	while (n--)
	{
		BinaryTree *root = NULL;
		CreateTree(&root);
		scanf("%d", &num1);
		scanf("%d", &num2);
		BinaryTree* common_node = GetLastCommonParent(root, num1, num2);
		if (TF == false)
			printf("My God\n");
		else
			printf("%d\n", common_node->value);

		DeleteTree(&root);
	}


	//system("pause");
	return 0;
}



/* ֻ��һ�α������LCA */
/*
#include <iostream>
using namespace std;
struct Node
{
    struct Node *left, *right;
    int key;
};
Node* newNode(int key)
{
    Node *temp = new Node;
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// ����n1��n2�� LCA��ָ��
// ����n1��n2������������
struct Node *findLCA(struct Node* root, int n1, int n2)
{
    if (root == NULL) return NULL;

    // ֻҪn1 �� n2 ����һ��ƥ�伴��
    //  (ע�⣺��� һ���ڵ�����һ�����ȣ��򷵻ص������Ƚڵ㡣��Ϊ�ݹ���Ҫ���ص����ȵ� )
    if (root->key == n1 || root->key == n2)
        return root;
    // �ֱ���������������
    Node *left_lca  = findLCA(root->left, n1, n2);
    Node *right_lca = findLCA(root->right, n1, n2);
    // ��������طǿ�ָ�� Non-NULL, ��˵�������ڵ�ֱ�����������������У���ǰ�ڵ�϶�ΪLCA
    if (left_lca && right_lca)  return root;
    // ���һ��Ϊ�գ���˵��LCA����һ������
    return (left_lca != NULL)? left_lca: right_lca;
}

//����
int main()
{
    // ��������ͼ�е���
    Node * root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    cout << "LCA(4, 5) = " << findLCA(root, 4, 5)->key;
    cout << "\nLCA(4, 6) = " << findLCA(root, 4, 6)->key;
    cout << "\nLCA(3, 4) = " << findLCA(root, 3, 4)->key;
    cout << "\nLCA(2, 4) = " << findLCA(root, 2, 4)->key;
	system("pause");
    return 0;
}
	*/
