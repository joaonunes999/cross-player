#ifndef CROSS_PLAYER_H
#define CROSS_PLAYER_H

#include "board.h"
#include "dictionary.h"

class cwplayer

{
public:

	void menu();
	/* Displays a menu with options */
	void playwords();

private:
	string name;
	string dictionaryname;
	Board board1;
};

#endif // CROSS_PLAYER_H