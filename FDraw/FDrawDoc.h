// FDrawDoc.h : interface of the CFDrawDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FDRAWDOC_H__A8421416_846B_487D_AAF9_1F54C1B37EA5__INCLUDED_)
#define AFX_FDRAWDOC_H__A8421416_846B_487D_AAF9_1F54C1B37EA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStroke:public CObject
{
public:
	CStroke(UINT nPenWidth);
protected:
	CStroke();
	DELARE_SERIAL(CStroke);
		//attributes
protected:
	UINT m_nPenWidth;
public:
	CArray<CPoint,CPoint> m_pointArray;
public:
	BOOL DrawStroke(CDC* pDC);
public:
	virtual void Serialize(CArchive & ar);
};

class CFDrawDoc : public CDocument
{
protected: // create from serialization only
	CFDrawDoc();
	DECLARE_DYNCREATE(CFDrawDoc)

// Attributes
public:

	CTypedPtrList<CObList,CStroke*> m_strokeList;
	CPen *GetCurrentPen(){ return &m_penCur; }
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFDrawDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	CStroke* NewStroke();
	virtual ~CFDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void InitDocument();
	CPen m_penCur;
	UINT m_nPenWidth;
	//{{AFX_MSG(CFDrawDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FDRAWDOC_H__A8421416_846B_487D_AAF9_1F54C1B37EA5__INCLUDED_)
