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
        return 0;  // 返回0 栈外优先级更高，直接进栈
    return 1;   // 返回1 栈内优先级更高或优先级相等，先出栈，再进栈
}

void Transfer(Stack S, char infix[], char postfix[])  //这里S是专门放运算符的栈，postfix是后缀表达式 
{
    char *p = infix;  //复制到p里面，不改infix本身 
    int i, j, k;
    char in, out;
    j = 0;
    for (i=0; p[i] != '#'; i++)
	{
        // 数字直接进后缀数组 
        if (p[i] >= '0' && p[i] <= '9')
            postfix[j++] = p[i];
        // 字符要进行判断 
        else
		{
            in = getTop(S);  //栈内运算符 
            out = p[i];      //栈外运算符 
            if (isEmpty(S))
            	Push(S, out);	
            // 如果栈非空
            else
			{
                if (out == ')')    //当右括号出现时，出栈到左括号（不包括左括号）进后缀数组 
				{
                    while (getTop(S) != '(')
                        postfix[j++] = Pop(S);
                    Pop(S);
                    continue;
                }
                else if (judgePriority(in, out))  //先将优先级高（或相等）的运算符出栈，再将新运算符进栈
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
           		else  //如果栈内优先级低于栈外（或左括号），栈外运算符直接进栈 
					Push(S, out);
            }
        }
    }

    while (!isEmpty(S))   //将剩余栈内运算符出栈 
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
            Push(S, postfix[i]-48);   //ASCII码，字符'0-9'是48-57，要变回数值0-9
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
