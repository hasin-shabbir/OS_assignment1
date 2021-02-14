#ifndef votedLinkedList_hpp
#define votedLinkedList_hpp
#include <string>

#include "linkedList.h"

using namespace std;

class votedNode {
private:
	Node* voterProfilePtr; //pointer to the node of the voter
	votedNode* votedNextPtr; //next pointer of the node
	friend class votedLinkedList; //make votedLinkedList class the friend of the Node class
};

//votedLinkedList
class votedLinkedList {
private:
	votedNode* head;	//Head Node of the LinkedList
	int size;	//size (number of voters) of the LinkedList
public:
	votedLinkedList();//constructor of the votedLinkedList class
	~votedLinkedList();//destructor of the votedLinkedList class
	bool empty() const;//method to check if the linked list is empty
	const votedNode* front() const; //method to return the voter node at the front of the linked list
	votedNode* getNode(Node* e) const; //method to return the node of the voted linked list with a specific RIN
	void addFront(Node* e); //method to add a voter who has cast their vote to the front of the linked list
	void removeFront(); //method to remove a voter (node) from the front of the voted linked list
	bool removeNode(Node* e); //remove a specific node from the voted linked list
	void printAll();//print all nodes in the voted linked list
	void printRegisteredVoter(); //prints all the voters in the linked list
	int getSize();	//returns number of voters in the linked list
};

#endif
