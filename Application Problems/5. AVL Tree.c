#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct AvlTree
{
	int data;
	struct AvlTree *Left;
	struct AvlTree *Right;
	int Height;
}AVL, *Tree, *Position;

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
	Tree T = (Tree)malloc(sizeof(AVL));
	T->Left = NULL;
	T->Right = NULL;
	T->Height = 0;
	puts("Enter the data of the first node:");
	scanf("%d", &T->data);
	return T;
}

static int Height(Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

Tree Insert(Tree T, int x)
{
	if (T == NULL)
	{
		T = (Tree)malloc(sizeof(AVL));
		T->data = x;
		T->Left = NULL;
		T->Right = NULL;
		T->Height = 0;
	}
	else if (x < T->data)
	{
		T->Left = Insert(T->Left, x);
		if (Height(T->Left) - Height(T->Right) == 2)
			if (x < T->Left->data)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
	}		
	else if (x > T->data)
	{
		T->Right = Insert(T->Right, x);
		if (Height(T->Right) - Height(T->Left) == 2)
			if (x > T->Right->data)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
	}
	T->Height = (Height(T->Left) > Height(T->Right)) ? Height(T->Left)+1 : Height(T->Right)+1;	
	
	return T;
}

static Position SingleRotateWithLeft(Position K2)
{
	Position K1;
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	
	K2->Height = (Height(K2->Left) > Height(K2->Right)) ? Height(K2->Left)+1 : Height(K2->Right)+1;
	K1->Height = (Height(K1->Left) > K2->Height) ? Height(K1->Left)+1 : K2->Height+1;
}

static Position DoubleRotateWithRight(Position K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);
	return SingleRotateWithLeft(K3);
}

//还需对称两个函数 


Tree Delete(Tree T, int x)  //需改 
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

void Print(Tree T)
{
	if (T)
	{
		Print(T->Left);
		printf("%d ", T->data);
		Print(T->Right);
	}
}

int main()  //需改 
{
	int n;
	Tree T = Create();
	puts("Enter the num to insert(nonnumeric to stop):");
	while (scanf("%d", &n) == 1)
	{
		Insert(T, n);
		puts("Enter the num(nonnumeric to stop):");
	}
	puts("Enter the num to delete(nonnumeric to stop):");
	while (scanf("%d", &n) && n != 0)
	{
		Delete(T, n);
		puts("Enter the num(nonnumeric to stop):");
	}
	Print(T);
	
	return 0; 
}


