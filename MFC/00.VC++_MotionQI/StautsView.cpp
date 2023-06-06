// StautsView.cpp : implementation file
//

#include "stdafx.h"
#include "CAMC_QI.h"
#include "StautsView.h"

#include "xShadeButton.h"
#include "Led.h"
#include "EditEx.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStautsView dialog
#define AXIS_EVN(AXIS_NO)		(AXIS_NO - (AXIS_NO % 2))			// Searching for even number axis of axis which makes couple
#define AXIS_ODD(AXIS_NO)		(AXIS_NO + ((AXIS_NO + 1) % 2))		// Searching for odd number axis of axis which makes couple

//CStautsView::CStautsView(CWnd* pParent /*=NULL*/)
CStautsView::CStautsView(CWnd* pParent, long nAxis)
	: CDialog(CStautsView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStautsView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT	
	m_pParent	= pParent;
	m_aAxis[0]	= AXIS_EVN(nAxis);
	m_aAxis[1]	= AXIS_ODD(nAxis);
}

void CStautsView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStautsView)
	DDX_Control(pDX, IDC_STC_AXIS_Y, m_stcAxisY);
	DDX_Control(pDX, IDC_STC_AXIS_X, m_stcAxisX);
	DDX_Control(pDX, IDC_BTN_PREV, m_btnPrev);
	DDX_Control(pDX, IDC_BTN_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_LED_XENS31, m_ledXENS31);
	DDX_Control(pDX, IDC_LED_XENS30, m_ledXENS30);
	DDX_Control(pDX, IDC_LED_XENS16, m_ledXENS16);
	DDX_Control(pDX, IDC_LED_XENS15, m_ledXENS15);
	DDX_Control(pDX, IDC_LED_XENS14, m_ledXENS14);
	DDX_Control(pDX, IDC_LED_XENS13, m_ledXENS13);
	DDX_Control(pDX, IDC_LED_XENS12, m_ledXENS12);
	DDX_Control(pDX, IDC_LED_XENS11, m_ledXENS11);
	DDX_Control(pDX, IDC_LED_XENS10, m_ledXENS10);
	DDX_Control(pDX, IDC_LED_XENS09, m_ledXENS09);
	DDX_Control(pDX, IDC_LED_XENS08, m_ledXENS08);
	DDX_Control(pDX, IDC_LED_XENS07, m_ledXENS07);
	DDX_Control(pDX, IDC_LED_XENS06, m_ledXENS06);
	DDX_Control(pDX, IDC_LED_XENS05, m_ledXENS05);
	DDX_Control(pDX, IDC_LED_XENS04, m_ledXENS04);
	DDX_Control(pDX, IDC_LED_XENS03, m_ledXENS03);
	DDX_Control(pDX, IDC_LED_XENS02, m_ledXENS02);
	DDX_Control(pDX, IDC_LED_XENS01, m_ledXENS01);
	DDX_Control(pDX, IDC_LED_XENS00, m_ledXENS00);

	DDX_Control(pDX, IDC_LED_XDRS10, m_ledXDRS10);
	DDX_Control(pDX, IDC_LED_XDRS09, m_ledXDRS09);
	DDX_Control(pDX, IDC_LED_XDRS07, m_ledXDRS07);
	DDX_Control(pDX, IDC_LED_XDRS06, m_ledXDRS06);
	DDX_Control(pDX, IDC_LED_XDRS05, m_ledXDRS05);
	DDX_Control(pDX, IDC_LED_XDRS04, m_ledXDRS04);
	DDX_Control(pDX, IDC_LED_XDRS03, m_ledXDRS03);
	DDX_Control(pDX, IDC_LED_XDRS02, m_ledXDRS02);
	DDX_Control(pDX, IDC_LED_XDRS01, m_ledXDRS01);
	DDX_Control(pDX, IDC_LED_XDRS00, m_ledXDRS00);

	DDX_Control(pDX, IDC_LED_YENS31, m_ledYENS31);
	DDX_Control(pDX, IDC_LED_YENS30, m_ledYENS30);
	DDX_Control(pDX, IDC_LED_YENS16, m_ledYENS16);
	DDX_Control(pDX, IDC_LED_YENS15, m_ledYENS15);
	DDX_Control(pDX, IDC_LED_YENS14, m_ledYENS14);
	DDX_Control(pDX, IDC_LED_YENS13, m_ledYENS13);
	DDX_Control(pDX, IDC_LED_YENS12, m_ledYENS12);
	DDX_Control(pDX, IDC_LED_YENS11, m_ledYENS11);
	DDX_Control(pDX, IDC_LED_YENS10, m_ledYENS10);
	DDX_Control(pDX, IDC_LED_YENS09, m_ledYENS09);
	DDX_Control(pDX, IDC_LED_YENS08, m_ledYENS08);
	DDX_Control(pDX, IDC_LED_YENS07, m_ledYENS07);
	DDX_Control(pDX, IDC_LED_YENS06, m_ledYENS06);
	DDX_Control(pDX, IDC_LED_YENS05, m_ledYENS05);
	DDX_Control(pDX, IDC_LED_YENS04, m_ledYENS04);
	DDX_Control(pDX, IDC_LED_YENS03, m_ledYENS03);
	DDX_Control(pDX, IDC_LED_YENS02, m_ledYENS02);
	DDX_Control(pDX, IDC_LED_YENS01, m_ledYENS01);
	DDX_Control(pDX, IDC_LED_YENS00, m_ledYENS00);

	DDX_Control(pDX, IDC_LED_YDRS10, m_ledYDRS10);
	DDX_Control(pDX, IDC_LED_YDRS09, m_ledYDRS09);
	DDX_Control(pDX, IDC_LED_YDRS07, m_ledYDRS07);
	DDX_Control(pDX, IDC_LED_YDRS06, m_ledYDRS06);
	DDX_Control(pDX, IDC_LED_YDRS05, m_ledYDRS05);
	DDX_Control(pDX, IDC_LED_YDRS04, m_ledYDRS04);
	DDX_Control(pDX, IDC_LED_YDRS03, m_ledYDRS03);
	DDX_Control(pDX, IDC_LED_YDRS02, m_ledYDRS02);
	DDX_Control(pDX, IDC_LED_YDRS01, m_ledYDRS01);
	DDX_Control(pDX, IDC_LED_YDRS00, m_ledYDRS00);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStautsView, CDialog)
	//{{AFX_MSG_MAP(CStautsView)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_PREV, OnBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEXT, OnBtnNext)
	ON_BN_CLICKED(IDC_BTN_CUR, OnBtnCur)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStautsView message handlers

