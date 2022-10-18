#include <assert.h>
#include "board.h"
#include <fstream>
#include <cctype>
#include <list>
#include <string>
#include <sstream>

using std::getline;
using std::ifstream;
using std::list;
using std::string;
using std::stringstream;

bool board::isComputer[2];

int board::timeLimit = 0;

board::board()
{
	reset();
}

board::~board()
{
	while (!mlist.empty())
	{
		delete mlist.front();
		mlist.pop_front();
	}
}

board::board(const board &b) : color(b.color)
{
	for (int i = 0; i != 10; ++i)
	{
		for (int j = 0; j != 5; ++j)
		{
			plateau[i][j] = b.plateau[i][j];
		}
	}
}

void board::reset()
{
	color = 'b';
	for (int i = 0; i != 4; ++i)
	{
		for (int j = 0; j != 5; ++j)
		{
			plateau[i][j] = 'b';
		}
	}
	for (int i = 4; i != 6; ++i)
	{
		for (int j = 0; j != 5; ++j)
		{
			plateau[i][j] = 'e';
		}
	}
	for (int i = 6; i != 10; ++i)
	{
		for (int j = 0; j != 5; ++j)
		{
			plateau[i][j] = 'n';
		}
	}
}

void board::modifyBoard(ifstream &fin)
{
	string line;
	int count = 0;
	while (getline(fin, line) && count != 10)
	{
		remove_carriage_return(line);
		stringstream ss(line);
		for (int jIndex = 0; jIndex != 5; ++jIndex)
			ss >> plateau[count][jIndex];
		++count;
	}

	getline(fin, line);
	remove_carriage_return(line);
	stringstream ss(line);
	ss >> color;
	color = tolower(color);
	assert(color == 'b' || color == 'n');
}

inline void board::remove_carriage_return(std::string &line)
{
	if (*line.rbegin() == '\r' || *line.rbegin() == '\n')
	{
		line.erase(line.length() - 1);
	}
}
