// CAMC_QI.h : main header file for the CAMC_QI application
//

#if !defined(AFX_CAMC_QI_H__66989702_C24D_4F3F_B46B_1A115AB6EE48__INCLUDED_)
#define AFX_CAMC_QI_H__66989702_C24D_4F3F_B46B_1A115AB6EE48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCAMC_QIApp:
// See CAMC_QI.cpp for the implementation of this class
//

class CCAMC_QIApp : public CWinApp
{
public:
	CCAMC_QIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAMC_QIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCAMC_QIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMC_QI_H__66989702_C24D_4F3F_B46B_1A115AB6EE48__INCLUDED_)
