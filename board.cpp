#include "stdafx.h"
#include "board.h"
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib> 
#include <windows.h> 
#include "dictionary.h"
#include <sstream>
#include <algorithm>  
#include <fstream> 

using namespace std;

#define LIGHTRED 12
#define LIGHTGRAY 7 
#define BLACK 0
#define WHITE 15

// COLOR
void setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK)
		SetConsoleTextAttribute(hCon, color);
	else     SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}
// ------------------------------------------------------------------------------- //



bool Board::check_H(string &word, int &x, int &y)
{
	size_t acum = 0;
	if ((y - 1 < 0) && ((y + word.length() - 1) < columns)) //check if word starts at the beginning of the board 
		goto cycle;

	if ((y + word.length() - 1) == columns) //check if word ends at the beginning of the board 
		goto cycle;


	if ((matrix.at(y - 1).at(x) == '.' || matrix.at(y - 1).at(x) == '#') && ((y + word.length() - 1) < columns) && (matrix[y + word.length()][x] == '.' || matrix[y + word.length()][x] == '#'))
	{
	cycle:	while (acum < word.length())
	{
		if ((matrix[y + acum][x] == '.') || (matrix[y + acum][x] == word.at(acum)))
		{
			acum++;
		}

		else
			return false;
	}

			return true;
	}
	else
		return false;
}

bool Board::check_V(string &word, int &y, int &x)
{
	size_t acum = 0;
	if ((y - 1 < 0) && ((y + word.length() - 1) < lines)) //check if word starts at the beginning of the board 
		goto cycle;

	if ((y + word.length() - 1) == lines) //check if word ends at the beginning of the board 
		goto cycle;

	if ((matrix[x][y - 1] == '.' || matrix[x][y - 1] == '#') && ((y + word.length() - 1) < lines) && (matrix.at(x).at(y + word.length()) == '.' || matrix.at(x).at(y + word.length()) == '#'))
	{
		while (acum < word.length())
		{
		cycle:		if ((matrix[x][y + acum] == '.') || (matrix[x][y + acum] == word.at(acum)))
			acum++;
					else
						return false;
		}


		return true;
	}
	else
		return false;


}

Board::Board(unsigned int l, unsigned int c)
{

	lines = l;
	columns = c;

	//MATRIX BOARD
	matrix.resize(lines);

	for (size_t i = 0; i < matrix.size(); i++)
		matrix[i].resize(columns);

	for (size_t i = 0; i < matrix.size(); i++)
		fill(matrix[i].begin(), matrix[i].end(), '.');


	//NAME LINES
	name_lines.resize(lines);


	for (size_t i = 0; i < name_lines.size(); i++)
	{
		char letter = (char)('a' + i);
		name_lines[i] = letter;
	}

	// NAME COLUMNS
	name_columns.resize(columns);


	for (size_t i = 0; i < name_columns.size(); i++)
	{
		char letter = (char)('A' + i);
		name_columns[i] = letter;
	}

}

Board::Board(string boardfilename)
{
	ifstream boardfile;

	string line;
	string position, word;
	lines = 2;
	columns = 0;

	//opening file
	boardfile.open(boardfilename);

	while (!boardfile.is_open())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cerr << "File " << "board" << " not found !\n";
		cout << "Enter the board file name you want play: ";
		cin >> boardfilename;
		boardfile.open(boardfilename);
	}

	// ignore two first lines
	boardfile.ignore(1000, '\n');
	boardfile.ignore(1000, '\n');

	getline(boardfile, line); // Skip empty line

							  // Count the columns

	getline(boardfile, line) && line != "";

	string strings = " ";
	for (size_t i = 0; i < line.size(); i++)
	{
		strings[0] = line[i];
		if (strings != " ")
			columns++;
	}

	// Count the lines

	while (getline(boardfile, line) && line != "")
		lines++;

	matrix.resize(lines);

	for (size_t i = 0; i < matrix.size(); i++)
		matrix[i].resize(columns);


	while (!boardfile.eof())
	{
		getline(boardfile, line);
		if (!(line == ""))
			all_words.insert(pair<string, string>(line.substr(0, 3), line.substr(4)));
	}


	boardfile.close();

	for (const auto& x : all_words)
	{
		addword_nochecking(x.first, x.second);
	}
	//NAME LINES
	name_lines.resize(lines);


	for (size_t i = 0; i < name_lines.size(); i++)
	{
		char letter = (char)('a' + i);
		name_lines[i] = letter;
	}

	// NAME COLUMNS
	name_columns.resize(columns);


	for (size_t i = 0; i < name_columns.size(); i++)
	{
		char letter = (char)('A' + i);
		name_columns[i] = letter;
	}

	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t a = 0; a < matrix.at(i).size(); a++)
		{
			if (matrix.at(i).at(a) == '\0')
				matrix.at(i).at(a) = '.';
		}
	}

}

