#include <iostream>

using namespace std;

bool solveMaze(int x, int y, int maze[10][10]){
    //base cases
    if((x < 0) || (x > 9) || (y < 0) || (y > 9))
        return false; //index out of bounds

    if(maze[x][y] == 0)
        return false; //wall

    if(maze[x][y] == 3)
        return false; //already been there

    if(maze[x][y] ==2)
        return true; //is solveable


    //inductive step
    maze[x][y] = 3; //marks our path
    bool right = solveMaze(x+1, y, maze); //searches one square
    bool left = solveMaze(x-1, y, maze); //in each direction
    bool up = solveMaze(x, y+1, maze);
    bool down = solveMaze(x, y-1, maze);

    if(right || left || up || down) //solveable, some open route
        return true;


    return false;
}

void Maze(){
    int maze[10][10] = {{1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
                        {0, 1, 0, 0, 0, 0, 1, 0, 0, 1},
                        {1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
                        {0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                        {0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
                        {0, 0, 0, 0, 0, 1, 0, 1, 1, 0},
                        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                        {0, 1, 1, 1, 1, 1, 1, 1, 1, 2}};
}



int main() {

    int maze[10][10] = {{1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
                       {0, 1, 0, 0, 0, 0, 1, 0, 0, 1},
                       {1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
                       {0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                       {0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
                       {0, 0, 0, 0, 0, 1, 0, 1, 1, 0},
                       {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                       {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                       {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                       {0, 1, 1, 1, 1, 1, 1, 1, 0, 2}};


    if(solveMaze(0,0,maze)){
        cout << "It worked!" << endl;
    }
    else cout << "Whoops" << endl;
    return 0;
}
