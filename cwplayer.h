#ifndef CROSS_PLAYER_H
#define CROSS_PLAYER_H

#include "board.h"
#include "dictionary.h"

class cwplayer

{
public:

	void menu();
	/* Displays a menu with options */
	void start_time();
	void end_time();
	
private:
	int startime, endtime;
	int counterclues;
	string nameplayer, dictionaryname;
	Board board1;
	Dictionary dictionary1;
	map<string, string> insertedwords;
	map<string, string> mapall_words;
	void playwords();
	void addwordplayer();
	bool finalchecking();
	bool finalcheck();
	void save_game();
	void finalgame();
};

#endif // CROSS_PLAYER_H