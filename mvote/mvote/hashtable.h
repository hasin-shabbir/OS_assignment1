#ifndef hashtable_hpp
#define hashtable_hpp
#include <string>

#include<math.h>
#include "linkedList.h"
#include "pCodeLinkedList.h"

using namespace std;


class HashMap
{
private:
	linkedList* buckets;		// Array of lists to store HashNodes
	int size;					    //Current Size of HashMap
	int capacity;				    // Total Capacity of HashMap
	int numVoted;
public:
	HashMap(int capacity);
	unsigned long hashCode(const string key);
	void insert(const voterProfile vp);
	voterProfile* search(const string key); //returns pointer to the voter profile with a specific RIN, NULL if not found
	bool remove(const string key, postalCodeLinkedList& pCodeLL);
	bool modifyVoteStatus(const string key, postalCodeLinkedList& pCodeLL);
	int getSize();
	int getNumVoted();
	float getPercVoted();
	~HashMap();
};

#endif