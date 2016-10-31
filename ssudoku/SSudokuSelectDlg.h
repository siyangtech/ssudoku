
#pragma once
#include "afxwin.h"
#include "SSudokuPuzzleMgr.h"

class CSudokuSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSudokuSelectDlg)

public:
	CSudokuSelectDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSudokuSelectDlg();

	ePuzzleType GetPuzzleType();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SSUDOKU_SELECTOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// implementation
	virtual BOOL OnInitDialog();

private:

	CComboBox mSelectBox;
	ePuzzleType mPuzzleType;

	void OnTypeChanged(void);

	DECLARE_MESSAGE_MAP()
};
