// mvote.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>

#include "linkedList.h"
#include "hashtable.h"
#include "pCodeLinkedList.h"

using namespace std;

int getFileSize(string fileName);
int getHashSize(int fileSize);
void loadFileContent(HashMap& hMap,string filename);

int menu(HashMap& hMap, postalCodeLinkedList& pCodeLL);

string* splitStringGetWord(string);

int main()
{
	string filename;
	cout << "enter the filename"<<endl;
	cin >> filename;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	int fileSize=getFileSize(filename);
	int hashsize = getHashSize(fileSize);

	HashMap hMap(hashsize);
	postalCodeLinkedList pCodeLL;
	loadFileContent(hMap,filename);

	int choice = 0;
	do {
		
		choice=menu(hMap,pCodeLL);
	} while (choice != 10);

	//voterProfile* vp;
	//hMap.remove("100102");
	//vp=hMap.search("100102");

	/*cout << "VOTER PROFILE:\n";
	cout << vp->fName << endl
		<< vp->lName << endl
		<< vp->RIN << endl
		<< vp->postalCode << endl
		<< vp->voted << endl;*/

	//hMap.~HashMap();

	return 0;
}

int getFileSize(string fileName) {

	int numRecords=0;

	ifstream fin(fileName);
	if (fin.fail()) {
		cout << "input file \"" << fileName << "\" could not be opened\n";
		exit(EXIT_FAILURE);
	}

	string dump;
	while (!fin.eof()) {
		getline(fin, dump);
		numRecords++;
	}

	fin.close();

	return numRecords;
}

int getHashSize(int fileSize) {
	return ceil((float)fileSize / 0.75);
}

void loadFileContent(HashMap& hMap, string fileName) {
	ifstream fin(fileName);
	if (fin.fail()) {
		cout << "input file \"" << fileName << "\" could not be opened\n";
		exit(EXIT_FAILURE);
	}
	voterProfile vp;
	vp.voted = false;
	while (!fin.eof()) {
		getline(fin, vp.RIN, ' ');
		getline(fin, vp.fName, ' ');
		getline(fin, vp.lName, ' ');
		getline(fin, vp.postalCode);
		hMap.insert(vp);
	}
	fin.close();
}

string* splitStringGetWord(string str) {
	string* words = new string[str.length()];
	string returnWord = "";
	int count = 0;
	for (auto i: str) {
		if (i == ' ' || i=='\n' ) {
			words[count] = returnWord;
			returnWord = "";
			count++;
		}
		else {
			//cout << i << endl;
			returnWord = returnWord + i;
		}
	}
	return words;
}

int menu(HashMap& hMap, postalCodeLinkedList& pCodeLL) {
	string choice;
	string commandType;
	string parameters;

	cout << endl<<"Enter a command in the specified format:"<<endl
		<< "1- l <key>" << endl
		<< "2- i <rin> <lname> <fname> <zip>"<<endl
		<< "3- d <rin>"<<endl
		<< "4- r <rin>"<<endl
		<< "5- bv <fileofkeys>"<<endl
		<< "6- v"<<endl
		<< "7- perc"<<endl
		<< "8- z <zipcode>"<<endl
		<< "9- o"<<endl
		<< "10- exit"<<endl<<endl;
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');

	getline(cin,choice);
	//commandType = choice.substr(0, choose.find(" "));
	/*cout << commandType;*/
	//parameters = choose.substr(choose.find(" ") + 1);

	/*string* inputString=new string[choice.length()];
	inputString = splitStringGetWord(choice);
	commandType = inputString[0];*/
	/*cout << "CTYPE: " << commandType << endl;*/
	stringstream inputStream(choice);
	stringstream parameterStream(choice);

	inputStream >> commandType;

	//cout << "command type: " << commandType << endl;

	if (commandType == "l") {
		string ctype,RIN;
		getline(parameterStream, ctype, ' ');
		getline(parameterStream, RIN);
		
		voterProfile* vp;
		vp = hMap.search(RIN);

		if (vp != NULL) {
			cout << "VOTER PROFILE\n"
				<< "First Name: " << vp->fName << endl
				<< "Last Name: " << vp->lName << endl
				<< "RIN: " << vp->RIN << endl
				<< "Postal Code: " << vp->postalCode << endl
				<< " Voted: ";

			if (vp->voted) {
				cout << "YES\n";
			}
			else {
				cout << "NO\n";
			}
		}
		else {
			cout << "Record with this RIN not found\n";
		}

		return 1;
	}

	else if (commandType == "i") {
		string ctype,RIN, fName, lName, postalCode;
		getline(parameterStream, ctype, ' ');
		getline(parameterStream, RIN, ' ');
		getline(parameterStream, lName, ' ');
		getline(parameterStream, fName, ' ');
		getline(parameterStream, postalCode);



		voterProfile* vp;
		vp = hMap.search(RIN);
		if (vp != NULL) {
			cout << "Voter with this RIN already exists!\n";
		}
		else {
		
			/*	lName = inputString[2];
				fName = inputString[3];
				postalCode = inputString[4];*/

			voterProfile newVoter;
			newVoter.fName = fName;
			newVoter.lName = lName;
			newVoter.postalCode = postalCode;
			newVoter.RIN = RIN;
			newVoter.voted = false;
			hMap.insert(newVoter);

			cout << "New voter record successfully added!\n";
		}

		return 2;
	}
	else if (commandType == "d") {

		string ctype, RIN;
		getline(parameterStream, ctype, ' ');
		getline(parameterStream, RIN);
		if (hMap.remove(RIN)) {
			cout << "Record deleted successfully\n";
		};

		return 3;
	}
	else if (commandType == "r") {
		string ctype, RIN;
		getline(parameterStream, ctype, ' ');
		getline(parameterStream, RIN);
		hMap.modifyVoteStatus(RIN, pCodeLL);
		return 4;
	}
	else if (commandType == "bv") {
		string ctype, fileName, RIN;
		getline(parameterStream, ctype, ' ');
		getline(parameterStream, fileName);

		ifstream fin(fileName);
		if (fin.fail()) {
			cout << "File of keys \"" << fileName << "\" could not be opened\n";
			return 5;
		}
		while (!fin.eof()) {
			fin >> RIN;
			hMap.modifyVoteStatus(RIN, pCodeLL);
		}
		fin.close();
		return 5;
	}
	else if (commandType == "v") {
		cout << hMap.getNumVoted() << " people have voted so far\n";
		return 6;
	}
	else if (commandType == "perc") {
		cout << hMap.getPercVoted() << " percent people have voted so far\n";
		return 7;
	}
	else if (commandType == "z") {
		string ctype, postalCode;
		getline(parameterStream, ctype, ' ');
		getline(parameterStream, postalCode);
		pCodeLL.printVotersZipCode(postalCode);
		return 8;
	}
	else if (commandType == "o") {

		return 9;
	}
	else if (commandType == "exit") {
		cout << "Program exited successfully\n";
		return 10;
	}
	else {
		cout << "Invalid command!, please enter a valid command only\n";
		return 11;
	}

}

