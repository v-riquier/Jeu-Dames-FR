#ifndef GAME_H_
#define GAME_H_

#include "board.h"
#include "time.h"

template <class T>
class sptr
{
private:
	T* pData;
public:
	sptr(T* pVal): pData(pVal) {}
	~sptr()	{delete pData;}
	T& operator*() {return *pData;}
	T* operator->() {return pData;}
};

class game
{
	static const int maxIterDepth;
	mouve* bestM;
	mouve* tempBestM;
	int maxdepth;
	int cdepth;
	bool timeUp;
	bool reachedEnd;
	time_t startTime;
	time_t endTime;
	time_t startTimeD;
	time_t endTimeD;
	void outputMessage();
	int alphabeta(sptr<board>&, int, int, int);

public:
	game();
	sptr<board> currentB;
	void computerTurn();
};


#endif /* GAME_H_ */
