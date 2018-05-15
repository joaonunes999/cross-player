#ifndef PROG_EXERC_DATE_H
#define PROG_EXERC_DATE_H

#include <string>
#include <vector>
#include <map>


using namespace std;


class Board
{
public:
	Board() {};
	Board(int lines, int columns);
	bool addword(string position, string word);
	void remove_word(string position);
	void show();
	void fill_finished();
	void addword_nochecking(string position, string word);
private:
	unsigned int lines;
	unsigned int columns;
	vector<vector<char> > matrix;
	vector<char> name_lines;
	vector<char> name_columns;
	bool check_H(string &word, int &x, int &y);
	bool check_V(string &word, int &y, int &x);
	map<string, string> all_words;
	void transform_to_pos(string position, int &x, int &y, char &orientation);
};

#endif //PROG_EXERC_DATE_H
