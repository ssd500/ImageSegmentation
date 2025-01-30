/* A sorting based program to count pairs with difference k*/
#include <iostream>
#include<stdlib.h>
#include <algorithm>
using namespace std;

/* Standard binary search function */
int binarySearch(int arr[], int low, int high, int x)
{
	if (high >= low)
	{
		int mid = low + (high - low)/2;
		if (x == arr[mid])
			return mid;
		if (x > arr[mid])
			return binarySearch(arr, (mid + 1), high, x);
		else
			return binarySearch(arr, low, (mid -1), x);
	}
	return -1;
}

/* Returns count of pairs with difference k in arr[] of size n. */
/*int countPairsWithDiffK(int arr[], int n, int k)
{
	int count = 0, i;
	sort(arr, arr+n); // Sort array elements

	// Pick a first element point
	for (i = 0; i < n-1; i++)
		if (binarySearch(arr, i+1, n-1, arr[i] + k) != -1)
			count++;

	return count;
}*/
int find_count(int A[],int n,int k)
{
    int c=0;    
    sort(A,A+n);
    for(int i=0;i<n-1;i++)
     {
        int j=i+1;
        while(j<n)
         {
           if(abs(A[i]-A[j])>k)
              break;
           else if(abs(A[i]-A[j])==k)
              c++;
           j++;
         }  
     }
    
    return c; 
}
// Driver program 
int main()
{
	int arr[] = {1, 5, 3, 4, 2};
	int n = sizeof(arr)/sizeof(arr[0]);
	int k = 3;
//	cout << "Count of pairs with given diff is " << countPairsWithDiffK(arr, n, k);
    cout<<find_count(arr,n,k);
	return 0;
}

