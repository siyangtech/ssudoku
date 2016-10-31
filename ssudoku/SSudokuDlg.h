
// ssudokuDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "SSudokuPuzzleMgr.h"
#include <memory>

// CSudokuDlg9x9 dialog
class CSudokuDlg9x9 : public CDialogEx
{
// Construction
public:
	CSudokuDlg9x9(CSudokuPuzzle *puzzle, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SSUDOKU_DIALOG };
#endif

	afx_msg void OnBnClickedButtonLoadPuzzle();
	afx_msg void OnBnClickedButtonSolvePuzzle();
	afx_msg void OnBnClickedButtonGeneratePuzzle();
	afx_msg void OnBnClickedButtonValidatePuzzle();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CButton mLoadGame;
	CButton mSolveGame;
	CButton mGenerateGame;
	CButton mValidateGame;

	CEdit mLevel;

	CEdit mR1C1, mR1C2, mR1C3, mR1C4, mR1C5, mR1C6, mR1C7, mR1C8, mR1C9;
	CEdit mR2C1, mR2C2, mR2C3, mR2C4, mR2C5, mR2C6, mR2C7, mR2C8, mR2C9;
	CEdit mR3C1, mR3C2, mR3C3, mR3C4, mR3C5, mR3C6, mR3C7, mR3C8, mR3C9;
	CEdit mR4C1, mR4C2, mR4C3, mR4C4, mR4C5, mR4C6, mR4C7, mR4C8, mR4C9;
	CEdit mR5C1, mR5C2, mR5C3, mR5C4, mR5C5, mR5C6, mR5C7, mR5C8, mR5C9;
	CEdit mR6C1, mR6C2, mR6C3, mR6C4, mR6C5, mR6C6, mR6C7, mR6C8, mR6C9;
	CEdit mR7C1, mR7C2, mR7C3, mR7C4, mR7C5, mR7C6, mR7C7, mR7C8, mR7C9;
	CEdit mR8C1, mR8C2, mR8C3, mR8C4, mR8C5, mR8C6, mR8C7, mR8C8, mR8C9;
	CEdit mR9C1, mR9C2, mR9C3, mR9C4, mR9C5, mR9C6, mR9C7, mR9C8, mR9C9;

	CEdit* mCellMap[9][9] = {
		&mR1C1, &mR1C2, &mR1C3, &mR1C4, &mR1C5, &mR1C6, &mR1C7, &mR1C8, &mR1C9,
		&mR2C1, &mR2C2, &mR2C3, &mR2C4, &mR2C5, &mR2C6, &mR2C7, &mR2C8, &mR2C9,
		&mR3C1, &mR3C2, &mR3C3, &mR3C4, &mR3C5, &mR3C6, &mR3C7, &mR3C8, &mR3C9,
		&mR4C1, &mR4C2, &mR4C3, &mR4C4, &mR4C5, &mR4C6, &mR4C7, &mR4C8, &mR4C9,
		&mR5C1, &mR5C2, &mR5C3, &mR5C4, &mR5C5, &mR5C6, &mR5C7, &mR5C8, &mR5C9,
		&mR6C1, &mR6C2, &mR6C3, &mR6C4, &mR6C5, &mR6C6, &mR6C7, &mR6C8, &mR6C9,
		&mR7C1, &mR7C2, &mR7C3, &mR7C4, &mR7C5, &mR7C6, &mR7C7, &mR7C8, &mR7C9,
		&mR8C1, &mR8C2, &mR8C3, &mR8C4, &mR8C5, &mR8C6, &mR8C7, &mR8C8, &mR8C9,
		&mR9C1, &mR9C2, &mR9C3, &mR9C4, &mR9C5, &mR9C6, &mR9C7, &mR9C8, &mR9C9 };

	CString mFileName;
	CSudokuPuzzle *mPuzzle;
	CFont mFontSolved;
	CFont mFontGen;
	void UpdateCellMap(const bool isInit = false);
};
