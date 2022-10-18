#ifndef JUMP_H_
#define JUMP_H_

class jump
{
	jump* prev;
	char jumpingPiece;
	bool noNext;
	int numTimes;
	char c;
	int xs;
	int ys;
	int x;
	int y;
	int xend;
	int yend;
	int key;
	jump(char jpingp, char piece, int xs, int ys, int xc, int yc, int xe, int ye, jump* p, int k) :
		prev(p), jumpingPiece(jpingp), noNext(true), numTimes(0), c(piece), xs(xs), ys(ys),
		x(xc), y(yc), xend(xe), yend(ye), key(k) {}

	friend class mouve;
	friend class board;
};

#endif