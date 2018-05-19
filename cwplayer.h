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

	void start_time();
	void end_time();

private:
	int startime, endtime;
	string name, dictionaryname;
	Board board1;
	Dictionary dictionary1;
};

#endif // CROSS_PLAYER_H