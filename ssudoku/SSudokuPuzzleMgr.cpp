#include "stdafx.h"
#include "SSudokuPuzzleMgr.h"
#include "SSudokuSerializer.h"
#include "SSudokuPuzzle.h"
#include "SSudokuDlg.h"
#include "SSudokuSelectDlg.h"

CSudokuPuzzleMgr::CSudokuPuzzleMgr(): mPuzzleType(s9x9), mPuzzleDlg(NULL), mPuzzle(NULL) 
{
}

CSudokuPuzzleMgr::~CSudokuPuzzleMgr()
{
	Cleanup();
}

bool CSudokuPuzzleMgr::Initialize()
{
	// select puzzle type
	ePuzzleType type;
	CSudokuSelectDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		type = dlg.GetPuzzleType();
	}
	else if (nResponse == IDCANCEL)
	{
		return false;
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		// TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
		return false;
	}

	return true;
}

void CSudokuPuzzleMgr::Cleanup()
{
	if (mPuzzleDlg) {
		delete mPuzzleDlg;
		mPuzzleDlg = NULL;
	}
	if (mSerializer) {
		delete mSerializer;
		mSerializer = NULL;
	}
	if (mPuzzle) {
		delete mPuzzle;
		mPuzzle = NULL;
	}
}

bool CSudokuPuzzleMgr::Start(void)
{
	bool result = true;

	switch (mPuzzleType) {
	case s9x9:
		mSerializer = new CSudokuSerializerText(this);
		if (mSerializer == NULL) {
			result = false;
			break;
		}
		mPuzzle = new CSudokuPuzzle(*mSerializer);
		if (mPuzzle == NULL) {
			result = false;
			break;
		}
		mPuzzle->Initialize(mPuzzleType);

		mPuzzleDlg = new CSudokuDlg9x9(mPuzzle);
		if (mPuzzleDlg == NULL) {
			result = false;
			break;
		}
		break;
	default:
		TRACE(traceAppMsg, 0, "Warning: sudoku type %s is not supported at this point.\n",
				PuzzleTypeString(mPuzzleType));
		result = false;
		break;
	}

	if (result == true) {
		INT_PTR nResponse = mPuzzleDlg->DoModal();
		if (nResponse == IDOK)
		{
		}
		else if (nResponse == IDCANCEL)
		{
		}
		else if (nResponse == -1)
		{
			TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
			result = false;
		}
	}
	
	Cleanup();
	
	return result;
}