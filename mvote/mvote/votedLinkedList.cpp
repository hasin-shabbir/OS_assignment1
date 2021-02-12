#include "votedLinkedList.h"
#include <iostream>
using namespace std;

votedLinkedList::votedLinkedList() :head(NULL) { this->size = 0; };//initialize the head of the linked list to NULL pointer

votedLinkedList::~votedLinkedList() { while (!empty())removeFront(); } //remove nodes until the list is empty

bool votedLinkedList::empty() const { return head == NULL; } //if head points to NULL pointer, return true

const votedNode* votedLinkedList::front() const
{
    if (!empty()) //if the list is not empty
        return head;//return the element at the head node
    else
        throw out_of_range("The List is empty "); //if list is empty, throw exception
}

votedNode* votedLinkedList::getNode(Node* e) const {

    if (!empty()) {
        votedNode* node = this->head; //start from the head of the linked list
        while (node->voterProfilePtr != e) { //search for the node with the specific RIN
            node = node->votedNextPtr; //continue traversing the linked list until the node with the specific RIN is found
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
        throw out_of_range("The Voted List is empty!\n"); //if list is empty, throw exception
}

void votedLinkedList::addFront(Node* e)
{
    votedNode* v = new votedNode; //create a new node
    v->voterProfilePtr = e;
    v->votedNextPtr = head; //the head is assigned to the next pointer of the new node 
    head = v; //the new node is made the head node
    size++;
}

void votedLinkedList::removeFront() {
    votedNode* old = head; //assign head to a new node as old
    if (head == NULL) {//if the list is empty
        cout << "voted linked list was empty\n";//output a message telling the list was empty
        exit(13);//exit the program
    }
    head = old->votedNextPtr;//assign the next node of the old head to the head pointer
    delete old; //delete the old head
}

bool votedLinkedList::removeNode(Node* e) {


    // Store head node
    votedNode* temp = this->head;
    votedNode* prev = NULL;

    // If head node itself holds
    // the key to be deleted
    if (temp != NULL && temp->voterProfilePtr == e)
    {

        this->head = temp->votedNextPtr; // Changed head
        delete temp;            // free old head
        size--;
        return true;
    }

    // Else Search for the key to be deleted, 
    // keep track of the previous node as we
    // need to change 'prev->next' */
    else
    {
        while (temp != NULL && temp->voterProfilePtr != e)
        {
            prev = temp;
            temp = temp->votedNextPtr;
        }

        // If key was not present in linked list
        if (temp == NULL) {
            cout << "No such record with the specified RIN found in voted list\n";
            return false;
        }

        // Unlink the node from linked list
        prev->votedNextPtr = temp->votedNextPtr;

        // Free memory
        delete temp;
        size--;
        return true;
    }
}

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

void votedLinkedList::printRegisteredVoter() {
    votedNode* temp = this->head;
    if (temp == NULL) {
        cout << "No voters have voted in this ZipCode"<<endl;
    }
    else {
        cout << "The following voter IDs have been marked \"YES\" in this zipcode: " << endl;
        
        while (temp != NULL) {
            cout << temp->voterProfilePtr->getRIN() << endl;
            temp = temp->votedNextPtr;
        }
    }
}

int votedLinkedList::getSize() {
    return size;
}