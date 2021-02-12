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
pCodeNode* postalCodeLinkedList::getNodePointer(string pCode) const {

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
            return (node); //return the voterProfile with the specific RIN
        }
        else {

            return NULL; //if no node found, return
        }

    }
    else
        throw out_of_range("The pCode List is empty!\n"); //if list is empty, throw exception
}

void postalCodeLinkedList::addFront(string pCode,Node* e)
{
    pCodeNode* v = new pCodeNode; //create a new node
    v->pCode = pCode;
    v->votersList = new votedLinkedList;
    v->votersList->addFront(e);
    v->nextPtr = head;
    head = v; //the new node is made the head node
    size++;
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
        size--;
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
        size--;
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
        this->addFront(pCode, voterNode);
        return true;
    }
    votedLinkedList* vLL = this->getNode(pCode);
    if (vLL != NULL) {

        vLL->addFront(voterNode);
        return true;
    }
    else {

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

bool postalCodeLinkedList::removeVoter(string pCode, Node* e) {
    votedLinkedList* vLL = this->getNode(pCode);
    int countBeforeRemoval = this->getNode(pCode)->getSize();
    if (vLL != NULL) {
        vLL->removeNode(e);
        if (this->getNodePointer(pCode) != NULL) {
            if ((countBeforeRemoval-1)==0){
                this->removeNode(pCode);
            }
        }
        return true;
    }
    return false;
}

void postalCodeLinkedList::sorter(postalCodeLinkedList& pCodeLL, pCodeNode* currNode) {
    currNode->nextPtr = pCodeLL.head;
    pCodeLL.head = currNode;
    /*if (pCodeLL.head == NULL || pCodeLL.head->votersList->getSize() <= currNode->votersList->getSize()) {
        currNode->nextPtr = pCodeLL.head;
        pCodeLL.head = currNode;
    }
    else {
        pCodeNode* refNode;
        refNode = pCodeLL.head;
        while (refNode->nextPtr != NULL && refNode->nextPtr->votersList->getSize() > currNode->votersList->getSize()) {
            refNode = refNode->nextPtr;
        }
        currNode->nextPtr = refNode->nextPtr;
        refNode->nextPtr = currNode;
    }*/
}
void postalCodeLinkedList::swapArr(sortedStruct& elOne, sortedStruct& elTwo) {
    sortedStruct temp;
    temp = elOne;
    elOne = elTwo;
    elTwo = temp;
}

void postalCodeLinkedList::descendingOrder() {
    int count = this->size;
    sortedStruct* sortedList = new sortedStruct[count];
    pCodeNode* currNode = this->head;
    for (int i = 0; i < count; i++) {
        sortedList[i].numVoters = currNode->votersList->getSize();
        sortedList[i].pCode = currNode->pCode;
        currNode = currNode->nextPtr;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (sortedList[j].numVoters < sortedList[j+1].numVoters) {
                swapArr(sortedList[j], sortedList[j+1]);
                /*sortedStruct temp;
                temp = sortedList[j];
                sortedList[j] = sortedList[j + 1];
                sortedList[j + 1] = temp;*/
            }
        }
    }

    for (int i = 0; i < count; i++) {
        cout << "Zip Code: " << sortedList[i].pCode << " Num of Votes cast: " << sortedList[i].numVoters << endl;
    }
}