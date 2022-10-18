#include <assert.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "game.h"
#include <iostream>
#include <limits>
#include <list>
#include "board.h"
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::max;
using std::min;

const int game::maxIterDepth = 20;

game::game() : currentB(sptr<board>(new board())), bestM(NULL), tempBestM(NULL), maxdepth(0),
cdepth(0), timeUp(false), reachedEnd(false), startTime(0), endTime(0),
startTimeD(0), endTimeD(0) {}

void game::computerTurn()
{
	currentB->printMoves();
	cout << "The computer will make a move." << endl;

	if (currentB->mlist.size() == 1)
	{
		bestM = currentB->mlist.front();
		time(&startTime);
		time(&endTime);
		cdepth = 0;
	}
	else
	{
		time(&startTime);
		for (int i = 1; i != maxIterDepth; ++i)
		{
			time(&startTimeD);

			maxdepth = i;

			alphabeta(currentB, i, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
			time(&endTimeD);

			if (difftime(endTimeD, startTimeD) >= ((board::timeLimit) / 2))
			{
				time(&endTime);
				timeUp = true;
				break;
			}

			if (timeUp)
				break;
			else
				bestM = tempBestM;

			if (reachedEnd)
				break;
		}
	}
	assert(bestM != NULL);

	outputMessage();
}
void game::outputMessage()
{
	currentB->makeMove(bestM);
	cout << "Completed search to depth " << cdepth << "." << endl;
	if (timeUp && cdepth != maxIterDepth && !reachedEnd)
		cout << "Out of time searching to depth " << cdepth + 1 << "." << endl;
	cout << "Searched for a total of " << difftime(endTime, startTime) << " seconds" << endl;
	cout << "The chosen move is: ";
	board::convertCommand(bestM->command);
	cout << endl;

	bestM = NULL;
	tempBestM = NULL;
	timeUp = false;
	reachedEnd = false;
}

int game::alphabeta(sptr<board> &b, int depth, int alpha, int beta)
{
	if (depth != maxdepth && (!b->jumpsAvailable() || !b->listMoves()))
	{
		reachedEnd = true;
		cdepth = maxdepth;
		if (b->getTurn() == 'n')
			return std::numeric_limits<int>::max();
		else
			return std::numeric_limits<int>::min();
	}
	reachedEnd = false;
	if (depth == 0)
		return b->evaluate();
	list<mouve *>::iterator iter = b->mlist.begin();

	int localalpha = std::numeric_limits<int>::min();
	int localbeta = std::numeric_limits<int>::max();

	if (b->getTurn() == 'b')
	{
		for (; iter != b->mlist.end(); ++iter)
		{
			time(&endTime);

			if (difftime(endTime, startTime) >= (board::timeLimit - 1))
			{
				timeUp = true;
				break;
			}

			b->makeMove(*iter);
			sptr<board> newB(new board(*b));
			int value = alphabeta(newB, depth - 1, alpha, min(localbeta, beta));
			b->undoMove(*iter);
			b->changeTurn();

			if (value > alpha)
			{
				alpha = value;
				if (depth == maxdepth)
					tempBestM = (*iter);
			}

			if (alpha >= beta && depth < maxdepth)
				return alpha;
		}

		if (!timeUp && depth == maxdepth)
			cdepth = depth;

		return alpha;
	}

	else
	{
		for (; iter != b->mlist.end(); ++iter)
		{
			time(&endTime);
			if (difftime(endTime, startTime) >= (board::timeLimit - 1))
			{
				timeUp = true;
				break;
			}
			b->makeMove(*iter);
			sptr<board> newB(new board(*b));
			int value = alphabeta(newB, depth - 1, max(localalpha, alpha), beta);
			b->undoMove(*iter);
			b->changeTurn();

			if (value < beta)
			{
				beta = value;
				if (depth == maxdepth)
					tempBestM = (*iter);
			}

			if (alpha >= beta)
				return beta;
		}

		if (!timeUp && depth == maxdepth)
			cdepth = depth;

		return beta;
	}
}
