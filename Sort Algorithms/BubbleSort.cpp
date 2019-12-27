#include "stdio.h" 

/*
	1. Compare adjacent elements. If the first is larger than the second, swap them for both;
	2. Do the same for each pair of adjacent elements, from the first pair at the beginning to the last pair at the end, so the last element should be the largest
	3. Repeat the above steps for all elements except the last one;
	4. Repeat steps 1 to 3 until sorting is complete.
*/

void BubbleSort(int *arr, int size)  
{  
    int i, j, tmp;  
    for (i = 0; i < size - 1; i++) {  
        for (j = 0; j < size - i - 1; j++) {  
            if (arr[j] > arr[j+1]) {  
                tmp = arr[j];  
                arr[j] = arr[j+1];  
                arr[j+1] = tmp;  
            }  
        }  
    }  
}  

int main(){
	int i,arr[] = {23,56,9,75,18,42,11,67};
	BubbleSort(arr,8);
	for(i = 0;i < sizeof(arr)/sizeof(int);i++)
		printf("%d\t",arr[i]);
	return 0;
}
