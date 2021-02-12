#ifndef votedLinkedList_hpp
#define votedLinkedList_hpp
#include <string>

#include "linkedList.h"

using namespace std;


class votedNode {
private:
	Node* voterProfilePtr;
	votedNode* votedNextPtr; //next pointer of the node
	friend class votedLinkedList; //make linkedList class the friend of the Node class
};

//linkedList

class votedLinkedList {
private:
	votedNode* head;//Head of the LinkedList
	int size;
public:
	votedLinkedList();//constructor of the LinkedList class
	~votedLinkedList();//destructor of the LinkedList class
	bool empty() const;//method to check if the linked list is empty
	const votedNode* front() const; //method to return the front of the linked list
	votedNode* getNode(Node* e) const; //method to return the node of the linked list with a specific RIN
	void addFront(Node* e); //method to add a node to the front of the linked list
	void removeFront(); //method to remove a node from the front of the linked list
	bool removeNode(Node* e); //remove a specific node
	void printAll();//print all nodes
	void printRegisteredVoter(); //prints all the voters who have voted in that zipcode
	int getSize();//returns number of voters having voted yes in the postal code
};

#endif
