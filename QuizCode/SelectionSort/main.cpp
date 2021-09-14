#include<iostream>
#include<vector>

using namespace std;

void selectionSort(vector<int> &nums){
	int min, temp;
	for(int i = 0; i < nums.size() - 1; i++){
		min = i;
		for(int j = i + 1; j < nums.size(); j++){
			if(nums.at(j) < nums.at(min)){
				min = j;
			}
		}
		temp = nums.at(i);
		nums.at(i) = nums.at(min);
		nums.at(min) = temp;
	}
}

int main(int argc, char* argv[]){
	vector<int> numericals = {23,14,65,3,19,2,71,12,8,61,5,25};

	selectionSort(numericals);

	for(int i = 0; i < numericals.size(); i++){
		cout << numericals.at(i);
		if(i < numericals.size() - 1){
			cout << ", ";
		}
	}
	cout << endl;


	return 0;
}