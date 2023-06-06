// GL3DGraph.cpp : implementation file
//

#include "stdafx.h"
#include "camc_qi.h"
#include "GL3DGraph.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _M_X64
	#pragma comment(lib, "./KGraph3D/Library/64Bit/AjinGL3DGraph.lib")
#else
	#pragma comment(lib, "./KGraph3D/Library/32Bit/AjinGL3DGraph.lib")
#endif

/////////////////////////////////////////////////////////////////////////////
// GL3DGraph dialog

UINT GraphThread(LPVOID pFuncData);

 GL3DGraph::GL3DGraph(CWnd* pParent, long nAxis)
	: CDialog(GL3DGraph::IDD, pParent)
{
	//{{AFX_DATA_INIT(GL3DGraph)
	m_nDimension = 3;
	m_nResetAxis = 0;
	m_bBoxEnable = TRUE;
	//}}AFX_DATA_INIT
	m_pParent	= pParent;

	/*m_aAxis[0]	= AXIS_N04(nAxis, 0);
	m_aAxis[1]	= AXIS_N04(nAxis, 1);
	m_aAxis[2]	= AXIS_N04(nAxis, 2);
	m_aAxis[3]	= AXIS_N04(nAxis, 3);*/

	m_aAxis[0] = 3;
	m_aAxis[1] = 2;
	m_aAxis[2] = 0;
	m_aAxis[3] = AXIS_N04(nAxis, 3);

	m_PlotColor = RGB(255,0,0);

	m_hGraphThread		= FALSE;
	m_bGraphThread		= NULL;
}


void GL3DGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GL3DGraph)
	DDX_Control(pDX, IDC_EDIT_RANGEZ, m_editRangeZ);
	DDX_Control(pDX, IDC_EDIT_RANGEY, m_editRangeY);
	DDX_Control(pDX, IDC_EDIT_RANGEX, m_editRangeX);
	DDX_Control(pDX, IDC_STC_ZCMD, m_ctrlZCmd);
	DDX_Control(pDX, IDC_STC_YCMD, m_ctrlYCmd);
	DDX_Control(pDX, IDC_STC_XCMD, m_ctrlXCmd);
	DDX_Control(pDX, IDC_STC_ZCMDPOS, m_ctrlZCmdPos);
	DDX_Control(pDX, IDC_STC_YCMDPOS, m_ctrlYCmdPos);
	DDX_Control(pDX, IDC_STC_XCMDPOS, m_ctrlXCmdPos);
	DDX_CBIndex(pDX, IDC_CMB_DIMENSION, m_nDimension);
	DDX_CBIndex(pDX, IDC_CMB_AXISRESET, m_nResetAxis);
	DDX_Check(pDX, IDC_CHK_BOX, m_bBoxEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GL3DGraph, CDialog)
	//{{AFX_MSG_MAP(GL3DGraph)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_HEL_ADD, OnBtnHelAdd)
	ON_BN_CLICKED(IDC_BTN_HEL_PLAY, OnBtnHelPlay)
	ON_BN_CLICKED(IDC_BTN_SPL_ADD, OnBtnSplAdd)
	ON_BN_CLICKED(IDC_BTN_SPL_PLAY, OnBtnSplPlay)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_CBN_SELCHANGE(IDC_CMB_DIMENSION, OnSelchangeCmbDimension)
	ON_CBN_SELCHANGE(IDC_CMB_AXISRESET, OnSelchangeCmbAxisreset)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BTN_PLOTCOLOR, OnBtnPlotcolor)
	ON_BN_CLICKED(IDC_CHK_BOX, OnChkBox)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SETRANGE, OnButtonSetRange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GL3DGraph message handlers

