/*https://www.cnblogs.com/You0/p/4477538.html?utm_source=tuicool*/ 

#include <stdio.h>
#include <stdlib.h>

//����һ���߱�ڵ�Ľṹ 
typedef struct node
{
    int adjvex;
    //int Mark; //���ڱ���Ƿ񱻷��ʹ� 
    struct node *next;
}VerAndedge; 

//����� 
typedef struct Fixed
{
    int Mark;
    int fixedvex;
    struct node* firsthead;
}Fixednode;

//�������������Ϣ�� 
typedef struct ALgraph
{
    int a,b;  //��������ͱ߸��� 
    Fixednode adjlist[100];
}ALgraph;


void create(ALgraph *);
void Adj_DFS_Recursive(ALgraph *, int);
void Adj_DFS_Nonrecursive(ALgraph *, int);
void Adj_BFS_Nonrecursive(ALgraph *, int);
void ConnectedComponent(ALgraph *); 
void InDegreeAndOutDegree(ALgraph *);
void Topo_Order(int [], ALgraph *);


int main(void)
{
    int i;
    ALgraph * S = (ALgraph *)malloc(sizeof(ALgraph));
    create(S);
     VerAndedge *current;
    for(i=0;i<S->a;i++)
    {
        printf("%d->",S->adjlist[i].fixedvex);
        current = S->adjlist[i].firsthead;
        while(current!=NULL)
        {
            printf("%d->",current->adjvex);
            current= current->next;
        }
        printf("\n");
    }
    
    int vi;
    printf("������Դ�㣺\n");
    scanf("%d",&vi);
    Adj_BFS_Nonrecursive(S, vi);
    
	
    return 0;
}

 

void create(ALgraph *S)
{
    int i,x,y;
    printf("�����붥��ĸ����ͱߵ�����:");
    scanf("%d%d",&S->a,&S->b);   //��ȡ������ͱߵ���Ϣ
         
    for(i=0;i<S->a;i++)
    {
        printf("���붥�㣬���������:");   //��������� 
        scanf("%d",&S->adjlist[i].fixedvex);
        S->adjlist[i].firsthead= NULL;  //��ʼ��firsthead 
        S->adjlist[i].Mark = 0;//��ʼ����� 

    }
    printf("�����߱�\n");//�����߱��ڽ�����ͬʱ�����ǵĹ�ϵ��Ӧ
    for(i=0;i<S->b;i++)
    {
        printf("�������ڵĶ���:");
        scanf("%d%d",&x,&y);
        VerAndedge * G = (VerAndedge *)malloc(sizeof(VerAndedge)); //����һ���߱�ṹ 
    //    G->Mark = 0; //���Ϊ���ʾδ���� 
        G->adjvex = y;
        G->next = S->adjlist[x].firsthead; //���뵽ͷ��
        S->adjlist[x].firsthead = G;
        //��Ϊ������ͼ�����Ե������ڵ�Ĺ�ϵ���ٴ����ɡ� 
        G= (VerAndedge *)malloc(sizeof(VerAndedge));
    //    G->Mark = 0;
        G->adjvex= x;
        G->next= S->adjlist[y].firsthead; //���뵽ͷ��
        S->adjlist[y].firsthead= G;
    
    }
}

void Adj_DFS_Recursive(ALgraph *S, int vi)   //�ݹ� ������� 
{
    printf("�����������:");
    if(S->adjlist[vi].Mark == 0)
    {
        printf("%-2d",S->adjlist[vi].fixedvex);
        S->adjlist[vi].Mark = 1;
    }
	    
    VerAndedge * current = S->adjlist[vi].firsthead;
    
    for(;current!=NULL;current=current->next)
    {
        if(S->adjlist[current->adjvex].Mark==0)
        	Adj_DFS_Recursive(S,current->adjvex);
    }
}


void Adj_DFS_Nonrecursive(ALgraph *S, int vi)   //�ǵݹ� ������� 
{
    int Visited[100];
    int Stack[100];
    int Top = 0;
    int u;
    Visited[vi] = 1;
    Stack[++Top] = vi;
    struct node *P = S->adjlist[vi].firsthead;
    printf("%d ", vi);
    while (P != NULL || Top > 0)
    {
    	while (P != NULL && Visited[P->adjvex] == 1)
    		P = P->next;
    	if (P == NULL)
    	{
    		if (Top > 0)
    			P = S->adjlist[Stack[--Top]].firsthead;
		}
		else
    	{
    		u = P->adjvex;
    		printf("%d ", u);
    		Visited[u] = 1;
    		Stack[++Top] = u;
    		P = S->adjlist[u].firsthead;
		}
	}
}

void Adj_BFS_Nonrecursive(ALgraph *S, int vi)  //�ǵݹ� ������� 
{
	struct node *P;
	int Visited[100];
	int Queue[100];
	int u;
	int Front = 0;
	int Rear = 0;
	Visited[vi] = 1;
	Queue[++Rear] = vi;
	
	while (Front < Rear)
	{
		u = Queue[++Front];
		printf("%d ", u);
		P = S->adjlist[u].firsthead;
		while (P != NULL)
		{
			u = P->adjvex;
			if (Visited[u] != 1)
			{
				Queue[++Rear] = u;
				Visited[u] = 1;
			}
			P = P->next;
		}
	}
}

void ConnectedComponent(ALgraph *S)  //��ͨ���� 
{
	int j, k;
	int Visited[100];
	for (j = 1; j <= S->a; j++)
		Visited[j] = 0;
	k = 0;
	for (j = 1; j <= S->a; j++)
	{
		if (Visited[j] == 0)
		{
			printf("\n��%d����ͨ����", ++k);
			Adj_BFS_Nonrecursive(S, j);
		}
	}
}


int InDgree[100];
int OutDgree[100];
void InDegreeAndOutDegree(ALgraph *S)
{
	int i;
	int j, k = 0;
	struct node *P;
	for (i = 1; i <= S->a; i++)
	{
		P = S->adjlist[i].firsthead;
		while (P != NULL)
		{
			j++;
			P = P->next;
		}
		OutDgree[i] = j;
	}
	for (i = 1; i <= S->a; i++)
	{
		for (j = 1; j <= S->a; j++)
		{
			P = S->adjlist[j].firsthead;
			while (P != NULL)
			{
				if (P->adjvex == i)
				{
					k++;
					break;
				}
				P = P->next;
			}
		}
		InDgree[i] = k;
	}
}

void Topo_Order(int InDegree[100], ALgraph *S)   //�������� 
{
	int Top = 0;
	int i;
	struct node *P;
	for (i = 0; i < S->a; i++)
	{
		if (InDgree[i] == 0)
		{
			InDgree[i] = Top;
			Top = i;
		}
	}
	while (InDgree[Top] > 0)
	{
		printf("%d->", Top);
		P = S->adjlist[Top].firsthead;
		while (P != NULL)
		{
			InDgree[P->adjvex]--;
			if (InDgree[P->adjvex] == 0)
			{
				Top = InDgree[Top];
				InDgree[P->adjvex] = Top;
				Top = P->adjvex; 
			}
			else
				P = P->next;
		}		
	}
	printf("%d", Top);
}











