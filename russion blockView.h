// russion blockView.h : interface of the CRussionblockView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUSSIONBLOCKVIEW_H__2C673C61_B6E1_4F3E_8729_825A74988683__INCLUDED_)
#define AFX_RUSSIONBLOCKVIEW_H__2C673C61_B6E1_4F3E_8729_825A74988683__INCLUDED_

#include "Russion1.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRussionblockView : public CView
{
protected: // create from serialization only
	CRussionblockView();
	DECLARE_DYNCREATE(CRussionblockView)

// Attributes
public:
	CRussionblockDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRussionblockView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool m_IsStart;
	//static int i;
	Russion Game;
	virtual ~CRussionblockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRussionblockView)
	afx_msg void OnExit();
	afx_msg void OnExport();
	afx_msg void OnHigh();
	afx_msg void OnLow();
	afx_msg void OnMiddle();
	afx_msg void OnPause();
	afx_msg void OnStart();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in russion blockView.cpp
inline CRussionblockDoc* CRussionblockView::GetDocument()
   { return (CRussionblockDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUSSIONBLOCKVIEW_H__2C673C61_B6E1_4F3E_8729_825A74988683__INCLUDED_)
