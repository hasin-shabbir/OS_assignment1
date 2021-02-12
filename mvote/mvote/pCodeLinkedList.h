#ifndef pCodeLinkedList_hpp
#define pCodeLinkedList_hpp
#include <string>
#include "votedLinkedList.h"
using namespace std;


class pCodeNode {
private:
	string pCode;
	votedLinkedList* votersList; //pointer to voted linked list comes here
	pCodeNode* nextPtr; //next pointer of the node
	friend class postalCodeLinkedList; //make linkedList class the friend of the Node class
};
struct sortedStruct {
	string pCode;
	int numVoters;
};
//linkedList

class postalCodeLinkedList {
private:
	pCodeNode* head;//Head of the LinkedList
	void sorter(postalCodeLinkedList& pCodeLL, pCodeNode*);
	void swapArr(sortedStruct& elOne, sortedStruct& elTwo);
	int size;

public:
	postalCodeLinkedList();//constructor of the LinkedList class
	~postalCodeLinkedList();//destructor of the LinkedList class
	bool empty() const;//method to check if the linked list is empty
	const string front() const; //method to return the front of the linked list
	votedLinkedList* getNode(string pCode) const; //method to return the node of the linked list with a specific RIN
	pCodeNode* getNodePointer(string pCode) const; //method to return the node of the linked list with a specific RIN

	void addFront(string pCode, Node* e); //method to add a node to the front of the linked list
	void removeFront(); //method to remove a node from the front of the linked list
	bool removeNode(string pCode); //remove a specific node
	void printAll();
	bool modifyVote(string key);
	bool registerVoter(string postalCode,Node* voterNode);
	void printVotersZipCode(string key);
	bool removeVoter(string pCode, Node* e);
	void descendingOrder();
	
	//removeVoter (makes use of remove node in votedLinkedList)
	//addVoter (makes use of addFront if no such PCode, addFront of votedLinkedList in all cases)
};

#endif