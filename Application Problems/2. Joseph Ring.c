#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int num;
	struct Node *next;
}Link, *List, *Position;

List create(int n)   //创建链表 
{
	int i;
	List first;    //第一位是first 
	Position p, q;
	p = (Position)malloc(sizeof(Link));
	p->num = 1;
	first = p;
	q = p;
	for (i = 2; i <= n; i++)
	{
		p = (Position)malloc(sizeof(Link));   //创建p的空间 
		q->next = p;   //p是q的后一项 
		p->num = i;
		q = p;
	}
	p->next = first;    //最后一项指回到第一项 first
	
	return first;    //返回第一项first 
}

void del(List A, int k, int m)
{
	int i;
	Position p, q, tmp;
	p = A;
	for (i = 1; i <k; i++)    //将p指向第k个人 
	{
		q = p;
		p = p->next;
	}
	printf("\n\nDelete num: ");
	while (p->next != p)
	{
		for (i = 1; i < m; i++)    //循环报数m，删掉第m个 
		{
			q = p;
			p = p->next;
		}
		printf("%d -> ", p->num);   //打印被删掉的人 
		tmp = p;
		q->next = p->next;
		p = p->next;
		free(tmp);    //free释放空间 
	}
	printf("%d", p->num);   //打印最后一个被删掉的嗯 
}

int main()
{
	int n, k, m;
	List A;
	puts("Enter the number of people(n): ");   //输入n、k、m 
	scanf("%d", &n);
	puts("Enter the first number(k): ");
	scanf("%d", &k);
	puts("Enter the circle of one delete(m): ");
	scanf("%d", &m);
	A = create(n);    //调用函数 
	del(A, k, m);
	
	return 0;
}
