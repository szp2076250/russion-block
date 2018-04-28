// russion blockDoc.h : interface of the CRussionblockDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUSSIONBLOCKDOC_H__64D3620C_6BD9_4D70_ADFC_38ADF555A23B__INCLUDED_)
#define AFX_RUSSIONBLOCKDOC_H__64D3620C_6BD9_4D70_ADFC_38ADF555A23B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRussionblockDoc : public CDocument
{
protected: // create from serialization only
	CRussionblockDoc();
	DECLARE_DYNCREATE(CRussionblockDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRussionblockDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRussionblockDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRussionblockDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUSSIONBLOCKDOC_H__64D3620C_6BD9_4D70_ADFC_38ADF555A23B__INCLUDED_)
