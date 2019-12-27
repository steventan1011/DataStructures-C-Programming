#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int num;
	struct Node *next;
}Link, *List, *Position;

List create(int n)   //�������� 
{
	int i;
	List first;    //��һλ��first 
	Position p, q;
	p = (Position)malloc(sizeof(Link));
	p->num = 1;
	first = p;
	q = p;
	for (i = 2; i <= n; i++)
	{
		p = (Position)malloc(sizeof(Link));   //����p�Ŀռ� 
		q->next = p;   //p��q�ĺ�һ�� 
		p->num = i;
		q = p;
	}
	p->next = first;    //���һ��ָ�ص���һ�� first
	
	return first;    //���ص�һ��first 
}

void del(List A, int k, int m)
{
	int i;
	Position p, q, tmp;
	p = A;
	for (i = 1; i <k; i++)    //��pָ���k���� 
	{
		q = p;
		p = p->next;
	}
	printf("\n\nDelete num: ");
	while (p->next != p)
	{
		for (i = 1; i < m; i++)    //ѭ������m��ɾ����m�� 
		{
			q = p;
			p = p->next;
		}
		printf("%d -> ", p->num);   //��ӡ��ɾ������ 
		tmp = p;
		q->next = p->next;
		p = p->next;
		free(tmp);    //free�ͷſռ� 
	}
	printf("%d", p->num);   //��ӡ���һ����ɾ������ 
}

int main()
{
	int n, k, m;
	List A;
	puts("Enter the number of people(n): ");   //����n��k��m 
	scanf("%d", &n);
	puts("Enter the first number(k): ");
	scanf("%d", &k);
	puts("Enter the circle of one delete(m): ");
	scanf("%d", &m);
	A = create(n);    //���ú��� 
	del(A, k, m);
	
	return 0;
}
