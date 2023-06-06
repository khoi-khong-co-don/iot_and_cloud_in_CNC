#if !defined(AFX_GLMOUSEROTATE_H__666349A6_A07C_44B1_A6CB_4740703399A9__INCLUDED_)
#define AFX_GLMOUSEROTATE_H__666349A6_A07C_44B1_A6CB_4740703399A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GLMouseRotate.h : header file
//

#include "OpenGLWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CGLMouseRotate window

class CGLMouseRotate : public COpenGLWnd
{
// Construction
public:
	 CGLMouseRotate();

// Attributes
public:

protected:
	BOOL m_bAllowMouseRotate;
	void DoMouseRotate();
	void DoMouseScale();
	float m_xMouseRotation;
	float m_yMouseRotation;
	float m_zMouseRotation;
	float m_MouseScale;

private:
	BOOL m_bInMouseRotate;
	CPoint m_LeftDownPos;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLMouseRotate)
	//}}AFX_VIRTUAL

// Implementation
public:
	__declspec(dllexport) void AllowMouseRotate(BOOL bAllow) {m_bAllowMouseRotate = bAllow;}
	virtual ~CGLMouseRotate();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLMouseRotate)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLMOUSEROTATE_H__666349A6_A07C_44B1_A6CB_4740703399A9__INCLUDED_)
