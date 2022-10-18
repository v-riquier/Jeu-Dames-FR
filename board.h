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
	//tableau de 10x5 car la moitié des cases ne sont pas utilisées
	char plateau[10][5];

	//couleur du pion : b pour blanc et n pour noir
	char color;

	//tableau de booléen pour dire si les participants sont des joueurs ou des IA
	//[0] pour blanc, [1] pour noir
	static bool isComputer[2];

	board();
	~board();
	board(const board &);

	void changeTurn()
	{
		if (color == 'n')
		{
			color = 'b';
		}
		else
		{
			color = 'n';
		}
	}

	static void convertCommand(const std::string &);

	// si un pion atteint l'autre coté du plateau, il devient une dame
	void handleKinging(const int &x, const int &y)
	{
		if (x == 0 && plateau[x][y] == 'n')
		{
			plateau[x][y] = 'N';
		}
		if (x == 9 && plateau[x][y] == 'b')
		{
			plateau[x][y] = 'B';
		}
	}

	// retourne true si la position plateau[i][j] est une position valide
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

	void modifyBoard(std::ifstream &);
	void remove_carriage_return(std::string &);

	int createkey(int, int, int, int, int, int);
	int reverse(int);
	void createJump(std::list<jump *> &, char, int, int, int, int, int, int, jump *);
	void createJumpMove(std::list<jump *> &);
	void jumpAvailable(std::list<jump *> &, char c, int, int, jump *);
	bool jumpConditions(int, int, int, int);

	void checkNeighbors(int &, int &);
	void createMove(const int &, const int &, int, int);

	void convert(const int &, const int &, std::string &);

	int convertY(const int &x, const int &y);
	
	void printline(const int &, const std::string &, const std::string &);

	void printcolor(const char &);

	static int timeLimit;

	std::list<mouve *> mlist;

	//affiche les mouvements du joueur actuel
	void printMoves();

	void makeMove(mouve *);

	void undoMove(mouve *);

	int cornerDiagonal(char, char);

	int evaluate();

	friend class game;
	template <class T>
	friend class sptr;

public:
	// création du plateau
	void reset();

	// change un des joueurs en IA
	static void whoComputer();

	// affiche le plateau
	void printBoard();

	bool jumpsAvailable();
	bool listMoves();

	// renvoie la couleur du joueur actuel
	char getTurn()
	{
		return color;
	}

	bool isComputerTurn()
	{
		if (color == 'b' && isComputer[0])
		{
			return true;
		}
		if (color == 'n' && isComputer[1])
		{
			return true;
		}
		return false;
	}

	void inputCommand();
};

#endif /* BOARD_H_ */
