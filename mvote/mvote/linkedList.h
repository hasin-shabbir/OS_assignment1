#ifndef linkedList_hpp
#define linkedList_hpp
#include <string>

using namespace std;

//structure of the entire voter profile
struct voterProfile {
	string fName;
	string lName;
	string RIN;
	string postalCode;
	bool voted;
};

//Node of the linked list (chain/bucket) of voters in the hashtable
class Node {
private:
	voterProfile element; //voter profile of the node
	Node* next; //next pointer of the node
	friend class linkedList; //make linkedList class the friend of the Node class
public:
	string getRIN() { return element.RIN; };//returns RIN of a voter profile/node
};

//linkedList (chain/bucket) of hashtable
class linkedList {
private:
	Node* head;//Head of the LinkedList
public:
	linkedList();//constructor of the LinkedList class
	~linkedList();//destructor of the LinkedList class
	bool empty() const;//method to check if the linked list is empty
	const voterProfile front() const; //method to return the voter profile at the front of the linked list
	voterProfile* getNode(string RIN) const; //method to return a specific voter profile pointer using the RIN
	Node* getNodePointer(string RIN) const;  //method to return the pointer to the node containing the voter profile with the specified RIN
	void addFront(const voterProfile& e); //method to add a node to the front of the linked list
	void removeFront(); //method to remove a node from the front of the linked list
	bool removeNode(string RIN); //remove a specific node/voter profile specified by its RIN
	void printAll(); //print all the nodes/voter profiles in the linked list
	bool modifyVote(string key); //modify the status of a voter to "YES" and report if successfully modified
};

#endif