void Board::show()
{

	cout << ' ';
	// PRINT name of lines

	setcolor(LIGHTRED);
	for (size_t i = 0; i < lines; i++)
	{
		cout << ' ' << name_lines[i];
	}

	cout << endl;

	for (size_t i = 0; i < columns; i++)
	{
		setcolor(LIGHTRED, BLACK);
		cout << name_columns[i] << ' ';

		setcolor(BLACK, LIGHTGRAY);
		for (size_t a = 0; a < lines; a++)
			cout << matrix[a][i] << ' ';
		cout << endl;
	}
	setcolor(WHITE, BLACK);
	cout << endl;

}

void Board::printboard(string filenames, string dictionaryfile)
{
	ofstream output;
	output.open(filenames);

	output << dictionaryfile << endl << endl;

	for (size_t i = 0; i < columns; i++)
	{
		for (size_t a = 0; a < lines; a++)
			output << matrix[a][i] << ' ';
		output << endl;
	}
	output << endl;

	// Save a list of positions with the words in the file
	for (const auto & s : mapall_words())
	{
		output << s.first << " " << s.second << endl;
	}

	output.close();
}

void Board::transform_to_pos(string position, int &x, int &y, char &orientation)
{
	x = position[0] - 'A';
	y = position[1] - 'a';
	orientation = position[2];
}

void Board::addword(string position, string word)
{
	//check if valid input
	if (position.length() == 3 && isupper(position[0]) && !(isupper(position[1])) && (toupper(position[2]) == 'V' || toupper(position[2]) == 'H'))
	{
		//initializing variables position
		int x = 0;
		int y = 0;
		char orientation = 'a';

		//get true value for variables position 
		transform_to_pos(position, x, y, orientation);

		transform(word.begin(), word.end(), word.begin(), toupper); //transform to uppercase


		switch (orientation) {
		case 'H':
		case 'h':
		{
			//check if empty
			if (check_H(word, x, y))
			{

				if (y - 1 >= 0) //check if it starts in the beginning of the board 
					matrix[y - 1][x] = '#';

				if (y + word.length() <= columns) //check if it ends in the end of the board 
					matrix[y + word.length()][x] = '#';
				size_t i = 0;
				while (i < word.length())

					//check if empty
					if (check_H(word, x, y))
					{
						if (y - 1 >= 0) //check if it starts in the beginning of the board 
							matrix[y - 1][x] = '#';

						if (y + word.length() <= columns) //check if it ends in the end of the board 
							matrix[y + word.length()][x] = '#';
						size_t i = 0;
						while (i < word.length())
						{
							matrix[y + i][x] = word.at(i);

							i++;
						}

						//add to map
						all_words.insert(pair<string, string>(position, word));
						break;


					}
					else

					{
						matrix[y + i][x] = word.at(i);

						i++;
					}

				//add to map
				all_words.insert(pair<string, string>(position, word));
				break;


			}
			else
			{
				std::cout << "Cannot fit " << word << " in position " << position << endl << endl;
				break;


			}


		}

		case 'V':
		case 'v':
		{
			if (check_V(word, x, y))
			{

				if (x - 1 >= 0) //check if it starts in the beginning of the board 
					matrix[y][x - 1] = '#';

				if (x + word.length() <= lines) //check if it ends in the end of the board 
					matrix[y][x + word.length()] = '#';
				size_t i = 0;
				while (i < word.length())

					if (check_V(word, x, y))
					{
						if (x - 1 >= 0) //check if it starts in the beginning of the board 
							matrix[y][x - 1] = '#';

						if (x + word.length() <= lines) //check if it ends in the end of the board 
							matrix[y][x + word.length()] = '#';
						size_t i = 0;
						while (i < word.length())
						{
							matrix[y][x + i] = word.at(i);

							i++;
						}

						//add to map
						all_words.insert(pair<string, string>(position, word));
						break;


					}
					else
					{
						matrix[y][x + i] = word.at(i);

						i++;
					}

				//add to map
				all_words.insert(pair<string, string>(position, word));
				break;


			}
			else
			{
				std::cout << "Cannot fit " << word << " in position " << position << endl << endl;
				break;
			}

		}
		}
	}
	else
		cout << "Invalid input\n";
}

