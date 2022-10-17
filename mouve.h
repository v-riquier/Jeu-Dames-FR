#ifndef MOUVE_H_
#define MOUVE_H_

#include <list>
#include <string>
#include "jump.h"

using std::list;
using std::string;

class mouve
{
	// moving piece
	char mP;

	// start point's coordinates
	int xi;
	int yi;

	// end point's coordinates
	int xf;
	int yf;

	// command used to map a string to the move
	// used for when the player enters a string for a move
	string command;

	// list storing all the jumps made by the move
	list<jump *> jpoints;

	// constructor for move
	mouve(char c, int xs, int ys, int xe, int ye) : mP(c), xi(xs), yi(ys), xf(xe), yf(ye) {}

	// frees the memory allocated on the heap for each jump pointer
	// avoids double freeing of memory by keeping track of the
	// number of times each jump was added to a moves jump list
	// first decrements each jump's numTimes
	// only deletes the jump if numTimes equals 0
	// this is necessary for multiple moves utilizing the same jumps,
	// such as in the case of branching jumps:
	//			1
	//		2
	//	3		3'
	//		4
	//  1 -> 2 would have numTimes equal to 2 since the jump would be utilized twice,
	// once for each move
	~mouve()
	{
		for (list<jump *>::iterator it = jpoints.begin(); it != jpoints.end(); ++it)
		{
			--(*it)->numTimes;
			if ((*it)->numTimes == 0)
			{
				delete (*it);
			}
		}
	}

	//---------------------------------------------------------------------------------
	// friend classes:
	//---------------------------------------------------------------------------------
	// board creates moves and it accesses many of move's members
	friend class board;
	// move's member: command is accessed in game::outputMessage()
	friend class game;
};

#endif