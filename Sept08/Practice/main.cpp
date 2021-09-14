#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

string toNewString(int maze[5][5][5]){
	int len = 5;
	string output;

	for(int x = 0; x < len; x++){
		for(int y = 0; y < len; y++){
			for(int z = 0; z < len; z++){
				output += to_string(maze[x][y][z]) + " ";
			}
			output += "\n";
		}
		output += "\n";
	}

	return output;
}
bool importMaze(string file_name){
	int maze[5][5][5];
	ifstream in(file_name + ".txt");
	int len = 5;
	string next;
	string temp;
	int num;
	queue<int> numQ;

	if(in.is_open()){
		while(getline(in, next)){ //next line
			for(int i = 0; i < next.length(); i++){
				temp = next.at(i);
				if(temp == "0" || temp == "1"){
					num = stoi(temp);
					numQ.push(num);
				}
				else if(temp != " "){
					return false;
				}
			}
		}
		if(numQ.size() != 125){
			return false;
		}
		in.close();
	}
	else return false;

	//numQ checked for accuracy


	
	//updates maze if valid input
	for(int x = 0; x < 5; x++){
		for(int y = 0; y < len; y++){
			for(int z = 0; z < len; z++){
				maze[x][y][z] = numQ.front();
				numQ.pop();
			}
		}
	}

	return true;
}



bool findPath (int maze[5][5][5], int x, int y, int z, vector<string> &path){
	string box = "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
	path.push_back(box);
	
	//base cases
	if(x < 0 || x > 4 || y < 0 || y > 4 || z < 0 || z > 4){ //out of maze
		path.pop_back();
		return false;
	}
	else if(maze[x][y][z] == 0){ //not part of path
		path.pop_back();
		return false;
	}
	else if(maze[x][y][z] == 2){ //already visited
		path.pop_back();
		return false;
	}
	else if(x == 4 && y == 4 && z == 4){
		cout << "maze finished" << endl;
		return true;
	}

	//possible path
	maze[x][y][z] = 2;
	bool right = findPath(maze, x, y, z+1, path);
	bool left = findPath(maze, x, y, z-1, path);
	bool up = findPath(maze, x, y+1, z, path);
	bool down = findPath(maze, x, y-1, z, path);
	bool in = findPath(maze, x+1, y, z, path);
	bool out = findPath(maze, x-1, y, z, path);
	if(right || down || in || left || up || out){ //right, left, up, down, in, out
		cout << path.back() << endl;
		return true;
	}
	else{
		path.pop_back();
		return false;
	}


	return false;
}

vector<string> solveMaze(int maze[5][5][5]){
	vector<string> path;

	if(findPath(maze, 0, 0, 0, path)){
		return path;
	}
	else{
		return path;
	}
}



int main(){
	int maze[5][5][5] = {{	{1, 1, 0, 1, 0},
							{0, 0, 0, 1, 0},
							{1, 1, 1, 1, 0},
							{1, 0, 0, 0, 0},
							{1, 0, 0, 0, 0}},
							
							{{0, 1, 0, 1, 0},
							{0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0},
							{1, 0, 0, 0, 0}},
							
							{{0, 1, 0, 1, 0},
							{0, 1, 0, 0, 0},
							{0, 1, 1, 1, 0},
							{0, 0, 0 ,0, 0},
							{1, 0, 0, 0, 0}},
							
							{{0, 0, 0, 1, 0},
							{0, 0, 0, 0, 0},
							{0, 0, 0, 1, 0},
							{0, 0, 0, 0, 0},
							{1, 0, 0, 0, 0}},
							
							{{0, 0, 0, 1, 0},
							{0, 0, 0, 1, 0},
							{0, 0, 0, 1, 0},
							{0, 0, 0, 0, 0},
							{1, 1, 1, 1, 1}}};
	
	
	vector<string> path = solveMaze(maze);

	for(int i = 0; i < path.size(); i++){
		cout << path.at(i) << endl;
	}


}