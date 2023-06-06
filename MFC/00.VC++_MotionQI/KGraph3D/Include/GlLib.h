// GlLib.h : main header file for the GLLIB application
//

#if !defined(AFX_GLLIB_H__C2609FD5_55C3_45D4_831D_FAA3384AD93B__INCLUDED_)
#define AFX_GLLIB_H__C2609FD5_55C3_45D4_831D_FAA3384AD93B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGlLibApp:
// See GlLib.cpp for the implementation of this class
//

class CGlLibApp : public CWinApp
{
public:
	CGlLibApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlLibApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGlLibApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLLIB_H__C2609FD5_55C3_45D4_831D_FAA3384AD93B__INCLUDED_)