void GL3DGraph::InitialControl()
{
	//X Control
	m_ctrlXCmd.SetTextColor(YELLOW);
	m_ctrlXCmd.SetFont("Arial", 15, FW_NORMAL);
	m_ctrlXCmd.Format("X CMD");
	m_ctrlXCmd.SetBkColor(RGB(0,0,0), RGB(0,0,0), CxStatic::VGradient);

	m_ctrlXCmdPos.SetTextColor(GREEN);
	m_ctrlXCmdPos.SetFont("Arial", 15, FW_NORMAL);
	m_ctrlXCmdPos.Format("0.000");
	m_ctrlXCmdPos.SetBkColor(RGB(0,0,0), RGB(0,0,0), CxStatic::VGradient);


	//Y Control
	m_ctrlYCmd.SetTextColor(YELLOW);
	m_ctrlYCmd.SetFont("Arial", 15, FW_NORMAL);
	m_ctrlYCmd.Format("Y CMD");
	m_ctrlYCmd.SetBkColor(RGB(0,0,0), RGB(0,0,0), CxStatic::VGradient);

	m_ctrlYCmdPos.SetTextColor(GREEN);
	m_ctrlYCmdPos.SetFont("Arial", 15, FW_NORMAL);
	m_ctrlYCmdPos.Format("0.000");
	m_ctrlYCmdPos.SetBkColor(RGB(0,0,0), RGB(0,0,0), CxStatic::VGradient);

	//Z Control
	m_ctrlZCmd.SetTextColor(YELLOW);
	m_ctrlZCmd.SetFont("Arial", 15, FW_NORMAL);
	m_ctrlZCmd.Format("Z CMD");
	m_ctrlZCmd.SetBkColor(RGB(0,0,0), RGB(0,0,0), CxStatic::VGradient);

	m_ctrlZCmdPos.SetTextColor(GREEN);
	m_ctrlZCmdPos.SetFont("Arial", 15, FW_NORMAL);
	m_ctrlZCmdPos.Format("0.000");
	m_ctrlZCmdPos.SetBkColor(RGB(0,0,0), RGB(0,0,0), CxStatic::VGradient);

	m_strFont1.LoadString(IDS_STRING1001);

	m_editRangeX.bkColor( BLACK );
	m_editRangeX.textColor( YELLOW );
	m_editRangeX.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_editRangeX.SetWindowText("50000");

	m_editRangeY.bkColor( BLACK );
	m_editRangeY.textColor( YELLOW );
	m_editRangeY.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_editRangeY.SetWindowText("50000");

	m_editRangeZ.bkColor( BLACK );
	m_editRangeZ.textColor( YELLOW );
	m_editRangeZ.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_editRangeZ.SetWindowText("50000");
}


BOOL GL3DGraph::OnInitDialog() 
{
	CDialog::OnInitDialog();
	 CRect rect(10, 10, 10, 10);
	m_pDisplay.Create(NULL,		//CWnd default
					   NULL,		//has no name
					   WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_VISIBLE,
					   rect,
					   this,		//this is the parent
					   0);			//this should really be a different number ... check resource.h
	//Generate OnSize to get Graph window positioned right
	CRect r;
	GetWindowRect(&r);
	r.InflateRect(1,1);
	MoveWindow(r);

	m_pDisplay.SetProjection(ORTHOGRAPHICS);
	m_pDisplay.SetSymbolSize(5);
	m_pDisplay.SetBackgroundColor(RGB(0,0,0));
	m_pDisplay.AllowMouseRotate(1);

	// TODO: Add extra initialization here
	m_pDisplay.SetRange3Axis(2500, 2500, 2500);

	InitialControl();

	StartGraphThread();

	return TRUE;  // return TRUE unless you set the focus to a control
	            
}

void GL3DGraph::UpdateAxis(long lAxis)
{
	/*m_aAxis[0]	= AXIS_N04(lAxis, 0);
	m_aAxis[1]	= AXIS_N04(lAxis, 1);
	m_aAxis[2]	= AXIS_N04(lAxis, 2);
	m_aAxis[3]	= AXIS_N04(lAxis, 3);
*/
	m_aAxis[0] = 3;
	m_aAxis[1] = 2;
	m_aAxis[2] = 0;
}

void GL3DGraph::UpdateRange(long lRange)
{
	if(lRange < 0)	return;

	m_pDisplay.SetRangeX(lRange);
	m_pDisplay.SetRangeY(lRange);
	m_pDisplay.SetRangeZ(lRange);

	m_pDisplay.Clear();
}

