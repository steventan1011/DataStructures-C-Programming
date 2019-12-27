#include<stdio.h>
#include<stdlib.h>

//Prove that P = A when the next item of A changes, so does the next item of P.

typedef struct Node
{
	int data;
	struct Node *next;
	Node (int v):data(v){}
}Link, *List, *Position;

int main()
{
	List A;
	A = (List)malloc(sizeof(Link));
	A->next = NULL;
	Position P;
	P = A;
	Position a1 = new Link(1);
	Position a2 = new Link(2);
	A->next = a1;
	a1->next = a2;
	a2->next = NULL;
	printf("%d", P->next->next->data);
	
	return 0;
}
