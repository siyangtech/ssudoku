#include "stdafx.h"
#include "SSudokuSerializer.h"
#include <new>
#include <fstream>
#include <sstream>
#include "SSudokuPuzzle.h"
#include "SSudokuPuzzleMgr.h"

bool CSudokuSerializerText::FileToBoard(const std::string & name, ISSudokuBoard &board)
{
	std::ifstream inFile(name, std::ifstream::in);
	if(inFile.fail()) {
		return 0;
	}

	std::string line;
	std::string content;
	while (std::getline(inFile, line)) {
		content += line;
	}

	inFile.close();

	if (board.GetNumCells() != content.length()) {
		return false;
	}
	board.LoadBoard(content);
	return true;
}

bool CSudokuSerializerText::BoardToFile(const std::string & name, const ISSudokuBoard &board)
{
	return 0;
}

