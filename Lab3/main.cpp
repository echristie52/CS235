#include <vector>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//Part 2
void ReadToVector(string filename){
	vector<string> tokens;	
    set <string> unique;
    string next_line;
	ifstream in(filename);
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for(auto &c : token) { // Remove Punctuation      
                if (isalpha(c)) {
                    nopunct +=c;       
                }
            }
	          tokens.push_back(nopunct);
		    // cout << token<<endl;
	    }
    }
	in.close();

	ofstream outFile(filename + "_vector.txt");
	for(int i = 0; i < tokens.size(); i++){
		outFile << tokens.at(i) << endl;
	}
	outFile.close();
	//cout << "Size: " << tokens.size() << endl;
}

void printMap(map<string,string> wordMap, string filename){
	map<string,string>::iterator it;
	ofstream outFile(filename + "_map.txt");
	for(it = wordMap.begin(); it != wordMap.end(); it++){
		outFile << it->first << ", " << it->second << endl;
	}
}

int main(int argc, char* argv[]){
	
	vector<string> tokens;	
    set <string> unique;
    string next_line;  // Each data line
	string filename = argv[1];
    ifstream in(filename);
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for(auto &c : token) { // Remove Punctuation      
                if (isalpha(c)) {
                    nopunct +=c;       
                }
            }
	          tokens.push_back(nopunct);
		        unique.insert(nopunct);
		    // cout << token<<endl;
	    }
    }
	in.close();
    cout << "Number of words "<<tokens.size()<<endl;
    cout << "Number of unique words "<<unique.size()<<endl;
	ofstream outFile(filename + "_set.txt");
    for (set<string>::iterator it=unique.begin(); it!=unique.end(); ++it){
        //cout << ' ' << *it;
		outFile << ' ' << *it;
	}
	outFile.close();

	ReadToVector(filename);


	map<string,string> wordMap;
	string last = "";
	for(vector<string>::iterator it=tokens.begin(); it!=tokens.end(); ++it){
		wordMap[last] = *it;
		last = *it;
	}
	printMap(wordMap, filename); //part 3

	
	//part four
	string state = "";
	for(int i = 0; i < 100; i++){
  		cout << wordMap[state] << " ";
  		state = wordMap[state];
	}
	cout << endl << endl;

	//part 5
	map<string, vector<string> > wordMapVector;
	state = "";
	for(vector<string>::iterator it=tokens.begin(); it !=tokens.end(); it++) {
		wordMapVector[state].push_back(*it);
		state = *it;
	}
	srand(time(NULL)); // this line initializes the random number generated
                   // so you dont get the same thing every time
	state = "";
	for (int i = 0; i < 100; i++) {
	int ind = rand() % wordMapVector[state].size();
		cout << wordMapVector[state][ind] << " ";
		state = wordMapVector[state][ind];
	}
	cout << endl << endl;

	//PArt 6
	map<list<string>, vector<string> > wordmap;
	list<string> phrase;
	const int M = 3;
	for (int i = 0; i < M; i++) {
		phrase.push_back("");
	}
							
	for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
		wordmap[phrase].push_back(*it);
		phrase.push_back(*it);
		phrase.pop_front();
	}

	phrase.clear();
	for (int i = 0; i < M; i++) {
		phrase.push_back("");
	}
	for (int i = 0; i < 100; i++) {
		int ind = rand() % wordmap[phrase].size();
		cout << wordmap[phrase][ind]<<" ";
		phrase.push_back(wordmap[phrase][ind]);
		phrase.pop_front();
	}





    cout << endl;
}