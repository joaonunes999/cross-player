#include "board.h"
#include "cwplayer.h"
#include "dictionary.h"
#include <ctime>

int main()
{
	// ================= INTERFACE ================= //
	cout << "CROSSWORDS PLAYER " << endl;
	cout << "================================================" << endl << endl;
	cout << "INSTRUCTIONS: " << endl;
	cout << "The user enters his name " << endl;
	cout << "You are presented with a timer you are playing" << endl << endl;
	cout << "------------------------------------------------" << endl << endl;

	srand(time(NULL));
	
	cwplayer player1;
	player1.menu();

}