#include<stdio.h>
 
void quicksort(int a[],int n){
	int i,j;
	int pivot = a[0];	//Set the reference value 
	i = 0;
	j = n - 1;
	while(i < j){
		//Those greater than the reference value remain in their original positions
		while(i < j && a[j] > pivot){	j--;} 
		if(i < j){
			a[i] = a[j];
			i++;
		}
		//Those who are not greater than the reference value remain in place
		while(i < j && a[i] <= pivot){ 	i++;} 
		if(i < j){
			a[j] = a[i];
			j--;
		}
	} 
	a[i] = pivot;	//Reference element homing
		if(i > 1){
			//Quickly sort left subsequence recursively
			quicksort(a,i); 
		}
		if(n-i-1 > 1){
			quicksort(a+i+1,n-i-1)s;
		}
} 
 
int main(){
	int i,arr[] = {23,56,9,75,18,42,11,67};
	quicksort(arr,8);
	for(i = 0;i < sizeof(arr)/sizeof(int);i++)
		printf("%d\t",arr[i]);
	return 0;
}
