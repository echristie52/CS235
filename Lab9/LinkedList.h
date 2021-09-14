#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include "LinkedListInterface.h"

using namespace std;

template<typename T> //template class, like Vector can adapt to data type given
class LinkedList : public LinkedListInterface<T>
{
private:
	struct Node{
		Node(T val){
			value = val;
			next = NULL;
		}
		T value;
		Node *next;
	};

	Node *head;

public:

	LinkedList(void) {
		head = NULL;
	}; 
	~LinkedList(void) {clear();};

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	void insertHead(T value){
		//checks for duplicates
		if(!find(value)){
			Node *n = new Node(value);
			n->next = head;
			head = n;
		}
	}

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	void insertTail(T value){
		if(!find(value)){
			if(head == NULL){
				insertHead(value);
			}
			else{
				Node *ptr = head;
				while(ptr->next != NULL){ //iterated to tail
					ptr = ptr->next;
				}
				ptr->next = new Node(value);
			}
		}
	}

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	void insertAfter(T value, T insertionNode){
		if(find(insertionNode) && !find(value)){ //only searches if in list
			Node *ptr = head;
			while(ptr->value != insertionNode){ //iterates until finds value
				ptr = ptr->next;
			}

			Node *entry = new Node(value);
			entry->next = ptr->next; //links entry to following node
			ptr->next = entry; //links pointer to new entry
		}

	}

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	void remove(T value){
		if(find(value)){ //included in list
			Node *ptr = head;
			Node *deleter = NULL;

			if(head->value == value){ //if head, redefines head and deletes old memory
				head = head->next; //head moves down one
				delete ptr;
			}
			else{
				while(ptr->next->value != value){ //iterates to node before node to remove
					ptr = ptr->next;
				}

				deleter = ptr->next; //deleter points to node to remove
				ptr->next = deleter->next; //reroutes around node
				delete deleter;
			}
		}
		//value not in list
	}

	/*
	clear

	Remove all nodes from the list.
	*/
	void clear(){
		while(head != NULL){ //while items in list
			remove(head->value); //deletes head until all nodes are gone
		}
	}

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	T at(int index){
		if(index < 0 || index >= size()){ //throws error - FIXME
			throw out_of_range("out of range");			
		}

		Node *itr = head;
		for(int i = 0; i < index; i++){			
			itr = itr->next; //moves to next value
		}
		return itr->value;
	}

	/*
	size

	Returns the number of nodes in the list.
	*/
	int size(){
		Node *ptr = head;
		int count = 0;

		while(ptr != NULL){ //iterates through each node (if head == null, returns 0)
			ptr = ptr->next;
			count++;
		}
		return count;
	}

	/*
	toString
	
	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	string toString(){
		stringstream ss;

		Node *itr = head;
		while(itr != NULL){
			ss << itr->value;
			if(itr->next != NULL){ //comma separated list, with final endline
				ss << " ";
			}

			itr = itr->next; //iterates to next node
		}

		return ss.str(); //if head is NULL, returns empty string
	}

	bool find(T value){
		Node *itr = head;
		while(itr != NULL){
			if(itr->value == value){
				return true;
			}
			itr = itr->next;
		}
		return false;
	}

};
