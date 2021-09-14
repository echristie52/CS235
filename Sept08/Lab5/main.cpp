#include <iostream>

using namespace std;

int main(){
	int left = 0;
	int right = 4;
	int insertIndex = 5;
	int aptr[5] = {0,1,25,3,4};
	
	cout << "Begin median" << endl;
		if(left < 0 || left > right || right >= insertIndex || insertIndex == 0){ //input check
			cout << "Failed input check" << endl;
		}
		cout << "Passed input check" << endl;

		int middle = (left + right) / 2;
		int temp;

		if(aptr[left] > aptr[middle]){ //bubblesort left and middle
			temp = aptr[left];
			aptr[left] = aptr[middle];
			aptr[middle] = temp;
			cout << "Left/Middle swap" << endl;
		}
		if(aptr[middle] > aptr[right]){ //bubblesort middle and right
			temp = aptr[middle];
			aptr[middle] = aptr[right];
			aptr[right] = temp;
			cout << "Middle/Right swap" << endl;
		}
		if(aptr[left] > aptr[middle]){ // repeat bubblesort left and middle
			temp = aptr[left];
			aptr[left] = aptr[middle];
			aptr[middle] = temp;
			cout << "Left/Middle swap" << endl;
		}
		
		cout << "Middle: " << middle << endl;

}