#include "pCodeLinkedList.h"
#include <iostream>
using namespace std;

postalCodeLinkedList::postalCodeLinkedList() :head(NULL) { size = 0; };//initialize the head of the linked list to NULL pointer

postalCodeLinkedList::~postalCodeLinkedList() { while (!empty())removeFront(); } //remove nodes until the list is empty

bool postalCodeLinkedList::empty() const { return head == NULL; } //if head points to NULL pointer, return true signifying as such

const string postalCodeLinkedList::front() const
{
    if (!empty()) //if the list is not empty
        return head->pCode;//return the postal code at the head node
    else
        throw out_of_range("The List is empty "); //if list is empty, throw exception
}

//get linked list of voters who have voted in a particular postal code
votedLinkedList* postalCodeLinkedList::getNode(string pCode) const {

    if (!empty()) {
        pCodeNode* node = this->head; //start from the head of the linked list
        while (node->pCode != pCode) { //search for the node with the specific postal code
            node = node->nextPtr; //continue traversing the linked list until the node with the specific RIN is found
            if (node != NULL) {
                continue;
            }
            else {
                break;
            }
        }

        if (node != NULL) {
            return (node->votersList); //return the pointer to the voters linked list in the specified postal code
        }
        else {

            return NULL; //if no node found, return NULL signifying as such
        }

    }
    else
        return NULL; //if list is empty, return NULL signifying as such
}

//get node of a particular postal code
pCodeNode* postalCodeLinkedList::getNodePointer(string pCode) const {

    if (!empty()) {
        pCodeNode* node = this->head; //start from the head of the linked list
        while (node->pCode != pCode) { //search for the node with the specific postal code
            node = node->nextPtr; //continue traversing the linked list until the node with the specific postal code is found
            if (node != NULL) {
                continue;
            }
            else {
                break;
            }
        }

        if (node != NULL) {
            return (node); //return the node with the specific postal code
        }
        else {

            return NULL; //if no node found, report as such by returning NULL
        }

    }
    else
        throw out_of_range("The pCode List is empty!\n"); //if list is empty, throw an exception
}

//add new node to the front of the postal code linked list using postal code
void postalCodeLinkedList::addFront(string pCode,Node* e)
{
    pCodeNode* v = new pCodeNode; //create a new node
    v->pCode = pCode; //assign the postal code value to the postal code of the node
    v->votersList = new votedLinkedList; //create a new list of voters who have voted in the postal code
    v->votersList->addFront(e); //insert to the front of the voters list who have voted, the newly registered vote
    v->nextPtr = head; //the head node is made the next pointer of the new node
    head = v; //the new node is made the head node
    size++;
}

void postalCodeLinkedList::removeFront() {
    pCodeNode* old = head; //assign head to a new node as old
    if (head == NULL) {//if the list is empty
        cout << "voted linked list was empty\n";//output a message reporting that the list was empty
        exit(13);//exit the program
    }
    head = old->nextPtr;//assign the next node of the old head to the head pointer
    delete old; //delete the old head
}

bool postalCodeLinkedList::removeNode(string pCode) {


    // Store head node
    pCodeNode* temp = this->head;
    pCodeNode* prev = NULL;

    // If head node is the node to be deleted, delete it
    if (temp != NULL && temp->pCode == pCode){
        this->head = temp->nextPtr; // Changed head
        delete temp;            // free old head
        size--;
        return true;
    }

    // Else Search for the node to be deleted using the postal code
    else
    {
        while (temp != NULL && temp->pCode != pCode)
        {
            prev = temp;
            temp = temp->nextPtr;
        }

        // If the postal code was not present in linked list, report as such
        if (temp == NULL) {
            cout << "No such record with the specified postal code found in voted list\n";
            return false;
        }

        // Unlink the node from linked list
        prev->nextPtr = temp->nextPtr;

        // Free memory
        delete temp;
        size--; //decrease the number of postal codes with votes cast
        return true; //report successful removal of the node
    }
}

//print all the postal codes with their registered votes
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

