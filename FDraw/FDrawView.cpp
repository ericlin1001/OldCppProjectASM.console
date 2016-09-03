// FDrawView.cpp : implementation of the CFDrawView class
//

#include "stdafx.h"
#include "FDraw.h"

#include "FDrawDoc.h"
#include "FDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFDrawView

IMPLEMENT_DYNCREATE(CFDrawView, CView)

BEGIN_MESSAGE_MAP(CFDrawView, CView)
	//{{AFX_MSG_MAP(CFDrawView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFDrawView construction/destruction

CFDrawView::CFDrawView()
{
	// TODO: add construction code here

}

CFDrawView::~CFDrawView()
{
}

BOOL CFDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFDrawView drawing

void CFDrawView::OnDraw(CDC* pDC)
{
	CFDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFDrawView printing

BOOL CFDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFDrawView diagnostics

#ifdef _DEBUG
void CFDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CFDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFDrawDoc* CFDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFDrawDoc)));
	return (CFDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFDrawView message handlers
