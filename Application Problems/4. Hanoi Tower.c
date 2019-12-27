#include <stdio.h>

void Hanoi(int, char, char, char);

void Hanoi(int n, char A, char B, char C)
{
	if (n == 1)
		printf("%c --> %c\n", A, C);
	else
	{
		Hanoi(n-1, A, C, B);
		Hanoi(1, A, B, C);
		Hanoi(n-1, B, A, C);
	}
}

int main()
{
	int num;
	puts("Enter the num:");
	scanf("%d", &num);
	Hanoi(num, 'A', 'B', 'C');
	
	return 0;
}
