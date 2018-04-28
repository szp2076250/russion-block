// russion blockView.cpp : implementation of the CRussionblockView class
//
#ifndef INCLUDE
#define INCLUDE 100

#include "stdafx.h"
#include "russion block.h"

#include "russion blockDoc.h"
#include "russion blockView.h"
#include "Russion1.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRussionblockView

IMPLEMENT_DYNCREATE(CRussionblockView, CView)

BEGIN_MESSAGE_MAP(CRussionblockView, CView)
	//{{AFX_MSG_MAP(CRussionblockView)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_COMMAND(IDM_EXPORT, OnExport)
	ON_COMMAND(IDM_HIGH, OnHigh)
	ON_COMMAND(IDM_LOW, OnLow)
	ON_COMMAND(IDM_MIDDLE, OnMiddle)
	ON_COMMAND(IDM_PAUSE, OnPause)
	ON_COMMAND(IDM_START, OnStart)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(IDM_TEST, OnTest)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRussionblockView construction/destruction

CRussionblockView::CRussionblockView()
{
	// TODO: add construction code here

}

CRussionblockView::~CRussionblockView()
{
}

BOOL CRussionblockView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRussionblockView drawing

void CRussionblockView::OnDraw(CDC* pDC)
{
	CRussionblockDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	//MoveWindow(0,0,375,224,true);

	if(Game.mGameStart==false)
	{
	Game.DrawBackground(pDC);
	}
	else
	{
	//InvaldateRect()
	Game.Clear(pDC);

	//CView::OnDraw(pDC);
	
	}



	CDC dcm;  //记忆dc

	dcm.CreateCompatibleDC(pDC);

	//Game.DrawBlock(pDC);

	ReleaseDC(&dcm);
}

/////////////////////////////////////////////////////////////////////////////
// CRussionblockView printing

BOOL CRussionblockView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRussionblockView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRussionblockView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRussionblockView diagnostics

#ifdef _DEBUG
void CRussionblockView::AssertValid() const
{
	CView::AssertValid();
}

void CRussionblockView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRussionblockDoc* CRussionblockView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRussionblockDoc)));
	return (CRussionblockDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRussionblockView message handlers

void CRussionblockView::OnExit() 
{

	AfxMessageBox("退出...");

	KillTimer(1);

	exit(0);
	
}

void CRussionblockView::OnExport() 
{
	if (!Game.mGameStart) { AfxMessageBox("游戏尚未开始!"); return; }
	static int s = 1;

	s++;

	if(s%2==0)
	{
	AfxMessageBox("扩展版开启!请耐心等待");
	Game.mAdvanceVersion = true;
	}
	else
	{
	AfxMessageBox("扩展版关闭!");
	Game.mAdvanceVersion = false;
	}

}

void CRussionblockView::OnHigh()    //高难度
{
	if (!Game.mGameStart) { AfxMessageBox("游戏尚未开始!"); return; }
	Game.mSpeed = 8;
	KillTimer(1);
	SetTimer(1,100/Game.mSpeed*10,NULL);
}

void CRussionblockView::OnLow()    //低难度
{
	if (!Game.mGameStart) { AfxMessageBox("游戏尚未开始!"); return; }
	Game.mSpeed = 1;
	KillTimer(1);
	SetTimer(1,100/Game.mSpeed*10,NULL);
	
}

void CRussionblockView::OnMiddle()  //普通难度
{
	if (!Game.mGameStart) { AfxMessageBox("游戏尚未开始!"); return; }
	Game.mSpeed = 4;
	KillTimer(1);
	SetTimer(1,100/Game.mSpeed*10,NULL);
}

void CRussionblockView::OnPause() 
{
	if (!Game.mGameStart) { AfxMessageBox("游戏尚未开始!"); return; }

	static int i = 1 ;   //暂停因子

	if(0==i%2)
	{
		Game.mGamePause = false;
		Game.mGameStart = true;
		SetTimer(1,100/Game.mSpeed*10,NULL);
	}
	else
	{
		Game.mGamePause = true;
		KillTimer(1);
	}
	i++;
}

void CRussionblockView::OnStart() 
{
	if (Game.mGameStart)
	{
		AfxMessageBox("已经开始游戏!\n请不要再次点击开始!");
		return;
	}

	Game.mGameStart = true;  //开始游戏
	AfxMessageBox("开始游戏！");
	//AfxGetMainWnd()->SetWindowPos(NULL,50,50,400,600,SWP_NOMOVE);

	//调整客户区大小
	RECT rectClient,rectWindow;
	GetWindowRect(&rectWindow);
	GetClientRect(&rectClient);
	auto borderWidth = (rectWindow.right - rectWindow.left)
		- (rectClient.right - rectClient.left);
	auto borderHeight = (rectWindow.bottom - rectWindow.top)
		- (rectClient.bottom - rectClient.top);
	AfxGetMainWnd()->SetWindowPos(NULL, 50, 50, MAX_COL*24, MAX_ROW * 24, SWP_NOMOVE);

    CDC * pDC = GetDC();
    Game.Clear(pDC);
	Game.DrawBlock(pDC);
	ReleaseDC(pDC);
	SetTimer(1,100/Game.mSpeed*10,NULL);
}

void CRussionblockView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	Game.IniBlock();
}

void CRussionblockView::OnTimer(UINT nIDEvent) 
{
	CDC * pDC = GetDC();

	Game.Change();

	Game.UpdateBackGround(pDC);

	if(!Game.CanNotDown())
	{
		Game.RemoveLine();
		Game.ClearBlock(Game.mOldBlock);
	    Game.GetABlock();

		Game.mLeftTopPoint.x = 0;     //方块开始下落的行数
		Game.mLeftTopPoint.y = 19/2;    //方块开始下落的列数
		Game.mCanMove = false;

	    Game.UpdateBackGround(pDC);
	}

	if (Game.mGameStop) return;
	Game.MoveBlocks(2);

	if(Game.TheEnd()==true)
	{
		Game.ClearBlock(Game.mOldBlock);
		Game.ZeroBackGround(); 
		AfxMessageBox("Game Over!");

		Game.UpdateBackGround(pDC);  
		Game.DrawBackground(pDC);
		Game.mGameStart = false;
		KillTimer(1);
		Game.IniBlock();
	}

	ReleaseDC(pDC);
	CView::OnTimer(nIDEvent);
}

void CRussionblockView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	
	switch(nChar)
	{
	case VK_LEFT:
		if(Game.mCanMove==false)
		{
		Game.MoveBlocks(3);
		}
		break;
	case VK_RIGHT:
		if(Game.mCanMove==false)
		{
		Game.MoveBlocks(4);
		}
		break;
	case VK_DOWN:
		if(Game.mGameStop==false)
		{
		Game.MoveBlocks(2);
		}
		break;
	default:
		Game.MoveBlocks(1);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRussionblockView::OnTest() 
{
	Game.Test();
}
