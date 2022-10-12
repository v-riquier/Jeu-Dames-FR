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

// initializes everything for the checker board
board::board()
{
	reset();
}

// destructor deallocates memory for all the moves in mlist
board::~board()
{
	while (!mlist.empty())
	{
		delete mlist.front();
		mlist.pop_front();
	}
}

// copy constructor: copies over all data values except the move list
// useful for creating new boards for each move in alpha-beta search
board::board(const board &b) : color(b.color)
{
	for (int i = 0; i != 10; ++i)
	{
		for (int j = 0; j != 5; ++j)
		{
			arr[i][j] = b.arr[i][j];
		}
	}
}

// resets the board, called by printEBoard in boardPublic.cpp
// create the start board
// first four rows are filled with black pieces
// next two rows are empty
// last four rows are filled with red pieces
void board::reset()
{
	color = 'b';
	/*for (int i = 0; i != 4; ++i)
	{
		for (int j = 0; j != 5; ++j)
		{
			arr[i][j] = 'b';
		}
	}
	for (int i = 4; i != 6; ++i)
	{
		for (int j = 0; j != 5; ++j)
		{
			arr[i][j] = 'e';
		}
	}
	for (int i = 6; i != 10; ++i)
	{
		for (int j = 0; j != 5; ++j)
		{
			arr[i][j] = 'r';
		}
	}*/
	for (int i = 0; i != 10; ++i)
	{
		for (int j = 0; j != 5; ++j)
		{
			arr[i][j] = 'e';
		}
	}
}

// store it all in a list
// parse each line
// modify the board per line
// last line, the 9th line, will be turn
// a sample line of input would be
// e b b e
// the last line, get the current piece color's turn
// set color equal to it
// make sure the color is valid
void board::modifyBoard(ifstream &fin)
{
	string line;
	int count = 0;
	while (getline(fin, line) && count != 10)
	{
		remove_carriage_return(line);
		stringstream ss(line);
		for (int jIndex = 0; jIndex != 5; ++jIndex)
			ss >> arr[count][jIndex];
		++count;
	}

	getline(fin, line);
	remove_carriage_return(line);
	stringstream ss(line);
	ss >> color;
	color = tolower(color);
	assert(color == 'b' || color == 'r');
}

// eliminate the \r character in a string or the \n character
inline void board::remove_carriage_return(std::string &line)
{
	if (*line.rbegin() == '\r' || *line.rbegin() == '\n')
	{
		line.erase(line.length() - 1);
	}
}
