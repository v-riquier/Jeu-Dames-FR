#include <assert.h>
#include "board.h"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <limits>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::list;
using std::string;
using std::tolower;
using std::copy;

void board::convertCommand(const string& s)
{
	string::const_iterator it = s.begin();
	cout << "(" << (*it) << ", ";
	it += 2;
	cout << (*it) << ") ";
	it += 2;
	while (*it != '-')
	{
		cout << "-> (" << (*it) << ", ";
		it += 2;
		cout << (*it) << ") ";
		it += 2;
	}
}

void board::inputCommand()
{
	printMoves();
	char* deplacement = new char[40];
	cout << "Enter a sequence of integers indicating a move." << endl;
	cout << "Each set of two integers represents a position." << endl;
	cout << "End the sequence with -1." << endl;
	cout << "For example: 2 3 3 2 -1" << endl;
	cout <<	"	represents (2,3) -> (3,2)" << endl;
	cout << "Enter move: ";

	cin.clear();
	cin.getline(deplacement, 40);
	list<mouve*>::iterator it = mlist.begin();
	while (it != mlist.end())
	{
		if ((*it)->command == deplacement)
		{
			cout << "You have chosen the move: ";
			convertCommand((*it)->command);
			cout << endl;
			break;
		}
		++it;
		if (it == mlist.end())
		{
			cin.getline(deplacement, 40);
			it = mlist.begin();
			cout << deplacement << endl;
		}
	}
	makeMove(*it);
	delete deplacement;
}

void board::printBoard()
{
	cout << "Current board:" << endl;
	cout << endl;
	cout << "Player 1 is ";
	printcolor('b');
	cout << " (normal piece) and ";
	printcolor('B');
	cout << " (king)" << endl;
	cout << "Player 2 is ";
	printcolor('n');
	cout << " (normal piece) and ";
	printcolor('N');
	cout <<	" (king)" << endl;
	int count = 0;
	cout << "       " << count;
	++count;
	while (count != 10)
	{
		cout << "     " << count++;
	}
	cout << " " << endl;
	string lineEven = "    |XXXXX|     |XXXXX|     |XXXXX|     |XXXXX|     |XXXXX|     |";
	string lineOdd = "    |     |XXXXX|     |XXXXX|     |XXXXX|     |XXXXX|     |XXXXX|";
	string linebreak = "    -------------------------------------------------------------";

	cout << linebreak << endl;
	for (int i = 0; i != 10; ++i)
	{
		printline(i, lineEven, lineOdd);
		if (i != 9)
			cout << linebreak << endl;
	}
	cout << linebreak << endl;

	cout << endl;
}

void board::printMoves()
{
	if (color == 'b')
		cout << "Player 1 to move." << endl;
	else cout << "Player 2 to move." << endl;
	cout << "The legal moves are:" << endl;
	list<mouve*>::const_iterator it = mlist.begin();
	while (it != mlist.end()) {
		cout << (*it)->command << endl;
		++it;
	}
	for (; it != mlist.end(); ++it)
	{
		cout << "Move: ";
		convertCommand((*it)->command);
		cout << endl;
	}
	cout << endl;
}

void board::makeMove(mouve* m)
{
	if (!m->jpoints.empty())
	{
		list<jump*>::iterator it = m->jpoints.begin();
		for (; it != m->jpoints.end(); ++it)
			plateau[(*it)->x][(*it)->y] = 'e';
	}

	char c = plateau[m->xi][m->yi];
	plateau[m->xi][m->yi] = 'e';
	plateau[m->xf][m->yf] = c;

	handleKinging(m->xf, m->yf);
	changeTurn();
}

void board::undoMove(mouve* m)
{
	if (!m->jpoints.empty())
	{
		for (list<jump*>::iterator it = m->jpoints.begin(); it != m->jpoints.end(); ++it)
		{
			plateau[(*it)->xs][(*it)->ys] = 'e';
			plateau[(*it)->x][(*it)->y] = (*it)->c;
			plateau[(*it)->xend][(*it)->yend] = 'e';
		}
	}
	plateau[m->xf][m->yf] = 'e';
	plateau[m->xi][m->yi] = m->mP;
}

int board::cornerDiagonal(char losing, char winning)
{
	int c = 0;
	if (tolower(plateau[0][0]) == losing || tolower(plateau[1][0]) == losing)
	{
		c += 9;
		if (tolower(plateau[0][0]) == winning)
			c -= 3;
		if (tolower(plateau[1][0]) == winning)
			c -= 3;
		if (tolower(plateau[1][1]) == winning)
			c -= 1;
		if (tolower(plateau[2][0]) == winning)
			c -= 1;
		if (tolower(plateau[2][1]) == winning)
			c -= 1;
		if (tolower(plateau[3][1]) == winning)
			c -= 1;
	}
	if (tolower(plateau[6][3]) == losing || tolower(plateau[7][3]) == losing)
	{
		c += 9;
		if (tolower(plateau[4][2]) == winning)
			c -= 1;
		if (tolower(plateau[5][2]) == winning)
			c -= 1;
		if (tolower(plateau[5][3]) == winning)
			c -= 1;
		if (tolower(plateau[6][2]) == winning)
			c -= 1;
		if (tolower(plateau[6][3]) == winning)
			c -= 3;
		if (tolower(plateau[7][3]) == winning)
			c -= 3;
	}
	return c;
}

int board::evaluate()
{
	int a1 = 0, a2 = 0, b = 0, c = 0, d = 0;
	for (int i = 0; i != 10; ++i)
		for (int j = 0; j != 5; ++j)
		{
			if (plateau[i][j] == 'b')
			{
				a1 += 2;
				if (i == 0)
					b += 9;
				else b += i;
				c += 1;
			}
			else if (plateau[i][j] == 'n')
			{
				a2 -=2;
				if (i == 9)
					b -= 9;
				else b -= (9 - i);
				c -= 1;
			}
			else if (plateau[i][j] == 'B')
			{
				a1 += 3;
				c += 1;
			}
			else if (plateau[i][j] == 'N')
			{
				a2 -= 3;
				c -= 1;
			}
		}
	if (c > 0 && a2 >= -10)
		d -= cornerDiagonal('n', 'b');
	else if (c < 0 && a1 <= 10)
		d += cornerDiagonal('b', 'n');
	a1 *= 100000000;
	a2 *= 100000000;
	b *= 1000000;
	c *= 10000;
	d *= 100;
	int e = rand() % 100;
	if (color == 'n')
		e = -e;
	return a1 + a2 + b + c + d + e;
}

