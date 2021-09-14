#include "Pathfinder.h"


	
	Pathfinder::Pathfinder(){ //constructor, initializes maze to 1's
		int maze[5][5][5];
		vector<string> path;
		for(int x = 0; x < 5; x++){
			for(int y = 0; y < 5; y++){
				for(int z = 0; z < 5; z++){
					maze[x][y][z] = 1;
				}
			}
		}
		
	}
	//Part 1-----------------------------------------------------------------------------------
	/*
	* toString
	*
	* Returns a string representation of the current maze. Returns a maze of all 1s if no maze
	* has yet been generated or imported.
	*
	* A valid string representation of a maze consists only of 125 1s and 0s (each separated
	* by spaces) arranged in five 5x5 grids (each separated by newlines) with no trailing newline. A valid maze must
	* also have 1s in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).
	*
	* Cell (0, 0, 0) is represented by the first number in the string representation of the
	* maze. Increasing in x means moving toward the east, meaning cell (1, 0, 0) is the second
	* number. Increasing in y means moving toward the south, meaning cell (0, 1, 0) is the
	* sixth number. Increasing in z means moving downward to a new grid, meaning cell
	* (0, 0, 1) is the twenty-sixth cell in the maze. Cell (4, 4, 4) is represented by the last number.
	*
	* Returns:		string
	*				A single string representing the current maze
	*/
	string Pathfinder::toString() const{
		int len = 5;
		string output;

		for(int x = 0; x < len; x++){
			for(int y = 0; y < len; y++){
				for(int z = 0; z < len; z++){
					output += to_string(maze[x][y][z]);

					if(z < len - 1){
						output += " ";
					}
				}
				output += "\n";
			}
			if(x < len - 1)	output += "\n";
		}

		return output;
	}

	/*
	* createRandomMaze
	*
	* Generates a random maze and stores it as the current maze.
	*
	* The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
	* in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).  The generated maze may be
	* solvable or unsolvable, and this method should be able to produce both kinds of mazes.
	*/
	void Pathfinder::createRandomMaze(){
		int len = 5;

		for(int z = 0; z < len; z++){ //z-dimension, layers
			for(int y = 0; y < len; y++){ //y-dimension, rows
				for(int x = 0; x < len; x++){ //x-dimension, columns
					maze[z][y][x] = rand() % 2;
				}
			}
		}
		maze[0][0][0] = 1;
		maze[4][4][4] = 1;
	}
	//-----------------------------------------------------------------------------------------

	//Part 2-----------------------------------------------------------------------------------
	/*
	* importMaze
	*
	* Reads in a maze from a file with the given file name and stores it as the current maze.
	* Does nothing if the file does not exist or if the file's data does not represent a valid
	* maze.
	*
	* The file's contents must be of the format described above to be considered valid.
	*
	* Parameter:	file_name
	*				The name of the file containing a maze
	* Returns:		bool
	*				True if the maze is imported correctly; false otherwise
	*/
	bool Pathfinder::importMaze(string file_name){
		ifstream in;
		in.open(file_name);
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
		else{ 
			return false;
		}

		//validate begins and ends
		if(numQ.front() == 0 || numQ.back() == 0){
			return false;
		}

		
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
	//-----------------------------------------------------------------------------------------

	//Part 3-----------------------------------------------------------------------------------
	/*
	* solveMaze
	*
	* Attempts to solve the current maze and returns a solution if one is found.
	*
	* A solution to a maze is a list of coordinates for the path from the entrance to the exit
	* (or an empty vector if no solution is found). This list cannot contain duplicates, and
	* any two consecutive coordinates in the list can only differ by 1 for only one
	* coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
	* in the solution. Each string in the solution vector must be of the format "(x, y, z)",
	* where x, y, and z are the integer coordinates of a cell.
	*
	* Understand that most mazes will contain multiple solutions
	*
	* Returns:		vector<string>
	*				A solution to the current maze, or an empty vector if none exists
	*/
	vector<string> Pathfinder::solveMaze(){
		path.clear();
		findPath(0,0,0);
		
		for(int x = 0; x < 5; x++){
			for(int y = 0; y < 5; y++){
				for(int z = 0; z < 5; z++){
					if(maze[x][y][z] == 2){
						maze[x][y][z] = 1;
					}
				}
			}
		}
		return path;
	}

	bool Pathfinder::findPath(int x, int y, int z){
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
		return true;
	}

	//possible path
	maze[x][y][z] = 2;
	bool right = findPath(x, y, z+1);
	bool left = findPath(x, y, z-1);
	bool up = findPath(x, y+1, z);
	bool down = findPath(x, y-1, z);
	bool in = findPath(x+1, y, z);
	bool out = findPath(x-1, y, z);
	if(right || down || in || left || up || out){ //right, left, up, down, in, out
		return true;
	}
	else{
		path.pop_back();
		return false;
	}


	return false;
}



	//-----------------------------------------------------------------------------------------