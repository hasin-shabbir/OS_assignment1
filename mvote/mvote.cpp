// mvote.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <sstream>

#include "linkedList.h"
#include "hashtable.h"
#include "pCodeLinkedList.h"

using namespace std;

void loadFileContent(HashMap& hMap, string filename);//function to load content of the file

bool isNumber(string);//function to check if a string contains only numerical characters or not

//function to implement functionality of different commands
int menu(HashMap& hMap, postalCodeLinkedList& pCodeLL);

int main(int argc, char* argv[])
{
	//filename for the voters record
	string filename;
	//size of hash table
	int hashsize;

	//get the arguments from the terminal
	if (strcmp(argv[1], "-f") == 0) {
		filename = argv[2];
		stringstream s(argv[4]);
		s >> hashsize;
	}
	else {
		filename = argv[4];
		stringstream s(argv[2]);
		s >> hashsize;
	}

	//insert records in the hashtable
	HashMap hMap(hashsize);
	postalCodeLinkedList pCodeLL;
	loadFileContent(hMap, filename);

	//implement commands until user decides to exit
	int choice = 0;
	do {
		choice = menu(hMap, pCodeLL);
	} while (choice != 10);

	return 0;
}

//function to load the content of the file in the hash map
void loadFileContent(HashMap& hMap, string fileName) {
	//open file for input
	ifstream fin(fileName);

	//report file opening failure if that is the case and exit the program
	if (fin.fail()) {
		cout << "input file \"" << fileName << "\" could not be opened"<<endl;
		exit(EXIT_FAILURE);
	}

	//create a voter profile
	voterProfile vp;
	//set the initial voted status to false, signifying "NO"
	vp.voted = false;
	//read all the records in the file and insert each of them into the hashmap
	while (!fin.eof()) {
		getline(fin, vp.RIN, ' ');
		if (vp.RIN == "\0" || vp.RIN == "\n") {
			continue;
		}
		getline(fin, vp.fName, ' ');
		getline(fin, vp.lName, ' ');
		getline(fin, vp.postalCode);
		hMap.insert(vp);
	}
	//close the input file
	fin.close();
}

//function to check if a string only contains numerical characters
bool isNumber(string s) {
	//check if every character is a digit
	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) { return false; }
	}
	return true;
}

