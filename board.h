#ifndef CROSS_PLAYER_BOARD_DATE_H
#define CROSS_PLAYER_BOARD_DATE_H

#include <string>
#include <vector>
#include <map>

using namespace std;


class Board
{
public:
	Board() {};
	Board(unsigned int lines, unsigned int columns);
	/* Creates board*/
	void addword(string position, string word);
	/* Adds word to board and map
	@position for the first letter, must be a 3 char str: 1st char is an uppercase letter representing the line, second char: a lowercase representing the column and last char a 'H' for horizontal or 'V' for vertical
	@word: str to be written in the board
	@returns error message if word doesnt fit
	@does not check if word exists*/
	void remove_word(string position);
	/* Removes word from board and map
	@position for the first letter, must be a 3 char str: 1st char is an uppercase letter representing the line, second char: a lowercase representing the column and last char a 'H' for horizontal or 'V' for vertical
	*/
	void printboard(string filename, string dictionaryfile);
	/* Prints the dictionary file name, the board, and a list of words placed on the board with their respective positions */
	void show();
	/* prints board to console*/
	//void show_emptyboard();
	/* prints empty board to console*/
	void fill_finished();
	/* fills all positions that have '.' with '#' */
	void addword_nochecking(string position, string word);
	/* Adds word to board and NOT to map, WITHOUT checking if word fits
	@position for the first letter, must be a 3 char str: 1st char is an uppercase letter representing the line, second char: a lowercase representing the column and last char a 'H' for horizontal or 'V' for vertical
	@word: str to be written in the board
	@does not check if word exists*/
	const vector<vector<char>> &matrixboard() const;
	/* returns the matrix of the board */
	const map<string, string> &mapall_words() const;
	/* return a map with the positions and words placed on the board */
	vector<string> get_wildcard(string position);
	/* gets all words that fit in a space starting at @position with wildcards ('?') for instance "A?A??B"
	@position for the first letter, must be a 3 char str: 1st char is an uppercase letter representing the line, second char: a lowercase representing the column and last char a 'H' for horizontal or 'V' for vertical*/
	bool is_word_at_position(string &position, string &word);
	/*  check if str word is locatedd at position in the board*/
	//bool finalcheck();
	//checks if all words in the board make sense
	bool is_word_in_board(string &word);
	//check if str word is already in board

private:
	unsigned int lines;
	unsigned int columns;
	vector<vector<char> > matrix;
	vector<vector<char> > empty_matrix;
	vector<char> name_lines;
	vector<char> name_columns;
	bool check_H(string &word, int &x, int &y);
	bool check_V(string &word, int &y, int &x);
	map<string, string> all_words;
	void transform_to_pos(string position, int &x, int &y, char &orientation);
};

#endif //CROSS_PLAYER_BOARD_DATE_H
