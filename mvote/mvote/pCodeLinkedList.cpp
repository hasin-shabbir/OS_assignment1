#include "pCodeLinkedList.h"
#include <iostream>
using namespace std;

postalCodeLinkedList::postalCodeLinkedList() :head(NULL) {};//initialize the head of the linked list to NULL pointer

postalCodeLinkedList::~postalCodeLinkedList() { while (!empty())removeFront(); } //remove nodes until the list is empty

bool postalCodeLinkedList::empty() const { return head == NULL; } //if head points to NULL pointer, return true

const string postalCodeLinkedList::front() const
{
    if (!empty()) //if the list is not empty
        return head->pCode;//return the element at the head node
    else
        throw out_of_range("The List is empty "); //if list is empty, throw exception
}

votedLinkedList* postalCodeLinkedList::getNode(string pCode) const {

    if (!empty()) {
        pCodeNode* node = this->head; //start from the head of the linked list
        while (node->pCode != pCode) { //search for the node with the specific RIN
            node = node->nextPtr; //continue traversing the linked list until the node with the specific RIN is found
            if (node != NULL) {
                continue;
            }
            else {
                break;
            }
        }

        if (node != NULL) {
            return (node->votersList); //return the voterProfile with the specific RIN
        }
        else {

            return NULL; //if no node found, return
        }

    }
    else
        return NULL;
        /*throw out_of_range("The pCode List is empty!\n");*/ //if list is empty, throw exception
}

void postalCodeLinkedList::addFront(string pCode,Node* e)
{
    pCodeNode* v = new pCodeNode; //create a new node
    v->pCode = pCode;
    v->votersList = new votedLinkedList;
    v->votersList->addFront(e);
    v->nextPtr = head;
    head = v; //the new node is made the head node
}

void postalCodeLinkedList::removeFront() {
    pCodeNode* old = head; //assign head to a new node as old
    if (head == NULL) {//if the list is empty
        cout << "voted linked list was empty\n";//output a message telling the list was empty
        exit(13);//exit the program
    }
    head = old->nextPtr;//assign the next node of the old head to the head pointer
    delete old; //delete the old head
}

bool postalCodeLinkedList::removeNode(string pCode) {


    // Store head node
    pCodeNode* temp = this->head;
    pCodeNode* prev = NULL;

    // If head node itself holds
    // the key to be deleted
    if (temp != NULL && temp->pCode == pCode)
    {

        this->head = temp->nextPtr; // Changed head
        delete temp;            // free old head
        return true;
    }

    // Else Search for the key to be deleted, 
    // keep track of the previous node as we
    // need to change 'prev->next' */
    else
    {
        while (temp != NULL && temp->pCode != pCode)
        {
            prev = temp;
            temp = temp->nextPtr;
        }

        // If key was not present in linked list
        if (temp == NULL) {
            cout << "No such record with the specified RIN found in voted list\n";
            return false;
        }

        // Unlink the node from linked list
        prev->nextPtr = temp->nextPtr;

        // Free memory
        delete temp;
        return true;
    }
}

void postalCodeLinkedList::printAll() {
    pCodeNode* temp = this->head;
    if (temp == NULL) {
        cout << "empty list\n";
    }
    else {
        while (temp != NULL) {
            cout << temp->pCode << "->"<<"(";
            temp->votersList->printAll();
            cout << ")->";
            temp = temp->nextPtr;
        }
        cout << "|||\n";
    }
}

bool postalCodeLinkedList::registerVoter(string pCode, Node* voterNode) {
    if (head == NULL) {
        cout << "here"<<endl;
        this->addFront(pCode, voterNode);
        return true;
    }
    votedLinkedList* vLL = this->getNode(pCode);
    if (vLL != NULL) {
        cout << "here2" << endl;

        vLL->addFront(voterNode);
        return true;
    }
    else {
        cout << "here3" << endl;

        this->addFront(pCode, voterNode);
        return true;
    }
    return false;
}

void postalCodeLinkedList::printVotersZipCode(string postalCode) {
    votedLinkedList* vLL = this->getNode(postalCode);
    if (vLL != NULL) {
        cout << vLL->getSize() << " voters have voted in this postal code" << endl;
        vLL->printRegisteredVoter();
    }
    else {
        cout << "The postal code does not exist or has not voters who have voted yet" << endl;
    }
}

