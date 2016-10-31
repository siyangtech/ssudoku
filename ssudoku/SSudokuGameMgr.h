#pragma once
#include <unordered_map>
#include <string>

class SSudokuSerializerText;
class SSudokuGameGenerator;
class ISSudokuGame;

class SSudokuGameMgr
{
public:
	SSudokuGameMgr() {}
	~SSudokuGameMgr();

	int init();

	ISSudokuGame* GetGameFromFile(const std::string &fileName, const std::string &fileExt);
	ISSudokuGame* GetGameFromGenerator(const int & level);
	
	int GetRowSize() const { return ROW_SZ; }
	int GetColSize() const { return COL_SZ; }
	
private:
	static const int ROW_SZ = 9;
	static const int COL_SZ = 9;

	SSudokuGameMgr(const SSudokuGameMgr & rhs) {}
	SSudokuGameMgr& operator=(const SSudokuGameMgr & rhs) {}

	SSudokuGameGenerator *mGenerator;
	SSudokuSerializerText *mSerializer;
};