#include "TodoList.h"

TodoList::TodoList(){ //constructor
}	

TodoList::~TodoList(){ //de-constructor
}	
	    /*    
		*   Adds an item to the todo list with the data specified by the string "_duedate" and the task specified by "_task"    */    
			
void TodoList::add(string _duedate, string _task){
	ReadInFile();

	dates.push_back(_duedate);
	tasks.push_back(_task);

	PrintToFile();
}   
		/*    
		*   Removes an item from the todo list with the specified task name    *    *   Returns 1 if it removes an item, 0 otherwise    */    
			
int TodoList::remove(string _task){
	ReadInFile();

	for(int i = 0; i < tasks.size(); i++){
		if(_task.compare(tasks.at(i)) == 0){
			dates.erase(dates.begin() + i);
			tasks.erase(tasks.begin() + i);

			PrintToFile();
			return 1;	//task removed
		}
	}
	return 0; //task wasn't found
}    
		/*    
		*   Prints out the full todo list to the console    */    
			
void TodoList::printTodoList(){
	ReadInFile();

	for(int i = 0; i < dates.size(); i++){
		cout << dates.at(i) << endl;
		cout << tasks.at(i) << endl;
	}
}    
		/*    
		*   Prints out all items of a todo list with a particular due date (specified by _duedate)    */    
void TodoList::printDaysTasks(string _date){
	ReadInFile();
	cout << _date << endl;

	for(int i = 0; i < dates.size(); i++){
		if(_date.compare(dates.at(i)) == 0){
			cout << tasks.at(i) << endl;
		}
	}
}

void TodoList::ReadInFile(){	//reads current todolist from file
	ifstream readIn("TODOList.txt");

	string input;
	while(readIn.is_open() && !readIn.eof()){
		getline(readIn, input);	//reads in date
		if(input.length() > 1){
			dates.push_back(input);
		}

		getline(readIn, input);	//reads in task
		if(input.length() > 0){
			tasks.push_back(input);
		}
	}

	readIn.close();
}

void TodoList::PrintToFile(){	//returns the list to the file
	ofstream toFile("TODOList.txt");
	
	for(int i = 0; i < dates.size(); i++){
		toFile << dates.at(i) << endl;
		toFile << tasks.at(i) << endl;
	}
}
