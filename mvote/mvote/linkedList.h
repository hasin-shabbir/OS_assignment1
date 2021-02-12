#ifndef linkedList_hpp
#define linkedList_hpp
#include <string>


using namespace std;

struct voterProfile {
	string fName;
	string lName;
	string RIN;
	string postalCode;
	bool voted;
};

class Node {
private:
	
	voterProfile element;
	Node* next; //next pointer of the node
	friend class linkedList; //make linkedList class the friend of the Node class
public:
	string getRIN() { return element.RIN; };//returns RIN of a node
};

//linkedList

class linkedList {
private:
	Node* head;//Head of the LinkedList
public:
	linkedList();//constructor of the LinkedList class
	~linkedList();//destructor of the LinkedList class
	bool empty() const;//method to check if the linked list is empty
	const voterProfile front() const; //method to return the front of the linked list
	voterProfile* getNode(string key) const; //method to return the node of the linked list with a specific RIN
	Node* getNodePointer(string key) const; 
	void addFront(const voterProfile& e); //method to add a node to the front of the linked list
	void removeFront(); //method to remove a node from the front of the linked list
	bool removeNode(string RIN); //remove a specific node
	void printAll();
	bool modifyVote(string key);
};

#endif