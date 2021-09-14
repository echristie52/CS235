#include <iostream>

using namespace std;

int fibonacci(int n){
	if(n < 2){
		return 1;
	}
	else{
		return (fibonacci(n - 1) + fibonacci(n - 2));
	}
}

int main(int argc, char* argv[]){
	int i;

	for(i = 0; i < 5; i++){

	}
	cout << i << endl;
}