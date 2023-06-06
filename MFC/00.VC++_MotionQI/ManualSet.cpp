// ManualSet.cpp : implementation file
//

#include "stdafx.h"
#include "CAMC_QI.h"
#include "ManualSet.h"

#define TM_MONITOR	100

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManualSet dialog


ManualSet::ManualSet(CWnd* pParent /*=NULL*/, long nAxisCount)
	: CDialog(ManualSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManualSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_lAxisCount	= nAxisCount;
	m_lAxisNo		= 0;
}

void ManualSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManualSet)
	DDX_Control(pDX, IDC_CBO_PORT, m_cboPort);
	DDX_Control(pDX, IDC_CHK_HEX, m_chkHex);
	DDX_Control(pDX, IDC_CBO_AXISSEL, m_cboAxisSel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManualSet, CDialog)
	//{{AFX_MSG_MAP(ManualSet)
	ON_BN_CLICKED(IDC_BTN_CMD, OnCmd)
	ON_BN_CLICKED(IDC_BTN_RD, OnRd)
	ON_BN_CLICKED(IDC_BTN_WR, OnWr)
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
	ON_CBN_EDITCHANGE(IDC_CBO_AXISSEL, OnEditchangeCboAxissel)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_CBO_AXISSEL, &ManualSet::OnCbnSelchangeCboAxissel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManualSet message handlers
BOOL ManualSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strAxis;
	for( int i=0; i < m_lAxisCount; i++){
		strAxis.Format("%d Axis", i);
		m_cboAxisSel.AddString(strAxis);
	}
	
	m_cboAxisSel.SetCurSel(0);
	m_cboPort.SetCurSel(0);
	m_chkHex.SetCheck(TRUE);

	SetTimer(TM_MONITOR, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ManualSet::OnCmd() 
{
	CString strTemp;
	BYTE	bCmd;
	DWORD	dwData;
	long	lTempData;

	GetDlgItemText(IDC_EDT_CMD, strTemp);

	if(strTemp.IsEmpty())										lTempData = 0;
	else if(strTemp.Left(2) == "0x" || strTemp.Left(2) == "0X")	sscanf(strTemp, "%x", &lTempData);
	else														sscanf(strTemp, "%d", &lTempData);

	bCmd	=	0x000000FF & lTempData;
	GetDlgItemText(IDC_EDT_DATA, strTemp);

	if(strTemp.IsEmpty())										lTempData = 0;
	else if(strTemp.Left(2) == "0x" || strTemp.Left(2) == "0X")	sscanf(strTemp, "%x", &lTempData);
	else														sscanf(strTemp, "%d", &lTempData);

	dwData	=	0xFFFFFFFF & lTempData; 
	if(0x80 & bCmd)	AxmSetCommandData32Qi(m_lAxisNo, (QICOMMAND)bCmd, dwData);
	else			AxmGetCommandData32Qi(m_lAxisNo, (QICOMMAND)bCmd, &dwData);

	if (m_chkHex.GetCheck())	strTemp.Format("0x%08x", dwData);
	else						strTemp.Format("%d", dwData);
	
	SetDlgItemText(IDC_EDT_DATA, strTemp.operator LPCTSTR());
}

void ManualSet::OnRd() 
{
	long	lTempData;
	CString strTemp;
	BYTE	bCmd;
	WORD	dwData, dwOffset;

	lTempData = m_cboPort.GetCurSel();
	dwOffset = 0x200 | ((0xFF &lTempData) << 2);
	AxmGetPortDataQi(m_lAxisNo, dwOffset, &dwData);
	
	if (m_chkHex.GetCheck())	strTemp.Format("0x%08x", dwData);
	else						strTemp.Format("%d", dwData);
	
	SetDlgItemText(IDC_EDT_DATA, strTemp.operator LPCTSTR());	
}

void ManualSet::UpdateAxis(long nAxis)
{
	m_lAxisNo = nAxis;
	m_cboAxisSel.SetCurSel(m_lAxisNo);
}

void ManualSet::OnWr() 
{
	CString strTemp;
	BYTE	bCmd;
	DWORD	dwData, dwOffset;
	long	lTempData;
	lTempData = m_cboPort.GetCurSel();
	dwOffset = 0x200 | ((0xFF &lTempData) << 2);

	GetDlgItemText(IDC_EDT_DATA, strTemp);

	if(strTemp.IsEmpty())										lTempData = 0.0;
	else if(strTemp.Left(2) == "0x" || strTemp.Left(2) == "0X")	sscanf(strTemp, "%x", &lTempData);
	else														sscanf(strTemp, "%d", &lTempData);
	
	dwData	=	lTempData;
	AxmSetPortDataQi(m_lAxisNo, dwOffset, dwData);

	if (m_chkHex.GetCheck())	strTemp.Format("0x%08x", dwData);
	else						strTemp.Format("%d", dwData);		
	
	SetDlgItemText(IDC_EDT_DATA, strTemp.operator LPCTSTR());
}

void ManualSet::OnTimer(UINT_PTR nIDEvent) 
{
	CString strTemp;
	BYTE	bCmd;
	DWORD	dwData;
	long	lTempData;
	int		i;

	if(nIDEvent == TM_MONITOR)
	{
		UpdateAxis();
	}
	CDialog::OnTimer(nIDEvent);
}

void ManualSet::OnEditchangeCboAxissel() 
{
	m_lAxisNo = m_cboAxisSel.GetCurSel();
}

void ManualSet::OnCbnSelchangeCboAxissel()
{
	m_lAxisNo = m_cboAxisSel.GetCurSel();
	UpdateAxis();	
}

void ManualSet::UpdateAxis(void)
{
	CString strTemp;
	BYTE	bCmd;
	DWORD	dwData;
	long	lTempData;
	int		i;

	for(i = 0; i < 6; i++){
		if(((CButton*)GetDlgItem(IDC_CHK_ONOFF1 + i))->GetCheck()){
			GetDlgItemText(IDC_EDT_CMD1 + i, strTemp);
			if(strTemp.IsEmpty())										lTempData = 0;
			else if(strTemp.Left(2) == "0x" || strTemp.Left(2) == "0X")	sscanf(strTemp, "%x", &lTempData);
			else														sscanf(strTemp, "%d", &lTempData);

			bCmd	=	0x0000007F & lTempData;
			AxmGetCommandData32Qi(m_lAxisNo, (QICOMMAND)bCmd, &dwData);

			if (m_chkHex.GetCheck())	strTemp.Format("0x%08x", dwData);
			else						strTemp.Format("%d", dwData);

			SetDlgItemText(IDC_EDT_DATA1 + i, strTemp.operator LPCTSTR());
		}
	}
}