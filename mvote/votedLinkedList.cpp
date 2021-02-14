#include "votedLinkedList.h"
#include <iostream>
using namespace std;

votedLinkedList::votedLinkedList() :head(NULL) { this->size = 0; };//initialize the head of the linked list to NULL pointer, set size to zero

votedLinkedList::~votedLinkedList() { while (!empty())removeFront(); } //remove nodes until the list is empty

bool votedLinkedList::empty() const { return head == NULL; } //if head points to NULL pointer, return true signifying an empty list

const votedNode* votedLinkedList::front() const
{
    if (!empty()) //if the list is not empty
        return head;//return the head node
    else
        throw out_of_range("The List is empty "); //if list is empty, throw an exception
}

votedNode* votedLinkedList::getNode(Node* e) const {

    if (!empty()) { //if list is not empty
        votedNode* node = this->head; //start from the head of the linked list
        while (node->voterProfilePtr != e) { //search for the node pointing to the specific voter
            node = node->votedNextPtr; //continue traversing the linked list until the node pointing to the specific voter
            if (node != NULL) {
                continue;
            }
            else {
                break;
            }
        }

        if (node != NULL) {
            return (node); //return the node pointing to the specific voter
        }
        else {

            return NULL; //if no such node found, return NULL to report as such
        }

    }
    else
        throw out_of_range("The Voted List is empty!\n"); //if list is empty, throw exception
}

void votedLinkedList::addFront(Node* e)
{
    votedNode* v = new votedNode; //create a new node
    v->voterProfilePtr = e; //set this node to point to the voter registered as "YES"
    v->votedNextPtr = head; //the head is assigned to the next pointer of the new node 
    head = v; //the new node is made the head node
    size++; //increment the size count of the linked list
}

void votedLinkedList::removeFront() {
    votedNode* old = head; //assign head to a new node as old
    if (head == NULL) {//if the list is empty
        cout << "voted linked list was empty\n";//output a message reporting the list was empty
        exit(13);//exit the program
    }
    head = old->votedNextPtr;//assign the next node of the old head to the head pointer
    delete old; //delete the old head
}

bool votedLinkedList::removeNode(Node* e) {


    // Store head node
    votedNode* temp = this->head;
    votedNode* prev = NULL;

    // If head node points to the voter profile to be deleted, delete the head node
    if (temp != NULL && temp->voterProfilePtr == e)
    {

        this->head = temp->votedNextPtr; // Changed head
        delete temp;            // free old head
        size--; //decrement the size of the linked list
        return true; //report successful removal
    }

    // Else search for the node pointing to the voter to be removed
    else
    {
        while (temp != NULL && temp->voterProfilePtr != e)
        {
            prev = temp;
            temp = temp->votedNextPtr;
        }

        // If no such node is present in the linked list, report as such
        if (temp == NULL) {
            cout << "No such record with the specified RIN found in voted list\n";
            return false;
        }

        // Unlink the node from linked list
        prev->votedNextPtr = temp->votedNextPtr;

        // Free memory
        delete temp;
        //decrement the size of the linked list
        size--;
        return true; //report successful removal of the node
    }
}

//print all nodes in the voted linked list
void votedLinkedList::printAll() {
    votedNode* temp = this->head;
    if (temp == NULL) {
        cout << "empty list\n";
    }
    else {
        while (temp != NULL) {
            cout << temp->voterProfilePtr->getRIN() << "->";
            temp = temp->votedNextPtr;
        }
        cout << "|||\n";
    }
}

//prints all the voters in the linked list
void votedLinkedList::printRegisteredVoter() {
    //start from the head
    votedNode* temp = this->head;
    //if list is empty, report as such
    if (temp == NULL) {
        cout << "No voters have voted in this ZipCode"<<endl;
    }
    //if list has voters
    else {
        cout << "The following voter IDs have been marked \"YES\" in this zipcode: " << endl;
        //traverse the entire list and print the RIN of the voters being pointed to in this list
        while (temp != NULL) {
            cout << temp->voterProfilePtr->getRIN() << endl;
            temp = temp->votedNextPtr;
        }
    }
}

//return the size of the linked list
int votedLinkedList::getSize() {
    return size;
}