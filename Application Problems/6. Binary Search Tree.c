#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 512
 
typedef struct TreeNode
{
	int data;
	struct TreeNode *Left;
	struct TreeNode *Right;
}ST, *Tree, *Position;

Tree MakeEmpty(Tree T)
{
	if (T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Tree Create()
{
	Tree T = (Tree)malloc(sizeof(ST));
	T->Left = NULL;
	T->Right = NULL;
	puts("Enter the data of the first node:");
	scanf("%d", &T->data);
	return T;
}

Position Find(Tree T, int x)
{
	if (T == NULL)
		return NULL;
	if (x < T->data)
		return Find(T->Left, x);
	else if (x > T->data)
		return Find(T->Right, x);
	else
		return T;
}

Position FindMin(Tree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}

Position FindMax(Tree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Right == NULL)
		return T;
	else
		return FindMax(T->Right);
}

int DepthRecursive(Tree T)     //递归求深度 
{
	int LeftDepth, RightDepth;
	if (T == NULL)
		return 0;
	else
	{
		LeftDepth = DepthRecursive(T->Left);
		RightDepth = DepthRecursive(T->Right);
		if (LeftDepth > RightDepth)
			return LeftDepth+1;
		else
			return RightDepth+1;
	}
}

int DepthNonRecursive(Tree T)     //非递归求深度 
{
	Position S[MAXSIZE];
	Position P = T;
	int B[MAXSIZE];
	int Top = 0;
	int depth = 0;
	while (P != NULL || Top > 0)
	{
		while (P != NULL)
		{
			S[++Top] = P;
			B[Top] = 0;
			P = P->Left;
		}
		if (B[Top] == 0)
		{
			P = S[Top];
			P = P->Right;
			B[Top] = 1;
		}
		else
		{
			depth = (depth > Top) ? depth : Top;
			S[Top--] = NULL;
			P = NULL;
		}
	}
	return depth;
}

void Exchange(Tree T)   //利用中序遍历交换左右子树 
{
	Position S[MAXSIZE];
	Position P = T;
	Position TempCell;
	int Top = 0;
	while (P != NULL || Top > 0)
	{
		if (P != NULL)
		{
			S[++Top] = P;
			P = P->Left;
		}
		else
		{
			P = S[Top--];
			TempCell = P->Left;
			P->Left = P->Right;   //交换 
			P->Right = TempCell;
			P = P->Left;          //原P->Right 
		}
	}
}

Tree Insert(Tree T, int x)
{
	if (T == NULL)
	{
		T = (Tree)malloc(sizeof(ST));
		T->data = x;
		T->Left = NULL;
		T->Right = NULL;
	}
	else if (x < T->data)
		T->Left = Insert(T->Left, x);
	else
		T->Right = Insert(T->Right, x);
	
	return T;
}

Tree Delete(Tree T, int x)
{
	Position TempCell;
	if (T == NULL)
		return NULL;
	else if (x < T->data)
		T->Left = Delete(T->Left, x);
	else if (x > T->data)
		T->Right = Delete(T->Right, x);
	else if (T->Left && T->Right)
	{
		TempCell = FindMin(T->Right);
		T->data = TempCell->data;
		T->Right = Delete(T->Right, T->data);
	}
	else
	{
		TempCell = T;
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TempCell);
	}
	return T;
}

Tree BuildTree()
{
	fflush(stdin);
	int n;
	Tree T = Create();
	puts("Enter the num to insert(nonnumeric to stop):");
	while (scanf("%d", &n) == 1)
	{
		Insert(T, n);
		puts("Enter the num(nonnumeric to stop):");
	}
	return T;
}

Tree DeleteTree(Tree T)
{
	fflush(stdin);
	int m;
	puts("Enter the num to delete(nonnumeric to stop):");
	while (scanf("%d", &m) == 1)
	{
		Delete(T, m);
		puts("Enter the num(nonnumeric to stop):");
	}
	return T;
}

void PreorderRecursivePrint(Tree T)   //前序递归遍历 
{
	if (T != NULL)
	{
		printf("%d ", T->data);
		PreorderRecursivePrint(T->Left);
		PreorderRecursivePrint(T->Right);
	}
}

void PreorderNonRecursivePrint(Tree T)      //前序非递归遍历 
{
	Position S[MAXSIZE];
	Position P = T;
	int Top = 0;
	while (P != NULL || Top > 0)
	{
		if (P != NULL)
		{
			printf("%d ", P->data);
			S[++Top] = P;
			P = P->Left;
		}
		else
		{
			P = S[Top--];
			P = P->Right;
		}
	}
}

void InorderRecursivePrint(Tree T)
{
	if (T != NULL)
	{
		InorderRecursivePrint(T->Left);
		printf("%d ", T->data);
		InorderRecursivePrint(T->Right);
	}
}

void InorderNonRecursivePrint(Tree T)
{
	Position S[MAXSIZE];
	Position P = T;
	int Top = 0;
	while (P != NULL || Top > 0)
	{
		if (P != NULL)
		{
			S[++Top] = P;
			P = P->Left;
		}
		else
		{
			P = S[Top--];
			printf("%d ", P->data);
			P = P->Right;
		}
	}
}

void PostorderRecursivePrint(Tree T)
{
	if (T != NULL)
	{
		PostorderRecursivePrint(T->Left);
		PostorderRecursivePrint(T->Right);
		printf("%d ", T->data);
	}
}

void PostorderNonRecursivePrint(Tree T)
{
	Position S[MAXSIZE];
	Position P = T;
	int B[MAXSIZE];
	int Top = 0;
	
	while (P != NULL || Top > 0)
	{
		if (P != NULL)
		{
			S[++Top] = P;
			B[Top] = 0;
			P = P->Left;
		}
		else
		{
			P = S[Top--];
			if (B[Top+1] == 0)
			{
				S[++Top] = P;
				B[Top] = 1;
				P = P->Right;
			}
			else
			{
				printf("%d ", P->data);
				P = NULL;
			}
		}
	}
}

void LayerPrint(Tree T)   //层次遍历 
{
	Position P, Q[MAXSIZE];
	int Front = 0;
	int Rear = 1;
	Q[Rear] = T;
	while (Front < Rear)
	{
		P = Q[++Front];
		printf("%d ", P->data);
		if (P->Left != NULL)
			Q[++Rear] = P->Left;
		if (P->Right != NULL)
			Q[++Rear] = P->Right;
	}
}

int main()
{
	Tree T = BuildTree();
	T = DeleteTree(T);
	Exchange(T);
	PreorderRecursivePrint(T);
	printf("\n");
	InorderNonRecursivePrint(T);
	printf("\n\n%d", DepthRecursive(T));
	printf("\n%d", DepthNonRecursive(T));
	
	return 0; 
}


