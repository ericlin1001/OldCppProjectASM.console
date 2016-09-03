// myfirstMFCView.cpp : implementation of the CMyfirstMFCView class
//

#include "stdafx.h"
#include "myfirstMFC.h"

#include "myfirstMFCDoc.h"
#include "myfirstMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCView

IMPLEMENT_DYNCREATE(CMyfirstMFCView, CView)

BEGIN_MESSAGE_MAP(CMyfirstMFCView, CView)
	//{{AFX_MSG_MAP(CMyfirstMFCView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCView construction/destruction

CMyfirstMFCView::CMyfirstMFCView()
{
	// TODO: add construction code here

}

CMyfirstMFCView::~CMyfirstMFCView()
{
}

BOOL CMyfirstMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCView drawing

void CMyfirstMFCView::OnDraw(CDC* pDC)
{
	CMyfirstMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CTypedPtrList<CObList,CStroke*>& strokeList=pDoc->m_strokeList;
	POSITION pos=strokeList.GetHeadPosition();
	while(pos!=NULL){
		CStroke* pStroke =strokeList.GetNext(pos);
		pStroke->DrawStroke(pDC);
	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCView printing

BOOL CMyfirstMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyfirstMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyfirstMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCView diagnostics

#ifdef _DEBUG
void CMyfirstMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMyfirstMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyfirstMFCDoc* CMyfirstMFCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyfirstMFCDoc)));
	return (CMyfirstMFCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCView message handlers

void CMyfirstMFCView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pStrokeCur=GetDocument()->NewStroke();
	m_pStrokeCur->m_pointArray.Add(point);
	SetCapture();
	m_ptPrev=point;
	//CView::OnLButtonDown(nFlags, point);
}

void CMyfirstMFCView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(GetCapture() !=this)
		return ;
	CMyfirstMFCDoc *pDoc=GetDocument();
	CClientDC dc(this);
	CPen *pOldPen=dc.SelectObject(pDoc->GetCurrentPen());
	dc.MoveTo(m_ptPrev);
	dc.LineTo(point);
	dc.SelectObject(pOldPen);
	m_pStrokeCur->m_pointArray.Add(point);
	ReleaseCapture();

	//CView::OnLButtonUp(nFlags, point);
}

void CMyfirstMFCView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(GetCapture() !=this)
		return ;
	CClientDC dc(this);
	m_pStrokeCur->m_pointArray.Add(point);
	CPen *pOldPen=dc.SelectObject(GetDocument()->GetCurrentPen());
	dc.MoveTo(m_ptPrev);
	dc.LineTo(point);
	dc.SelectObject(pOldPen);
	m_ptPrev=point;
	//CView::OnMouseMove(nFlags, point);
}
