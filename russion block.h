// russion block.h : main header file for the RUSSION BLOCK application
//

#if !defined(AFX_RUSSIONBLOCK_H__28BCFA03_917F_4C09_8CBE_684904814BC5__INCLUDED_)
#define AFX_RUSSIONBLOCK_H__28BCFA03_917F_4C09_8CBE_684904814BC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRussionblockApp:
// See russion block.cpp for the implementation of this class
//

class CRussionblockApp : public CWinApp
{
public:
	CRussionblockApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRussionblockApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRussionblockApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUSSIONBLOCK_H__28BCFA03_917F_4C09_8CBE_684904814BC5__INCLUDED_)
