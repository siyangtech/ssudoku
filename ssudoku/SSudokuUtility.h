#pragma once

enum ePuzzleType {
	s9x9 = 0,
	MAX_PUZZLE_TYPE = s9x9
};

extern LPCTSTR PuzzleTypeString(ePuzzleType type);

enum ePuzzleLevel {
	LEVEL_NONE,
	LEVEL_EASY,
	LEVEL_MEDIUM,
	LEVEL_DIFFICULT,
	LEVEL_EVIL,
	MAX_PUZZLE_LEVEL = LEVEL_EVIL
};

enum eSequenceOfDigging {
	SEQ_LR_TB,
	SEQ_S,
	SEQ_JUMPING_ONE,
	SEQ_RANDOM
};

enum ePropagateType {
	PROPG_SWITCH_DIGIT,
	PROPG_SWITCH_COL,
	PROPG_ROTATE
};

#define GENERATE_NUM_GIVENS 11
#define GENERATE_GIVENS_TIMER 10000
#define NUM_TIMES_TO_TRY 5

typedef struct sRate {
	int nGivens;
	int nMinGivensPerUnits;
	int nSkillsUsed;
	int nSearchTimes;
} tPuzzleRate;