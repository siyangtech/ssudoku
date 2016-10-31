#include "stdafx.h"
#include "SSudokuGameGenerator.h"
#include "SSudokuGame.h"
#include <new>
#include "SSudokuGameMgr.h"

SSudokuGameGenerator::~SSudokuGameGenerator()
{
	//release resources
}

int SSudokuGameGenerator::init()
{
	//allocate resources
	return 0;
}

ISSudokuGame * SSudokuGameGenerator::Generate(const int & level)
{
	SSudokuGame * pGame = new (std::nothrow) SSudokuGame(mMgr->GetRowSize(), mMgr->GetColSize());
	if (pGame == 0) {
		return 0;
	}
	

	return pGame;
}