#include "hashtable.h"
#include <iostream>
using namespace std;

HashMap::HashMap(int capacity)
{
	buckets = new linkedList[capacity];
	this->capacity = capacity;
	this->size = 0;
	this->numVoted = 0;
}

unsigned long HashMap::hashCode(const string key)
{
	unsigned long num = 5381;
	int c;
	int i = 0;
	while (c = key[i++])
		num += ((num << 5) + num) + c; 		//Add ascci code of each letter to (num * 33)

	return num;
}
//================================================
void HashMap::insert(const voterProfile vp)
{
	int index = hashCode(vp.RIN) % this->capacity; //Find the bucket index where the new voter profile will be added, make sure that the index is within the bounds of the hashtable

	
	buckets[index].addFront(vp);	//add the new voter into the bucket/list at the appropriate position in hashmap
	this->size++;					//Increment the number of voters present in the hashtable
}

voterProfile* HashMap::search(const string key)
{
	int index = hashCode(key) % this->capacity;			//Get the index of the bucket

	if (buckets[index].empty()) { //if bucket is empty, it means there is no such record and report as such
		return NULL; 
	}

	voterProfile* vp= buckets[index].getNode(key); //return the voter profile with the specific RIN
	if (vp != NULL) {
		return vp;
	}
	else { //if voter profile is not found, report as such
		return NULL;
	}
	
}

bool HashMap::remove(const string key, postalCodeLinkedList& pCodeLL)
{
	bool removed;  //to check if a profile has been removed or not
	int index = hashCode(key) % this->capacity;	//Get the index of the bucket from where the voter profile has to be deleted

	if (buckets[index].getNode(key)->voted == true) { //if the voter has already voted, remove them from the postal code linked list of registered votes too
		pCodeLL.removeVoter(buckets[index].getNode(key)->postalCode, buckets[index].getNodePointer(key));
		numVoted--;
	}

	removed=buckets[index].removeNode(key); //remove the voter profile from the hashtable
	size--; //decrement the number of voter profiles in the hashtable

	return removed;  // report if removal of a profile was successful or not
}

bool HashMap::modifyVoteStatus(const string key, postalCodeLinkedList& pCodeLL) {
	int index = hashCode(key) % this->capacity;	//Get the index of the bucket where the voter profile is to be found
	voterProfile* vp = buckets[index].getNode(key);
	bool modified = false;
	//if no such voter with the RIN (key) exists, report as such
	if (vp == NULL) {
		cout << "no such voter exists" << endl;
		return modified;
	}
	modified = buckets[index].modifyVote(key); //change voted status to "YES" of the particular voter and report if it was successfully modified
	if (modified) { //if the status was changed to "YES", add the voter to the postal code list of registered votes
		pCodeLL.registerVoter(buckets[index].getNode(key)->postalCode, buckets[index].getNodePointer(key));

		this->numVoted++; // increase the number of voters who have voted
	}

	return modified; //report if the status of the voter was modified or not
}

int HashMap::getSize(){	return this->size;} //return the number of voter profiles in the hashtable

int HashMap::getNumVoted() { return this->numVoted; } //return the number of votes cast

float HashMap::getPercVoted() { return ((float)(this->numVoted)) / ((float)(this->size)); } //return the percentage of registered voters who have voted

//destructor for the hashtable
HashMap::~HashMap()
{
	for (int i = 0; i < capacity; i++)
		buckets[i].~linkedList(); //deallocate dynamically allocated memory to buckets/chains in the hashtable

	delete[] this->buckets; //deallocate dynamcially allocated memory to the hashtable
}
