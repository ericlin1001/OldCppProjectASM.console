// myfirstMFCDoc.h : interface of the CMyfirstMFCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFIRSTMFCDOC_H__67A45B03_70BA_4F13_B695_499E01EAB76E__INCLUDED_)
#define AFX_MYFIRSTMFCDOC_H__67A45B03_70BA_4F13_B695_499E01EAB76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStroke :public CObject
{
public:
	CStroke(UINT nPenWidth);
protected:
	CStroke();
	DECLARE_SERIAL(CStroke);
protected://attributes
	UINT m_nPenWidth;
	BOOL m_bThickPen;
	UINT m_nThinWidth;
	UINT m_nThickWidth;
public:
	CArray<CPoint,CPoint> m_pointArray;
public://operations
	BOOL DrawStroke(CDC* pDC);
public:
	virtual void Serialize(CArchive& ar);
};
class CMyfirstMFCDoc : public CDocument
{
protected: // create from serialization only
	CMyfirstMFCDoc();
	DECLARE_DYNCREATE(CMyfirstMFCDoc)

// Attributes
public:
	CTypedPtrList<CObList,CStroke*> m_strokeList;
// Operations
public:
	CPen *GetCurrentPen(){ return &m_penCur;}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyfirstMFCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	CStroke* NewStroke();
	virtual ~CMyfirstMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void ReplacePen();
	void InitDocument();
	CPen m_penCur;
	UINT m_nPenWidth;
	//{{AFX_MSG(CMyfirstMFCDoc)
	afx_msg void OnEditClearAll();
	afx_msg void OnPenThickOrThin();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFIRSTMFCDOC_H__67A45B03_70BA_4F13_B695_499E01EAB76E__INCLUDED_)
