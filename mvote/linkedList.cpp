#include "linkedList.h"

#include <iostream>
using namespace std;

linkedList::linkedList() :head(NULL) {};//initialize the head of the linked list to NULL pointer

linkedList::~linkedList() { while (!empty())removeFront(); } //remove nodes until the list is empty

bool linkedList::empty() const { return head == NULL; } //if head points to NULL pointer, return true (meaning the list is empty)

const voterProfile linkedList::front() const
{
	if (!empty()) //if the list is not empty
		return head->element;//return the voter profile at the head node
	else
		throw out_of_range("The List is empty "); //if list is empty, throw an exception
}

voterProfile* linkedList::getNode(string key) const {
    
    if (!empty()) { //if the list if not empty
        Node* node = this->head; //start from the head of the linked list
        while (node->element.RIN != key) { //search for the node with the specific RIN
            node = node->next; //continue traversing the linked list until the node with the specific RIN is found
            if (node != NULL) {
                continue;
            }
            else {
                break;
            }
        }
       
        if (node != NULL) {
            return &(node->element); //return the pointer to the voterProfile with the specific RIN
        }
        else {
            return NULL; //if no node found, return NULL signifying the same
        }
        
    }
    else
        return NULL; //if list is empty, return NULL signifying the same
}

Node* linkedList::getNodePointer(string key) const {
    if (!empty()) {
        Node* node = this->head; //start from the head of the linked list
        while (node->element.RIN != key) { //search for the node with the specific RIN
            node = node->next; //continue traversing the linked list until the node with the specific RIN is found
            if (node != NULL) {
                continue;
            }
            else {
                break;
            }
        }

        if (node != NULL) {
            return (node); //return the node containing the voter profile with the specific RIN
        }
        else {

            return NULL; //if no node found, return NULL signifying the same
        }

    }
    else
        throw out_of_range("The List is empty!\n"); //if list is empty, throw an exception
}

void linkedList::addFront(const voterProfile& e)
{
	Node* v = new Node; //create a new node
	v->element.fName = e.fName; //assign the first name to the new voter profile
    v->element.lName = e.lName; //assign the last name to the new voter profile
    v->element.RIN = e.RIN; //assign the RIN to the new voter profile
    v->element.postalCode = e.postalCode; //assign the postal code to the new voter profile
    v->element.voted = e.voted; //assign the voted status to the new voter profile

	v->next = head; //the head is assigned to the next pointer of the new node 
	head = v; //the new node is made the head node
}

void linkedList::removeFront() {
	Node* old = head; //assign head to a new node as old
	if (head == NULL) {//if the list is empty
		cout << "linked list was empty"<<endl;//output a message reporting the list was empty
		exit(13);//exit the program
	}
	head = old->next;//assign the next node of the old head to the head pointer
	delete old; //delete the old head
}

bool linkedList::removeNode(string RIN) {


    // Store head node
    Node* temp = this->head;
    Node* prev = NULL;

    // If head node itself holds the voter profile to be removed
    if (temp != NULL && temp->element.RIN == RIN){
        this->head = temp->next; // Change the head

        delete temp;  // delete old head
        return true; //report successful removal
    }

    // Else Search for the node with the voter profile to be deleted
    else
    {
        //keep traversing the hashtable until the relevant node is found, keep track of the previous node for linking purposes
        while (temp != NULL && temp->element.RIN != RIN)
        {
            prev = temp;
            temp = temp->next;
        }

        // If voter profile was not present in linked list, report as such
        if (temp == NULL){
            cout << "No such record with the specified RIN found\n";
            return false;
        }

        // Unlink the node from linked list
        prev->next = temp->next;

        // Free memory
        delete temp;
        // Report successfull removal of node
        return true;
    }
}

//print the entire linked list by traversing each node and printing its voter profile
void linkedList::printAll() {
    Node* temp = this->head;
    if (temp == NULL) {
        cout << "empty list\n";
    }
    else {
        while (temp != NULL) {
            cout << temp->element.fName << ","
                << temp->element.lName << ","
                << temp->element.postalCode << ","
                << temp->element.RIN << ","
                << temp->element.voted << "->";
            temp = temp->next;
        }
        cout << "|||\n";
    }
}

//change the status of a voter to "YES"
bool linkedList::modifyVote(string key) {
    voterProfile* vp = this->getNode(key); //find the voter profile to be registered as voted
    if (vp != NULL) { //if such a node is found
        if (!(vp->voted)) { //and if they have not voted
            vp->voted = true; //change their statues to "YES" (signified by true)
            cout << "Voter ID: "<< key << " status changed to \"YES\"\n";
            return true; //report successful change of status
        }
        else { //if the voter has already voted, report as such
            cout << "Voter ID: " << key << " status already set to \"YES\"\n";
            return false;
        }
    }
    else { // if the voter profile is not found, report as such
        cout << "Voter ID: " << key << " record not found\n";
        return false;
    }
}
