#include "stdio.h" 

/*
	In general, insertion sort is implemented on arrays using in-place. The specific algorithm is described as follows:
	1. Starting from the first element, the element can be considered as sorted;
	2. Take the next element and scan it backwards and forwards in the sequence of ordered elements;
	3. If the element (sorted) is larger than the new element, move the element to the next position;
	4. Repeat step 3 until you find a position where the sorted element is less than or equal to the new element;
	5. After inserting a new element into that position;
	6. Repeat steps 2 ~ 5.
*/

void InsertionSort(int *arr, int size)    
{    
    int i, j, tmp;    
    for (i = 1; i < size; i++) {    
        if (arr[i] < arr[i-1]) {    
            tmp = arr[i];    
            for (j = i - 1; j >= 0 && arr[j] > tmp; j--) {  
                arr[j+1] = arr[j];    
            }  
            arr[j+1] = tmp;    
        }          
    }    
}    

int main(){
	int i,arr[] = {23,56,9,75,18,42,11,67};
	InsertionSort(arr,8);
	for(i = 0;i < sizeof(arr)/sizeof(int);i++)
		printf("%d\t",arr[i]);
	return 0;
}
