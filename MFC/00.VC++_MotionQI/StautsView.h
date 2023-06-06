#if !defined(AFX_STAUTSVIEW_H__EFC1D4ED_7B10_4B80_BFE9_3EAA83DFEE20__INCLUDED_)
#define AFX_STAUTSVIEW_H__EFC1D4ED_7B10_4B80_BFE9_3EAA83DFEE20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StautsView.h : header file
//
#include "xShadeButton.h"
#include "OScopeCtrl.h"
#include "CSGraph.h"
#include "Led.h"
#include "EditEx.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CStautsView dialog
typedef struct {
	unsigned	b0 : 1, b1 : 1, b2 : 1, b3 : 1, b4 : 1, b5 : 1, b6 : 1, b7 : 1;
} byte_bits;

typedef struct {
	unsigned	b0 : 1, b1 : 1, b2  : 1, b3  : 1, b4  : 1, b5  : 1, b6  : 1, b7  : 1,
				b8 : 1, b9 : 1, b10 : 1, b11 : 1, b12 : 1, b13 : 1, b14 : 1, b15 : 1;
} word_bits;

typedef struct {
	unsigned	b0 : 1, b1 : 1, b2  : 1, b3  : 1, b4  : 1, b5  : 1, b6  : 1, b7  : 1,
				b8 : 1, b9 : 1, b10 : 1, b11 : 1, b12 : 1, b13 : 1, b14 : 1, b15 : 1,
				b16 : 1, b17 : 1, b18 : 1, b19 : 1, b20 : 1, b21 : 1, b22 : 1, b23 : 1,
				b24 : 1, b25 : 1, b26 : 1, b27 : 1, b28 : 1, b29 : 1, b30 : 1, b31 : 1;
} dword_bits;

typedef union {
	WORD wWord;
	BYTE bByte;
    DWORD dwWord;
	word_bits wbit; 
	dword_bits dwbit; 
	byte_bits bit;
} lsByte;

typedef int								BOOL;			// 0(FALSE), 1(TRUE)
typedef signed char						INT8;			// -128 .. 127
typedef unsigned char					UINT8;			// 0 .. 255
typedef signed short int				INT16;			// -32768 .. 32767
typedef unsigned short int				UINT16;			// 0 .. 65535
typedef int								INT32;			// -2,147,483,648 .. 2,147,483,647
typedef unsigned int					UINT32;			// 0 .. 4,294,967,295

#define	STATUS_TIMER	0

class CStautsView : public CDialog
{
// Construction
public:
	CStautsView(CWnd* pParent, long  nAxis);   // standard constructor

public:
	long	m_aAxis[2];
	CWnd	*m_pParent;
	
	void	LampUpdate();
	void	UpdateAxis(long nAxis);

// Dialog Data
	//{{AFX_DATA(CStautsView)
	enum { IDD = IDD_STATUSVIEW };
	CButton	m_stcAxisY;
	CButton	m_stcAxisX;
	CButton	m_btnPrev;
	CButton	m_btnNext;

	CLed	m_ledXENS31;
	CLed	m_ledXENS30;
	CLed	m_ledXENS16;
	CLed	m_ledXENS15;
	CLed	m_ledXENS14;
	CLed	m_ledXENS13;
	CLed	m_ledXENS12;
	CLed	m_ledXENS11;
	CLed	m_ledXENS10;
	CLed	m_ledXENS09;
	CLed	m_ledXENS08;
	CLed	m_ledXENS07;
	CLed	m_ledXENS06;
	CLed	m_ledXENS05;
	CLed	m_ledXENS04;
	CLed	m_ledXENS03;
	CLed	m_ledXENS02;
	CLed	m_ledXENS01;
	CLed	m_ledXENS00;

	CLed	m_ledXDRS10;
	CLed	m_ledXDRS09;
	CLed	m_ledXDRS07;
	CLed	m_ledXDRS06;
	CLed	m_ledXDRS05;
	CLed	m_ledXDRS04;
	CLed	m_ledXDRS03;
	CLed	m_ledXDRS02;
	CLed	m_ledXDRS01;
	CLed	m_ledXDRS00;

	CLed	m_ledYENS31;
	CLed	m_ledYENS30;
	CLed	m_ledYENS16;
	CLed	m_ledYENS15;
	CLed	m_ledYENS14;
	CLed	m_ledYENS13;
	CLed	m_ledYENS12;
	CLed	m_ledYENS11;
	CLed	m_ledYENS10;
	CLed	m_ledYENS09;
	CLed	m_ledYENS08;
	CLed	m_ledYENS07;
	CLed	m_ledYENS06;
	CLed	m_ledYENS05;
	CLed	m_ledYENS04;
	CLed	m_ledYENS03;
	CLed	m_ledYENS02;
	CLed	m_ledYENS01;
	CLed	m_ledYENS00;

	CLed	m_ledYDRS10;
	CLed	m_ledYDRS09;
	CLed	m_ledYDRS07;
	CLed	m_ledYDRS06;
	CLed	m_ledYDRS05;
	CLed	m_ledYDRS04;
	CLed	m_ledYDRS03;
	CLed	m_ledYDRS02;
	CLed	m_ledYDRS01;
	CLed	m_ledYDRS00;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStautsView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStautsView)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnPrev();
	afx_msg void OnBtnNext();
	afx_msg void OnBtnCur();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAUTSVIEW_H__EFC1D4ED_7B10_4B80_BFE9_3EAA83DFEE20__INCLUDED_)