void CStautsView::OnTimer(UINT_PTR nIDEvent) 
{
	DWORD	dwIsMotionModule;

	AxmInfoIsMotionModule(&dwIsMotionModule);
	if(!dwIsMotionModule)
	{
		CDialog::OnTimer(nIDEvent);
		return;
	}

	switch(nIDEvent)
	{
	case STATUS_TIMER:
		{
			CString		strAxis;
			long		lAxisCount;
			lsByte		byteDriver;
			DWORD		DrvStatus;

			AxmStatusReadMotion(m_aAxis[0], &DrvStatus);

			byteDriver.dwWord	= (UINT32)DrvStatus;

			m_ledXDRS10.SetStatus(byteDriver.dwbit.b10);
			m_ledXDRS09.SetStatus(byteDriver.dwbit.b9);
			m_ledXDRS07.SetStatus(byteDriver.dwbit.b7);
			m_ledXDRS06.SetStatus(byteDriver.dwbit.b6);
			m_ledXDRS05.SetStatus(byteDriver.dwbit.b5);
			m_ledXDRS04.SetStatus(byteDriver.dwbit.b4);
			m_ledXDRS03.SetStatus(byteDriver.dwbit.b3);
			m_ledXDRS02.SetStatus(byteDriver.dwbit.b2);
			m_ledXDRS01.SetStatus(byteDriver.dwbit.b1);
			m_ledXDRS00.SetStatus(byteDriver.dwbit.b0);

			AxmStatusReadMotion(m_aAxis[1], &DrvStatus);

			byteDriver.dwWord	= (UINT32)DrvStatus;

			m_ledYDRS10.SetStatus(byteDriver.dwbit.b10);
			m_ledYDRS09.SetStatus(byteDriver.dwbit.b9);
			m_ledYDRS07.SetStatus(byteDriver.dwbit.b7);
			m_ledYDRS06.SetStatus(byteDriver.dwbit.b6);
			m_ledYDRS05.SetStatus(byteDriver.dwbit.b5);
			m_ledYDRS04.SetStatus(byteDriver.dwbit.b4);
			m_ledYDRS03.SetStatus(byteDriver.dwbit.b3);
			m_ledYDRS02.SetStatus(byteDriver.dwbit.b2);
			m_ledYDRS01.SetStatus(byteDriver.dwbit.b1);
			m_ledYDRS00.SetStatus(byteDriver.dwbit.b0);
		}
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CStautsView::UpdateAxis(long lAxis)
{
	m_aAxis[0]	= AXIS_EVN(lAxis);
	m_aAxis[1]	= AXIS_ODD(lAxis);

	LampUpdate();

	SetTimer(STATUS_TIMER, 100, NULL);
}

void CStautsView::LampUpdate()
{
	CString		strAxis;							
	long		lAxisCount;
	lsByte		byteEnd;
	DWORD		EndStatus;

	AxmStatusReadStop(m_aAxis[0], &EndStatus);

	byteEnd.dwWord		= (UINT32)EndStatus;

	m_ledXENS31.SetStatus(byteEnd.dwbit.b31);
	m_ledXENS30.SetStatus(byteEnd.dwbit.b30);
	m_ledXENS16.SetStatus(byteEnd.dwbit.b16);
	m_ledXENS15.SetStatus(byteEnd.dwbit.b15);
	m_ledXENS14.SetStatus(byteEnd.dwbit.b14);
	m_ledXENS13.SetStatus(byteEnd.dwbit.b13);
	m_ledXENS12.SetStatus(byteEnd.dwbit.b12);
	m_ledXENS11.SetStatus(byteEnd.dwbit.b11);
	m_ledXENS10.SetStatus(byteEnd.dwbit.b10);
	m_ledXENS09.SetStatus(byteEnd.dwbit.b9);
	m_ledXENS08.SetStatus(byteEnd.dwbit.b8);
	m_ledXENS07.SetStatus(byteEnd.dwbit.b7);
	m_ledXENS06.SetStatus(byteEnd.dwbit.b6);
	m_ledXENS05.SetStatus(byteEnd.dwbit.b5);
	m_ledXENS04.SetStatus(byteEnd.dwbit.b4);
	m_ledXENS03.SetStatus(byteEnd.dwbit.b3);
	m_ledXENS02.SetStatus(byteEnd.dwbit.b2);
	m_ledXENS01.SetStatus(byteEnd.dwbit.b1);
	m_ledXENS00.SetStatus(byteEnd.dwbit.b0);

	AxmStatusReadStop(m_aAxis[1], &EndStatus);

	byteEnd.dwWord		= (UINT32)EndStatus;

	m_ledYENS31.SetStatus(byteEnd.dwbit.b31);
	m_ledYENS30.SetStatus(byteEnd.dwbit.b30);
	m_ledYENS16.SetStatus(byteEnd.dwbit.b16);
	m_ledYENS15.SetStatus(byteEnd.dwbit.b15);
	m_ledYENS14.SetStatus(byteEnd.dwbit.b14);
	m_ledYENS13.SetStatus(byteEnd.dwbit.b13);
	m_ledYENS12.SetStatus(byteEnd.dwbit.b12);
	m_ledYENS11.SetStatus(byteEnd.dwbit.b11);
	m_ledYENS10.SetStatus(byteEnd.dwbit.b10);
	m_ledYENS09.SetStatus(byteEnd.dwbit.b9);
	m_ledYENS08.SetStatus(byteEnd.dwbit.b8);
	m_ledYENS07.SetStatus(byteEnd.dwbit.b7);
	m_ledYENS06.SetStatus(byteEnd.dwbit.b6);
	m_ledYENS05.SetStatus(byteEnd.dwbit.b5);
	m_ledYENS04.SetStatus(byteEnd.dwbit.b4);
	m_ledYENS03.SetStatus(byteEnd.dwbit.b3);
	m_ledYENS02.SetStatus(byteEnd.dwbit.b2);
	m_ledYENS01.SetStatus(byteEnd.dwbit.b1);
	m_ledYENS00.SetStatus(byteEnd.dwbit.b0);

	strAxis.Format("X Axis: %02d", m_aAxis[0]);
	m_stcAxisX.SetWindowText(strAxis);

	strAxis.Format("Y Axis: %02d", m_aAxis[1]);
	m_stcAxisY.SetWindowText(strAxis);

	AxmInfoGetAxisCount(&lAxisCount);
	if(m_aAxis[0] == 0)	m_btnPrev.EnableWindow(DISABLE);
	else				m_btnPrev.EnableWindow(ENABLE);

	if(m_aAxis[1] == (lAxisCount - 1))	m_btnNext.EnableWindow(DISABLE);
	else								m_btnNext.EnableWindow(ENABLE);
}

BOOL CStautsView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStautsView::OnOK() 
{
	CDialog::OnOK();
}

void CStautsView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
}


void CStautsView::OnBtnPrev() 
{
	if(m_aAxis[0] >= 2){
		m_aAxis[0]	-= 2;
		m_aAxis[1]	-= 2;
		LampUpdate();
	}
}

void CStautsView::OnBtnNext() 
{
	long	lAxisCount;
	AxmInfoGetAxisCount(&lAxisCount);
	if(m_aAxis[1] < lAxisCount-1){
		m_aAxis[0]	+= 2;
		m_aAxis[1]	+= 2;
		LampUpdate();
	}	
}

void CStautsView::OnBtnCur() 
{
	LampUpdate();	
}
