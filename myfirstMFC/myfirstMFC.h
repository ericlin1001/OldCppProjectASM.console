// myfirstMFC.h : main header file for the MYFIRSTMFC application
//

#if !defined(AFX_MYFIRSTMFC_H__FF94BB60_77AC_4DE1_B1E7_71034D59DCB6__INCLUDED_)
#define AFX_MYFIRSTMFC_H__FF94BB60_77AC_4DE1_B1E7_71034D59DCB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyfirstMFCApp:
// See myfirstMFC.cpp for the implementation of this class
//

class CMyfirstMFCApp : public CWinApp
{
public:
	CMyfirstMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyfirstMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyfirstMFCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFIRSTMFC_H__FF94BB60_77AC_4DE1_B1E7_71034D59DCB6__INCLUDED_)
