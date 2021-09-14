#include <iostream>

using namespace std;

bool linearSearch(int *L, int len, int n){ //Big O search, goes through all the indeces potentially, increases linearly
	for(int i = 0; i < len; i++){
		if(L[i] == n)
			return true;
	}
	return false;
}

//binarySearch is much faster if data is sorted
//unfortunately takes longer to sort and then search than just to linearly search
bool binarySearch(int *L, int min, int max, int n){ //increases by 1 each time size doubles. Log(n)
	int middle = (max + min) / 2;

	//base cases
	if(min > max)
		return false;
	if(L[middle] == n)
		return true;
	if(L[middle] > n){
		binarySearch(L, min, middle -1, n);
	}
	else{
		binarySearch(L, middle +1, max, n);
	}
	return false;
}

//O(n^2) because 2 nested loops = n^2
//always O(n^2), doesn't change
void selectionSort(int *theArray, int len){
	int i, j;
	int min, tmp;

	for(int i = 0; i < len-1; i++){ //increases sorted list by 1
		min = i;
		for(j = i+1; j < len; j++){ //searches through unsorted
			if(theArray[j] < theArray[min])
				min = j;
		}
	//performs the swap
	tmp = theArray[i];
	theArray[i] = theArray[min];
	theArray[min] = tmp;
	}

	
}

//Avg/worst case: O(n^2) - missorted or sorted backwards
//best case: O(n) - already sorted, just access through
//better than selection sort by this notation
void insertionSort(int *theArray, int len){
	int temp;
	int trace;
	for(int i = 0; i < len; i++){ //outer loop, increases sorted area by one
	trace = i;
		for(int j = i-1; j >=0; j--){ //goes through sorted section to find where to insert
			if(theArray[j] > theArray[trace]){ //swaps until fits
				temp = theArray[trace];
				theArray[trace] = theArray[j];
				theArray[j] = temp;
				trace--;
			}
		}
	}
}

//from Prof Crandall, much more elegant
void insertionSortProf(int *theArray, int len){
	int i,j;
	int item;

	for(i = 1; i < len; i++){
		j=i;
		item = theArray[j];

		while((j > 0) && (theArray[j-1] > item)){
			theArray[j] = theArray[j-1];
			j--;
		}
		theArray[j] = item;
	}
}

int partition(int *L){ 
	//'medium of three' (first, middle, last)
	//sorts and replaces them (in order)
	//puts pivot into 0 index

	//pointers search to find violations in partition
		//big point starts on left, if bigger than pivot, waits to swap
		//small starts on right, if small than pivot, waits to swap
		//when both have stopped, swap
		//pointers continue
	//once pass each other, they are done
		//all left of small are small list, all right of big are big list
	//O(n) only n checks 
	//swap pivot and small --> small, pivot, big (all in order, no need to concatenate)

	

}


//using partition, O(n*log(n))
int* quickSort(int *L, int min, int max){ //min/max of bounds we are working with
	//function partition divids list into small and big lists (does all the work)
	//recursively calls to the small and big lists (quicksort)
		//continually divides, until just one in each call - cutting is log(n) for big O
	//concatenate function to sticks them back together (will be in order)

	//base case
	//if(L.size() > 3){
		//run standard sorting

	//}
	//else sort 3; (will be last set of 3)

	return L;
}

void mergeSort(int *L){
	/*if(L.size() > 1){
		split(List, left, right) //creates two arrays based on index, increased memory needs
		mergesort(left);
		mergesort(right);
		merge(left, right, L); //rewrites over L, compares between vectors, adds lower and increments that vector (comparing secon there with other first) until all of both vectors are added.
	}


	*/
}



int main(int argc, char* args[]){
	int L[10] = {1,2,3,4,5,6,7,8,9,10};
	int unsorted[10] = {4,7,1,3,2,9,10,6,8,5};

	//selectionSort(unsorted, 10);
	insertionSort(unsorted, 10);

	for(int i = 0; i < 10; i++){
		cout << unsorted[i] << " ";
	}
	cout << endl;
}