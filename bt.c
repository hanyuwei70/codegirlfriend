/*
第三次上机作业
@author 黄琪东
*/
#include <stdio.h>
#include <string.h>
typedef struct node
{
	char data;
	struct node *left, *right;
}NODE;
NODE *root=NULL;
NODE* init()
{
	char a;
	NODE *q;
	scanf("%c", &a);
	if (a == '0') return NULL;
	q = (NODE*)malloc(sizeof(NODE));
	q->data = a; q->left = q->right = NULL;
	q->left = init();
	q->right = init();
	return q;
}
void LCR(NODE *root)
{
	if (root == NULL) return;
	LCR(root->left);
	printf("%c", root->data);
	LCR(root->right);
	return;
}
void LRC(NODE *root)
{
	if (root == NULL)return;
	LRC(root->left);
	LRC(root->right);
	printf("%c", root->data);
	return;
}
int height(NODE *root)
{
	if (root == NULL)return 0;
	int a, b;
	a = height(root->left);
	b = height(root->right);
	return ((a > b) ? a : b) + 1;
}
int countleaf(NODE *root)
{
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	return countleaf(root->left) + countleaf(root->right);
}
int main()
{
	root=init();
	LCR(root); printf("\n");
	LRC(root); printf("\n");
	printf("leaf node(s):%d\n", countleaf(root))
	return 0;
}
