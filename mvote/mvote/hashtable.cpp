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
	unsigned long sum = 0;
	for (int i = 0; i < key.length(); i++)
		sum += key[i] * pow(i, 10); 		//Add ascci code of each letter times i power 10

	return sum;
}
//================================================
void HashMap::insert(const voterProfile vp)
{
	int index = hashCode(vp.RIN) % this->capacity; //Find the bucket index where the new node will fall, make sure that the index is within the bounds of array

	
	buckets[index].addFront(vp);	//add the new voter into the bucket/list
	this->size++;									//Increate number of elements in the array
}
//===================================================
voterProfile* HashMap::search(const string key)
{
	int index = hashCode(key) % this->capacity;			//Get the index of the bucket
	int counter = 0;
	if (buckets[index].empty()) { //if bucket is empty, it means there is no such record
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
//=====================================================
bool HashMap::remove(const string key, postalCodeLinkedList& pCodeLL)
{
	bool removed;
	int index = hashCode(key) % this->capacity;	//Get the index of the bucket
	
	//cout << "ind:" << index << endl << endl;
	//buckets[index].printAll();
	if (buckets[index].getNode(key)->voted == true) {
		pCodeLL.removeVoter(buckets[index].getNode(key)->postalCode, buckets[index].getNodePointer(key));
	}

	removed=buckets[index].removeNode(key);

	//buckets[index].printAll();
	size--;
	return removed;
}
bool HashMap::modifyVoteStatus(const string key, postalCodeLinkedList& pCodeLL) {
	int index = hashCode(key) % this->capacity;	//Get the index of the bucket
	bool modified = buckets[index].modifyVote(key);
	if (modified) {
		pCodeLL.registerVoter(buckets[index].getNode(key)->postalCode, buckets[index].getNodePointer(key));
		this->numVoted++;
	}
	return modified;
}

//===================================================
int HashMap::getSize()
{
	return this->size;
}

int HashMap::getNumVoted() { return this->numVoted; }

float HashMap::getPercVoted() { return ((float)(this->numVoted)) / ((float)(this->size)); }

HashMap::~HashMap()
{
	for (int i = 0; i < capacity; i++)
		buckets[i].~linkedList();

	delete[] this->buckets;
}