void Board::remove_word(string position)
{
	if (position.length() == 3 && isupper(position[0]) && !(isupper(position[1])) && (all_words.find(position) != all_words.end()))
	{
		all_words.erase(position);
		int y = position[0] - 'A';  //y and x is diferent from the ones in addword
		int x = position[1] - 'a';
		char orientation = position[2];
		switch (orientation)
		{
		case 'H':
		case 'h':
		{
			size_t i = 0;
			matrix[x - 1][y] = '.';
			do
			{
				matrix[x + i][y] = '.';
				i++;
			} while (matrix[x + i][y] != '#' && matrix[x + i][y] != (columns - 2));

			matrix[x + i][y] = '.';
			break;

		}
		case 'V':
		case 'v':
		{
			size_t i = 0;
			matrix[x][y - 1] = '.';
			do
			{
				matrix[x][y + i] = '.';
				i++;


			} while (matrix[x][y + i] != '#' && matrix[x][y + i] != lines - 2);
			matrix[x][y + i] = '.';
			break;

		}

		}

		for (const auto& x : all_words)
		{
			addword_nochecking(x.first, x.second);
		}

	}
	else
		cout << "Not a valid input\n";



}

void Board::fill_finished()
{
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t a = 0; a < matrix.at(i).size(); a++)
		{
			if (matrix.at(i).at(a) == '.')
				matrix.at(i).at(a) = '#';
		}
	}
}

void Board::addword_nochecking(string position, string word)
{

	//initializing variables position
	int x = 0;
	int y = 0;
	char orientation = 'a';

	//get true value for variables position 
	transform_to_pos(position, x, y, orientation);

	//write the word
	switch (orientation)
	{
	case 'H':
	case 'h':
	{
		if (y - 1 >= 0) //check if it starts in the beginning of the board 
			matrix[y - 1][x] = '#';

		if (y + word.length() <= columns) //check if it ends in the end of the board 
			matrix[y + word.length()][x] = '#';
		size_t i = 0;
		while (i < word.length())
		{
			matrix[y + i][x] = word.at(i);

			i++;
		}
		break;
	}

	case 'V':
	case 'v':
	{
		if (x - 1 >= 0) //check if it starts in the beginning of the board 
			matrix[y][x - 1] = '#';

		if (x + word.length() <= lines) //check if it ends in the end of the board 
			matrix[y][x + word.length()] = '#';
		size_t i = 0;
		while (i < word.length())
		{
			matrix[y][x + i] = word.at(i);

			i++;
		}
		break;
	}
	}

}

const vector<vector<char>> &Board::matrixboard() const
{
	return matrix;
}

