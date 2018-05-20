#include "board.h"
#include "dictionary.h"
#include "cwplayer.h"
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

void cwplayer::menu() // The user enters an option
{
	unsigned int option;
	cout << "OPTIONS: " << endl;
	cout << "1 - Play Crosswords " << endl;
	cout << "0 - Exit" << endl << endl;

	cout << "Option ? ";
	cin >> option;

	switch (option)
	{

	case 1:
		playwords();
		dictionary1.show_tracks();
		start_time();
		addwordplayer();
		break;

	case 0:
		cout << " End of program " << endl;
		exit(1);

	default:
		cout << "Option is invalid" << endl;
		cout << "Please enter a valid option" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		menu();
	}
}

void cwplayer::playwords()
{
	cout << "Enter your name: ";
	
	while (true)
	{
		cin >> name;

		if (!cin.fail()) 
		break; 
		else {
			cin.clear();
			cin.ignore(10000, '\n');;
			cerr << "Invalid input";
			cout << "Enter your name ";
		}
	}

	ifstream boardfile, dictionaryfile;

	string boardfilename, dictionaryfilename, line;
	int lines = 1;
	int columns = 0;

	cout << "Enter the board file name you want play: ";
	cin >> boardfilename;

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
	getline(boardfile, dictionaryfilename);
	this->dictionaryname = dictionaryfilename;
	Dictionary dictionary1(dictionaryfilename);
	
	getline(boardfile, line); // Skip empty line

	mapall_words = board1.mapall_words();
	for (auto &it: mapall_words)
	{
		string position = it.first;
		string word = it.second;
		dictionary1.boardwordspair(position, word);

	}
	
	//board1.show_emptyboard();
	//board1.fill_finished();
	//board1.show();

}

void cwplayer::start_time()
{
	startime = clock();
}

void cwplayer::end_time()
{
	endtime = clock();
}

void cwplayer::addwordplayer()
{
	string position, word, option;
	bool continued = true;

	while (continued) {

		cout << "Position (LCD formart) ?: ";
		cin >> position;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cerr << "Invalid input. " << endl;
			exit(0);
		}

		cout << "Insert a valid word (- remove / ? - clue): ";
		cin >> word;
		if (word == "-")
		{
			board1.remove_word(position);
			insertedwords.erase(position);
		}
		else if (word == "?")
		{
			dictionary1.other_track(position);
		}
		else if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cerr << "Invalid word, nothing added." << endl;
			exit(1);
		}
		else
		{
			insertedwords.insert(pair<string, string>(position, word));
			board1.addword(position, word);
		}

		// check if board is complete
		if (insertedwords.size() == mapall_words.size())
		{
			cout << "The board is complete, do you want to finish? (yes/no): ";

			do
			{
				cin >> option;
				if (option == "no")
				{
					addwordplayer();
				}
				else if (option == "yes")
				{
					continued = false;
					//funcao checking
				}
				else {
					cin.clear();
					cin.ignore(1000, '\n');
					cerr << "Insert a valid option (yes/no): ";
				}
			} while (option != "yes" && option != "no");
		}
	}
}