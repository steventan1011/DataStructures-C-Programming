/*https://www.cnblogs.com/You0/p/4477538.html?utm_source=tuicool*/ 

#include <stdio.h>
#include <stdlib.h>

//定义一个边表节点的结构 
typedef struct node
{
    int adjvex;
    //int Mark; //用于标记是否被访问过 
    struct node *next;
}VerAndedge; 

//顶点表 
typedef struct Fixed
{
    int Mark;
    int fixedvex;
    struct node* firsthead;
}Fixednode;

//保存各个顶点信息。 
typedef struct ALgraph
{
    int a,b;  //顶点个数和边个数 
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
    printf("请输入源点：\n");
    scanf("%d",&vi);
    Adj_BFS_Nonrecursive(S, vi);
    
	
    return 0;
}

 

void create(ALgraph *S)
{
    int i,x,y;
    printf("请输入顶点的个数和边的数量:");
    scanf("%d%d",&S->a,&S->b);   //获取到顶点和边的信息
         
    for(i=0;i<S->a;i++)
    {
        printf("输入顶点，建立顶点表:");   //建立顶点表。 
        scanf("%d",&S->adjlist[i].fixedvex);
        S->adjlist[i].firsthead= NULL;  //初始化firsthead 
        S->adjlist[i].Mark = 0;//初始化标记 

    }
    printf("建立边表\n");//建立边表，在建立的同时将他们的关系对应
    for(i=0;i<S->b;i++)
    {
        printf("输入相邻的顶点:");
        scanf("%d%d",&x,&y);
        VerAndedge * G = (VerAndedge *)malloc(sizeof(VerAndedge)); //生成一个边表结构 
    //    G->Mark = 0; //标记为零表示未访问 
        G->adjvex = y;
        G->next = S->adjlist[x].firsthead; //插入到头部
        S->adjlist[x].firsthead = G;
        //因为是无向图，所以调换个节点的关系，再次生成。 
        G= (VerAndedge *)malloc(sizeof(VerAndedge));
    //    G->Mark = 0;
        G->adjvex= x;
        G->next= S->adjlist[y].firsthead; //插入到头部
        S->adjlist[y].firsthead= G;
    
    }
}

void Adj_DFS_Recursive(ALgraph *S, int vi)   //递归 深度优先 
{
    printf("遍历结果如下:");
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


void Adj_DFS_Nonrecursive(ALgraph *S, int vi)   //非递归 深度优先 
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

void Adj_BFS_Nonrecursive(ALgraph *S, int vi)  //非递归 广度优先 
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

void ConnectedComponent(ALgraph *S)  //连通分量 
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
			printf("\n第%d个连通分量", ++k);
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

void Topo_Order(int InDegree[100], ALgraph *S)   //拓扑排序 
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