//register a new vote to the postal codes linked list
bool postalCodeLinkedList::registerVoter(string pCode, Node* voterNode) {
    //if this is the first vote, make the head node using the postal code of the voter
    if (head == NULL) {
        //add to the front of the postal code list the new voter and the new postal code
        this->addFront(pCode, voterNode);
        return true;//report successfull entry
    }

    votedLinkedList* vLL = this->getNode(pCode);
    //if the postal code already exists
    if (vLL != NULL) {
        //add to the front of the cast votes linked list the new vote
        vLL->addFront(voterNode);
        return true;
    }
    else {
        //else, add a new node to the postal code linked list and add the new voter in its list of votes
        this->addFront(pCode, voterNode);
        return true;
    }
    return false;
}

//print votes cast in a specific postal code
void postalCodeLinkedList::printVotersZipCode(string postalCode) {
    votedLinkedList* vLL = this->getNode(postalCode);
    //if the postal code exists in the list
    if (vLL != NULL) {
        //print the number of votes cast in it
        cout << vLL->getSize() << " voters have voted in this postal code" << endl;
        //print the RIN of voters who have voted in this postal code
        vLL->printRegisteredVoter();
    }
    //else report that the postal code has no voters who have voted, or does not exist
    else {
        cout << "The postal code does not exist or has no voters who have voted yet" << endl;
    }
}

//remove a specific voter
bool postalCodeLinkedList::removeVoter(string pCode, Node* e) {
    //search, using the postal code, the node containing the list of voters where the voter can be found
    votedLinkedList* vLL = this->getNode(pCode);
    //get the number of votes in the particular postal code before removal
    int countBeforeRemoval = this->getNode(pCode)->getSize();
    if (vLL != NULL) {
        vLL->removeNode(e); //remove the voter node from the votes list if it is found
        if (this->getNodePointer(pCode) != NULL) {
            if ((countBeforeRemoval - 1) == 0) { // if it was the only vote in the postal code, remove the postal code node from the postal code list
                this->removeNode(pCode);
            }
        }
        return true; //report successfull removal
    }
    return false; //report failed removal
}

//function to swap two array elements
void postalCodeLinkedList::swapArr(sortedStruct& elOne, sortedStruct& elTwo) {
    sortedStruct temp;
    temp = elOne;
    elOne = elTwo;
    elTwo = temp;
}

//sort the postal code linked list in descending order of number of votes cast per postal code, and output the result
void postalCodeLinkedList::descendingOrder() {
    //get the number of postal codes where votes have been cast
    int count = this->size;

    //if no votes have been cast, report as such
    if (count == 0) {
        cout << "No votes have been cast yet" << endl;
        return;
    }

    //create a dynamic structure to hold the postal code and their respective number of votes cast
    sortedStruct* sortedList = new sortedStruct[count];

    //store the information required for the sorted structure in sortedList by traversing the linked list
    pCodeNode* currNode = this->head;
    for (int i = 0; i < count; i++) {
        sortedList[i].numVoters = currNode->votersList->getSize();
        sortedList[i].pCode = currNode->pCode;
        currNode = currNode->nextPtr;
    }

    //use heapsort to sort the list in decreasing order of votes cast
    heapSort(sortedList);

    //output the required information in decreasing order of votes cast
    for (int i = 0; i < count; i++) {
        cout << "Zip Code: " << sortedList[i].pCode << " Num of Votes cast: " << sortedList[i].numVoters << endl;
    }

    //deallocate the dynamically allocated memory
    delete[] sortedList;
}

//function to heapify an array as a max heap
void postalCodeLinkedList::heapify(sortedStruct* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left<n && arr[left].numVoters<arr[largest].numVoters) {
        largest = left;
    }

    if (right<n && arr[right].numVoters<arr[largest].numVoters) {
        largest = right;
    }

    if (largest != i) {
        swapArr(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }

}

//function to implement heapsort
void postalCodeLinkedList::heapSort(sortedStruct* arr) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr,size, i);//create a max heap from the array
    }

    for (int i = size - 1; i > 0; i--) {
        //keep extracting the root from the max heap and heapify again for all the elements of the array
        swapArr(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

}