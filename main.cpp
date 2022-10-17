#define NDEBUG
#include <iostream>
#include "board.h"
#include <fstream>
#include <list>
#include "game.h"

using namespace std;

int main()
{
	game g;
	bool gameOver = false;
	g.currentB->reset();
	g.currentB->whoComputer();
	while (!gameOver)
	{
		g.currentB->printBoard();
		if (!(g.currentB->jumpsAvailable() || g.currentB->listMoves()))
		{
			gameOver = true;
			cout << "The game is over." << endl;
			cout << endl;
			if (g.currentB->getTurn() == 'r')
				cout << "Player 1 wins." << endl;
			else
				cout << "Player 2 wins." << endl;
			cout << "Do you want to play again? (Y/N):" << endl;
			char answer;
			cin >> answer;
			bool loop = true;
			while (loop)
			{
				if (tolower(answer) == 'y')
				{
					loop = false;
					gameOver = false;
					g.currentB->reset();
					g.currentB->whoComputer();
				}
				else if (tolower(answer) == 'n')
					loop = false;
				else
				{
					cout << "Do you want to play again? (Y/N):" << endl;
					cin >> answer;
				}
			}
		}
		else if (g.currentB->isComputerTurn())
			g.computerTurn();
		else
			/* int clicsdepart[2];
			int clicsarrivee[2];
			clicsdepart[0] = event.mouseButton.x / 75;
			clicsdepart[1] = event.mouseButton.y / 75;
			clicsarrivee[0] = event.mouseButton.x / 75;
			clicsarrivee[1] = event.mouseButton.y / 75;
			currentB->inputCommand(clicsdepart,clicsarrivee);
			*/
			g.currentB->inputCommand();
	}
}
