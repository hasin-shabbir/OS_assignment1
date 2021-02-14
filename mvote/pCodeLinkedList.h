#ifndef pCodeLinkedList_hpp
#define pCodeLinkedList_hpp
#include <string>
#include "votedLinkedList.h"
using namespace std;

class pCodeNode {
private:
	string pCode; //postal code
	votedLinkedList* votersList; //pointer to linked list of registered votes in the particular postal code
	pCodeNode* nextPtr; //next pointer of the node
	friend class postalCodeLinkedList; //make postalCodeLinkedList class the friend of the Node class
};

//structure used for ordered output by number of votes cast per postal code
struct sortedStruct {
	string pCode;
	int numVoters;
};

//linked List of postal codes with votes cast
class postalCodeLinkedList {
private:
	pCodeNode* head;//Head of the LinkedList
	int size; //number of postal codes where votes have been cast

	void swapArr(sortedStruct& elOne, sortedStruct& elTwo); //helper function to swap two elements
	void heapSort(sortedStruct* arr); //function to sort list in descending order of votes cast using heapsort
	void heapify(sortedStruct* arr,int n, int i); //function to create a max heap


public:
	postalCodeLinkedList();//constructor of the postalCodeLinkedList class
	~postalCodeLinkedList();//destructor of the postalCodeLinkedList class
	bool empty() const;//method to check if the postalCodeLinkedList is empty
	const string front() const; //method to return the postal code at the front of the linked list
	votedLinkedList* getNode(string pCode) const; //method to return the linked list of votes cast in the specified postal code
	pCodeNode* getNodePointer(string pCode) const; //method to return the pointer to the node of the specified postal code
	void addFront(string pCode, Node* e); //method to add a voter who has cast vote to the front of the linked list using the postal code
	void removeFront(); //method to remove a node from the front of the linked list
	bool removeNode(string pCode); //remove a specific node with a specific postal code
	void printAll(); //print all the nodes in the postal code linked list
	bool registerVoter(string postalCode,Node* voterNode); //add a voter to the linked list of postal code
	void printVotersZipCode(string key); //print all the voters who have cast vote in a specific zipcode
	bool removeVoter(string pCode, Node* e); //remove a voter from the linked list of postal codes
	void descendingOrder(); //sort the postal code linked list in descending order of number of votes cast per postal code, and output the result
};

#endif