#if !defined(AFX_GL3DGRAPH_H__862C7F5A_5DAF_4F50_8A7A_B302D905316C__INCLUDED_)
#define AFX_GL3DGRAPH_H__862C7F5A_5DAF_4F50_8A7A_B302D905316C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GL3DGraph.h : header file
//
#include "CxStatic.h"
#include "./KGraph3D/Include/GL3DGraph.h"
#include "EditEx.h"

#define COORDINATE	0

#define AXIS_N04(AXIS_NO, POS)		(((AXIS_NO / 4) * 4) + POS)	
#define GREEN						RGB(0,255,0)
#define YELLOW						RGB(255,255,0)
#define BLACK						RGB(0,0,0)


const int ONE_MS	 = 50;	
const int MM_START_TIMER = WM_APP + 1;
const int MM_START_SIMULATION = WM_APP + 2;
/////////////////////////////////////////////////////////////////////////////
// GL3DGraph dialog
class CGL3DGraph;
class GL3DGraph : public CDialog
{
// Construction
public:
	GL3DGraph(CWnd* pParent, long nAxis);   // standard constructor
	CGL3DGraph	m_pDisplay;
	BOOL		m_bDisplay;
	BOOL		m_bStartTimer;
	CWnd		*m_pParent;
	long		m_aAxis[4];

	long			m_lAxis;
	long			m_lRange;
	CString		m_strFont1;

	COLORREF	m_PlotColor;

	//GL3DGraph(CWnd* pParent = NULL);   // standard constructor

	HANDLE		m_hGraphThread;
	BOOL		m_bGraphThread;
	
	void		UpdateAxis(long lAxis);
	void		UpdateRange(long lRange);
	void		StartGraphThread();

// Dialog Data
	//{{AFX_DATA(GL3DGraph)
	enum { IDD = IDD_3DGRAPH };
	CEditEx	m_editRangeZ;
	CEditEx	m_editRangeY;
	CEditEx	m_editRangeX;
	CxStatic	m_ctrlZCmd;
	CxStatic	m_ctrlYCmd;
	CxStatic	m_ctrlXCmd;
	CxStatic	m_ctrlZCmdPos;
	CxStatic	m_ctrlYCmdPos;
	CxStatic	m_ctrlXCmdPos;
	int		m_nDimension;
	int		m_nResetAxis;
	BOOL	m_bBoxEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GL3DGraph)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	void InitialControl();
protected:
	// Generated message map functions
	//{{AFX_MSG(GL3DGraph)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnHelAdd();
	afx_msg void OnBtnHelPlay();
	afx_msg void OnBtnSplAdd();
	afx_msg void OnBtnSplPlay();
	afx_msg void OnBtnClear();
	afx_msg void OnSelchangeCmbDimension();
	afx_msg void OnSelchangeCmbAxisreset();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBtnPlotcolor();
	afx_msg void OnChkBox();
	afx_msg void OnDestroy();
	afx_msg void OnButtonSetRange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GL3DGRAPH_H__862C7F5A_5DAF_4F50_8A7A_B302D905316C__INCLUDED_)
