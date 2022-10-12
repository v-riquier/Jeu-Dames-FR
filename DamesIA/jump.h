#ifndef JUMP_H_
#define JUMP_H_

class jump
{
	//previous jump
	jump* prev;

	//the piece jumping
	char jumpingPiece;

	//when there are no next moves, noNext is true
	bool noNext;

	//used to keep track of how many times jump was inserted into a move,
	//increment every time jump is concatenated to a move
	//prevents double freeing of memory
	int numTimes;

	//character jumped over
	char c;

	//start point's x and y coordinate
	int xs;
	int ys;

	//jumped character's point coordinates
	int x;
	int y;

	//end point of the jump
	int xend;
	int yend;

	int key;

	//constructor for each data value
	jump(char jpingp, char piece, int xs, int ys, int xc, int yc, int xe, int ye, jump* p, int k) :
		prev(p), jumpingPiece(jpingp), noNext(true), numTimes(0), c(piece), xs(xs), ys(ys),
		x(xc), y(yc), xend(xe), yend(ye), key(k) {}

	//---------------------------------------------------------------------------------
	//friend classes:
	//---------------------------------------------------------------------------------
	//pointers to jump are deleted in move's destructor
	friend class mouve;
	//board's members create jumps
	friend class board;
};

#endif