int menu(HashMap& hMap, postalCodeLinkedList& pCodeLL) {

	string choice;
	string commandType;
	string parameters;

	//output the available commands
	cout << endl << "Enter a command in the specified format:" << endl
		<< "1- l <key>" << endl
		<< "2- i <rin> <lname> <fname> <zip>" << endl
		<< "3- d <rin>" << endl
		<< "4- r <rin>" << endl
		<< "5- bv <fileofkeys>" << endl
		<< "6- v" << endl
		<< "7- perc" << endl
		<< "8- z <zipcode>" << endl
		<< "9- o" << endl
		<< "10- exit" << endl << endl;

	//get the user entered command
	getline(cin, choice);

	//create string streams from the command
	stringstream inputStream(choice);
	stringstream parameterStream(choice);

	//get the type of commmand by reading to the first white space
	inputStream >> commandType;

	////////////////////////////////////////////////////
	//generate an action based on the type of command://
	///////////////////////////////////////////////////
	if (commandType == "l") { //look up command
		string ctype, RIN;
		getline(parameterStream, ctype, ' ');//get the command type
		getline(parameterStream, RIN);//get the RIN entered by the user

		//check for validity of inputs
		if (RIN == "\0") {
			cout << "Enter a valid RIN" << endl;
			return 1;
		}
		if (!isNumber(RIN)) {
			cout << "please provide a valid RIN" << endl;
			return 1;
		}

		//create a voter profile
		voterProfile* vp;
		//search the voter profile using RIN from the hashmap
		vp = hMap.search(RIN);

		//if the voter profile exists, output it
		if (vp != NULL) {
			cout << "VOTER PROFILE" << endl
				<< "First Name: " << vp->fName << endl
				<< "Last Name: " << vp->lName << endl
				<< "RIN: " << vp->RIN << endl
				<< "Postal Code: " << vp->postalCode << endl
				<< " Voted: ";

			if (vp->voted) {
				cout << "YES" << endl;
			}
			else {
				cout << "NO" << endl;
			}
		}
		//if voter profile does not exist, report as such
		else {
			cout << "Record with this RIN not found" << endl;
		}

		//return the command number
		return 1;
	}

	// insert command
	else if (commandType == "i") {
		//get the input voter profile
		string ctype, RIN, fName, lName, postalCode;
		getline(parameterStream, ctype, ' ');
		getline(parameterStream, RIN, ' ');
		getline(parameterStream, lName, ' ');
		getline(parameterStream, fName, ' ');
		getline(parameterStream, postalCode);

		//check for validity of inputs
		if (RIN == "\0" || lName == "\0" || fName == "\0" || postalCode == "\0") {
			cout << "Provide valid parameters" << endl;
			return 2;
		}
		if (!isNumber(RIN)) {
			cout << "please provide a valid RIN" << endl;
			return 2;
		}
		if (!isNumber(postalCode)) {
			cout << "please provide a valid postal code" << endl;
			return 2;
		}

		//search if a profile with same RIN exists
		voterProfile* vp;
		vp = hMap.search(RIN);
		//if such a profile exists, report as such and exit
		if (vp != NULL) {
			cout << "Voter with this RIN already exists!" << endl;
		}
		//if this is a new profile
		else {
			//create the new voter profile
			voterProfile newVoter;
			newVoter.fName = fName;
			newVoter.lName = lName;
			newVoter.postalCode = postalCode;
			newVoter.RIN = RIN;
			newVoter.voted = false;
			//insert the new voter in the hashmap
			hMap.insert(newVoter);
			//report successful insertion
			cout << "New voter record successfully added!" << endl;
		}
		//return the command number
		return 2;
	}

	//delete command
	else if (commandType == "d") {

		string ctype, RIN;
		getline(parameterStream, ctype, ' ');
		//get the RIN of the voter to be removed
		getline(parameterStream, RIN);

		//check for validity of inputs
		if (RIN == "\0") {
			cout << "please provide a RIN" << endl;
			return 3;
		}
		if (!isNumber(RIN)) {
			cout << "please provide a valid RIN" << endl;
			return 3;
		}
		if (hMap.remove(RIN, pCodeLL)) {//remove the voter from the records and report upon successful removal
			cout << "Record deleted successfully" << endl;
		};

		//return the command number
		return 3;
	}

	//register command
	else if (commandType == "r") {
		string ctype, RIN;
		getline(parameterStream, ctype, ' ');
		//get the RIN of the voter to be registered
		getline(parameterStream, RIN);

		//check for validity of inputs
		if (RIN == "\0") {
			cout << "please provide a RIN" << endl;
			return 4;
		}
		if (!isNumber(RIN)) {
			cout << "please provide a valid RIN" << endl;
			return 4;
		}

		//register the vote of the voter with the specified RIN
		hMap.modifyVoteStatus(RIN, pCodeLL);
		//return the command number
		return 4;
	}

	//bulkvote command
	else if (commandType == "bv") {
		string ctype, fileName, RIN;
		getline(parameterStream, ctype, ' ');
		//get the filename with the voter IDs
		getline(parameterStream, fileName);

		//open the file
		ifstream fin(fileName);
		//if the file open fails, report as such
		if (fin.fail()) {
			cout << "File of keys \"" << fileName << "\" could not be opened" << endl;
			return 5;
		}
		//read all the records from the file
		while (!fin.eof()) {
			fin >> RIN;

			//check for validity of inputs
			if (!isNumber(RIN)) {
				cout << "RIN \"" << RIN << "\" invalid!" << endl;
				continue;
			}

			//modify the vote status of each voter from the file
			hMap.modifyVoteStatus(RIN, pCodeLL);
		}
		//close the file
		fin.close();

		//return the command type
		return 5;
	}

	//number of people voted command
	else if (commandType == "v") {
		//print the number of people who have voted so far
		cout << hMap.getNumVoted() << " people have voted so far" << endl;
		//return the command type
		return 6;
	}

	//percentage of people voted command
	else if (commandType == "perc") {
		//print the percentage of people who have voted so far
		cout << hMap.getPercVoted() << " percent people have voted so far" << endl;
		//return the command type
		return 7;
	}

	//print voters who have cast vote in a zipcode command
	else if (commandType == "z") {
		string ctype, postalCode;
		getline(parameterStream, ctype, ' ');

		//get the postal code from the input
		getline(parameterStream, postalCode);

		//check for validity of inputs
		if (postalCode == "\0") {
			cout << "Provide a postal code" << endl;
			return 8;
		}
		if (!isNumber(postalCode)) {
			cout << "Provide a valid postal code" << endl;
			return 8;
		}

		//print the voters who have voted in that zipcode
		pCodeLL.printVotersZipCode(postalCode);
		//return the command type
		return 8;
	}

	//output command for ordered output of postal codes according to number of votes cast
	else if (commandType == "o") {
		//ordered output
		pCodeLL.descendingOrder();
		//return the command type
		return 9;
	}

	//exit the program
	else if (commandType == "exit") {
		cout << "Program exited successfully" << endl;
		//return the command type
		return 10;
	}
	//report invalid command
	else {
		cout << "Invalid command!, please enter a valid command only" << endl;
		//return the command type
		return 11;
	}

}

