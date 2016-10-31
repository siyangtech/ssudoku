#include "stdafx.h"
#include "SSudokuSerializerText.h"
#include <new>
#include <fstream>
#include <sstream>
#include "SSudokuGame.h"
#include "SSudokuGameMgr.h"

int SSudokuSerializerText::init()
{
	return 0;
}

ISSudokuGame * SSudokuSerializerText::FileToGame(const std::string & name)
{
	std::ifstream inFile(name, std::ifstream::in);
	if(inFile.fail()) {
		return 0;
	}

	SSudokuGame *pGame = new (std::nothrow) SSudokuGame(mMgr->GetRowSize(), mMgr->GetColSize());
	if (pGame == 0) {
		inFile.close();
		return 0;
	}

	std::string line;
	std::vector< std::string > content;
	int r = 0;
	while (std::getline(inFile, line)) {
		content.push_back(line);
		++r;
	}
	if (r != mMgr->GetRowSize()) {
		inFile.close();
		delete pGame;
		return 0;
	}

	inFile.close();

	pGame->Read(content);
	return pGame;
}

int SSudokuSerializerText::GameToFile(const std::string & name, const ISSudokuGame * pGame)
{
	return 0;
}

