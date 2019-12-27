#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 1024

typedef struct StackRecord
{
	int Top;
	int Array[MAXSIZE];
}*Stack;


Stack create()
{
	Stack S = (Stack)malloc(sizeof(int) * MAXSIZE);
	S->Top = -1;
	return S;
}

int isEmpty(Stack S)
{
	return S->Top==-1?1:0;
}

void Push(Stack S, int x)
{
	if (S->Top >= MAXSIZE)
	{
		puts("FULL");
		exit(1);
	}
	S->Array[++S->Top] = x;
}

int Pop(Stack S)
{
	if (S->Top <= -1)
	{
		puts("EMPTY");
		exit(1);
	}
	return S->Array[S->Top--];
}

int getTop(Stack S)
{
    if (S->Top < MAXSIZE)
        return S->Array[S->Top];
    exit(1);
}

int inPriority(char in)
{
	switch (in)
	{
		case '+':
			return 1;
			break;
		case '-':
			return 1;
			break;
		case '*' :
			return 2;
			break;
		case '/':
			return 2;
			break;
		case '^':
			return 3;
			break;
		case '(':
			return 0;
			break;
		default:
			puts("Error!");
			break;
	}
}

int outPriority(char out)
{
	switch (out)
	{
		case '+':
			return 1;
			break;
		case '-':
			return 1;
			break;
		case '*':
			return 2;
			break;
		case '/':
			return 2;
			break;
		case '^':
			return 4;
			break;
		case '(':
			return 5;
			break;
		default:
			puts("Error!");
			break;
	}
}

int judgePriority(char in, char out)
{  
    if (inPriority(in) < outPriority(out))
        return 0;  // ����0 ջ�����ȼ����ߣ�ֱ�ӽ�ջ
    return 1;   // ����1 ջ�����ȼ����߻����ȼ���ȣ��ȳ�ջ���ٽ�ջ
}

void Transfer(Stack S, char infix[], char postfix[])  //����S��ר�ŷ��������ջ��postfix�Ǻ�׺���ʽ 
{
    char *p = infix;  //���Ƶ�p���棬����infix���� 
    int i, j, k;
    char in, out;
    j = 0;
    for (i=0; p[i] != '#'; i++)
	{
        // ����ֱ�ӽ���׺���� 
        if (p[i] >= '0' && p[i] <= '9')
            postfix[j++] = p[i];
        // �ַ�Ҫ�����ж� 
        else
		{
            in = getTop(S);  //ջ������� 
            out = p[i];      //ջ������� 
            if (isEmpty(S))
            	Push(S, out);	
            // ���ջ�ǿ�
            else
			{
                if (out == ')')    //�������ų���ʱ����ջ�������ţ������������ţ�����׺���� 
				{
                    while (getTop(S) != '(')
                        postfix[j++] = Pop(S);
                    Pop(S);
                    continue;
                }
                else if (judgePriority(in, out))  //�Ƚ����ȼ��ߣ�����ȣ����������ջ���ٽ����������ջ
				{
					postfix[j++] = Pop(S);
                   	for (k=0; k<=S->Top; k++)
					{
                   	   	if (!judgePriority(getTop(S), out))
							break;
                		postfix[j++] = Pop(S);
                  	}
                   	Push(S, out);
           		}
           		else  //���ջ�����ȼ�����ջ�⣨�������ţ���ջ�������ֱ�ӽ�ջ 
					Push(S, out);
            }
        }
    }

    while (!isEmpty(S))   //��ʣ��ջ���������ջ 
        postfix[j++] = Pop(S);
    postfix[j] = 0;
}

int Calculate(Stack S, char postfix[])   
{
    int i, k, j;
    for (i=0; postfix[i]; i++)
	{
        switch(postfix[i])
		{
        case '+':
            k = Pop(S) + Pop(S);
            Push(S, k);
            break;
        case '-':
            j = Pop(S);
            k = Pop(S) - j;
            Push(S, k);
            break;
        case '*':
            k = Pop(S) * Pop(S);
            Push(S, k);
            break;
        case '/':
            j = Pop(S);
            k = Pop(S)/j;
            Push(S, k);
            break;
        case '^':
			j = Pop(S);
			k = pow(Pop(S), j);
			Push(S, k);
			break; 
        default:
            Push(S, postfix[i]-48);   //ASCII�룬�ַ�'0-9'��48-57��Ҫ�����ֵ0-9
            break;
        }
    }
    return Pop(S);

}
int main()
{
	int i;
	Stack S = create();
    char infix[MAXSIZE], postfix[MAXSIZE];
    puts("Enter the infix (enter # to stop):");
    gets(infix);
    Transfer(S, infix, postfix);
    printf("\nThe postfix is : %s", postfix);
    printf("\n\nThe result is : %d\n", Calculate(S, postfix));
    
    return 0;
}
