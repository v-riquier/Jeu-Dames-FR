#ifndef MOUVE_H_
#define MOUVE_H_

#include <list>
#include <string>
#include "jump.h"

using std::list;
using std::string;

class mouve
{
	char mP;
	int xi;
	int yi;
	int xf;
	int yf;
	string command;
	list<jump *> jpoints;
	mouve(char c, int xs, int ys, int xe, int ye) : mP(c), xi(xs), yi(ys), xf(xe), yf(ye) {}
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
	friend class board;
	friend class game;
};

#endif