void GL3DGraph::StartGraphThread()
{
	unsigned long	ThreadID;
	if(m_hGraphThread == NULL)
	{
		m_bGraphThread = TRUE;
		m_hGraphThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GraphThread, this, 0, &ThreadID);
	}
}

UINT GraphThread(LPVOID pFuncData)
{
	GL3DGraph		*pDlg = (GL3DGraph *)pFuncData;

	double dCmdX, dCmdY, dCmdZ; 
	double dVelX, dVelY, dVelZ; 

	while(pDlg->m_bGraphThread)
	{
		AxmStatusReadVel(pDlg->m_aAxis[0], &dVelX);
		AxmStatusReadVel(pDlg->m_aAxis[1], &dVelY);
		AxmStatusReadVel(pDlg->m_aAxis[2], &dVelZ);
		
		AxmStatusGetCmdPos(pDlg->m_aAxis[0], &dCmdX);
		AxmStatusGetCmdPos(pDlg->m_aAxis[1], &dCmdY);
		AxmStatusGetCmdPos(pDlg->m_aAxis[2], &dCmdZ);
		
		pDlg->m_ctrlXCmdPos.Format("%.3f", dCmdX);
		pDlg->m_ctrlYCmdPos.Format("%.3f", dCmdY);
		pDlg->m_ctrlZCmdPos.Format("%.3f", dCmdZ);

		pDlg->m_pDisplay.AddPoint(dCmdX, dCmdY, dCmdZ);

		pDlg->m_pDisplay.RedrawWindow();

		Sleep(10);
	}

	pDlg->m_bGraphThread = FALSE;
	CloseHandle(pDlg->m_hGraphThread);
	pDlg->m_hGraphThread = NULL;

	return 0;
}

void GL3DGraph::OnSize(UINT nType, int cx, int cy) 
{
	if(m_pDisplay.GetSafeHwnd() == NULL)		//OnSize first called before Buttons created ??
		return;
	// TODO: Add your message handler code here
	ModifyStyle(0, WS_CLIPCHILDREN);

	CRect rect;
	GetDlgItem(IDC_PIC_3DGRAPH)->GetWindowRect(rect);
	ScreenToClient(rect);

	rect.right = cx - 10;
	rect.bottom = cy - 10;
	m_pDisplay.MoveWindow(rect);
	ModifyStyle(WS_CLIPCHILDREN, 0);
	
	// TODO: Add your message handler code here
	
}

void GL3DGraph::OnBtnHelAdd() 
{
	double  dVelocity = 2000, dAccel = 4000;

	AxmContiSetAxisMap(COORDINATE, 4, m_aAxis);
	AxmContiWriteClear(COORDINATE);
	AxmContiSetAbsRelMode(COORDINATE, POS_REL_MODE);

	AxmContiBeginNode(COORDINATE);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
		AxmHelixCenterMove(COORDINATE, 500, 500, 0, 0, 100, dVelocity, dAccel, dAccel, DIR_CW);
	AxmContiEndNode(COORDINATE);
}

void GL3DGraph::OnBtnHelPlay() 
{
	AxmContiStart(COORDINATE , 0, 0);
}

void GL3DGraph::OnBtnSplAdd() 
{
	double  dVelocity = 2000, dAccel = 4000;
	double  dPosX[5];
	double  dPosY[5];


	AxmContiSetAxisMap(COORDINATE, 3, m_aAxis);
	AxmContiWriteClear(COORDINATE);
	AxmContiSetAbsRelMode(COORDINATE, POS_ABS_MODE);

	dPosX[0] = 0,		dPosY[0] = 0;
	dPosX[1] = 450,		dPosY[1] = 100;
	dPosX[2] = 750,		dPosY[2] = 450;
	dPosX[3] = 1080,	dPosY[3] = 750;
	dPosX[4] = 1300,	dPosY[4] = 700;

	AxmContiBeginNode(COORDINATE);
	AxmSplineWrite(COORDINATE, 5, dPosX, dPosY, dVelocity, dAccel, dAccel, 1, 100);
	AxmContiEndNode(COORDINATE);
}

void GL3DGraph::OnBtnSplPlay() 
{
	AxmContiStart(COORDINATE , 0, 0);
}

