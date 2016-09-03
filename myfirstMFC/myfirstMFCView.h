// myfirstMFCView.h : interface of the CMyfirstMFCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFIRSTMFCVIEW_H__48BC3E86_3CD2_42A9_9E50_B3E9239BBA2E__INCLUDED_)
#define AFX_MYFIRSTMFCVIEW_H__48BC3E86_3CD2_42A9_9E50_B3E9239BBA2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyfirstMFCView : public CView
{
protected: // create from serialization only
	CMyfirstMFCView();
	DECLARE_DYNCREATE(CMyfirstMFCView)

// Attributes
public:
	CMyfirstMFCDoc* GetDocument();
protected:
	CStroke* m_pStrokeCur;
	CPoint m_ptPrev;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyfirstMFCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyfirstMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyfirstMFCView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in myfirstMFCView.cpp
inline CMyfirstMFCDoc* CMyfirstMFCView::GetDocument()
   { return (CMyfirstMFCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFIRSTMFCVIEW_H__48BC3E86_3CD2_42A9_9E50_B3E9239BBA2E__INCLUDED_)
