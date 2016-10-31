#pragma once
#include "IFSSudokuGenerator.h"

class SSudokuGameMgr;

class SSudokuGameGenerator : public ISSudokuGenerator
{
public:
	SSudokuGameGenerator(SSudokuGameMgr *mgr) : mMgr(mgr) {}
	~SSudokuGameGenerator();

	int init();

	ISSudokuGame * Generate(const int & level);

private:
	SSudokuGameGenerator(const SSudokuGameGenerator &rhs) {}
	SSudokuGameGenerator& operator=(const SSudokuGameGenerator &rhs) {}

	SSudokuGameMgr *mMgr;
};