void GL3DGraph::OnBtnClear() 
{
	AxmStatusSetActPos(m_aAxis[0], 0.0);
	AxmStatusSetActPos(m_aAxis[1], 0.0);
	AxmStatusSetActPos(m_aAxis[2], 0.0);
	AxmStatusSetActPos(m_aAxis[3], 0.0);

	AxmStatusSetCmdPos(m_aAxis[0], 0.0);
	AxmStatusSetCmdPos(m_aAxis[1], 0.0);
	AxmStatusSetCmdPos(m_aAxis[2], 0.0);
	AxmStatusSetCmdPos(m_aAxis[3], 0.0);

	AxmContiWriteClear(COORDINATE);
    m_pDisplay.Clear();
}

void GL3DGraph::OnSelchangeCmbDimension() 
{
	UpdateData();
	switch(m_nDimension)
	{
	case 0:
		m_pDisplay.SetDimensionXY();
		break;
	case 1:
		m_pDisplay.SetDimensionYZ();
		break;
	case 2:
		m_pDisplay.SetDimensionXZ();
		break;
	case 3:
		m_pDisplay.SetDimensionXYZ();
		break;
	default:
		m_pDisplay.SetDimensionXYZ();
		break;
	}
}

void GL3DGraph::OnSelchangeCmbAxisreset() 
{
	UpdateData();
	switch(m_nResetAxis)
	{
	case 0:
		m_pDisplay.SetRangeX(50000);
		m_pDisplay.SetRangeY(50000);
		break;
	case 1:
		m_pDisplay.SetRangeY(50000);
		m_pDisplay.SetRangeZ(50000);
		break;
	case 2:
		m_pDisplay.SetRangeX(50000);
		m_pDisplay.SetRangeZ(50000);
		break;
	case 3:
		m_pDisplay.SetRange3Axis(50000,50000,50000);
		break;
	default:
		break;
	}
}

void GL3DGraph::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if(nIDCtl == IDC_BTN_PLOTCOLOR)
	{
		if(lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
		{
			HBRUSH hBrush;
			hBrush = ::CreateSolidBrush(m_PlotColor);
			::FillRect(lpDrawItemStruct->hDC, &(lpDrawItemStruct->rcItem), hBrush);
			::DeleteObject(hBrush);
		}
		else if(lpDrawItemStruct->itemAction & ODA_FOCUS)
		{
			RECT focusR = lpDrawItemStruct->rcItem;
			focusR.top += 2;
			focusR.bottom -= 2;
			focusR.left +=2;
			focusR.right -= 2;
			::DrawFocusRect(lpDrawItemStruct->hDC, &focusR);
		}
		return;
	}
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void GL3DGraph::OnBtnPlotcolor() 
{
	CColorDialog dlg;
	if(dlg.DoModal() != IDOK)
		return;
	m_PlotColor = dlg.GetColor();
	GetDlgItem(IDC_BTN_PLOTCOLOR)->Invalidate();
	m_pDisplay.SetPlotColor(m_PlotColor);
}

void GL3DGraph::OnChkBox() 
{
	UpdateData();
	m_pDisplay.SetBoxEnable(m_bBoxEnable);
}

void GL3DGraph::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_bGraphThread = FALSE;
		
	if(m_hGraphThread != NULL){
		TerminateThread(m_hGraphThread, 0);
		WaitForSingleObject(m_hGraphThread,  WAIT_ABANDONED);
		CloseHandle(m_hGraphThread);
		m_hGraphThread = NULL;
	}
}

void GL3DGraph::OnButtonSetRange() 
{
	CString strRangeX, strRangeY, strRangeZ;
	float   flRangeX, flRangeY, flRangeZ;

	GetDlgItemText(IDC_EDIT_RANGEX, strRangeX);
	GetDlgItemText(IDC_EDIT_RANGEY, strRangeY);
	GetDlgItemText(IDC_EDIT_RANGEZ, strRangeZ);

	flRangeX =atof (strRangeX);
	flRangeY =atof (strRangeY);
	flRangeZ =atof (strRangeZ);

	m_pDisplay.SetRangeX(flRangeX);
	m_pDisplay.SetRangeY(flRangeY);
	m_pDisplay.SetRangeZ(flRangeZ);
}
