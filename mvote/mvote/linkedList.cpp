#include "linkedList.h"

#include <iostream>
using namespace std;

linkedList::linkedList() :head(NULL) {};//initialize the head of the linked list to NULL pointer

linkedList::~linkedList() { while (!empty())removeFront(); } //remove nodes until the list is empty

bool linkedList::empty() const { return head == NULL; } //if head points to NULL pointer, return true

const voterProfile linkedList::front() const
{
	if (!empty()) //if the list is not empty
		return head->element;//return the element at the head node
	else
		throw out_of_range("The List is empty "); //if list is empty, throw exception
}

voterProfile* linkedList::getNode(string key) const {
    
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
            return &(node->element); //return the voterProfile with the specific RIN
        }
        else {
 
            return NULL; //if no node found, return
        }
        
    }
    else
        throw out_of_range("The List is empty!\n"); //if list is empty, throw exception
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
            return (node); //return the voterProfile with the specific RIN
        }
        else {

            return NULL; //if no node found, return
        }

    }
    else
        throw out_of_range("The List is empty!\n"); //if list is empty, throw exception
}

void linkedList::addFront(const voterProfile& e)
{
	Node* v = new Node; //create a new node
	v->element.fName = e.fName; //assign the element to be added to the element of the new node
    v->element.lName = e.lName; //assign the element to be added to the element of the new node
    v->element.RIN = e.RIN; //assign the element to be added to the element of the new node
    v->element.postalCode = e.postalCode; //assign the element to be added to the element of the new node
    v->element.voted = e.voted; //assign the element to be added to the element of the new node

	v->next = head; //the head is assigned to the next pointer of the new node 
	head = v; //the new node is made the head node
}

void linkedList::removeFront() {
	Node* old = head; //assign head to a new node as old
	if (head == NULL) {//if the list is empty
		cout << "linked list was empty\n";//output a message telling the list was empty
		exit(13);//exit the program
	}
	head = old->next;//assign the next node of the old head to the head pointer
	delete old; //delete the old head
}

bool linkedList::removeNode(string RIN) {


    // Store head node
    Node* temp = this->head;
    Node* prev = NULL;

    // If head node itself holds
    // the key to be deleted
    if (temp != NULL && temp->element.RIN == RIN)
    {
     
        this->head = temp->next; // Changed head
        string pCode = temp->element.postalCode;

        delete temp;            // free old head
        return true;
    }

    // Else Search for the key to be deleted, 
    // keep track of the previous node as we
    // need to change 'prev->next' */
    else
    {
        while (temp != NULL && temp->element.RIN != RIN)
        {
            prev = temp;
            temp = temp->next;
        }

        // If key was not present in linked list
        if (temp == NULL){
            cout << "No such record with the specified RIN found\n";
            return false;
        }

        // Unlink the node from linked list
        prev->next = temp->next;

        // Free memory
        delete temp;
        return true;
    }
}

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
bool linkedList::modifyVote(string key) {
    voterProfile* vp = this->getNode(key);
    if (vp != NULL) {
        if (!(vp->voted)) {
            vp->voted = true;
            cout << "Voter ID: "<< key << " status changed to \"YES\"\n";
            return true;
        }
        else {
            cout << "Voter ID: " << key << " status already set to \"YES\"\n";
            return false;
        }
    }
    else {
        cout << "Voter ID: " << key << " record not found\n";
        return false;
    }
}
