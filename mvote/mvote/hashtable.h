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
	linkedList* buckets;		// Array of chain/lists to store HashNodes
	int size;					//Current Size of HashMap
	int capacity;				// Total Capacity of HashMap
	int numVoted;				// number of voters who have voted
public:
	HashMap(int capacity); //constructor of hashmap
	unsigned long hashCode(const string key); //hashing function
	void insert(const voterProfile vp); //insert element into hashmap
	voterProfile* search(const string key); //returns pointer to the voter profile with a specific RIN, NULL if not found
	bool remove(const string key, postalCodeLinkedList& pCodeLL);//remove a voter profile from the hashtable
	bool modifyVoteStatus(const string key, postalCodeLinkedList& pCodeLL); //register a voter to voted="YES"
	int getSize(); //get number of voters added in the hashtable
	int getNumVoted(); //get number of voters who have voted
	float getPercVoted(); //get the percentage of voters who have voted
	~HashMap(); //destructor of the hashmap
};

#endif