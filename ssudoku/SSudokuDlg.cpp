
// ssudokuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ssudoku.h"
#include "SSudokuDlg.h"
#include "afxdialogex.h"
#include "SSudokuPuzzle.h"
#include "SSudokuBoard.h"
#include <new>

#if 0
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSudokuDlg9x9 dialog

CSudokuDlg9x9::CSudokuDlg9x9(CSudokuPuzzle *puzzle, CWnd* pParent): mPuzzle(puzzle), CDialogEx(IDD_SSUDOKU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSudokuDlg9x9::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LOAD_GAME, mLoadGame);
	DDX_Control(pDX, IDC_BUTTON_SOLVE_GAME, mSolveGame);
	DDX_Control(pDX, IDC_BUTTON_GENERATE_GAME, mGenerateGame);
	DDX_Control(pDX, IDC_BUTTON_CHECK_GAME, mValidateGame);

	DDX_Control(pDX, IDC_EDITR1C1, mR1C1);
	DDX_Control(pDX, IDC_EDITR1C2, mR1C2);
	DDX_Control(pDX, IDC_EDITR1C3, mR1C3);
	DDX_Control(pDX, IDC_EDITR1C4, mR1C4);
	DDX_Control(pDX, IDC_EDITR1C5, mR1C5);
	DDX_Control(pDX, IDC_EDITR1C6, mR1C6);
	DDX_Control(pDX, IDC_EDITR1C7, mR1C7);
	DDX_Control(pDX, IDC_EDITR1C8, mR1C8);
	DDX_Control(pDX, IDC_EDITR1C9, mR1C9);

	DDX_Control(pDX, IDC_EDITR2C1, mR2C1);
	DDX_Control(pDX, IDC_EDITR2C2, mR2C2);
	DDX_Control(pDX, IDC_EDITR2C3, mR2C3);
	DDX_Control(pDX, IDC_EDITR2C4, mR2C4);
	DDX_Control(pDX, IDC_EDITR2C5, mR2C5);
	DDX_Control(pDX, IDC_EDITR2C6, mR2C6);
	DDX_Control(pDX, IDC_EDITR2C7, mR2C7);
	DDX_Control(pDX, IDC_EDITR2C8, mR2C8);
	DDX_Control(pDX, IDC_EDITR2C9, mR2C9);

	DDX_Control(pDX, IDC_EDITR3C1, mR3C1);
	DDX_Control(pDX, IDC_EDITR3C2, mR3C2);
	DDX_Control(pDX, IDC_EDITR3C3, mR3C3);
	DDX_Control(pDX, IDC_EDITR3C4, mR3C4);
	DDX_Control(pDX, IDC_EDITR3C5, mR3C5);
	DDX_Control(pDX, IDC_EDITR3C6, mR3C6);
	DDX_Control(pDX, IDC_EDITR3C7, mR3C7);
	DDX_Control(pDX, IDC_EDITR3C8, mR3C8);
	DDX_Control(pDX, IDC_EDITR3C9, mR3C9);

	DDX_Control(pDX, IDC_EDITR4C1, mR4C1);
	DDX_Control(pDX, IDC_EDITR4C2, mR4C2);
	DDX_Control(pDX, IDC_EDITR4C3, mR4C3);
	DDX_Control(pDX, IDC_EDITR4C4, mR4C4);
	DDX_Control(pDX, IDC_EDITR4C5, mR4C5);
	DDX_Control(pDX, IDC_EDITR4C6, mR4C6);
	DDX_Control(pDX, IDC_EDITR4C7, mR4C7);
	DDX_Control(pDX, IDC_EDITR4C8, mR4C8);
	DDX_Control(pDX, IDC_EDITR4C9, mR4C9);

	DDX_Control(pDX, IDC_EDITR5C1, mR5C1);
	DDX_Control(pDX, IDC_EDITR5C2, mR5C2);
	DDX_Control(pDX, IDC_EDITR5C3, mR5C3);
	DDX_Control(pDX, IDC_EDITR5C4, mR5C4);
	DDX_Control(pDX, IDC_EDITR5C5, mR5C5);
	DDX_Control(pDX, IDC_EDITR5C6, mR5C6);
	DDX_Control(pDX, IDC_EDITR5C7, mR5C7);
	DDX_Control(pDX, IDC_EDITR5C8, mR5C8);
	DDX_Control(pDX, IDC_EDITR5C9, mR5C9);

	DDX_Control(pDX, IDC_EDITR6C1, mR6C1);
	DDX_Control(pDX, IDC_EDITR6C2, mR6C2);
	DDX_Control(pDX, IDC_EDITR6C3, mR6C3);
	DDX_Control(pDX, IDC_EDITR6C4, mR6C4);
	DDX_Control(pDX, IDC_EDITR6C5, mR6C5);
	DDX_Control(pDX, IDC_EDITR6C6, mR6C6);
	DDX_Control(pDX, IDC_EDITR6C7, mR6C7);
	DDX_Control(pDX, IDC_EDITR6C8, mR6C8);
	DDX_Control(pDX, IDC_EDITR6C9, mR6C9);

	DDX_Control(pDX, IDC_EDITR7C1, mR7C1);
	DDX_Control(pDX, IDC_EDITR7C2, mR7C2);
	DDX_Control(pDX, IDC_EDITR7C3, mR7C3);
	DDX_Control(pDX, IDC_EDITR7C4, mR7C4);
	DDX_Control(pDX, IDC_EDITR7C5, mR7C5);
	DDX_Control(pDX, IDC_EDITR7C6, mR7C6);
	DDX_Control(pDX, IDC_EDITR7C7, mR7C7);
	DDX_Control(pDX, IDC_EDITR7C8, mR7C8);
	DDX_Control(pDX, IDC_EDITR7C9, mR7C9);

	DDX_Control(pDX, IDC_EDITR8C1, mR8C1);
	DDX_Control(pDX, IDC_EDITR8C2, mR8C2);
	DDX_Control(pDX, IDC_EDITR8C3, mR8C3);
	DDX_Control(pDX, IDC_EDITR8C4, mR8C4);
	DDX_Control(pDX, IDC_EDITR8C5, mR8C5);
	DDX_Control(pDX, IDC_EDITR8C6, mR8C6);
	DDX_Control(pDX, IDC_EDITR8C7, mR8C7);
	DDX_Control(pDX, IDC_EDITR8C8, mR8C8);
	DDX_Control(pDX, IDC_EDITR8C9, mR8C9);

	DDX_Control(pDX, IDC_EDITR9C1, mR9C1);
	DDX_Control(pDX, IDC_EDITR9C2, mR9C2);
	DDX_Control(pDX, IDC_EDITR9C3, mR9C3);
	DDX_Control(pDX, IDC_EDITR9C4, mR9C4);
	DDX_Control(pDX, IDC_EDITR9C5, mR9C5);
	DDX_Control(pDX, IDC_EDITR9C6, mR9C6);
	DDX_Control(pDX, IDC_EDITR9C7, mR9C7);
	DDX_Control(pDX, IDC_EDITR9C8, mR9C8);
	DDX_Control(pDX, IDC_EDITR9C9, mR9C9);

	DDX_Control(pDX, IDC_EDIT85, mLevel);
}

