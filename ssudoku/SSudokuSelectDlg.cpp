// sudokuSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ssudoku.h"
#include "afxdialogex.h"
#include "SSudokuSelectDlg.h"
#include "SSudokuPuzzleMgr.h"


// CSudokuSelectDlg dialog

IMPLEMENT_DYNAMIC(CSudokuSelectDlg, CDialogEx)

CSudokuSelectDlg::CSudokuSelectDlg(CWnd* pParent /*=NULL*/)
	: mPuzzleType(s9x9), CDialogEx(IDD_SSUDOKU_SELECTOR, pParent)
{

}

CSudokuSelectDlg::~CSudokuSelectDlg()
{
}

void CSudokuSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_SELECT, mSelectBox);
}

BOOL CSudokuSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for (int i = 0; i < MAX_PUZZLE_TYPE+1; i++) {
		mSelectBox.AddString(PuzzleTypeString((ePuzzleType)i));
	}
	mSelectBox.SetCurSel(mPuzzleType);
	
	return TRUE;
}

void CSudokuSelectDlg::OnTypeChanged()
{
	mPuzzleType = (ePuzzleType)mSelectBox.GetCurSel();
}

ePuzzleType CSudokuSelectDlg::GetPuzzleType()
{
	//mPuzzleType = (ePuzzleType)mSelectBox.Select;
	return mPuzzleType;
}

BEGIN_MESSAGE_MAP(CSudokuSelectDlg, CDialogEx)
	ON_CBN_EDITUPDATE(IDC_COMBO_SELECT, &CSudokuSelectDlg::OnTypeChanged)
END_MESSAGE_MAP()


// CSudokuSelectDlg message handlers
