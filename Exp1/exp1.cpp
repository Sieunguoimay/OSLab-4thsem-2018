//
//											EXPERIMENT 1
//
//AIM:- Write a program for bubble sort in C on linux Operating System, Compile it
//		using gcc
//
//CODE:-
	
#include<iostream>

//Sorting function using bubble-sort algorithm
void bubble_sort(int*arr, int n){
	for(int i = 0; i<n-1; i++){
		for(int j = i; j<n-1; j++){
			if(arr[j]>arr[j+1]){
				//swap 2 adjecient elements in the array
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
//main function
int main(){
	//the given array
	int arr[]={5,1,8,6,7,10},n = 6;

	//function call
	bubble_sort(arr,n);

	//display the array
	for(int i = 0; i<n; i++)
		std::cout<<arr[i]<<" ";
	return 0;
}
