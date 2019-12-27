#include <stdio.h>
#include <stdlib.h>

#define MAX  100000
#define VNUM  10+1                                             //����û��IDΪ0�ĵ�,so id�ŷ�Χ1~10

int edge[VNUM][VNUM]={/*������ڽӾ���*/};
int lowcost[VNUM]={0};                                         //��¼Vnew��ÿ���㵽V���ڽӵ����̱�
int addvnew[VNUM];                                             //���ĳ���Ƿ����Vnew
int adjacent[VNUM]={0};                                        //��¼V����Vnew���ڽ��ĵ�


void prim(int start)
{
     int sumweight=0;
     int i,j,k=0;

     for(i=1;i<VNUM;i++)                                      //�����Ǵ�1��ʼ
     {
        lowcost[i]=edge[start][i];
        addvnew[i]=-1;                                         //�����е�����Vnew֮��,V֮�ڣ�����ֻҪ��Ӧ��Ϊ-1���ͱ�ʾ��Vnew֮��
     }

     addvnew[start]=0;                                        //����ʼ��start����Vnew
     adjacent[start]=start;
                                                 
     for(i=1;i<VNUM-1;i++)                                        
     {
        int min=MAX;
        int v=-1;
        for(j=1;j<VNUM;j++)                                      
        {
            if(addvnew[j]!=-1&&lowcost[j]<min)                 //��Vnew֮��Ѱ�����·��
            {
                min=lowcost[j];
                v=j;
            }
        }
        if(v!=-1)
        {
            printf("%d %d %d\n",adjacent[v],v,lowcost[v]);
            addvnew[v]=0;                                      //��v��Vnew��

            sumweight+=lowcost[v];                             //����·������֮��
            for(j=1;j<VNUM;j++)
            {
                if(addvnew[j]==-1&&edge[v][j]<lowcost[j])      
                {
                    lowcost[j]=edge[v][j];                     //��ʱv�����Vnew ��Ҫ����lowcost
                    adjacent[j]=v;                             
                }
            }
        }
    }
    printf("the minmum weight is %d",sumweight);
}
