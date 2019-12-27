#include "stdio.h" 

/* 
	Initial state: the disordered area is R [1..n], and the ordered area is empty;
	At the beginning of the i-th sort (i = 1,2,3 ... n-1), the current ordered and unordered regions are R [1..i-1] and R (i..n), respectively. 
	This trip sorting selects the record R [k] with the smallest keyword from the current disordered area, 
	and exchanges it with the first record R of the disordered area, making R [1..i] 
	and R [i + 1 ..n) respectively become a new ordered area where the number of records is increased by one 
	and a new disordered area where the number of records is reduced by one;
	At the end of n-1 passes, the array is ordered.
*/

void SelectionSort(int *arr, int size)
{
    int i, j, k, tmp;
    for (i = 0; i < size - 1; i++) {
        k = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[k]) {
                k = j;
            }
        }
        tmp = arr[k];
        arr[k] = arr[i];
        arr[i] = tmp;
    }
}

int main(){
	int i,arr[] = {23,56,9,75,18,42,11,67};
	SelectionSort(arr,8);
	for(i = 0;i < sizeof(arr)/sizeof(int);i++)
		printf("%d\t",arr[i]);
	return 0;
}

