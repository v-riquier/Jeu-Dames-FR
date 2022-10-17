#ifndef BOARD_H_
#define BOARD_H_

#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include "jump.h"
#include "mouve.h"

class board
{
	// first coordinate is x, second is y
	// x is vertical down, y is horizontal
	// don't need an 8x8 array since only half the spaces are legal positions for pieces
	char arr[10][5];

	//'b' for black, 'r' for red
	// indicates who's turn it is
	char color;

	//[0] for black, [1] for red
	// default initialized to false since it's a static array
	static bool isComputer[2];

	//---------------------------------------------------------------------------------
	// functions for board creation, found in board.cpp:
	//---------------------------------------------------------------------------------
	// 1: constructor for initializing an initial board
	// 2: destructor deallocates memory for all the moves in mlist
	// 3: copy constructor
	//   copies over all data values except the move list
	//   useful for creating new boards for each move in alpha-beta search
	// 4: changeTurn(), called after a move is made
	//   called in game.cpp by alphabeta
	//   called by makeMove, which is found in boardPublic.cpp
	//   is inlined
	// 5: converts a command stored in the form 2 3 3 2 -1 to (2,3) -> (3, 2)
	//   called in inputCommand in boardPrint.cpp
	// 6: create a list of moves by calling this
	//   is called each time a new board gets created after a move is made
	//   called by evaluate, in boardPublic.cpp
	//   is inlined
	board();
	~board();
	board(const board &);

	void changeTurn()
	{
		if (color == 'r')
		{
			color = 'b';
		}
		else
		{
			color = 'r';
		}
	}

	static void convertCommand(const std::string &);

	// if a red piece 'r' reaches the red side's end, it becomes a red king 'R'
	// if a black piece 'b' reaches the black side's end, it becomes a black king 'B'
	// called at the end of the makeMove function, which is found in boardPublic.cpp
	// is inlined
	void handleKinging(const int &x, const int &y)
	{
		if (x == 0 && arr[x][y] == 'r')
		{
			arr[x][y] = 'R';
		}
		if (x == 7 && arr[x][y] == 'b')
		{
			arr[x][y] = 'B';
		}
	}

	// returns true if the position arr[i][j] is a valid position on the checker board
	// called by jumpConditions, which is found in boardJumps.cpp
	// called by createMove, which is found in boardMoves.cpp
	// is inlined
	bool isValidPos(int i, int j)
	{
		if (i >= 0 && i < 10 && j >= 0 && j < 5)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// create a board from an input file:
	void modifyBoard(std::ifstream &);

	// function for fixing strings obtained via getline
	// eliminate the \r character in a string or the \n character
	// called by modifyBoard in board.cpp
	void remove_carriage_return(std::string &);

	//---------------------------------------------------------------------------------
	// functions for jumps: found in boardJumps.cpp
	//---------------------------------------------------------------------------------
	// createkey is inlined
	int createkey(int, int, int, int, int, int);
	int reverse(int);
	void createJump(std::list<jump *> &, char, int, int, int, int, int, int, jump *);
	void createJumpMove(std::list<jump *> &);
	void jumpAvailable(std::list<jump *> &, char c, int, int, jump *);
	bool jumpConditions(int, int, int, int);

	//---------------------------------------------------------------------------------
	// functions for regular moves, found in boardMoves.cpp
	//---------------------------------------------------------------------------------
	void checkNeighbors(int &, int &);
	void createMove(const int &, const int &, int, int);

	//---------------------------------------------------------------------------------
	// functions for printing, found in boardPrint.cpp
	//---------------------------------------------------------------------------------
	// converts a point to string form and appends it to command list for a move
	// called by createJumpMove in boardJumps.cpp
	// called by createMove in boardMoves.cpp
	void convert(const int &, const int &, std::string &);

	// used for printing out moves, converting the y coordinate in the matrix
	// to the coordinate on the expanded 8x8 board
	// called in printMoves in boardPrint.cpp
	int convertY(const int &x, const int &y);

	// prints out a row of the checkers board
	// called by boardPrint in boardPublic.cpp
	void printline(const int &, const std::string &, const std::string &);

	// change text color for red and black pieces
	void printcolor(const char &);
	//---------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------
	// FUNCTIONS AND MEMBERS UTILIZED DIRECTLY IN GAME.H:
	//-------------------------------------------------------------------------------------
	// timer for the computer
	static int timeLimit;

	// list of moves for the board:
	std::list<mouve *> mlist;

	//---------------------------------------------------------------------------------
	// functions found in boardPublic.cpp, functions called in game.cpp
	//---------------------------------------------------------------------------------

	// prints moves in order listed in the list
	// called by inputCommand in boardPrint.cpp
	// called by game::computerTurn in game.cpp
	void printMoves();

	// makes the move
	// should be used on a copy of a board when alpha-beta searching
	void makeMove(mouve *);

	// reverses a move
	void undoMove(mouve *);

	// checks double corners and diagonals near end game
	// gives points for occupying a double corner for losing player
	// winning player gets points for occupying a diagonal near losing player's corner
	// called by evaluate() in boardPublic.cpp
	int cornerDiagonal(char, char);

	// Evaluation function, need to do
	// will be implemented in alpha-beta search
	int evaluate();

	//---------------------------------------------------------------------------------
	// friend classes:
	//---------------------------------------------------------------------------------
	// game accesses many of move's functions (see above divider)
	friend class game;
	// sptr is a smart pointer class that automatically manages memory for boards created on the heap
	template <class T>
	friend class sptr;

public:
	// reset the board after game over
	// called by startup, which is in boardPublic.cpp
	void reset();

	// modifies who is a computer, called by startup
	static void whoComputer();

	// expands and prints board
	void printBoard();

	bool jumpsAvailable();
	bool listMoves();

	// gets the current color's turn
	// is inlined
	char getTurn()
	{
		return color;
	}

	// determines whether or not the current turn is a computer's turn
	// called to run alpha-beta search if necessary
	// is inlined
	bool isComputerTurn()
	{
		if (color == 'b' && isComputer[0])
		{
			return true;
		}
		if (color == 'r' && isComputer[1])
		{
			return true;
		}
		return false;
	}

	// prints out directions and available moves
	// need to add computer moves to it
	void inputCommand();
};

#endif /* BOARD_H_ */