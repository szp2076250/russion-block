// russion blockDoc.cpp : implementation of the CRussionblockDoc class
//

#include "stdafx.h"
#include "russion block.h"

#include "russion blockDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRussionblockDoc

IMPLEMENT_DYNCREATE(CRussionblockDoc, CDocument)

BEGIN_MESSAGE_MAP(CRussionblockDoc, CDocument)
	//{{AFX_MSG_MAP(CRussionblockDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRussionblockDoc construction/destruction

CRussionblockDoc::CRussionblockDoc()
{
	// TODO: add one-time construction code here

}

CRussionblockDoc::~CRussionblockDoc()
{
}

BOOL CRussionblockDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRussionblockDoc serialization

void CRussionblockDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRussionblockDoc diagnostics

#ifdef _DEBUG
void CRussionblockDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRussionblockDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRussionblockDoc commands