/*
vector<string> Board::get_wildcard(string position)
{
//initializing variables position
int x = 0;
int y = 0;
char orientation = 'a';
//get true value for variables position
transform_to_pos(position, y, x, orientation);
vector<string> words; //all possible words
string possible_word;
switch (orientation)
{
case 'V':
case 'v':
{
if (matrix[x][y] != '.')
possible_word += matrix[x][y];
for (size_t i = 1; matrix[x][y + i] != '#' && (y + i) < lines - 1; i++) //scan all possibilitis like 'w?', 'w??', ...
{
//for (size_t a=0; a<= i; a++)
if (matrix[x][y + i] == '.')
possible_word += '?';
else
possible_word += matrix[x][y + i];
words.push_back(possible_word);
}
}
case 'H':
case 'h':
{
if (matrix[x][y] != '.')
possible_word += matrix[x][y];
for (size_t i = 1; matrix[x + i][y] != '#' && (x + i) < columns - 1; i++) //scan all possibilitis like 'w?', 'w??', ...
{
//for (size_t a=0; a<= i; a++)
if (matrix[x + i][y] == '.')
possible_word += '?';
else
possible_word += matrix[x + i][y];
words.push_back(possible_word);
}
}
return words;
}
}
*/
vector<string> Board::get_wildcard(string position)
{
	vector<string> words; //all possible words 
						  //check if valid input 
	if (position.length() == 3 && isupper(position[0]) && !(isupper(position[1])) && (toupper(position[2]) == 'V' || toupper(position[2]) == 'H' || toupper(position[2]) == 'v' || toupper(position[2]) == 'h'))
	{
		//initializing variables position 
		int x = 0;
		int y = 0;
		char orientation = 'a';

		//get true value for variables position  
		transform_to_pos(position, y, x, orientation);


		string possible_word;
		switch (orientation)
		{
		case 'V':
		case 'v':
		{
			if (matrix[x][y] != '.')
				possible_word += matrix[x][y];


			for (size_t i = 1; matrix[x][y + i] != '#' && (y + i) < lines - 1; i++) //scan all possibilitis like 'w?', 'w??', ... 
			{
				//for (size_t a=0; a<= i; a++) 
				if (matrix[x][y + i] == '.')
					possible_word += '?';
				else
					possible_word += matrix[x][y + i];

				words.push_back(possible_word);
			}


			break;
		}

		case 'H':
		case 'h':
		{
			if (matrix[x][y] != '.')
				possible_word += matrix[x][y];


			for (size_t i = 1; matrix[x + i][y] != '#' && (x + i) < columns - 1; i++) //scan all possibilitis like 'w?', 'w??', ... 
			{
				//for (size_t a=0; a<= i; a++) 
				if (matrix[x + i][y] == '.')
					possible_word += '?';
				else
					possible_word += matrix[x + i][y];

				words.push_back(possible_word);
			}


			break;
		}
		}

		return words;
	}
	else
	{
		cout << "Invalid position \n \n";
		return words;
	}

}

const map<string, string> &Board::mapall_words() const
{
	return all_words;
}

bool Board::is_word_at_position(string &position, string &word)
{
	if (all_words.find(position)->second == word)
		return true;
	else
		return false;
}

/*
void Board::show_emptyboard()
{
empty_matrix.resize(lines);
for (size_t i = 0; i < empty_matrix.size(); i++)
matrix[i].resize(columns);
for (size_t i = 0; i < empty_matrix.size(); i++)
fill(matrix[i].begin(), matrix[i].end(), '.');
cout << ' ';
// PRINT name of lines
setcolor(LIGHTRED);
for (size_t i = 0; i < lines; i++)
{
cout << ' ' << name_lines[i];
}
<<<<<<< HEAD
cout << endl;
for (size_t i = 0; i < columns; i++)
{
setcolor(LIGHTRED, BLACK);
cout << name_columns[i] << ' ';
setcolor(BLACK, LIGHTGRAY);
for (size_t a = 0; a < lines; a++)
cout << empty_matrix[a][i] << ' ';
cout << endl;
}
setcolor(WHITE, BLACK);
cout << endl;
}
=======
>>>>>>> 3b6d597760a93b7ed360107da4fd5ecd5c178852
*/


bool Board::is_word_in_board(string &word)
{
	for (const auto& kv_pair : all_words)
	{
		if (kv_pair.second == word)
			return true;
	}
	return false;
}

void Board::create_playboard()
{
	for (size_t i = 0; i < columns; i++)
	{

		for (size_t a = 0; a < lines; a++)
			if (matrix[a][i] != '#')
				matrix[a][i] = '.';

	}
}


/*ector<string> Board::take_words_from_board()
{
	vector<string> words;
	//get words vertical
	for (size_t i = 0; i < columns; i++)
	{
		string line((matrix.at(i)).begin(), (matrix.at(i)).end());
		size_t a = 0;
		int index = 0;
		while (a < line.length())
			if (line.at(a) = '#')
			{
				words.push_back(line.substr(index, a - index + 1));
				index = a ++;

			}


	}
	return words;
}
*/
