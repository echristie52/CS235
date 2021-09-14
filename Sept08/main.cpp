#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <map>

using namespace std;

map<int,int> myFibMap;
int sumFuncRec(int n){
	if(n ==1){ //base case, what is the first step
		return 1;
	}
	else{ //just needs to reach next case
		return n + sumFuncRec(n - 1);
	}
}

//1 1 2 3 5 8 13 21....
long fibonacci(int n){
	cout << "fibonacci(" << n << ")" << endl;

	map<int,int>::iterator itr = myFibMap.find(n);
	if(itr != myFibMap.end()){
		cout <<"Found " << n << ": " << itr->second << endl;
		return itr->second;
	}

	if(n < 2){
		cout << "base case" << endl;
		myFibMap[n] = 1;
		return 1;
	}

	long answer = fibonacci(n-1) + fibonacci(n-2);
	myFibMap[n] = answer;

	cout << "returned " << answer << " (" << n << ")" << endl;
	return answer;
}



int main(int argv, char *args[]){
	int i = atoi(args[1]);
	cout << fibonacci(i) << endl;
	
	

}