BEGIN_MESSAGE_MAP(CSudokuDlg9x9, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD_GAME, &CSudokuDlg9x9::OnBnClickedButtonLoadPuzzle)
	ON_BN_CLICKED(IDC_BUTTON_SOLVE_GAME, &CSudokuDlg9x9::OnBnClickedButtonSolvePuzzle)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE_GAME, &CSudokuDlg9x9::OnBnClickedButtonGeneratePuzzle)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_GAME, &CSudokuDlg9x9::OnBnClickedButtonValidatePuzzle)
END_MESSAGE_MAP()


// CSudokuDlg9x9 message handlers

BOOL CSudokuDlg9x9::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	mFontSolved.CreateFont(20, 0, 0, 0, FW_HEAVY, true, false,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN, _T("Courier New"));

	mFontGen.CreateFont(30, 0, 0, 0, FW_HEAVY, false, false,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN, _T("Times"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSudokuDlg9x9::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSudokuDlg9x9::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSudokuDlg9x9::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Private handler
void CSudokuDlg9x9::OnBnClickedButtonLoadPuzzle()
{
	TCHAR szFilters[] = _T("Sudoku file (*.text)|*.text|All Files (*.*)|*.*||");

	CFileDialog fileDlg(TRUE, _T("txt"), _T("*.text"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	if (fileDlg.DoModal() == IDOK)
	{
		mFileName = fileDlg.GetPathName();

		// Implement opening and reading file in here.
		CFile sudokuFile;
		if(sudokuFile.Open((LPCTSTR)mFileName, CFile::modeRead) == FALSE) {
			CString msg = L"Cannot open " + mFileName;
			MessageBox(msg);
			return;
		}
		
		CT2CA pszConvertedAnsiString(sudokuFile.GetFilePath());
		std::string str(pszConvertedAnsiString);
		sudokuFile.Close();

		if (mPuzzle->LoadFromFile(str) == false) {
			CString msg = L"Cannot generate game from file: " + mFileName;
			MessageBox(msg);
			return;
		}

		UpdateCellMap(true);
	}
}

void CSudokuDlg9x9::OnBnClickedButtonSolvePuzzle()
{
	if (mPuzzle) {
		int nsolution = mPuzzle->Solve();
		if (nsolution <= 0) {
			MessageBox(L"NO SOLUTION FOUND");
		}
		else if (nsolution == 1) {
			UpdateCellMap(false);
			MessageBox(L"A UNIQUE SOLUTION FOUND");
		}
		else /*(nsolution > 1)*/ {
			UpdateCellMap(false);
			MessageBox(L"MORE THAN ONE SOLUTION FOUND");
		}
	}
	else {
		MessageBox(L"SYSTEM ERROR");
	}
}

void CSudokuDlg9x9::OnBnClickedButtonGeneratePuzzle()
{
	CString str;
	mLevel.GetWindowTextW(str);
	ePuzzleLevel level = (ePuzzleLevel)_wtoi(str);

	if (level <= LEVEL_NONE || level > MAX_PUZZLE_LEVEL) {
		MessageBox(L"Invalid. Puzzle level is from 1 to 4");
		return;
	}

	BeginWaitCursor();
	if (mPuzzle->Generate(level) == true) {
		UpdateCellMap(true);
	}
	else {
		mPuzzle->ResetBoard();
		MessageBox(L"Failed to generate puzzle");
	}
	EndWaitCursor();
}

void CSudokuDlg9x9::OnBnClickedButtonValidatePuzzle()
{
	if (mPuzzle->Validate() == true) {
		MessageBox(L"Valid Puzzle");
	}
	else {
		MessageBox(L"Invalid Puzzle");
	}
}

void CSudokuDlg9x9::UpdateCellMap(const bool isInit)
{
	ISSudokuBoard *board = mPuzzle->GetBoard();
	if (!board) {
		return;
	}
	int size = board->GetBoardSize();
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			bool isFixed = false;
			CString str = board->GetCell(i, j, isInit);
			//str.Format(L"%s", s);
			mCellMap[i][j]->SetWindowTextW(str);
			if (!board->IsGiven(i*size + j)) {
				mCellMap[i][j]->SetFont(&mFontSolved);
			}
			else {
				mCellMap[i][j]->SetFont(&mFontGen);
			}
		}
	}

	if (isInit) {
		ePuzzleLevel level = mPuzzle->Rate();
		CString str;
		str.Format(L"%d", level);
		mLevel.SetWindowTextW(str);
	}
}
