#if !defined(AFX_MANUALSET_H__B6B48ED1_218E_41AF_9479_528E30BAB359__INCLUDED_)
#define AFX_MANUALSET_H__B6B48ED1_218E_41AF_9479_528E30BAB359__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManualSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManualSet dialog

class ManualSet : public CDialog
{
// Construction
public:
	ManualSet(CWnd* pParent = NULL, long nAxisCount = 0);   // standard constructor

	long	m_lAxisCount;
	long	m_lAxisNo;

public:
	void	UpdateAxis(long nAxis);

// Dialog Data
	//{{AFX_DATA(ManualSet)
	enum { IDD = IDD_MANUAL_SET };
	CComboBox	m_cboPort;
	CButton		m_chkHex;
	CComboBox	m_cboAxisSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManualSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManualSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnCmd();
	afx_msg void OnRd();
	afx_msg void OnWr();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEditchangeCboAxissel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCboAxissel();
	void UpdateAxis(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUALSET_H__B6B48ED1_218E_41AF_9479_528E30BAB359__INCLUDED_)
