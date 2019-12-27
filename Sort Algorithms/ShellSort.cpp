#include "stdio.h" 

/* 
	First divide the entire record sequence to be sorted into several sub-sequences and directly insert and sort them. 
	The specific algorithm description:
	Select an incremental sequence t1, t2, ..., tk, where ti> tj, tk = 1;
	Sort the sequence k times by the number k of the incremental sequence;
	Each time the sort is performed, the sequence to be sorted is divided into several subsequences of length m according 
	to the corresponding increment ti, and each subtable is directly inserted and sorted. When only the increment factor is 1, 
	the entire sequence is treated as a table, and the length of the table is the length of the entire sequence.
*/

void ShellSort(int *arr, int size)  
{  
    int i, j, tmp, increment;  
    for (increment = size/ 2; increment > 0; increment /= 2) {    
        for (i = increment; i < size; i++) {  
            tmp = arr[i];  
            for (j = i - increment; j >= 0 && tmp < arr[j]; j -= increment) {  
                arr[j + increment] = arr[j];  
            }  
            arr[j + increment] = tmp;
        }  
    }  
}  


int main(){
	int i,arr[] = {23,56,9,75,18,42,11,67};
	ShellSort(arr,8);
	for(i = 0;i < sizeof(arr)/sizeof(int);i++)
		printf("%d\t",arr[i]);
	return 0;
}
