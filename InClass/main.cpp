#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

void printMap(map<string,int> m){
	map<string,int>::iterator its;

	for(its = m.begin(); its != m.end(); its++){ //index with iterator
		cout << its->first << ", " << its->second << endl;
	}			//first is key			value
}


int main(){
	set<string> st;
	map<string, int> age; //strings pointing to ints

	age["Mark"] = 16; //string key to int value pair
	age["John"] = 15;
	age["Mary"] = 17; //like indexing into map with a key and assign value
	age["Jane"] = 16;
	age["Mark"] = 19; //will overide key-value pair of 16 with 19

	age.erase("Mary"); //erases Mary and 17

	cout << age["Mary"] << endl; //prints vassociates value
		//if doesn't exist, will instantiate "Mary" and assigns a null value
	
	cout << age.find("Mary")->second << endl; //will print 0, but won't create "Mary"

	printMap(age);
	
}