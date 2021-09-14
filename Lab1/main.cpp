#include <iostream>
#include <string>
#include <cstring>
#include "TodoList.h"
using namespace std;





int main(int argc, char* argv[]) {
	//if-else tree to categorize input and call class functions
	TodoList taskList;
	
	
	
	if(argc > 1){ //arguments are inputted
		if(strcmp(argv[1], "add") == 0){	//add function
			if(argc < 2){ //no arg after "add"
				cout << "No task to add" << endl;
			}
			else{ //call 'add' class function
				taskList.add(argv[2], argv[3]);
			}
		}
		else if(strcmp(argv[1], "remove") == 0){ //remove function
			if(argc < 2){ //no arg after "remove"
				cout << "No task to remove" << endl;
			}
			else{ //call 'remove' class function
				if(taskList.remove(argv[2]) == 0){
					cout << "Task not found" << endl;
				}
			}
		}
		else if(strcmp(argv[1], "printList") == 0){ //print list
			taskList.printTodoList();
		}
		else if(strcmp(argv[1], "printDay") == 0){ //print day's task
			if(argc < 2){ //no arg after "add"
				cout << "No day to print" << endl;
			}
			else{ //calls 'printDay' class function
				taskList.printDaysTasks(argv[2]);
			}
		}
		else{
			cout << "unrecognized command" << endl;
		}
	}
	else{	//no args input
		cout << "Insufficient input" << endl;
	}


    return 0;
}