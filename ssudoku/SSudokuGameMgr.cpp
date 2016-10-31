#include "stdafx.h"
#include "SSudokuGameMgr.h"
#include "SSudokuGameGenerator.h"
#include "SSudokuSerializerText.h"
#include "SSudokuGame.h"

SSudokuGameMgr::~SSudokuGameMgr()
{
	delete mGenerator;
	delete mSerializer;
}

int SSudokuGameMgr::init()
{
	mGenerator = new (std::nothrow) SSudokuGameGenerator(this);
	if(mGenerator == 0) {
		return -1;
	}

	mSerializer = new (std::nothrow) SSudokuSerializerText(this);
	if (mSerializer == 0) {
		return -1;
	}

	SSudokuGame::Initialize();

	return 0;
}

ISSudokuGame * SSudokuGameMgr::GetGameFromFile(const std::string &fileName, const std::string &fileExt)
{
	return mSerializer->FileToGame(fileName);
}

ISSudokuGame * SSudokuGameMgr::GetGameFromGenerator(const int & level)
{
	return mGenerator->Generate(level);
}