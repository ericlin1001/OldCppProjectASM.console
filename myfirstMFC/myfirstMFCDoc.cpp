// myfirstMFCDoc.cpp : implementation of the CMyfirstMFCDoc class
//

#include "stdafx.h"
#include "myfirstMFC.h"

#include "myfirstMFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCDoc

IMPLEMENT_DYNCREATE(CMyfirstMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyfirstMFCDoc, CDocument)
	//{{AFX_MSG_MAP(CMyfirstMFCDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_COMMAND(ID_PEN_THICK_OR_THIN, OnPenThickOrThin)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCDoc construction/destruction

CMyfirstMFCDoc::CMyfirstMFCDoc()
{
	// TODO: add one-time construction code here

}

CMyfirstMFCDoc::~CMyfirstMFCDoc()
{
}

BOOL CMyfirstMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	InitDocument();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCDoc serialization

void CMyfirstMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
	m_strokeList.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCDoc diagnostics

#ifdef _DEBUG
void CMyfirstMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyfirstMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCDoc commands

CStroke* CMyfirstMFCDoc::NewStroke()
{
	CStroke* pStrokeItem=new CStroke(m_nPenWidth);
	m_strokeList.AddTail(pStrokeItem);
	SetModifiedFlag();
	return pStrokeItem;
}

void CMyfirstMFCDoc::InitDocument()
{
	m_bThickPen=FALSE;
	m_nThinWidth=2;
	m_nThickWidth=5;
	ReplacePen();
}

BOOL CMyfirstMFCDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	InitDocument();
	return TRUE;
}

void CMyfirstMFCDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	while(!m_strokeList.IsEmpty()){
		delete m_strokeList.RemoveHead();
	}
	CDocument::DeleteContents();
}
///////////////////
//CStroke
IMPLEMENT_SERIAL(CStroke,CObject,1);
CStroke::CStroke()
{
	//for erialization only
}
CStroke::CStroke(UINT nPenWidth){
	m_nPenWidth=nPenWidth;
}
BOOL CStroke::DrawStroke(CDC* pDC)
{
	CPen penStroke;
	if(!penStroke.CreatePen(PS_SOLID,m_nPenWidth,RGB(0,0,0)))
		return FALSE;
	CPen *pOldPen=pDC->SelectObject(&penStroke);
	pDC->MoveTo(m_pointArray[0]);
	for(int i=1;i<m_pointArray.GetSize();i++){
		pDC->LineTo(m_pointArray[i]);
	}
	pDC->SelectObject(pOldPen);
	return TRUE;
}
void CStroke::Serialize(CArchive& ar){
	if(ar.IsStoring()){
		ar<<(WORD)m_nPenWidth;
		m_pointArray.Serialize(ar);
	}else{
		WORD w;
		ar>>w;
		m_nPenWidth=w;
		m_pointArray.Serialize(ar);
	}
}

void CMyfirstMFCDoc::OnEditClearAll() 
{
	// TODO: Add your command handler code here
	DeleteContents();
	SetModifiedFlag();
	UpdateAllViews(NULL);
}

void CMyfirstMFCDoc::OnPenThickOrThin() 
{
	// TODO: Add your command handler code here
	m_bThickPen=!m_bThickPen;
	ReplacePen();
}

void CMyfirstMFCDoc::ReplacePen()
{
	m_nPenWidth=m_bThickPen? m_nThickWidth : m_nThinWidth;
	m_penCur.DeleteObject();
	m_penCur.CreatePen(PS_SOLID,m_nPenWidth,RGB(0,0,0));

}

void CMyfirstMFCDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
