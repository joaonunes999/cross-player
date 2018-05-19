#ifndef CROSS_PLAYER_DICTIONARY_H
#define CROSS_PLAYER_DICTIONARY_H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <iomanip>

using namespace std;

class Dictionary 
{
public:

	Dictionary();
	/* Standard function */
	Dictionary(string filename);
	/* Load the dictionary
	@Has as parameters the name of the file to load */
	void loadfile(const string &filename);
	/* Open the dictionary and put the words in a map
	@Has as parameters the name of the file to load */
	bool validword(string word);
	/* Checks if the word is valid, and puts the words on a set
	@It has as parameter a string that is a word that will verify if it is in the dictionary
	@Returns true if it is a valid word, or returns false if the word is not valid  */
	void print_matches(vector<string> &possible_words);
	/* prints possible matches for wildcard words from vector possible_words*/
	

private:
	map<string, vector<string>> synonymslist;
	set<string> validwordslist;
	vector<string> suggestedwords;
	vector<string> find_matches(vector<string> &possible_words);
};

#endif //CROSS_PLAYER_DICTIONARY_H
