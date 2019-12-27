#include<stdio.h>

/*
	1. Divide an input sequence of length n into two subsequences of length n / 2;
    2. Merge and sort these two subsequences respectively;
    3. Combines two sorted subsequences into a final sorted sequence.
*/


void Merge_Sort(int *arr, int *temparr,int start,int mid,int end)
{
    int left_start = start ;
    int left_end   = mid ;

    int right_start = mid+1 ;
    int right_end   = end ;

    int index = start ;

    while(left_start<=left_end&&right_start<=right_end)
    {
        if(arr[left_start]>arr[right_start])
            temparr[index++] = arr[right_start++] ;
        else
            temparr[index++] = arr[left_start++] ;
    }

    while(left_start<=left_end)
        temparr[index++] = arr[left_start++] ;

    while(right_start<=right_end)
        temparr[index++] = arr[right_start++] ;

    for(index = start ;index<=end ;++index)
        arr[index] = temparr[index] ;
}
void Sort_Message(int *arr, int *temparr,int start,int end)
{
    if(start<end)
    {
        int mid = (start+end)/2 ;
        Sort_Message(arr,temparr,start,mid) ;
        Sort_Message(arr,temparr,mid+1,end) ;
        Merge_Sort(arr,temparr,start,mid,end) ;
    }
}

int main(void)
{
    int i,arr[] = {23,56,9,75,18,42,11,67};
    int n = sizeof(arr)/sizeof(arr[0]) ;
    int temp[8] ;

    Sort_Message(arr,temp,0,n-1) ;

    for(i=0;i<n;++i)
        printf("%d ",arr[i]) ;
    printf("\n") ;
    return 0 ;
}

