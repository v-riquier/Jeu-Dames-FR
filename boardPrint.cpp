#include <assert.h>
#include "board.h"
#include <iostream>
#include <list>
#include <string>

using std::endl;
using std::cin;
using std::cout;
using std::getline;
using std::endl;
using std::list;
using std::string;


void board::convert(const int& x, const int& y, string& s)
{
	//assert(0 <= x && x <= 7 && 0 <= y && y <= 3);
	 char c1 = '0' + x;
	 char c2;
	 if (x % 2 == 0)
	 {
		 c2 = '0' + (2*y + 1);
	 }
	 else
	 {
		 c2 = '0' + (2*y);
	 }
	 s += c1;
	 s += ' ';
	 s += c2;
	 s += ' ';
}

inline int board::convertY(const int& x, const int& y)
{
    if (x % 2 == 0)
        return (2*y + 1);
    else return (2*y);
}

void board::printline(const int& i, const string& lineEven, const string& lineOdd)
{
	if (i % 2 == 0)
	{
		cout << lineEven << endl;
		cout << "  " << i << " |XXXXX|";
		for (int j = 0; j != 4; ++j)
		{
			cout << "  ";
			printcolor(plateau[i][j]);
			cout << "  |XXXXX|";
		}
		cout << "  ";
		printcolor(plateau[i][4]);
		cout << "  |" << endl;;
		cout << lineEven << endl;
	}
	else
	{
		cout << lineOdd << endl;
		cout << "  " << i << " |";
		for (int j = 0; j != 4; ++j)
		{
			cout << "  ";
			printcolor(plateau[i][j]);
			cout << "  |XXXXX|";
		}
		cout << "  ";
		printcolor(plateau[i][4]);
		cout << "  |XXXXX|" << endl;;
		cout << lineOdd << endl;
	}
}

void board::printcolor(const char& c)
{
	if (c == 'e')
		cout << ' ';
	else
	{
		cout << c;
	}
}

void board::whoComputer()
{
	bool b = true;
	char c = ' ';
	while (b)
	{
		cout << "Will player # 1 be a computer? (Y/N):" << endl;
		cin >> c;
		if (tolower(c) == 'y')
		{
			board::isComputer[0] = true;
			b = false;
		}
		else if (tolower(c) == 'n')
		{
			board::isComputer[0] = false;
			b = false;
		}
	}
	b = true;
	c = ' ';
	while (b)
	{
		cout << "Will player # 2 be a computer? (Y/N):" << endl;
		cin >> c;
		if (tolower(c) == 'y')
		{
			board::isComputer[1] = true;
			b = false;
		}
		else if (tolower(c) == 'n')
		{
			board::isComputer[1] = false;
			b = false;
		}
	}
	if (board::isComputer[0] == true || board::isComputer[1] == true)
	{
		cout << "Enter a time limit for the computer in seconds (3-60):" << endl;
		cin >> timeLimit;
		if (timeLimit > 60 || timeLimit < 3)
			cin >> timeLimit;
	}
}

