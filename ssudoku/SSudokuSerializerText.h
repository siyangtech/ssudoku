#pragma once
#include "ISSudokuSerializer.h"

class SSudokuGameMgr;

class SSudokuSerializerText : public ISSudokuSerializer
{
public:
	explicit SSudokuSerializerText(SSudokuGameMgr *mgr) : mMgr(mgr) {}
	~SSudokuSerializerText(){}

	int init();

	virtual ISSudokuGame * FileToGame(const std::string & name);
	virtual int GameToFile(const std::string & name, const ISSudokuGame * pGame);

private:

	SSudokuSerializerText(const SSudokuSerializerText & rhs) {}
	SSudokuSerializerText& operator=(const SSudokuSerializerText & rhs) {}

	SSudokuGameMgr *mMgr;

};