// CAMC_QIDlg.cpp : implementation file
//
#include "stdafx.h"
#include "CAMC_QIDlg.h"
#include "CAMC_QI.h"
#include "CSXButton.h"
#include "xShadeButton.h"
#include "Led.h"
#include "EditEx.h"
#include "math.h"
#include <nlohmann/json.hpp>
#include <cstring>
#include <iostream>
#include <fstream>
#include "afx.h"
#include <afxmt.h>
#include <sstream>
#include <chrono>
//#include "afxdialogex.h"

#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib") // trinh lien ket tim kiem thu vien




#ifdef _DEBUG
#define CURL_STATICLIB
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////khai bao cho chuong trinh G code///////////////////////
using namespace std;
using namespace chrono;
float x, y, z, a, b, i, j, f, spindle_speed, r, don_vi;
uint8_t g;
bool check_run = false;
bool spindle = false;
bool stop_code = false;
bool cirle = false;         // false: chạy với I,J     true: chạy với R
bool SET_RELATY = false;
bool rece1 = false;
bool connect_sucess = false;
bool run_gcode_finish = false;
bool disconnect = false;
bool internet_connect = false;
int temp = 0;
int dem1,dem2;
int dem = 0;
DWORD outPulse, outMethod, outlevel;
string mess_pas = "", str_post = "", str_post_2 = "", mess_time = "", mess_data = "", mess_data_pas = "", mess_time_pas = "";
string str_time[50];
string mess = "";
bool connect_iot = false;
bool rece = false;
int dem_str = 1;
CString strText;
string str_product;
double product = 0;
CString l_strFileName;
bool run_ok = false;
CMutex m_Mutex;
CString run_test;
DWORD stt0, stt1, stt2, stt3, stt4;
DWORD axmline;
long lAxis1[2];
ofstream myfiledata0;
ofstream myfiledata1;
ofstream myfiledata2;
ofstream myfiledata3;
ofstream myfiledata4;
ofstream myfiledata5;
//double Xcnc, Ycnc, Zcnc, M;
///////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#ifdef _M_X64
	#pragma comment(lib, "../../../../AXL(Library)/Library/64Bit/AxL.lib")
#else
	#pragma comment(lib, "../../../../AXL(Library)/Library/32Bit/AxL.lib")
#endif

#define TM_DISPLAY			0
#define TM_GRAPH			1
#define TM_IOT				101
#define TM_Internet			102


//#define TM_HOME_FUN1		102		// 0 Axis Starting point searching
//#define TM_HOME_FUN2		103		// 1 Axis Starting point searching
//#define TM_HOME_FUN3		104		// 2 Axis Starting point searching
//#define TM_HOME_FUN4		105		// 3 Axis Starting point searching

#define AXIS_EVN(AXIS_NO)		(AXIS_NO - (AXIS_NO % 2))			// Searching for even number axis of axis which makes couple
#define AXIS_ODD(AXIS_NO)		(AXIS_NO + ((AXIS_NO + 1) % 2))		// Searching for odd number axis of axis which makes couple
#define AXIS_QUR(AXIS_NO)		(AXIS_NO % 4)
#define AXIS_N04(AXIS_NO, POS)	(((AXIS_NO / 4) * 4) + POS)			// Change to the axis' location of the one chip
#define AXIS_N01(AXIS_NO)		((AXIS_NO % 4) >> 2)				// Change axis of 0, 1 or 0, 2, 3 to 1
#define AXIS_N02(AXIS_NO)		((AXIS_NO % 4)  % 2)				// Change axis of 0, 2 or 0, 1, 3 to 1

#define COORD_NO			0

UINT SearchThread(LPVOID pFuncData);
UINT RepeatThread(LPVOID pFuncData);

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAPz
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CCAMC_QIDlg dialog

CCAMC_QIDlg::CCAMC_QIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCAMC_QIDlg::IDD, pParent), m_GraphX(2), m_GraphY(2)
{
	m_pStatus		= NULL;
	m_pGL3DGraph	= NULL;
	m_bEstop		= FALSE;
	
	m_bStatus		= TRUE;
	m_bManualSet	= TRUE;
	m_b3DGraph		= TRUE;

	m_pManualSet	= NULL;

	m_lAxis			= 0;	
	m_lRange		= 2500;
	m_bContiFlag	= FALSE;
	
	m_bA4NAxis		= FALSE;

	for(int i = 0; i < MAX_AXIS_COUNT; i++)
	{
		m_bTestActive[i]	= FALSE;
		m_hTestThread[i]	= NULL;

		m_bThread[i]		= FALSE;
		m_hHandle[i]		= NULL;
		m_hInterrupt[i]		= NULL;
	}

	//{{AFX_DATA_INIT(CCAMC_QIDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32		
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCAMC_QIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCAMC_QIDlg)
	//DDX_Control(pDX, IDC_BTN_TRIG_RESET, m_btnTrigReset);
	//DDX_Control(pDX, IDC_BTN_TRIG_PERIOD, m_btnTrigPeriod);
	//DDX_Control(pDX, IDC_BTN_TRIG_ONESHOT, m_btnTrigOneshot);
	//DDX_Control(pDX, IDC_BTN_TRIG_ABS, m_btnTrigABS);
	//DDX_Control(pDX, IDC_EDT_TRIG_CYCLE, m_edtTrigCycle);
	//DDX_Control(pDX, IDC_EDT_TRIG_END_POS, m_edtTrigEndPos);
	//DDX_Control(pDX, IDC_EDT_TRIG_PULSE_WIDTH, m_edtTrigPulseWidth);
	//DDX_Control(pDX, IDC_EDT_TRIG_START_POS, m_edtTrigStartPos);
	//DDX_Control(pDX, IDC_CHK_GEAR_ONOFF, m_chkGearOnOff);
 	DDX_Control(pDX, IDC_CHK_XY_SYNC, m_chkXYsync);
	//DDX_Control(pDX, IDC_CHK_GANTRY, m_chkGantry);
	DDX_Control(pDX, IDC_LED_ZPHASE, m_ledZphase);
	DDX_Control(pDX, IDC_CBO_ENC_INPUTM, m_cboEncInputM);
	//DDX_Control(pDX, IDC_CHK_HOME_LEVEL, m_chkHomeLevel);
	DDX_Control(pDX, IDC_CHK_SCURVE, m_chkScurve);
	DDX_Control(pDX, IDC_BTN_JOG_PX, m_btnJogPx);
	DDX_Control(pDX, IDC_BTN_JOG_NX, m_btnJogNx);
	DDX_Control(pDX, IDC_BTN_JOG_PY, m_btnJogPy);
	DDX_Control(pDX, IDC_BTN_JOG_NY, m_btnJogNy);
	DDX_Control(pDX, IDC_BTN_JOG_PZ, m_btnJogPz);
	DDX_Control(pDX, IDC_BTN_JOG_NZ, m_btnJogNz);
	DDX_Control(pDX, IDC_BTN_JOG_PU, m_btnJogPu);
	DDX_Control(pDX, IDC_BTN_JOG_NU, m_btnJogNu);
	//DDX_Control(pDX, IDC_CBO_DETECT, m_cboDetect);
	//DDX_Control(pDX, IDC_CBO_DIRECTION, m_cboDirection);
	//DDX_Control(pDX, IDC_CBO_STOPM, m_cboStopM);
	DDX_Control(pDX, IDC_CBO_PULSE_OUTM, m_cboPulseOutM);
	//DDX_Control(pDX, IDC_CBO_HOME_SIGNAL, m_cboHomeSignal);
	//DDX_Control(pDX, IDC_CBO_HOME_DIR, m_cboHomeDir);
	DDX_Control(pDX, IDC_CHK_RELATIVE, m_chkRelative);
	//DDX_Control(pDX, IDC_CHK_PELM_LEVEL, m_chkPelmLevel);
	//DDX_Control(pDX, IDC_CHK_NELM_LEVEL, m_chkNelmLevel);
	//DDX_Control(pDX, IDC_CHK_INP_LEVEL, m_chkInpLevel);
	//DDX_Control(pDX, IDC_CHK_CW_CCW, m_chkCwCcw);
	//DDX_Control(pDX, IDC_CHK_GANTRY_SLAVE, m_chkGantrySlave);
	//DDX_Control(pDX, IDC_CHK_ZPHASE_LEVEL, m_chkZphaseLevel);
	DDX_Control(pDX, IDC_CHK_ASYM, m_chkAsym);
	//DDX_Control(pDX, IDC_CHK_ALARM_LEVEL, m_chkAlarmLevel);
	DDX_Control(pDX, IDC_CHK_ABSOLUTE, m_chkAbsolute);
	//DDX_Control(pDX, IDC_CHK_EMG_LEVEL, m_chkEmgLevel);
	DDX_Control(pDX, IDC_CBO_AXISSET, m_cboAxisSet);
	//DDX_Control(pDX, IDC_BTN_CIRCULAR, m_bthCircular);
	DDX_Control(pDX, IDC_BTN_COUNT_CLR, m_btnCountClr);
	DDX_Control(pDX, IDC_BTN_ESTOP, m_btnEstop);
	DDX_Control(pDX, IDC_LED_ALARM, m_ledAlarm);
	//DDX_Control(pDX, IDC_LED_BUSYY, m_ledBusyY);
	//DDX_Control(pDX, IDC_LED_BUSYX, m_ledBusyX);
	//DDX_Control(pDX, IDC_LED_EXMP, m_ledExmp);
	//DDX_Control(pDX, IDC_LED_EXPP, m_ledExpp);
	DDX_Control(pDX, IDC_LST_LOG, m_lstLog);
	DDX_Control(pDX, IDC_LST_LOG2, m_lstLog2);

	DDX_Control(pDX, IDC_LST_LOG_gcode, m_lstLoggcode);
	DDX_Control(pDX, IDC_LED_HOME, m_ledHome);
	DDX_Control(pDX, IDC_LED_PELM, m_ledPelm);
	/*DDX_Control(pDX, IDC_LED_OUT5, m_ledOut5);
	DDX_Control(pDX, IDC_LED_OUT4, m_ledOut4);
	DDX_Control(pDX, IDC_LED_OUT3, m_ledOut3);
	DDX_Control(pDX, IDC_LED_OUT2, m_ledOut2);
	DDX_Control(pDX, IDC_LED_OUT1, m_ledOut1);
	DDX_Control(pDX, IDC_LED_OUT0, m_ledOut0);*/
	DDX_Control(pDX, IDC_LED_NELM, m_ledNelm);
	//DDX_Control(pDX, IDC_LED_INP, m_ledInp);
	/*DDX_Control(pDX, IDC_LED_IN5, m_ledIn5);
	DDX_Control(pDX, IDC_LED_IN4, m_ledIn4);
	DDX_Control(pDX, IDC_LED_IN3, m_ledIn3);
	DDX_Control(pDX, IDC_LED_IN2, m_ledIn2);
	DDX_Control(pDX, IDC_LED_IN1, m_ledIn1);
	DDX_Control(pDX, IDC_LED_IN0, m_ledIn0);*/
	DDX_Control(pDX, IDC_LED_EMG, m_ledEmg);
	//DDX_Control(pDX, IDC_BTN_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BTN_STATUS, m_btnStatus);
	DDX_Control(pDX, IDC_BTN_REPEAT, m_btnRepeat);
	DDX_Control(pDX, IDC_BTN_MOVE, m_btnMove);
	//DDX_Control(pDX, IDC_BTN_LINEAR, m_btnLinear);
	//DDX_Control(pDX, IDC_BTN_HOME_ALL, m_btnHomeAll);
	//DDX_Control(pDX, IDC_BTN_HOME_SINGLE, m_btnHomeSingle);
	//DDX_Control(pDX, IDC_BTN_CRC_ON, m_btnCrcOn);
	//DDX_Control(pDX, IDC_BTN_CRC_OFF, m_btnCrcOff);
	DDX_Control(pDX, IDC_EDIT1, m_sendserver);
	//}}AFX_DATA_MAP
	
}

BEGIN_MESSAGE_MAP(CCAMC_QIDlg, CDialog)
	//{{AFX_MSG_MAP(CCAMC_QIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//ON_BN_CLICKED(IDC_BTN_HOME_ALL, OnBtnHomeAll)
	//ON_BN_CLICKED(IDC_BTN_HOME_SINGLE, OnBtnHomeSingle)
	//ON_BN_CLICKED(IDC_BTN_VEL_OVERRIDE, OnBtnVelOverride)
	//ON_BN_CLICKED(IDC_CHK_PELM_LEVEL, OnChkPelmLevel)
	//ON_BN_CLICKED(IDC_CHK_NELM_LEVEL, OnChkNelmLevel)
	//ON_BN_CLICKED(IDC_CHK_INP_LEVEL, OnChkInpLevel)
	//ON_BN_CLICKED(IDC_CHK_ALARM_LEVEL, OnChkAlarmLevel)
	//ON_BN_CLICKED(IDC_CHK_EMG_LEVEL, OnChkEmgLevel)	
	/*ON_BN_CLICKED(IDC_LED_OUT0, OnLedOut0)
	ON_BN_CLICKED(IDC_LED_OUT1, OnLedOut1)
	ON_BN_CLICKED(IDC_LED_OUT2, OnLedOut2)
	ON_BN_CLICKED(IDC_LED_OUT3, OnLedOut3)
	ON_BN_CLICKED(IDC_LED_OUT4, OnLedOut4)
	ON_BN_CLICKED(IDC_LED_OUT5, OnLedOut5)*/
	//ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	//ON_BN_CLICKED(IDC_CHK_HOME_LEVEL, OnChkHomeLevel)
	ON_BN_CLICKED(IDC_CHK_ASYM, OnChkAsym)
	ON_BN_CLICKED(IDC_CHK_ABSOLUTE, OnChkAbsolute)
	ON_BN_CLICKED(IDC_CHK_RELATIVE, OnChkRelative)
	ON_BN_CLICKED(IDC_BTN_SETTING, OnBtnSetting)
	ON_BN_CLICKED(IDC_BTN_REPEAT, OnBtnRepeat)
	//ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_ESTOP, OnBtnEstop)
	//ON_BN_CLICKED(IDC_CHK_ZPHASE_LEVEL, OnChkZphaseLevel)
	ON_BN_CLICKED(IDC_BTN_STATUS, OnBtnStatus)
	ON_CBN_SELCHANGE(IDC_CBO_AXISSET, OnSelchangeCmbAxisset)
	ON_CBN_SELCHANGE(IDC_CBO_PULSE_OUTM, OnSelchangeCmbPulseOutm)
	ON_CBN_SELCHANGE(IDC_CBO_ENC_INPUTM, OnSelchangeCmbEncInputm)
	ON_BN_CLICKED(IDC_BTN_MOVE, OnBtnMove)
	//ON_BN_CLICKED(IDC_BTN_LINEAR, OnBtnLinear)
	//ON_BN_CLICKED(IDC_BTN_CIRCULAR, OnBtnCircular)
	ON_BN_CLICKED(IDC_BTN_COUNT_CLR, OnBtnCountClr)
	ON_BN_CLICKED(IDC_BTN_CONTI_LINE, OnBtnContiLine)
	ON_BN_CLICKED(IDC_BTN_CONTI_SPLINE, OnBtnContiSpline)
	ON_BN_CLICKED(IDC_BTN_CONTI_START, OnBtnContiStart)
	//ON_BN_CLICKED(IDC_CHK_GANTRY, OnChkGantry)
	ON_BN_CLICKED(IDC_BTN_CONTI_CLR, OnBtnContiClr)
	//ON_BN_CLICKED(IDC_BTN_INT_DISABLE, OnBtnIntDisable)
	//ON_BN_CLICKED(IDC_BTN_CRC_OFF, OnBtnCrcOff)
	//ON_BN_CLICKED(IDC_BTN_CRC_ON, OnBtnCrcOn)
	//ON_BN_CLICKED(IDC_BTN_MPG_OFF, OnBtnMpgOff)
	//ON_BN_CLICKED(IDC_BTN_MPG_ON, OnBtnMpgOn)
	ON_BN_CLICKED(IDC_BTN_CONTI_TEST, OnBtncontiTest)
	ON_BN_CLICKED(IDC_BTN_MANUALSET, OnBtnManualset)
	ON_BN_CLICKED(IDC_CHK_SCURVE, OnChkScurve)
	ON_BN_CLICKED(IDC_BTN_LOAD, OnBtnLoad)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//ON_BN_CLICKED(IDC_BTN_TRIG_RESET, OnBtnTrigReset)
	//ON_BN_CLICKED(IDC_BTN_TRIG_ABS, OnBtnTrigAbs)
	//ON_BN_CLICKED(IDC_BTN_TRIG_PERIOD, OnBtnTrigPeriod)
	ON_WM_HSCROLL()
	//ON_BN_CLICKED(IDC_BTN_SIG_CAPTURE, OnBtnSigCapture)
	//ON_BN_CLICKED(IDC_BTN_INT_MESSAGE, OnBtnIntMessage)
	//ON_BN_CLICKED(IDC_BTN_INT_EVENT, OnBtnIntEvent)
	//ON_BN_CLICKED(IDC_BTN_INT_CALLBACK, OnBtnIntCallback)
	ON_BN_CLICKED(IDC_BTN_CONTI_BLEND, OnBtnContiBlend)
	ON_BN_CLICKED(IDC_BTN_CONTI_CIRCLE, OnBtnContiCircle)
	//ON_BN_CLICKED(IDC_BTN_TRIG_ONESHOT, OnBtnTrigOneshot)
	//ON_BN_CLICKED(IDC_CHK_GEAR_ONOFF, OnChkGearOnoff)
	ON_LBN_DBLCLK(IDC_LST_LOG, OnDblclkLstLog)
	//ON_BN_CLICKED(IDC_BTN_READ_CAPTURE, OnBtnReadCapture)
	ON_BN_CLICKED(IDC_BTN_3DGRAPH, OnBtn3dgraph)
	//ON_BN_CLICKED(IDC_CHK_GANTRY_SLAVE, OnChkGantrySlave)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CAMC_INTERRUPT, OnControlMessage)

	ON_BN_CLICKED(IDC_BTN_LOAD_gcode, OnBnClickedBtnLoadgcode)
	ON_BN_CLICKED(IDC_BTN_START_gcode, OnBnClickedBtnStartgcode)
	ON_BN_CLICKED(IDC_BTN_SPL,OnBnClickedBtnSpl)
	ON_BN_CLICKED(IDC_BTN_SET_SPD, OnBnClickedBtnSetSpd)
	ON_BN_CLICKED(IDC_BTN_CNT_IoT, OnBnClickedBtnCntIot)
	ON_BN_CLICKED(IDC_BTN_DISCNT_IoT, OnBnClickedBtnDiscntIot)
	ON_BN_CLICKED(IDC_BTN_TCP_IP, OnBnClickedBtnTcpIp)
	ON_EN_CHANGE(IDC_EDIT1,OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1,OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2,OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCAMC_QIDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCAMC_QIDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCAMC_QIDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BTN_SET_HOME, &CCAMC_QIDlg::OnBnClickedBtnSetHome)
	ON_BN_CLICKED(IDC_BTN_GO_HOME, &CCAMC_QIDlg::OnBnClickedBtnGoHome)
	ON_BN_CLICKED(IDC_BUTTON7, &CCAMC_QIDlg::OnBnClickedButton7)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAMC_QIDlg message handlers
int			g_nIntCnt;
CCAMC_QIDlg *g_QIDlg;
void __stdcall KeMotionInterruptCallback(long lActiveNo, DWORD dwFlag)
{	
	CString strData;
	g_nIntCnt++;

	DWORD IntBank0;
	DWORD IntBank1;

	AxmInterruptReadAxisFlag(lActiveNo, 0, &IntBank0);
	AxmInterruptReadAxisFlag(lActiveNo, 1, &IntBank1);

	strData.Format("Cal[%03d]Axis[%02d]Flag[0x%02X]", g_nIntCnt, lActiveNo, dwFlag);
	g_QIDlg->m_lstLog.AddString(strData);
}

BOOL CCAMC_QIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);				// Set big icon
	SetIcon(m_hIcon, FALSE);			// Set small icon
	// tạo luồng kiểm tra internet
	thread_check_connect = AfxBeginThread(Mythread_check_connect, this);

	str_time[49] = "k";
	//++
	InitLibrary();						// Combined Library and Module initialize
	InitControl();						// Graph and button control initialize

	UpdateAxisInfo();
	
	SetTimer(TM_DISPLAY, 50, NULL);		// Timer start of various information print out
	SetTimer(TM_GRAPH, 50, NULL);		// Timer start of speed graph
	SetTimer(TM_IOT, 50, NULL);
	SetTimer(TM_Internet, 1000, NULL);
	
	g_QIDlg = this;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCAMC_QIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CCAMC_QIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CCAMC_QIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Display double value on the designated control
void CCAMC_QIDlg::SetDlgItemDouble(int nID, double value, int nPoint)
{
	CString sTemp, sTemp2;
	sTemp2.Format("%%.%df", nPoint);
	sTemp.Format(sTemp2, value);
	GetDlgItem(nID)->SetWindowText(sTemp);
}

// Read double value on the designated control
double CCAMC_QIDlg::GetDlgItemDouble(int nID)
{
	double dRet;
	CString sTemp;
	GetDlgItem(nID)->GetWindowText(sTemp);
	dRet = atof((LPCTSTR)sTemp);
	return dRet;
}

void CCAMC_QIDlg::OnTimer(UINT_PTR nIDEvent) 
{
	CString	strData;

	DWORD   wReadInput = 0, wReadOuput = 0, wBusyStatus = 0, wReadHome = 0;
	DWORD   wReadInterpolationQueueFree = 0, wIsContMotion = 0, wMechanicalStatus = 0;	
	DWORD   wHomeResult0 = 0, wHomeResult1 = 0, wHomeResult2 = 0, wHomeResult3 = 0;

	lsByte  bUnivInput, bUnivOutput, bMechanic;
	double  dCmdPos[4] = {0}, dActPos[4] = {0}, dpCapPotition;
	long    lNodeNum1 = 0, lTotalNodeNum1 = 0;

	

	switch (nIDEvent)
	{
		// It is displayed part of motion on the screen and timer
	case TM_DISPLAY:
	{
		AxmStatusGetCmdPos(AXIS_N04(m_lAxis, 0), &dCmdPos[0]);
		AxmStatusGetActPos(AXIS_N04(m_lAxis, 0), &dActPos[0]);

		AxmStatusGetCmdPos(AXIS_N04(m_lAxis, 1), &dCmdPos[1]);
		AxmStatusGetActPos(AXIS_N04(m_lAxis, 1), &dActPos[1]);

		AxmStatusGetCmdPos(AXIS_N04(m_lAxis, 2), &dCmdPos[2]);
		AxmStatusGetActPos(AXIS_N04(m_lAxis, 2), &dActPos[2]);

		AxmStatusGetCmdPos(AXIS_N04(m_lAxis, 3), &dCmdPos[3]);
		AxmStatusGetActPos(AXIS_N04(m_lAxis, 3), &dActPos[3]);

		/*SetDlgItemDouble(IDC_EDT_CMD_POSX, dCmdPos[0]);
		SetDlgItemDouble(IDC_EDT_CMD_POSY, dCmdPos[1]);

		SetDlgItemDouble(IDC_EDT_ACT_POSX, dActPos[0]);
		SetDlgItemDouble(IDC_EDT_ACT_POSY, dActPos[1]);

		SetDlgItemDouble(IDC_EDT_CMD_POSZ, dCmdPos[2]);
		SetDlgItemDouble(IDC_EDT_CMD_POSU, dCmdPos[3]);

		SetDlgItemDouble(IDC_EDT_ACT_POSZ, dActPos[2]);
		SetDlgItemDouble(IDC_EDT_ACT_POSU, dActPos[3]);*/

		SetDlgItemDouble(IDC_EDT_CMD_POSX, dCmdPos[0] / 200);
		SetDlgItemDouble(IDC_EDT_CMD_POSY, dCmdPos[1] / 200);

		SetDlgItemDouble(IDC_EDT_ACT_POSX, dActPos[0]);
		SetDlgItemDouble(IDC_EDT_ACT_POSY, dActPos[1]);

		SetDlgItemDouble(IDC_EDT_CMD_POSZ, dCmdPos[2] / 200);
		SetDlgItemDouble(IDC_EDT_CMD_POSU, dCmdPos[3] / 200);

		SetDlgItemDouble(IDC_EDT_ACT_POSZ, dActPos[2]);
		SetDlgItemDouble(IDC_EDT_ACT_POSU, dActPos[3]);

		AxmSignalReadInput(m_lAxis, &wReadInput);
		AxmSignalReadOutput(m_lAxis, &wReadOuput);
		AxmStatusReadMechanical(m_lAxis, &wMechanicalStatus);

		bUnivInput.bByte = (BYTE)wReadInput;
		bUnivOutput.bByte = (BYTE)wReadOuput;
		bMechanic.wWord = (WORD)wMechanicalStatus;

		// General output
		/*m_ledOut0.SetStatus( bUnivOutput.bit.b0 );
		m_ledOut1.SetStatus( bUnivOutput.bit.b1 );
		m_ledOut2.SetStatus( bUnivOutput.bit.b2 );
		m_ledOut3.SetStatus( bUnivOutput.bit.b3 );
		m_ledOut4.SetStatus( bUnivOutput.bit.b4 );*/
		//		m_ledOut5.SetStatus( bUnivOutput.bit.b5 );

		AxmHomeReadSignal(m_lAxis, &wReadHome);
		m_ledHome.SetStatus(wReadHome);				// Starting point level condition		

		// General input
		/*m_ledIn0.SetStatus( wReadHome );
		m_ledIn1.SetStatus( bUnivInput.bit.b1 );
		m_ledIn2.SetStatus( bUnivInput.bit.b2 );
		m_ledIn3.SetStatus( bUnivInput.bit.b3 );
		m_ledIn4.SetStatus( bUnivInput.bit.b4 );*/
		//		m_ledIn5.SetStatus( bUnivInput.bit.b5 );

				// Hardware signal






				//m_ledAlarm.SetStatus(bMechanic.wbit.b0);
				//m_ledInp.SetStatus(bMechanic.wbit.b5);	
				//m_ledEmg.SetStatus(bMechanic.wbit.b6);	
		if (spindle == true)
		{
			m_ledZphase.SetStatus(bMechanic.wbit.b8);
		}
		else
		{
			m_ledZphase.SetStatus(bMechanic.wbit.b0);
		}
		//m_ledExpp.SetStatus(bMechanic.wbit.b11);
		//m_ledExmp.SetStatus(bMechanic.wbit.b12);

		AxmStatusReadInMotion(AXIS_EVN(m_lAxis), &wBusyStatus);
		//m_ledBusyX.SetStatus(wBusyStatus);			

		AxmStatusReadInMotion(AXIS_ODD(m_lAxis), &wBusyStatus);
		AxmStatusReadInMotion(0, &stt0);
		AxmStatusReadInMotion(1, &stt1);
		AxmStatusReadInMotion(2, &stt2);
		AxmStatusReadInMotion(4, &stt3);
		AxmStatusReadInMotion(5, &stt4);
		if ((stt0 == 0) && (stt1 == 0) && (stt2 == 0) && (stt3 == 0) && (stt4 == 0) && (stop_code == true))
		{
			CCAMC_QIDlg::OnBnClickedBtnSpl();
			stop_code = false;
		}

		//m_ledBusyY.SetStatus(wBusyStatus);			
		AxmContiReadFree(COORD_NO, &wReadInterpolationQueueFree);
		// A function which checks running of serial interpolation
		AxmContiIsMotion(COORD_NO, &wIsContMotion);
		// A function which reads current index value in interpolation queue
		AxmContiGetNodeNum(COORD_NO, &lNodeNum1);
		AxmContiGetTotalNodeNum(COORD_NO, &lTotalNodeNum1);

		strData.Format("%ld", lTotalNodeNum1);
		//SetDlgItemText(IDC_STC_TOTAL_NUM, strData);

		strData.Format("%ld", lNodeNum1);
		//SetDlgItemText(IDC_STC_CONTI_NUM, strData);

		strData.Format("%ld", wIsContMotion);
		//SetDlgItemText(IDC_STC_IN_MOTION, strData);

		strData.Format("%X", wReadInterpolationQueueFree);
		//SetDlgItemText(IDC_STC_Q_FREE, strData);

		strData.Format("%4d", g_nIntCnt);
		//SetDlgItemText(IDC_STC_INT_COUNT, strData);
	}
	break;

	// Display speed of each axis by graph
	case TM_GRAPH:
	{
		// Coordinate graph of X, Y axis
		double dX1 = 0.0, dY1 = 0.0;
		double dCurVelX[2] = { 0.0 }, dCurVelY[2] = { 0.0 };

		/*AxmStatusGetCmdPos(AXIS_EVN(m_lAxis), &dX1);
		AxmStatusGetCmdPos(AXIS_ODD(m_lAxis), &dY1);*/
		AxmStatusGetCmdPos(AXIS_N04(m_lAxis, 0), &dX1);
		AxmStatusGetCmdPos(AXIS_N04(m_lAxis, 1), &dY1);

		AxmStatusReadVel(AXIS_N04(m_lAxis, 0), &dCurVelX[0]);
		AxmStatusReadVel(AXIS_N04(m_lAxis, 1), &dCurVelX[1]);
		AxmStatusReadVel(AXIS_N04(m_lAxis, 2), &dCurVelY[0]);
		AxmStatusReadVel(AXIS_N04(m_lAxis, 3), &dCurVelY[1]);

		SetDlgItemDouble(IDC_EDT_CMD_VELX, dCurVelX[0]);
		SetDlgItemDouble(IDC_EDT_CMD_VELY, dCurVelX[1]);
		SetDlgItemDouble(IDC_EDT_CMD_VELZ, dCurVelY[0]);
		SetDlgItemDouble(IDC_EDT_CMD_VELU, dCurVelY[1]);

		m_XYGraph.AppendPoint(dX1, dY1);

		// Speed profile of X, Y axis
		if (dCurVelX[0] > 0 || dCurVelX[1] > 0)	m_GraphX.AppendPoints(dCurVelX);
		if (dCurVelY[0] > 0 || dCurVelY[1] > 0)	m_GraphY.AppendPoints(dCurVelY);
		if (check_run == true)
		{
			CString status_axm;
			status_axm.Format(_T("%lu"), axmline);
			m_lstLog2.AddString(status_axm);
		}
		
	}
	break;
	case TM_Internet:
	{
		AxmStatusReadMechanical(m_lAxis, &wMechanicalStatus);
		bMechanic.wWord = (WORD)wMechanicalStatus;
		if (internet_connect == true)
		{
			m_ledNelm.SetStatus(bMechanic.wbit.b8);
			dem2 = 0;
			if (dem1 == 0)
			{
				m_lstLog.AddString("Connected to Internet.");
				dem1++;
			}

		}
		else
		{
			m_ledNelm.SetStatus(bMechanic.wbit.b0);
			if (dem2 == 0)
			{
				m_lstLog.AddString("Error!!! Not connecting to Internet.");
				dem2++;
			}

			dem1 = 0;
		}
	}
	case TM_IOT:
	{
			long	lAxisNo;
			long	lAxis[1];
			double	dMVel[1], dMAcc[1], dMDec[1];

			double	dVelocity = fabs(GetDlgItemDouble(IDC_EDT_VELOCITY));
			double	dAccel = fabs(GetDlgItemDouble(IDC_EDT_ACCEL));
			double	dDecel = fabs(GetDlgItemDouble(IDC_EDT_DECEL));

			dMAcc[0] = dAccel;
			dMDec[0] = dDecel;
			AxmStatusReadMechanical(m_lAxis, &wMechanicalStatus);
			bMechanic.wWord = (WORD)wMechanicalStatus;
			//m_lstLog2.AddString(.c_str());
			if (rece1 == true)
			{
				/*m_lstLog2.ResetContent();
				m_lstLog2.AddString(mess_data.c_str());*/
				if (mess_data == "X+")
				{
					lAxisNo = AXIS_N04(m_lAxis, 0);
					lAxis[0] = AXIS_N04(m_lAxis, 0);
					dMVel[0] = dVelocity;
					m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
					AxmMoveStartMultiVel(1, lAxis, dMVel, dMAcc, dMDec);
				}
				if (mess_data == "X-")
				{
					lAxisNo = AXIS_N04(m_lAxis, 0);
					lAxis[0] = AXIS_N04(m_lAxis, 0);
					dMVel[0] = -dVelocity;
					m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
					AxmMoveStartMultiVel(1, lAxis, dMVel, dMAcc, dMDec);
				}
				if (mess_data == "Y+")
				{
					lAxisNo = AXIS_N04(m_lAxis, 1);
					lAxis[0] = AXIS_N04(m_lAxis, 1);
					dMVel[0] = dVelocity;
					m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
					AxmMoveStartMultiVel(1, lAxis, dMVel, dMAcc, dMDec);
				}
				if (mess_data == "Y-")
				{
					lAxisNo = AXIS_N04(m_lAxis, 1);
					lAxis[0] = AXIS_N04(m_lAxis, 1);
					dMVel[0] = -dVelocity;
					m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
					AxmMoveStartMultiVel(1, lAxis, dMVel, dMAcc, dMDec);
				}
				if (mess_data == "Z+")
				{
					lAxisNo = AXIS_N04(m_lAxis, 2);
					lAxis[0] = AXIS_N04(m_lAxis, 2);
					dMVel[0] = dVelocity;
					m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
					AxmMoveStartMultiVel(1, lAxis, dMVel, dMAcc, dMDec);
				}
				if (mess_data == "Z-")
				{
					lAxisNo = AXIS_N04(m_lAxis, 2);
					lAxis[0] = AXIS_N04(m_lAxis, 2);
					dMVel[0] = -dVelocity;
					m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
					AxmMoveStartMultiVel(1, lAxis, dMVel, dMAcc, dMDec);
				}
				if (mess_data == "A+")
				{
					lAxisNo = 4;
					lAxis[0] = 4;
					dMVel[0] = dVelocity;
					m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
					AxmMoveStartMultiVel(1, lAxis, dMVel, dMAcc, dMDec);
				}
				if (mess_data == "A-")
				{
					lAxisNo = 4;
					lAxis[0] = 4;
					dMVel[0] = -dVelocity;
					m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
					AxmMoveStartMultiVel(1, lAxis, dMVel, dMAcc, dMDec);
				}
				/*if (mess_data == "B+")
				{
					lAxisNo = AXIS_N04(m_lAxis, 0);
					lAxis[0] = AXIS_N04(m_lAxis, 0);
					dMVel[0] = dVelocity;
					m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
					AxmMoveStartMultiVel(1, lAxis, dMVel, dMAcc, dMDec);
				}
				if (mess_data == "B-")
				{
					lAxisNo = AXIS_N04(m_lAxis, 0);
					lAxis[0] = AXIS_N04(m_lAxis, 0);
					dMVel[0] = dVelocity;
					m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
					AxmMoveStartMultiVel(1, lAxis, dMVel, dMAcc, dMDec);
				}*/
				if (mess_data == "STOPX")
				{
					lAxisNo = AXIS_N04(m_lAxis, 0);
					lAxis[0] = AXIS_N04(m_lAxis, 0);
					dMVel[0] = dVelocity;
					AxmMoveSStop(lAxisNo);
				}
				if (mess_data == "STOPY")
				{
					lAxisNo = AXIS_N04(m_lAxis, 1);
					lAxis[0] = AXIS_N04(m_lAxis, 1);
					dMVel[0] = dVelocity;
					AxmMoveSStop(lAxisNo);
				}
				if (mess_data == "STOPZ")
				{
					lAxisNo = AXIS_N04(m_lAxis, 2);
					lAxis[0] = AXIS_N04(m_lAxis, 2);
					dMVel[0] = dVelocity;
					AxmMoveSStop(lAxisNo);
				}
				if (mess_data == "STOPA")
				{
					lAxisNo = 4;
					lAxis[0] = 4;
					dMVel[0] = dVelocity;
					AxmMoveSStop(lAxisNo);
				}
				if (mess_data == "STOPB")
				{

				}
				if (mess_data == "START" && mess_data_pas != mess_data)
				{
					autostartgcode();
				}
				if (mess_data == "SET HOME" && mess_data_pas != mess_data)
				{
					OnBnClickedBtnSetHome();
				}
			}
			if ((connect_iot == true) && (rece == true))
			{
			/*	m_lstLog.ResetContent();
				m_lstLog.AddString(mess_pas.c_str());*/
		        m_lstLog2.AddString(mess.c_str());
				if (mess == "CONNECT")
				{
					if (disconnect == false)
					{
						if (str_time[49] == str_time[25])
						{
							m_lstLog.AddString(">>Server is lost connection. Please check again!!!");
							m_lstLog.AddString(">>Connecting...");
							disconnect = true;
						}
						if (mess_pas != mess)
						{
							m_lstLog.AddString(">>Server 172.25.192.1 connect");
							disconnect = false;
							mess_pas = mess;
						}
						m_ledPelm.SetStatus(bMechanic.wbit.b8);
					}
					else
					{
						m_ledPelm.SetStatus(bMechanic.wbit.b0);
						if (mess_time_pas != mess_time)
						{
							disconnect = false;
							mess_pas = "";
							str_time[49] = "";
						}
					}
				}
				if (mess == "DISCONNECT")
				{
					m_ledPelm.SetStatus(bMechanic.wbit.b0);
					if (mess_pas != mess)
					{
						m_lstLog.AddString(">>Server 172.25.192.1 is disconnect");
						m_lstLog.AddString(">>Connecting...");
						mess_pas = mess;
						str_time[49] = "";
					}
				}
				
				temp++;
				if (temp >=50) temp = 1;
				rece = false;
			}
		}
			break;

		// Check completion condition of Home searching 
		/*case TM_HOME_FUN1:
			AxmHomeGetResult(AXIS_N04(m_lAxis, 0), &wHomeResult0);
			if(wHomeResult0 != HOME_SEARCHING)
			{
				KillTimer(TM_HOME_FUN1);
				if(wHomeResult0 == HOME_SUCCESS)	MessageBox("Home Search 1 Success", "OK", MB_OK|MB_ICONINFORMATION);
				else
				{
					strData.Format("Home Search 1 Fail[0x%x]", wHomeResult0);
					MessageBox(strData, "OK", MB_OK|MB_ICONINFORMATION);
				}
			}
			break;

		case TM_HOME_FUN2:
			AxmHomeGetResult(AXIS_N04(m_lAxis, 1), &wHomeResult1);
			if(wHomeResult1 != HOME_SEARCHING)
			{
				KillTimer(TM_HOME_FUN2);
				if(wHomeResult1 == HOME_SUCCESS)	MessageBox("Home Search 2 Success", "OK", MB_OK|MB_ICONINFORMATION);
				else
				{
					strData.Format("Home Search 2 Fail[0x%x]", wHomeResult1);
					MessageBox(strData, "OK", MB_OK|MB_ICONINFORMATION);
				}
			}
			break;

		case TM_HOME_FUN3:
			AxmHomeGetResult(AXIS_N04(m_lAxis, 2), &wHomeResult2);
			if(wHomeResult2 != HOME_SEARCHING)
			{
				KillTimer(TM_HOME_FUN3);
				if(wHomeResult2 == HOME_SUCCESS)	MessageBox("Home Search 3 Success", "OK", MB_OK|MB_ICONINFORMATION);
				else
				{
					strData.Format("Home Search 3 Fail[0x%x]", wHomeResult2);
					MessageBox(strData, "OK", MB_OK|MB_ICONINFORMATION);
				}
			}
			break;

		case TM_HOME_FUN4:
			AxmHomeGetResult(AXIS_N04(m_lAxis, 3), &wHomeResult3);
			if(wHomeResult3 != HOME_SEARCHING)
			{
				KillTimer(TM_HOME_FUN4);
				if(wHomeResult3 == HOME_SUCCESS)	MessageBox("Home Search 4 Success", "OK", MB_OK|MB_ICONINFORMATION);
				else
				{
					strData.Format("Home Search 4 Fail[0x%x]", wHomeResult3);
					MessageBox(strData, "OK", MB_OK|MB_ICONINFORMATION);
				}
			}
			break;*/
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CCAMC_QIDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	if(m_pStatus != NULL)
	{
		m_pStatus->DestroyWindow();
		delete m_pStatus;
		m_pStatus = NULL;
	}

	if(m_pManualSet != NULL)
	{
		m_pManualSet->DestroyWindow();
		delete m_pManualSet;
		m_pManualSet = NULL;
	}

	if(m_pGL3DGraph != NULL){
		m_pGL3DGraph->DestroyWindow();
		delete m_pGL3DGraph;
		m_pGL3DGraph = NULL;
	}

	int i = 0;

	m_bTestActive[0] = m_bTestActive[1] = FALSE;
	m_bTestActive[2] = m_bTestActive[3] = FALSE;
	for(i = 0; i < m_lAxisCounts; i++)
	{				
		AxmMoveEStop(i);
		AxmSignalWriteOutputBit(i, 0, 0);
	}

	for(i = 0; i < 4; i++)
	{
		if(m_hTestThread[i] != NULL)
		{
			TerminateThread(m_hTestThread[i], 0);
			WaitForSingleObject(m_hTestThread[i],  WAIT_ABANDONED);
			CloseHandle(m_hTestThread[i]);
			m_hTestThread[i] = NULL;
		}
	}

    AxlClose();		
}

// It running continuously when press jog button and reduce speed and stop when finger off the button.
BOOL CCAMC_QIDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pNMHDR = (NMHDR*)lParam;

	long	lAxisNo;
	long	lAxis[2];
	double	dMVel[2], dMAcc[2], dMDec[2];

	double	dVelocity	= fabs(GetDlgItemDouble(IDC_EDT_VELOCITY));
	double	dAccel 		= fabs(GetDlgItemDouble(IDC_EDT_ACCEL));
	double	dDecel		= fabs(GetDlgItemDouble(IDC_EDT_DECEL));
	
	dMAcc[0] = dMAcc[1] = dAccel;
	dMDec[0] = dMDec[1] = dDecel;
	/*if (connect_sucess == true)
	{
		if (mess_data == "X+")
		{
			m_lstLog2.AddString(mess_data.c_str());
		}
	}*/
	switch(wParam)
	{
	case IDC_BTN_JOG_PX:
		lAxisNo		= AXIS_N04(m_lAxis, 0);
		lAxis[0]	= AXIS_N04(m_lAxis, 0);
		lAxis[1]	= AXIS_N04(m_lAxis, 1);
		dMVel[0]	= dVelocity;
		dMVel[1]	= dVelocity;
		break;

	case IDC_BTN_JOG_NX:
		lAxisNo		= AXIS_N04(m_lAxis, 0);
		lAxis[0]	= AXIS_N04(m_lAxis, 0);
		lAxis[1]	= AXIS_N04(m_lAxis, 1);
		dMVel[0]	= -dVelocity;
		dMVel[1]	= -dVelocity;
		break;

	case IDC_BTN_JOG_PY:
		lAxisNo		= AXIS_N04(m_lAxis, 1);
		lAxis[0]	= AXIS_N04(m_lAxis, 0);
		lAxis[1]	= AXIS_N04(m_lAxis, 1);
		dMVel[0]	= dVelocity;
		dMVel[1]	= dVelocity;
		break;

	case IDC_BTN_JOG_NY:
		lAxisNo		= AXIS_N04(m_lAxis, 1);
		lAxis[0]	= AXIS_N04(m_lAxis, 0);
		lAxis[1]	= AXIS_N04(m_lAxis, 1);
		dMVel[0]	= -dVelocity;
		dMVel[1]	= -dVelocity;
		break;

	case IDC_BTN_JOG_PZ:
		lAxisNo		= AXIS_N04(m_lAxis, 2);
		lAxis[0]	= AXIS_N04(m_lAxis, 2);
		lAxis[1]	= AXIS_N04(m_lAxis, 3);
		dMVel[0]	= dVelocity;
		dMVel[1]	= dVelocity;
		break;

	case IDC_BTN_JOG_NZ:
		lAxisNo		= AXIS_N04(m_lAxis, 2);
		lAxis[0]	= AXIS_N04(m_lAxis, 2);
		lAxis[1]	= AXIS_N04(m_lAxis, 3);
		dMVel[0]	= -dVelocity;
		dMVel[1]	= -dVelocity;
		break;

	case IDC_BTN_JOG_PU:
		lAxisNo		= AXIS_N04(m_lAxis, 3);
		lAxis[0]	= AXIS_N04(m_lAxis, 2);
		lAxis[1]	= AXIS_N04(m_lAxis, 3);
		dMVel[0]	= dVelocity;
		dMVel[1]	= dVelocity;
		break;

	case IDC_BTN_JOG_NU:
		lAxisNo		= AXIS_N04(m_lAxis, 3);
		lAxis[0]	= AXIS_N04(m_lAxis, 2);
		lAxis[1]	= AXIS_N04(m_lAxis, 3);
		dMVel[0]	= -dVelocity;
		dMVel[1]	= -dVelocity;
		break;
	}

	if(wParam == IDC_BTN_JOG_PX || wParam == IDC_BTN_JOG_NX || (wParam == IDC_BTN_JOG_PY || wParam == IDC_BTN_JOG_NY) ||
		wParam == IDC_BTN_JOG_PZ || wParam == IDC_BTN_JOG_NZ || (wParam == IDC_BTN_JOG_PU || wParam == IDC_BTN_JOG_NU))
	{
		if(pNMHDR->code == TCN_SELCHANGE)
		{
			// Re-setup of the maximum value in chart for displaying running speed of each axis on the chart.
			if(wParam == IDC_BTN_JOG_PX || wParam == IDC_BTN_JOG_NX || (wParam == IDC_BTN_JOG_PY || wParam == IDC_BTN_JOG_NY))
				m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
			else
				m_GraphY.SetRanges(0, dVelocity + (dVelocity * 0.2));

			if (m_chkXYsync.GetCheck())
			{
				if(m_chkAsym.GetCheck())	AxmMoveStartMultiVel(2, lAxis, dMVel, dMAcc, dMDec);
				else						AxmMoveStartMultiVel(2, lAxis, dMVel, dMAcc, dMAcc);
			}
			else
			{
				if(m_chkAsym.GetCheck())	AxmMoveVel(lAxisNo, dMVel[0], dAccel, dDecel);
				else						AxmMoveVel(lAxisNo, dMVel[0], dAccel, dAccel);
			}
		}
		else
		{
			AxmMoveSStop(lAxisNo);
		}
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

BOOL CCAMC_QIDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->hwnd){		
		if (pMsg->message == WM_KEYDOWN){
			// It protects to finish program when ESC, ENTER Key is pressed.
			if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN){				
				return TRUE;
			}
		}
	}	
	
	return CDialog::PreTranslateMessage(pMsg);
}

//void CCAMC_QIDlg::OnBtnHomeAll() 
//{
//	long    lHmDir		= m_cboHomeDir.GetCurSel();		// Setup a direction of Home searching.
//	long    lHmsig		= m_cboHomeSignal.GetCurSel();	// Setup Home sensor.
//	DWORD   dwZphas		= 0;							// Setup whether Z phase is searching or not.
//	double  dHClrTim	= 1000.0;						// Delay time of Position Clear after searching Home sensor.
//	double  dHOffset	= 0.0;							// Setup Offset movement value after searching Home sensor.
//	DWORD	dwResult	= 0;
//
//	if (lHmsig > 1)
//		lHmsig += 2;
//
//	SetGraphRange(AXIS_N04(m_lAxis, 0), 100);
//	SetGraphRange(AXIS_N04(m_lAxis, 2), 100);
//
//	// Speed of starting point searching by each step must be changed to fit to the device.
//	dwResult = AxmHomeSetVel(AXIS_N04(m_lAxis, 0), 100, 50, 5, 1, 400, 100);
//	if (dwResult == AXT_RT_SUCCESS)
//	{
//		AxmHomeSetMethod(AXIS_N04(m_lAxis, 0), lHmDir, lHmsig, dwZphas, dHClrTim, dHOffset);
//		AxmHomeSetStart(AXIS_N04(m_lAxis, 0));
//		SetTimer(TM_HOME_FUN1, 100, NULL);
//	}
//
//	dwResult = AxmHomeSetVel(AXIS_N04(m_lAxis, 1), 100, 50, 5, 1, 400, 100);
//	if (dwResult == AXT_RT_SUCCESS)
//	{
//		AxmHomeSetMethod(AXIS_N04(m_lAxis, 1), lHmDir, lHmsig, dwZphas, dHClrTim, dHOffset);
//		AxmHomeSetStart(AXIS_N04(m_lAxis, 1));
//		SetTimer(TM_HOME_FUN2, 100, NULL);
//	}
//	
//	dwResult = AxmHomeSetVel(AXIS_N04(m_lAxis, 2), 100, 50, 5, 1, 400, 100);
//	if (dwResult == AXT_RT_SUCCESS)
//	{
//		AxmHomeSetMethod(AXIS_N04(m_lAxis, 2), lHmDir, lHmsig, dwZphas, dHClrTim, dHOffset);
//		AxmHomeSetStart(AXIS_N04(m_lAxis, 2));
//		SetTimer(TM_HOME_FUN3, 100, NULL);
//	}
//
//	dwResult = AxmHomeSetVel(AXIS_N04(m_lAxis, 3), 100, 50, 5, 1, 400, 100);
//	if (dwResult == AXT_RT_SUCCESS)
//	{
//		AxmHomeSetMethod(AXIS_N04(m_lAxis, 3), lHmDir, lHmsig, dwZphas, dHClrTim, dHOffset);
//		AxmHomeSetStart(AXIS_N04(m_lAxis, 3));
//		SetTimer(TM_HOME_FUN4, 100, NULL);
//	}
//}

// Home searching is running by the direction of CCW
//void CCAMC_QIDlg::OnBtnHomeSingle() 
//{	
//	DWORD   dwZphas		= 0;				// Setup whether Z phase is searching or not.
//	double  dHClrTim	= 1000.0;			// Delay time of Position Clear after searching Home sensor.
//	double  dHOffset	= 0.0;				// Setup Offset movement value after searching Home sensor.
//
//	double	dVelFirst	= GetDlgItemDouble(IDC_EDT_HOME_VEL_FIRST);
//	double	dVelSecond	= GetDlgItemDouble(IDC_EDT_HOME_VEL_SECOND);
//	double	dVelThird	= GetDlgItemDouble(IDC_EDT_HOME_VEL_THIRD);
//	double	dVelLast	= GetDlgItemDouble(IDC_EDT_HOME_VEL_LAST);
//
//	long    lHmsig		= m_cboHomeSignal.GetCurSel();		// Setup Home sensor.
//	long    lHmDir		= m_cboHomeDir.GetCurSel();			// Setup a direction of Home searching.
//
//	if (lHmsig > 1)
//		lHmsig += 2;
//	
//	SetGraphRange(m_lAxis, dVelFirst);
//
//	if(m_chkGantrySlave.GetCheck())
//	{
//		AxmHomeSetVel(AXIS_EVN(m_lAxis), dVelFirst, dVelSecond, dVelThird, dVelLast, dVelFirst * 4, dVelSecond * 10);
//		AxmHomeSetVel(AXIS_ODD(m_lAxis), dVelFirst, dVelSecond, dVelThird, dVelLast, dVelFirst * 4, dVelSecond * 10);
//
//		AxmHomeSetMethod(AXIS_EVN(m_lAxis), lHmDir, lHmsig, dwZphas, dHClrTim, dHOffset);
//		AxmHomeSetMethod(AXIS_ODD(m_lAxis), lHmDir, lHmsig, dwZphas, dHClrTim, dHOffset);
//
//		AxmHomeSetStart(AXIS_EVN(m_lAxis));
//		SetTimer(TM_HOME_FUN1 + AXIS_EVN(m_lAxis), 100, NULL);
//	}
//	else
//	{
//		AxmHomeSetVel(m_lAxis, dVelFirst, dVelSecond, dVelThird, dVelLast, dVelFirst * 4, dVelSecond * 10);
//
//		AxmHomeSetMethod(m_lAxis, lHmDir, lHmsig, dwZphas, dHClrTim, dHOffset);
//		AxmHomeSetStart(m_lAxis);
//		SetTimer(TM_HOME_FUN1 + AXIS_QUR(m_lAxis), 100, NULL);
//	}
//}

// Running of movement volume or speed over drive
//void CCAMC_QIDlg::OnBtnVelOverride() 
//{
//	double dPosition = GetDlgItemDouble(IDC_EDT_POSITION);
//	double dVelocity = fabs(GetDlgItemDouble(IDC_EDT_VELOCITY));
//	double dAccel	 = fabs(GetDlgItemDouble(IDC_EDT_ACCEL));
//	double dDecel	 = fabs(GetDlgItemDouble(IDC_EDT_DECEL));
//
//	SetGraphRange(m_lAxis, dVelocity*2);
//	AxmOverrideVelAtPos(m_lAxis, dPosition, dVelocity, dAccel, dAccel, dPosition/4,dVelocity*2, COMMAND);
//}

// Initialize Control
BOOL CCAMC_QIDlg::InitControl()
{	
	// Setup font
	m_strFont1.LoadString(IDS_STRING1001);

	// Initialize edit box
	m_edtMoveUnit.SubclassDlgItem(IDC_EDT_MOVEUNIT, this);
	m_edtMoveUnit.bkColor( BLACK );
	m_edtMoveUnit.textColor( YELLOW );
	m_edtMoveUnit.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtMoveUnit.SetWindowText("1");

	m_edtUnit.SubclassDlgItem(IDC_EDT_UNIT, this);
	m_edtUnit.bkColor( BLACK );
	m_edtUnit.textColor( YELLOW );
	m_edtUnit.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtUnit.SetWindowText("1");

	m_edtPulse.SubclassDlgItem(IDC_EDT_PULSE, this);
	m_edtPulse.bkColor( BLACK );
	m_edtPulse.textColor( YELLOW );
	m_edtPulse.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtPulse.SetWindowText("1");

	m_edtStartSpeed.SubclassDlgItem(IDC_EDT_STARTSPEED, this);
	m_edtStartSpeed.bkColor( BLACK );
	m_edtStartSpeed.textColor( YELLOW );
	m_edtStartSpeed.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtStartSpeed.SetWindowText("10");
	
	m_edtXend.SubclassDlgItem(IDC_EDT_XCEN, this);
	m_edtXend.bkColor( BLACK );
	m_edtXend.textColor( YELLOW );
	m_edtXend.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtXend.SetWindowText("0");

	/*m_edtYend.SubclassDlgItem(IDC_EDT_YCEN, this);
	m_edtYend.bkColor( BLACK );
	m_edtYend.textColor( YELLOW );
	m_edtYend.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtYend.SetWindowText("0");

	m_edtAngle.SubclassDlgItem(IDC_EDT_ANGLE, this);
	m_edtAngle.bkColor( BLACK );
	m_edtAngle.textColor( YELLOW );
	m_edtAngle.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtAngle.SetWindowText("0");*/

	m_edtCmdPos[0].SubclassDlgItem(IDC_EDT_CMD_POSX, this);
	m_edtCmdPos[0].bkColor( BLACK );
	m_edtCmdPos[0].textColor( YELLOW );
	m_edtCmdPos[0].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtCmdPos[0].SetWindowText("0");

	m_edtActPos[0].SubclassDlgItem(IDC_EDT_ACT_POSX, this);
	m_edtActPos[0].bkColor( BLACK );
	m_edtActPos[0].textColor( YELLOW );
	m_edtActPos[0].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtActPos[0].SetWindowText("0");

	m_edtCmdVel[0].SubclassDlgItem(IDC_EDT_CMD_VELX, this);
	m_edtCmdVel[0].bkColor( BLACK );
	m_edtCmdVel[0].textColor( YELLOW );
	m_edtCmdVel[0].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtCmdVel[0].SetWindowText("0");

	m_edtCmdPos[1].SubclassDlgItem(IDC_EDT_CMD_POSY, this);
	m_edtCmdPos[1].bkColor( BLACK );
	m_edtCmdPos[1].textColor( YELLOW );
	m_edtCmdPos[1].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtCmdPos[1].SetWindowText("0");

	m_edtActPos[1].SubclassDlgItem(IDC_EDT_ACT_POSY, this);
	m_edtActPos[1].bkColor( BLACK );
	m_edtActPos[1].textColor( YELLOW );
	m_edtActPos[1].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtActPos[1].SetWindowText("0");

	m_edtCmdVel[1].SubclassDlgItem(IDC_EDT_CMD_VELY, this);
	m_edtCmdVel[1].bkColor( BLACK );
	m_edtCmdVel[1].textColor( YELLOW );
	m_edtCmdVel[1].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtCmdVel[1].SetWindowText("0");

	m_edtCmdPos[2].SubclassDlgItem(IDC_EDT_CMD_POSU, this);
	m_edtCmdPos[2].bkColor( BLACK );
	m_edtCmdPos[2].textColor( YELLOW );
	m_edtCmdPos[2].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtCmdPos[2].SetWindowText("0");

	m_edtActPos[2].SubclassDlgItem(IDC_EDT_ACT_POSU, this);
	m_edtActPos[2].bkColor( BLACK );
	m_edtActPos[2].textColor( YELLOW );
	m_edtActPos[2].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtActPos[2].SetWindowText("0");

	m_edtCmdVel[2].SubclassDlgItem(IDC_EDT_CMD_VELU, this);
	m_edtCmdVel[2].bkColor( BLACK );
	m_edtCmdVel[2].textColor( YELLOW );
	m_edtCmdVel[2].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtCmdVel[2].SetWindowText("0");

	m_edtCmdPos[3].SubclassDlgItem(IDC_EDT_CMD_POSZ, this);
	m_edtCmdPos[3].bkColor( BLACK );
	m_edtCmdPos[3].textColor( YELLOW );
	m_edtCmdPos[3].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtCmdPos[3].SetWindowText("0");

	m_edtActPos[3].SubclassDlgItem(IDC_EDT_ACT_POSZ, this);
	m_edtActPos[3].bkColor( BLACK );
	m_edtActPos[3].textColor( YELLOW );
	m_edtActPos[3].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtActPos[3].SetWindowText("0");

	m_edtCmdVel[3].SubclassDlgItem(IDC_EDT_CMD_VELZ, this);
	m_edtCmdVel[3].bkColor( BLACK );
	m_edtCmdVel[3].textColor( YELLOW );
	m_edtCmdVel[3].setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtCmdVel[3].SetWindowText("0");

	m_edtPosition.SubclassDlgItem(IDC_EDT_POSITION, this);
	m_edtPosition.bkColor( BLACK );
	m_edtPosition.textColor( YELLOW );
	m_edtPosition.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtPosition.SetWindowText("0");

	m_edtVelocity.SubclassDlgItem(IDC_EDT_VELOCITY, this);
	m_edtVelocity.bkColor( BLACK );
	m_edtVelocity.textColor( YELLOW );
	m_edtVelocity.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtVelocity.SetWindowText("5000");

	m_edtAccel.SubclassDlgItem(IDC_EDT_ACCEL, this);
	m_edtAccel.bkColor( BLACK );
	m_edtAccel.textColor( YELLOW );
	m_edtAccel.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtAccel.SetWindowText("0");

	m_edtDecel.SubclassDlgItem(IDC_EDT_DECEL, this);
	m_edtDecel.bkColor( BLACK );
	m_edtDecel.textColor( YELLOW );
	m_edtDecel.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, _T("±Ã¼­"));
	m_edtDecel.SetWindowText("0.000");


	/*m_edtHomeVelFirst.SubclassDlgItem(IDC_EDT_HOME_VEL_FIRST, this);
	m_edtHomeVelFirst.bkColor( BLACK );
	m_edtHomeVelFirst.textColor( YELLOW );
	m_edtHomeVelFirst.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtHomeVelFirst.SetWindowText("0");*/

	/*m_edtHomeVelAfter.SubclassDlgItem(IDC_EDT_HOME_VEL_SECOND, this);
	m_edtHomeVelAfter.bkColor( BLACK );
	m_edtHomeVelAfter.textColor( YELLOW );
	m_edtHomeVelAfter.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, m_strFont1);
	m_edtHomeVelAfter.SetWindowText("0");*/

	/*m_edtHomeVelAgain.SubclassDlgItem(IDC_EDT_HOME_VEL_THIRD, this);
	m_edtHomeVelAgain.bkColor( BLACK );
	m_edtHomeVelAgain.textColor( YELLOW );
	m_edtHomeVelAgain.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, _T("±Ã¼­"));
	m_edtHomeVelAgain.SetWindowText("0.000");

	m_edtHomeVelLast.SubclassDlgItem(IDC_EDT_HOME_VEL_LAST, this);
	m_edtHomeVelLast.bkColor( BLACK );
	m_edtHomeVelLast.textColor( YELLOW );
	m_edtHomeVelLast.setFont( 14, FW_ULTRABOLD, DEFAULT_PITCH | FF_DONTCARE, _T("±Ã¼­"));
	m_edtHomeVelLast.SetWindowText("0.000");*/

	// Initialize speed graph
	// Speed graph of X axis
	CRect rect;    
	GetDlgItem(IDC_GRAPHX)->GetWindowRect(rect);
	ScreenToClient(rect);

	m_GraphX.Create(WS_VISIBLE|WS_CHILD, rect, this);
	m_GraphX.SetRanges(0, 400);

	m_GraphX.SetBackgroundColor(RGB(0,0,64));
	m_GraphX.SetGridColor(RGB(192,192,255));
	m_GraphX.SetPlotColor(RGB(255,0,0), 0);
	m_GraphX.SetPlotColor(RGB(0,255,0), 1);
	m_GraphX.SetXUnits("Time(sampling: 100 msec)", "0", "100000") ;
	m_GraphX.SetYUnits("unit/s", "0" ) ;

    // Speed graph of Y axis
	GetDlgItem(IDC_GRAPHY)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_GraphY.Create(WS_VISIBLE|WS_CHILD, rect, this);
	m_GraphY.SetRanges(0,400);

	m_GraphY.SetBackgroundColor(RGB(0,0,64));
	m_GraphY.SetGridColor(RGB(192,192,255));
	m_GraphY.SetPlotColor(RGB(255,255,0), 0);
	m_GraphY.SetPlotColor(RGB(0,255,255), 1);
	m_GraphY.SetXUnits("Time(sampling: 100 msec)", "0", "100000") ;
	m_GraphY.SetYUnits("unit/s", "0" ) ;

    // Location graph of X-Y
	GetDlgItem(IDC_XYPLOT)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_XYGraph.Create(WS_VISIBLE | WS_CHILD, rect, this);
	m_XYGraph.SetRange(-2500, 2500, -2500, 2500, 1);
	m_XYGraph.SetYUnits("Y AXIS");
	m_XYGraph.SetXUnits("X AXIS");
	m_XYGraph.SetBackgroundColor(RGB(0, 0, 64));
	m_XYGraph.SetGridColor(RGB(192, 192, 255));
	m_XYGraph.SetPlotColor(RGB(0, 255, 0));	
	m_strFont2.LoadString(IDS_STRING1002);

	// Initialize font
	m_sFont.CreateFont(-10,0,0,0,FW_SEMIBOLD, FALSE, FALSE, 0, 0, 0, 0, 0, 0, m_strFont2);
	m_sFont1.CreateFont(-12,0,0,0,FW_NORMAL, FALSE, FALSE, 0, 0, 0, 0, 0, 0, "Arial Narrow");
	m_sFont2.CreateFont(-14,0,0,0,FW_NORMAL, FALSE, FALSE, 0, 0, 0, 0, 0, 0, m_strFont2);
	
	// Initialize combo box
	m_cboAxisSet.SetCurSel(0);
	m_cboPulseOutM.SetCurSel(0);
	m_cboEncInputM.SetCurSel(0);
	m_cboPulseOutM.SetFont(&m_sFont1, TRUE);
	m_cboEncInputM.SetFont(&m_sFont1, TRUE);

	//m_cboDetect.SetFont(&m_sFont1, TRUE);
	//m_cboDirection.SetFont(&m_sFont1, TRUE);
	//m_cboStopM.SetFont(&m_sFont1, TRUE);

	// Initialize icon button
	m_btnCountClr.SetIcon( IDI_CNTCLR, 14, 14 );
	m_btnCountClr.SetImagePos( CPoint ( 1, SXBUTTON_CENTER ) );
	m_btnCountClr.SetTextPos( CPoint ( 20, SXBUTTON_CENTER ) );
	m_btnCountClr.SetFont(&m_sFont);
	
	m_btnMove.SetIcon( IDI_MOVE, 19, 19 );
	m_btnMove.SetImagePos( CPoint ( 2, SXBUTTON_CENTER ) );
	m_btnMove.SetTextPos( CPoint ( 22, SXBUTTON_CENTER ) );
	m_btnMove.SetFont(&m_sFont2);

	m_btnRepeat.SetIcon( IDI_REPEAT, 19, 19 );
	m_btnRepeat.SetImagePos( CPoint ( 3, SXBUTTON_CENTER ) );
	m_btnRepeat.SetTextPos( CPoint ( 22, SXBUTTON_CENTER ) );
	m_btnRepeat.SetFont(&m_sFont2);
	
	/*m_btnStop.SetIcon( IDI_STOP, 19, 19 );
	m_btnStop.SetImagePos( CPoint ( 2, SXBUTTON_CENTER ) );
	m_btnStop.SetTextPos( CPoint ( 22, SXBUTTON_CENTER ) );
	m_btnStop.SetFont(&m_sFont2);*/

	m_btnEstop.SetIcon( IDI_EMG, 14, 14 );
	m_btnEstop.SetImagePos( CPoint ( 2, SXBUTTON_CENTER ) );
	m_btnEstop.SetTextPos( CPoint ( 10, SXBUTTON_CENTER ) );
	m_btnEstop.SetFont(&m_sFont);

	m_edtDecel.EnableWindow(FALSE);

	//m_ledBusyX.m_bSensor = UNIVERSAL_IO;
	//m_ledBusyY.m_bSensor = UNIVERSAL_IO;

	//m_cboDetect.SetCurSel(4);
	//m_cboDirection.SetCurSel(1);
	//m_cboStopM.SetCurSel(1);

	//m_cboHomeSignal.SetCurSel(2);
	//m_cboHomeDir.SetCurSel(0);

	/*SetDlgItemDouble( IDC_EDT_HOME_VEL_FIRST, 10000.0);
	SetDlgItemDouble( IDC_EDT_HOME_VEL_SECOND, 5000.0);
	SetDlgItemDouble( IDC_EDT_HOME_VEL_THIRD, 1000.0);
	SetDlgItemDouble( IDC_EDT_HOME_VEL_LAST, 100.0);
*/
	SetDlgItemDouble( IDC_EDT_XCEN, 100.0);
	SetDlgItemDouble(IDC_EDT_VELOCITY, 5000);
	SetDlgItemDouble(IDC_EDT_ACCEL, 30000);
	SetDlgItemDouble(IDC_EDT_DECEL, 30000);
	/*SetDlgItemDouble( IDC_EDT_YCEN, 200.0);
	SetDlgItemDouble( IDC_EDT_ANGLE, 360.0);*/
	//SetDlgItemDouble( IDC_EDT_GEAR_RATIO, 1.0);

	//SetDlgItemText(IDC_EDT_TRIG_START_POS, "1000");
	//SetDlgItemText(IDC_EDT_TRIG_CYCLE, "100");
	//SetDlgItemText(IDC_EDT_TRIG_PULSE_WIDTH, "1000");
	//SetDlgItemText(IDC_EDT_TRIG_END_POS, "5000");
	m_edtDecel.EnableWindow(FALSE);

	CString strData;	
	DWORD	dwModuleID;

	AxmInfoGetAxisCount(&m_lAxisCounts);

	// Initialize setup of axis
	for(int i = 0; i < m_lAxisCounts; i++)
	{
		AxmInfoGetAxis(i, NULL, NULL, &dwModuleID);
		switch(dwModuleID){
		case AXT_SMC_4V04:				strData.Format("%02ld-[4V04]", i);	break;
		case AXT_SMC_R1V04:				strData.Format("%02ld-[R1V04]", i);	break;
		case AXT_SMC_2V04:				strData.Format("%02ld-[2V04]", i);	break;
		case AXT_SMC_R1V04MLIIPM:		strData.Format("%02ld-[R1V04MLIIPM]", i);	break;
		case AXT_SMC_R1V04PM2Q:			strData.Format("%02ld-[R1V04PM2Q]", i);	break;
		case AXT_SMC_R1V04PM2QE:		strData.Format("%02ld-[R1V04PM2QE]", i);	break;
		case AXT_SMC_R1V04MLIIIPM:		strData.Format("%02ld-[R1V04MLIIIPM]", i);	break;
	    case AXT_SMC_R1V04MLIISV:		strData.Format("%02ld-[R1V04MLIISV]", i);	break;
		case AXT_SMC_R1V04A5:			strData.Format("%02ld-[R1V04A5]", i);	break;
		case AXT_SMC_R1V04A4:			strData.Format("%02ld-[R1V04A4]", i);	break;
		case AXT_SMC_R1V04SIIIHMIV:		strData.Format("%02ld-[R1V04SIIIHMIV]", i);	break;
		case AXT_SMC_R1V04SIIIHMIV_R:	strData.Format("%02ld-[R1V04SIIIHMIV_R]", i);	break;
		case AXT_SMC_R1V04MLIIISV:		strData.Format("%02ld-[R1V04MLIIISV]", i);	break;
		case AXT_SMC_R1V04MLIIISV_MD:	strData.Format("%02ld-[R1V04MLIIISV_MD]", i);	break;
		case AXT_SMC_R1V04MLIIIS7S:		strData.Format("%02ld-[R1V04MLIIIS7S]", i);	break;
		case AXT_SMC_R1V04MLIIIS7W:		strData.Format("%02ld-[R1V04MLIIIS7W]", i);	break;
		default:					strData.Format("%02ld-[Unknown]",i);
		}
		m_cboAxisSet.AddString(strData);
	}

	return 0;
}

// Initialize of combined Library and module
BOOL CCAMC_QIDlg::InitLibrary()
{
	// Initialize AXT board
	if ((AxlOpen(7) != AXT_RT_SUCCESS))
		AfxMessageBox("AxlOpen Fail...");
	return TRUE;
}

void CCAMC_QIDlg::SetTitleBar(long lAxis)
{
	CString strCaption;
	DWORD	dwModuleID;
	long	lAxtBoardNo = 0, lModulePos = 0;

	if(AXT_RT_SUCCESS == AxmInfoGetAxis(lAxis, &lAxtBoardNo, &lModulePos, &dwModuleID))
		strCaption.Format("Ajinextek Motion Board No[%02d], Module Pos[%02d], Module ID[0x%02X]", lAxtBoardNo, lModulePos, dwModuleID);
	else
		strCaption.Format("Ajinextek Motion Board is not detected");

	SetWindowText(strCaption);
}

BOOL CCAMC_QIDlg::SetGraphRange(long lAxis, double dVelocity)
{
	if(dVelocity <= 0)	return FALSE;

	// Re-setup of the maximum value in chart for displaying running speed of each axis on the chart.
	if(AXIS_QUR(lAxis) < 2)	m_GraphX.SetRanges(0, dVelocity + (dVelocity * 0.2));
	else					m_GraphY.SetRanges(0, dVelocity + (dVelocity * 0.2));

	return TRUE;
}

// Setup active level value of (+) End Limit.
//void CCAMC_QIDlg::OnChkPelmLevel() 
//{
//	DWORD   dwNegativeLevel, upStopMode, dwLevel;
//	AxmSignalGetLimit(m_lAxis, &upStopMode, NULL, &dwNegativeLevel);
//
//	if (!m_bA4NAxis)
//		AxmSignalSetLimit(m_lAxis, upStopMode, m_chkPelmLevel.GetCheck(), dwNegativeLevel);
//	else
//	{
//		if (m_chkPelmLevel.GetCheck() == false) dwLevel   = 2;
//        else									dwLevel   = 1;
//		AxmSignalSetLimit(m_lAxis, upStopMode, dwLevel, dwNegativeLevel);
//	}
//}

// Setup active level value of (-) End Limit.
//void CCAMC_QIDlg::OnChkNelmLevel() 
//{
//	DWORD   dwPositiveLevel, upStopMode, dwLevel;	
//	AxmSignalGetLimit(m_lAxis, &upStopMode, &dwPositiveLevel, NULL);
//	
//	if (!m_bA4NAxis)
//		AxmSignalSetLimit(m_lAxis, upStopMode, dwPositiveLevel, m_chkNelmLevel.GetCheck());
//	else
//	{
//		if (m_chkNelmLevel.GetCheck() == false) dwLevel   = 2;
//        else									dwLevel   = 1;
//		AxmSignalSetLimit(m_lAxis, upStopMode, dwPositiveLevel, dwLevel);
//	}
//}

// Setup active level value of Emg signal.
//void CCAMC_QIDlg::OnChkEmgLevel() 
//{
//	DWORD   dwLevel;	
//	
//	if (!m_bA4NAxis)
//		AxmSignalSetStop(m_lAxis, EMERGENCY_STOP, m_chkEmgLevel.GetCheck());
//	else
//	{
//		if (m_chkEmgLevel.GetCheck() == false)	dwLevel   = 2;
//        else									dwLevel   = 1;
//		AxmSignalSetStop(m_lAxis, EMERGENCY_STOP, dwLevel);
//	}
//}

// Setup active level value of in-position signal.  High if checked, Low if not checked.
//void CCAMC_QIDlg::OnChkInpLevel() 
//{
//	DWORD   dwLevel;	
//	
//	if (!m_bA4NAxis)
//		AxmSignalSetInpos(m_lAxis, m_chkInpLevel.GetCheck()); 
//	else
//	{
//		if (m_chkInpLevel.GetCheck() == false)	dwLevel   = 2;
//        else									dwLevel   = 1;
//		AxmSignalSetInpos(m_lAxis, dwLevel); 
//	}
//}

// Setup active level value of alarm signal.  High if checked, Low if not checked.
//void CCAMC_QIDlg::OnChkAlarmLevel() 
//{
//	DWORD   dwLevel;	
//	
//	if (!m_bA4NAxis)
//		AxmSignalSetServoAlarm(m_lAxis, m_chkAlarmLevel.GetCheck()); 
//	else
//	{
//		if (m_chkAlarmLevel.GetCheck() == false)	dwLevel   = 2;
//        else										dwLevel   = 1;
//		AxmSignalSetServoAlarm(m_lAxis, dwLevel); 
//	}
//}

//void CCAMC_QIDlg::OnChkHomeLevel() 
//{
//	if (!m_bA4NAxis)
//		AxmHomeSetSignalLevel(m_lAxis, m_chkHomeLevel.GetCheck()); 
//}

/*void CCAMC_QIDlg::OnChkZphaseLevel()
{
	if (!m_bA4NAxis)
		AxmSignalSetZphaseLevel(m_lAxis, m_chkZphaseLevel.GetCheck()); 
}*/

// Setup general output #0(Servo-On).  Output will go out if checked, Output will not go out if not checked.
//void CCAMC_QIDlg::OnLedOut0() 
//{
//	DWORD   dwOnOff;
//	AxmSignalIsServoOn(m_lAxis, &dwOnOff);		
//	if(dwOnOff)	AxmSignalServoOn(m_lAxis, FALSE);
//	else		AxmSignalServoOn(m_lAxis, TRUE);		
//}
//
//// Setup general output #1(Alarm-Clear).
//void CCAMC_QIDlg::OnLedOut1() 
//{
//	DWORD   dwOutBit;
//	AxmSignalReadOutputBit(m_lAxis, 1, &dwOutBit);
//	if (dwOutBit)	AxmSignalServoAlarmReset(m_lAxis, FALSE);
//	else			AxmSignalServoAlarmReset(m_lAxis, TRUE);	
//}
//
//// Setup general output #2.
//void CCAMC_QIDlg::OnLedOut2() 
//{
//	DWORD   dwOutBit;
//	AxmSignalReadOutputBit(m_lAxis, 2, &dwOutBit);	
//	if(dwOutBit)	AxmSignalWriteOutputBit(m_lAxis, 2, FALSE);
//	else			AxmSignalWriteOutputBit(m_lAxis, 2, TRUE);	
//}
//
//// Setup general output #3.
//void CCAMC_QIDlg::OnLedOut3() 
//{
//	DWORD   dwOutBit;
//	AxmSignalReadOutputBit(m_lAxis, 3, &dwOutBit);	
//	if(dwOutBit)	AxmSignalWriteOutputBit(m_lAxis, 3, FALSE);
//	else			AxmSignalWriteOutputBit(m_lAxis, 3, TRUE);	
//}
//
//// Setup general output #4.
//void CCAMC_QIDlg::OnLedOut4() 
//{
//	DWORD   dwOutBit;
//	AxmSignalReadOutputBit(m_lAxis, 4, &dwOutBit);	
//	if(dwOutBit)	AxmSignalWriteOutputBit(m_lAxis, 4, FALSE);
//	else			AxmSignalWriteOutputBit(m_lAxis, 4, TRUE);	
//}
//
//// Setup general output #5.
//void CCAMC_QIDlg::OnLedOut5() 
//{
//	DWORD   dwOutBit;
//	AxmSignalReadOutputBit(m_lAxis, 5, &dwOutBit);	
//	if(dwOutBit)	AxmSignalWriteOutputBit(m_lAxis, 5, FALSE);
//	else			AxmSignalWriteOutputBit(m_lAxis, 5, TRUE);	
//}

// It is for the test of Home searching, about setup signal to be searched and searching direction and stop method after searching
// Repeated running after reading running parameter from edit box.
//void CCAMC_QIDlg::OnBtnSearch() 
//{
//	unsigned long	ThreadID;
//	if(m_hTestThread[m_lAxis] == NULL)
//	{
//		m_bTestActive[m_lAxis] = TRUE;
//		m_hTestThread[m_lAxis] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SearchThread, this, 0, &ThreadID);
//	}
//	else
//	{
//		m_lstLog.AddString("Already Moving");
//		m_lstLog.SetTopIndex(m_lstLog.GetCount() - 1);
//	}
//}

// Create thread for repeated running.
// It is the function that user outputting one trigger pulse by force.
void CCAMC_QIDlg::OnBtnRepeat() 
{
	unsigned long	ThreadID;
	int nCurSel = m_cboAxisSet.GetCurSel();

	if (!m_bTestActive[nCurSel])
	{
		m_bTestActive[nCurSel] = TRUE;
		if (m_hTestThread[nCurSel] == NULL)
			m_hTestThread[nCurSel] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RepeatThread, this, NULL, &ThreadID);
	}
	else
	{
		m_lstLog.AddString("Already Moving");
		m_lstLog.SetTopIndex(m_lstLog.GetCount() - 1);
	}
}

//void CCAMC_QIDlg::OnBtnTrigOneshot() 
//{
//	//int	pulse_width	= GetDlgItemInt(IDC_EDT_TRIG_PULSE_WIDTH);
//	// It is the function that user outputting one trigger pulse by force.
//	AxmTriggerSetTimeLevel(m_lAxis, pulse_width, HIGH, COMMAND, ENABLE);
//	AxmTriggerOneShot(m_lAxis);
//}

//void CCAMC_QIDlg::OnBtnTrigAbs() 
//{
//	DWORD	uErrorCode;
//	double	trig_pos[1];
//	//int		pulse_width	= GetDlgItemInt(IDC_EDT_TRIG_PULSE_WIDTH);
//	//trig_pos[0] = GetDlgItemDouble(IDC_EDT_TRIG_START_POS);
//
//	AxmTriggerSetReset(m_lAxis);
//	AxmTriggerSetTimeLevel(m_lAxis, pulse_width, HIGH, COMMAND, ENABLE);
//
//	uErrorCode = AxmTriggerOnlyAbs(m_lAxis, 1, trig_pos);
//	if(uErrorCode == AXT_RT_SUCCESS)	m_lstLog.AddString("Setting Trigger");
//	else								m_lstLog.AddString("Not setting Trigger");
//}

//void CCAMC_QIDlg::OnBtnTrigPeriod() 
//{
//	DWORD	uErrorCode;
//	double	start_pos	= GetDlgItemDouble(IDC_EDT_TRIG_START_POS);
//	double  cycle       = GetDlgItemDouble(IDC_EDT_TRIG_CYCLE);
//	double	end_pos		= GetDlgItemDouble(IDC_EDT_TRIG_END_POS);
//	int		pulse_width	= GetDlgItemInt(IDC_EDT_TRIG_PULSE_WIDTH);
//
//	AxmTriggerSetReset(m_lAxis);
//	AxmTriggerSetTimeLevel(m_lAxis, pulse_width, HIGH, COMMAND, ENABLE);
//
//	uErrorCode = AxmTriggerSetBlock(m_lAxis, start_pos, end_pos, cycle);
//	if(uErrorCode == AXT_RT_SUCCESS)	m_lstLog.AddString("Setting Trigger");
//	else								m_lstLog.AddString("Not setting Trigger");
//}

//void CCAMC_QIDlg::OnBtnTrigReset() 
//{
//	AxmTriggerSetReset(m_lAxis);
//}

// Make edit window to be active for setting a value of reduced speed when asymmetric running mode.
void CCAMC_QIDlg::OnChkAsym() 
{
	DWORD dwProfile;
	//ProfileMode: '0' - symmetry Trapezoid
	//             '1' - asymmetry Trapezoid
	//             '2' - symmetry Quasi-S Curve
	//             '3' - symmetry S Curve
	//             '4' - asymmetry S Curve
	AxmMotGetProfileMode(m_lAxis, &dwProfile);
	if(m_chkAsym.GetCheck())
	{
		m_edtDecel.EnableWindow(TRUE);
		if((dwProfile == 0) || (dwProfile == 3))	dwProfile += 1;
		else										dwProfile  = 4;
	}else
	{
		m_edtDecel.EnableWindow(FALSE);		
		if((dwProfile == 1) || (dwProfile == 4))	dwProfile -= 1;
		else										dwProfile  = 3;			
	}
	AxmMotSetProfileMode(m_lAxis, dwProfile);
}

void CCAMC_QIDlg::OnChkScurve() 
{
	DWORD dwProfile;
	//ProfileMode: '0' - symmetry Trapezoid
	//             '1' - asymmetry Trapezoid
	//             '2' - symmetry Quasi-S Curve
	//             '3' - symmetry S Curve
	//             '4' - asymmetry S Curve
	AxmMotGetProfileMode(m_lAxis, &dwProfile);
	if (m_chkScurve.GetCheck())
	{
		if((dwProfile == 0) || (dwProfile == 1))	dwProfile += 3;
		else										dwProfile  = 3;
	}else
	{
		if((dwProfile == 3) || (dwProfile == 4))	dwProfile -= 3;
		else										dwProfile  = 0;			
	}
	AxmMotSetProfileMode(m_lAxis, dwProfile);
}

// To opposite coordinate if it was checked when click the check box of absolute coordinate.
void CCAMC_QIDlg::OnChkAbsolute() 
{
	if (m_chkAbsolute.GetCheck())
	{
		m_chkRelative.SetCheck(FALSE);
		AxmMotSetAbsRelMode(m_lAxis, POS_ABS_MODE);
	}else
	{
		m_chkRelative.SetCheck(TRUE);
		AxmMotSetAbsRelMode(m_lAxis, POS_REL_MODE);
	}
}

// To opposite coordinate if it was checked when click the check box of opposite coordinate.
void CCAMC_QIDlg::OnChkRelative() 
{
	if (m_chkRelative.GetCheck())
	{
		m_chkAbsolute.SetCheck(FALSE);
		AxmMotSetAbsRelMode(m_lAxis, POS_REL_MODE);
	}else
	{
		m_chkAbsolute.SetCheck(TRUE);
		AxmMotSetAbsRelMode(m_lAxis, POS_ABS_MODE);
	}
}

// Setup distance rate and initial speed by pulse among those initial parameter.
// Change maximum speed to fit if setup distance rate by pulse.
void CCAMC_QIDlg::OnBtnSetting() 
{
	long	lPulse;
	CString strData;
	double	dMoveUnit, dStartStop;
	double	dUnit, dMinVelocity;
	
	lPulse		= (LONG)GetDlgItemDouble(IDC_EDT_PULSE);
	dMoveUnit	= GetDlgItemDouble(IDC_EDT_UNIT);
	dStartStop	= GetDlgItemDouble(IDC_EDT_STARTSPEED);
	
	AxmMotSetMoveUnitPerPulse(m_lAxis, dMoveUnit, lPulse);
	AxmMotSetMinVel(m_lAxis, dStartStop);
	AxmMotGetMoveUnitPerPulse(m_lAxis, &dUnit , &lPulse);
	AxmMotGetMinVel(m_lAxis, &dMinVelocity);

	strData.Format("%lf", dUnit/lPulse);	m_edtMoveUnit.SetWindowText(strData);
	strData.Format("%.3lf",dUnit);			m_edtUnit.SetWindowText(strData);
	strData.Format("%ld",lPulse);			m_edtPulse.SetWindowText(strData);
	strData.Format("%.0lf", dMinVelocity);	m_edtStartSpeed.SetWindowText(strData);
}

// Make reduced speed and stop to the running axis.
//void CCAMC_QIDlg::OnBtnStop() 
//{
//	if(m_bTestActive[m_lAxis])
//	{
//		m_bTestActive[m_lAxis] = FALSE;
//		AxmMoveSStop(m_lAxis);
//	}
//	else
//	{
//		AxmMoveSStop(m_lAxis);
//	}
//
//	m_lstLog.AddString("STOP.");
//	m_lstLog.SetTopIndex(m_lstLog.GetCount() - 1);
//}

// Make quick stop to the running axis.
void CCAMC_QIDlg::OnBtnEstop() 
{
	for(int i = 0; i < m_lAxisCounts; i++)
	{
		m_bTestActive[i] = FALSE;
		AxmMoveEStop(i);
	}

	m_lstLog.AddString("ESTOP.");
	m_lstLog.SetTopIndex(m_lstLog.GetCount() - 1);	
}

// Make active window of condition register.
void CCAMC_QIDlg::OnBtnStatus() 
{
	if(m_bStatus)
	{
		if(m_pStatus == NULL)
		{
			m_pStatus = new CStautsView(this, m_lAxis);
			m_pStatus->Create(IDD_STATUSVIEW, GetDesktopWindow());
		}
		
		m_bStatus = TRUE;
		m_pStatus->UpdateAxis(m_lAxis);			
		m_pStatus->ShowWindow(SW_SHOW);	
		m_pStatus->SetFocus();
	}
	else
	{
		m_bStatus = FALSE;
		m_pStatus->ShowWindow(SW_HIDE);
	}
}

void CCAMC_QIDlg::OnBtnManualset() 
{
	if(m_bManualSet)
	{
		if (m_pManualSet == NULL)
		{
			m_pManualSet = new ManualSet(this, m_lAxisCounts);
			m_pManualSet->Create(IDD_MANUAL_SET, GetDesktopWindow());
		}
		m_bManualSet = TRUE;
		m_pManualSet->UpdateAxis(m_lAxis);
		m_pManualSet->ShowWindow(SW_SHOW);
	}
	else
	{
		m_bManualSet = FALSE;
		m_pManualSet->ShowWindow(SW_HIDE);
	}
}

// Setup to fit to changed axis for distance rate by pulse when axis is changed, initial speed, pulse output method, encoder input method.
void CCAMC_QIDlg::OnSelchangeCmbAxisset() 
{
	m_lAxis = m_cboAxisSet.GetCurSel();	
	UpdateAxisInfo();
}

void CCAMC_QIDlg::UpdateAxisInfo() 
{
	CString	strData;
	DWORD	dwMEncInput, dwMPulseOut;
	DWORD	dwAbsRel, dwProfile;

	long	lPulse;
	double	dUnit;
	double	dMinVelocity;
	double	dInitpos, dInitvel, dInitaccel, dInitdecel;

	DWORD	dwModuleID;
	CString strGroup;

	lPulse	= 1;
	dUnit	= dMinVelocity = 1.0;	
	dInitpos = dInitvel = dInitaccel = dInitdecel = 1.0;
	m_cboAxisSet.SetCurSel(m_lAxis);

	AxmInfoGetAxis(m_lAxis, NULL, NULL, &dwModuleID);
    switch(dwModuleID)
    {
    case AXT_SMC_2V02:       
    case AXT_SMC_1V02:       
    case AXT_SMC_4V04:       
    case AXT_SMC_R1V04:      
    case AXT_SMC_2V04:
    case AXT_SMC_R1V04MLIIPM:
    case AXT_SMC_R1V04PM2Q: 
    case AXT_SMC_R1V04PM2QE:
    case AXT_SMC_R1V04MLIIIPM:
	case AXT_SMC_R1V04MLIIISV:
	case AXT_SMC_R1V04MLIIISV_MD:
	case AXT_SMC_R1V04MLIIIS7S:
	case AXT_SMC_R1V04MLIIIS7W:
        m_bA4NAxis = false;
        m_cboEncInputM.EnableWindow(true);
        m_cboPulseOutM.EnableWindow(true);

		//m_chkPelmLevel.SetButtonStyle(BS_AUTO3STATE);
		//m_chkNelmLevel.SetButtonStyle(BS_AUTO3STATE);
		//m_chkInpLevel.SetButtonStyle(BS_AUTO3STATE);
		//m_chkAlarmLevel.SetButtonStyle(BS_AUTO3STATE);
		//m_chkEmgLevel.SetButtonStyle(BS_AUTO3STATE);
		//m_chkZphaseLevel.EnableWindow(true);
		//m_chkHomeLevel.EnableWindow(true);

		//m_btnTrigReset.EnableWindow(true);
		//m_btnTrigPeriod.EnableWindow(true);
		//m_btnTrigOneshot.EnableWindow(true);
		//m_btnTrigABS.EnableWindow(true);
		//m_edtTrigCycle.EnableWindow(true);
		//m_edtTrigEndPos.EnableWindow(true);
		//m_edtTrigPulseWidth.EnableWindow(true);
		//m_edtTrigStartPos.EnableWindow(true);

		strGroup.Format("Level Setting");
		SetDlgItemText(IDC_STATIC_LEVEL, strGroup);

		if(dwModuleID == AXT_SMC_R1V04 || dwModuleID == AXT_SMC_R1V04MLIIPM){
			//m_btnCrcOn.EnableWindow(false);
			//m_btnCrcOff.EnableWindow(false);
			//GetDlgItem(IDC_BTN_INT_MESSAGE)->EnableWindow(false);
			//GetDlgItem(IDC_BTN_INT_EVENT)->EnableWindow(false);
			//GetDlgItem(IDC_BTN_INT_CALLBACK)->EnableWindow(false);
			//GetDlgItem(IDC_BTN_INT_DISABLE)->EnableWindow(false);
			//GetDlgItem(IDC_BTN_READ_CAPTURE)->EnableWindow(false);
			//GetDlgItem(IDC_BTN_MPG_ON)->EnableWindow(false);
			//GetDlgItem(IDC_BTN_MPG_OFF)->EnableWindow(false);
			//GetDlgItem(IDC_BTN_CRC_ON)->EnableWindow(false);
			//GetDlgItem(IDC_BTN_CRC_OFF)->EnableWindow(false);
		}else{
			//GetDlgItem(IDC_BTN_INT_MESSAGE)->EnableWindow(true);
			//GetDlgItem(IDC_BTN_INT_EVENT)->EnableWindow(true);
			//GetDlgItem(IDC_BTN_INT_CALLBACK)->EnableWindow(true);
			//GetDlgItem(IDC_BTN_INT_DISABLE)->EnableWindow(true);
			//GetDlgItem(IDC_BTN_SIG_CAPTURE)->EnableWindow(true);
			//GetDlgItem(IDC_BTN_READ_CAPTURE)->EnableWindow(true);
			//GetDlgItem(IDC_BTN_MPG_ON)->EnableWindow(true);
			//GetDlgItem(IDC_BTN_MPG_OFF)->EnableWindow(true);
			//GetDlgItem(IDC_BTN_CRC_ON)->EnableWindow(true);
			//GetDlgItem(IDC_BTN_CRC_OFF)->EnableWindow(true);
		}
        break;

    case AXT_SMC_R1V04MLIISV:
    case AXT_SMC_R1V04A5:
    case AXT_SMC_R1V04A4:
    case AXT_SMC_R1V04MLIICL:
    case AXT_SMC_R1V04MLIICR:
    case AXT_SMC_R1V04MLIIORI:
    case AXT_SMC_R1V04SIIIHMIV:
    case AXT_SMC_R1V04SIIIHMIV_R:
		m_bA4NAxis = true;

        m_cboEncInputM.EnableWindow(false);
        m_cboPulseOutM.EnableWindow(false);

		//m_chkPelmLevel.SetButtonStyle(BS_AUTOCHECKBOX);
		//m_chkNelmLevel.SetButtonStyle(BS_AUTOCHECKBOX);
		//m_chkInpLevel.SetButtonStyle(BS_AUTOCHECKBOX);
	//	m_chkAlarmLevel.SetButtonStyle(BS_AUTOCHECKBOX);
		//m_chkEmgLevel.SetButtonStyle(BS_AUTOCHECKBOX);
		//m_chkZphaseLevel.EnableWindow(false);
		//m_chkHomeLevel.EnableWindow(false);

		//m_btnTrigReset.EnableWindow(false);
		//m_btnTrigPeriod.EnableWindow(false);
		//m_btnTrigOneshot.EnableWindow(false);
		//m_btnTrigABS.EnableWindow(false);
		//m_edtTrigCycle.EnableWindow(false);
		//m_edtTrigEndPos.EnableWindow(false);
		//m_edtTrigPulseWidth.EnableWindow(false);
		//m_edtTrigStartPos.EnableWindow(false);

		strGroup.Format("Level/Usage");
		SetDlgItemText(IDC_STATIC_LEVEL, strGroup);

		//GetDlgItem(IDC_BTN_INT_MESSAGE)->EnableWindow(false);
		//GetDlgItem(IDC_BTN_INT_EVENT)->EnableWindow(false);
		//GetDlgItem(IDC_BTN_INT_CALLBACK)->EnableWindow(false);
		//GetDlgItem(IDC_BTN_INT_DISABLE)->EnableWindow(false);
		//GetDlgItem(IDC_BTN_SIG_CAPTURE)->EnableWindow(false);
		//GetDlgItem(IDC_BTN_READ_CAPTURE)->EnableWindow(false);
		//GetDlgItem(IDC_BTN_MPG_ON)->EnableWindow(false);
		//GetDlgItem(IDC_BTN_MPG_OFF)->EnableWindow(false);
		//GetDlgItem(IDC_BTN_CRC_ON)->EnableWindow(false);
		//GetDlgItem(IDC_BTN_CRC_OFF)->EnableWindow(false);
		break;
	}

	AxmMotGetParaLoad(m_lAxis, &dInitpos ,&dInitvel, &dInitaccel, &dInitdecel);	

	// Display pulse output method after initialization, encoder input method, initial speed, distance rate by pulse on the screen.
	AxmMotGetMoveUnitPerPulse(m_lAxis, &dUnit , &lPulse);
	AxmMotGetMinVel(m_lAxis, &dMinVelocity);

	strData.Format("%.5lf", dUnit);
	m_edtUnit.SetWindowText(strData);

	strData.Format("%ld",lPulse);
	m_edtPulse.SetWindowText(strData);

	strData.Format("%lf", dUnit / lPulse );
	m_edtMoveUnit.SetWindowText(strData);

	strData.Format("%.3lf",dMinVelocity);
	m_edtStartSpeed.SetWindowText(strData);

	SetDlgItemDouble( IDC_EDT_POSITION, dInitpos);
	SetDlgItemDouble( IDC_EDT_VELOCITY, 5000);
	SetDlgItemDouble( IDC_EDT_ACCEL, 30000);
	SetDlgItemDouble( IDC_EDT_DECEL, 30000);

	AxmMotGetProfileMode(m_lAxis, &dwProfile);
	AxmMotGetAbsRelMode(m_lAxis, &dwAbsRel);
 
	if (!m_bA4NAxis)
	{
		AxmMotGetEncInputMethod(m_lAxis, &dwMEncInput);
		AxmMotGetPulseOutMethod(m_lAxis, &dwMPulseOut);
		m_cboEncInputM.SetCurSel(dwMEncInput);
		m_cboPulseOutM.SetCurSel(dwMPulseOut);
	}

	if(dwAbsRel == 1)
	{
		m_chkRelative.SetCheck(TRUE);
		m_chkAbsolute.SetCheck(FALSE);
	}else
	{
		m_chkRelative.SetCheck(FALSE);
		m_chkAbsolute.SetCheck(TRUE);
	}

	if((dwProfile == 2) || (dwProfile == 3) || (dwProfile == 4))	m_chkScurve.SetCheck(TRUE);
	else															m_chkScurve.SetCheck(FALSE);

	if((dwProfile == 1) || (dwProfile == 4))
	{
		m_edtDecel.EnableWindow(TRUE);
		m_chkAsym.SetCheck(TRUE);
	}
	else
	{
		m_edtDecel.EnableWindow(FALSE);		
		m_chkAsym.SetCheck(FALSE);
	}

	DWORD   dwPositiveLevel, dwNegativeLevel, dwAlarmLevel, dwInposLevel;
	DWORD   dwHomeLevel, dwZphaseLevel;
	DWORD	dwStopMode, dwReadEmg;
	//double	dGearRatio;

	AxmSignalGetLimit(m_lAxis, &dwStopMode, &dwPositiveLevel, &dwNegativeLevel);
	AxmSignalGetServoAlarm(m_lAxis, &dwAlarmLevel);
	AxmSignalGetInpos(m_lAxis, &dwInposLevel);

	AxmSignalGetStop(m_lAxis, &dwStopMode, &dwReadEmg);

	if (!m_bA4NAxis)
	{
		AxmHomeGetSignalLevel(m_lAxis, &dwHomeLevel);		
		AxmSignalGetZphaseLevel(m_lAxis, &dwZphaseLevel);

		//m_chkPelmLevel.SetCheck(dwPositiveLevel);
		//m_chkNelmLevel.SetCheck(dwNegativeLevel);
		//m_chkEmgLevel.SetCheck(dwReadEmg);	
		//m_chkAlarmLevel.SetCheck(dwAlarmLevel);
		//m_chkInpLevel.SetCheck(dwInposLevel);
		//m_chkHomeLevel.SetCheck(dwHomeLevel);
		//m_chkZphaseLevel.SetCheck(dwZphaseLevel);
	}
	else
	{
		/*if (dwPositiveLevel == UNUSED)	m_chkPelmLevel.SetCheck(0);
		else							m_chkPelmLevel.SetCheck(1);*/

		/*if (dwNegativeLevel == UNUSED)	m_chkNelmLevel.SetCheck(0);
		else							m_chkNelmLevel.SetCheck(1);*/

		/*if (dwReadEmg == UNUSED)		m_chkEmgLevel.SetCheck(0);
		else							m_chkEmgLevel.SetCheck(1);*/

		/*if (dwAlarmLevel == UNUSED)		m_chkAlarmLevel.SetCheck(0);
		else							m_chkAlarmLevel.SetCheck(1);*/

		/*if (dwInposLevel == UNUSED)		m_chkInpLevel.SetCheck(0);
		else							m_chkInpLevel.SetCheck(1);*/
	}
	
	//AxmLinkGetMode(AXIS_EVN(m_lAxis), NULL, &dGearRatio); 	
	//if(dGearRatio > 0)
	//{
	//	SetDlgItemDouble(IDC_EDT_GEAR_RATIO, dGearRatio);
	//	m_chkGearOnOff.SetCheck(TRUE);
	//}
	//else
	//{
	//	//m_chkGearOnOff.SetCheck(FALSE);
	//}

	DWORD upSlHomeUse;
	AxmGantryGetEnable(m_lAxis, &upSlHomeUse, NULL, NULL, NULL);
//	m_chkGantrySlave.SetCheck(upSlHomeUse);
	//OnChkGantrySlave();

	SetTitleBar(m_lAxis);

	if(AXIS_N04(m_lAxis, 0) < m_lAxisCounts){
		strData.Format("%02d Axis", AXIS_N04(m_lAxis, 0));
		m_GraphX.SetLegendLabel(strData, 0);
	}else{
		m_GraphX.SetLegendLabel("None", 0);
	}

	if(AXIS_N04(m_lAxis, 1) < m_lAxisCounts){
		strData.Format("%02d Axis", AXIS_N04(m_lAxis, 1));
		m_GraphX.SetLegendLabel(strData, 1);
	}else{
		m_GraphX.SetLegendLabel("None", 1);
	}

	if(AXIS_N04(m_lAxis, 2) < m_lAxisCounts){
		strData.Format("%02d Axis", AXIS_N04(m_lAxis, 2));
		m_GraphY.SetLegendLabel(strData, 0);
	}else{
		m_GraphY.SetLegendLabel("None", 0);
	}

	if(AXIS_N04(m_lAxis, 3) < m_lAxisCounts){
		strData.Format("%02d Axis", AXIS_N04(m_lAxis, 3));
		m_GraphY.SetLegendLabel(strData, 1);
	}else{
		m_GraphY.SetLegendLabel("None", 1);
	}
}

void CCAMC_QIDlg::OnSelchangeCmbPulseOutm() 
{	
	AxmMotSetPulseOutMethod(m_lAxis, m_cboPulseOutM.GetCurSel()); 
}

void CCAMC_QIDlg::OnSelchangeCmbEncInputm() 
{
	AxmMotSetEncInputMethod(m_lAxis, m_cboEncInputM.GetCurSel());
}

void CCAMC_QIDlg::OnBtnMove() 
{
	double	dPosition	= GetDlgItemDouble(IDC_EDT_POSITION);
	double	dVelocity	= fabs(GetDlgItemDouble(IDC_EDT_VELOCITY));
	double	dAccel		= fabs(GetDlgItemDouble(IDC_EDT_ACCEL));
	double	dDecel		= fabs(GetDlgItemDouble(IDC_EDT_DECEL));

	SetGraphRange(m_lAxis, dVelocity);	
	if (m_chkXYsync.GetCheck())
	{		
		long	lAxis[2];
		double	dMPos[2], dMVel[2], dMAcc[2], dMDec[2];

		lAxis[0] = AXIS_ODD(m_lAxis);
		lAxis[1] = AXIS_EVN(m_lAxis);

		dMPos[0] = dPosition;	dMPos[1] = dPosition;
		dMVel[0] = dVelocity;	dMVel[1] = dVelocity;
		dMAcc[0] = dAccel;		dMAcc[1] = dAccel;
		dMDec[0] = dDecel;		dMDec[1] = dDecel;

		AxmMoveStartMultiPos(2, lAxis, dMPos, dMVel, dMAcc, dMDec);
	}
	else
	{
		 AxmMoveStartPos(m_lAxis, dPosition, dVelocity, dAccel, dDecel);
	}
	AxmMotSetParaLoad(m_lAxis, dPosition, dVelocity, dAccel, dDecel);	
}

// Straight line interpolation running
//void CCAMC_QIDlg::OnBtnLinear() 
//{
//	CString strMsg;
//	long    lAxis[2];
//	double  dPos[2];
//	DWORD	uErrorCode;
//	double	dVelocity, dAccel, dDecel;
//
//	dVelocity	= GetDlgItemDouble(IDC_EDT_VELOCITY);
//	dAccel		= GetDlgItemDouble(IDC_EDT_ACCEL);
//	dDecel		= GetDlgItemDouble(IDC_EDT_DECEL);
//
//	dPos[0]		= GetDlgItemDouble(IDC_EDT_XCEN);
//	dPos[1]		= GetDlgItemDouble(IDC_EDT_YCEN);
//
//	lAxis[0]	= AXIS_EVN(m_lAxis);
//	lAxis[1]	= AXIS_ODD(m_lAxis);
//
//	SetGraphRange(lAxis[0], dVelocity);	
//
//	AxmContiSetAxisMap(COORD_NO, 2, lAxis);
//	AxmContiWriteClear(COORD_NO);
//
//	SetCoordMovePara();
//	uErrorCode = AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);
//
//	strMsg.Format("Linear Error Code: %d", uErrorCode);	
//	if(uErrorCode != AXT_RT_SUCCESS)	m_lstLog.AddString(strMsg);
//
//	double	dPosition;
//	AxmMotGetParaLoad(m_lAxis, &dPosition, 0, 0, 0);	
//	AxmMotSetParaLoad(m_lAxis, dPosition, dVelocity, dAccel, dDecel);	
//}

void CCAMC_QIDlg::SetCoordMovePara()
{
	//ProfileMode: '0' - symmetry Trapezode
	//             '1' - asymmetry Trapezode
	//             '2' - symmetry Quasi-S Curve
	//             '3' - symmetry S Curve
	//             '4' - asymmetry S Curve
	if (m_chkAbsolute.GetCheck())	AxmContiSetAbsRelMode(COORD_NO, POS_ABS_MODE);
	else							AxmContiSetAbsRelMode(COORD_NO, POS_REL_MODE);
}

//void CCAMC_QIDlg::OnBtnCircular() 
//{
//	CString strMsg;
//	long    lAxis[2];
//	double  dCenPos[2];	
//	DWORD	uErrorCode;
//	double	dVelocity, dAccel, dDecel, dAngle;
//
//	dVelocity	= GetDlgItemDouble(IDC_EDT_VELOCITY);
//	dAccel		= GetDlgItemDouble(IDC_EDT_ACCEL);
//	dDecel		= GetDlgItemDouble(IDC_EDT_DECEL);
//	dAngle		= GetDlgItemDouble(IDC_EDT_ANGLE);
//
//	dCenPos[0]	= GetDlgItemDouble(IDC_EDT_XCEN);
//	dCenPos[1]	= GetDlgItemDouble(IDC_EDT_YCEN);
//
//	lAxis[0]	= AXIS_EVN(m_lAxis);
//	lAxis[1]	= AXIS_ODD(m_lAxis);
//
//	SetGraphRange(lAxis[0], dVelocity);	
//
//	AxmContiSetAxisMap(COORD_NO, 2, lAxis);
//	AxmContiWriteClear(COORD_NO);
//
//	SetCoordMovePara();
//	if(m_chkCwCcw.GetCheck())	uErrorCode = AxmCircleAngleMove(COORD_NO, lAxis, dCenPos, dAngle, dVelocity, dAccel, dDecel, 0);
//	else						uErrorCode = AxmCircleAngleMove(COORD_NO, lAxis, dCenPos, dAngle, dVelocity, dAccel, dDecel, 1);
//
//	strMsg.Format("Circular Error Code: %d", uErrorCode);	
//	if(uErrorCode != AXT_RT_SUCCESS)	m_lstLog.AddString(strMsg);
//
//	double	dPosition;
//	AxmMotGetParaLoad(m_lAxis, &dPosition, 0, 0, 0);	
//	AxmMotSetParaLoad(m_lAxis, dPosition, dVelocity, dAccel, dDecel);	
//}

void CCAMC_QIDlg::OnBtnCountClr() 
{
	AxmStatusSetActPos(AXIS_N04(m_lAxis, 0), 0.0);
	AxmStatusSetActPos(AXIS_N04(m_lAxis, 1), 0.0);
	AxmStatusSetCmdPos(AXIS_N04(m_lAxis, 2), 0.0);
	AxmStatusSetCmdPos(AXIS_N04(m_lAxis, 3), 0.0);

	AxmStatusSetCmdPos(AXIS_N04(m_lAxis, 0), 0.0);
	AxmStatusSetCmdPos(AXIS_N04(m_lAxis, 1), 0.0);
	AxmStatusSetActPos(AXIS_N04(m_lAxis, 2), 0.0);
	AxmStatusSetActPos(AXIS_N04(m_lAxis, 3), 0.0);

	m_XYGraph.Reset();
	m_lstLog.ResetContent();	
}

//void CCAMC_QIDlg::OnBtnSigCapture() 
//{
//	BYTE	bySignal;	
//	DWORD   dwEdge;
//	long	lDirect;
//	long	lSignalMethod;
//	double	dVelocity, dAccel;
//
//	dVelocity		= GetDlgItemDouble(IDC_EDT_VELOCITY);		
//	dAccel			= GetDlgItemDouble(IDC_EDT_ACCEL);		
//	bySignal		= m_cboDetect.GetCurSel();
//	lDirect			= m_cboDirection.GetCurSel();
//	lSignalMethod	= m_cboStopM.GetCurSel();	
//
//	// Re-setup of the maximum value in chart for displaying running speed of each axis on the chart.
//	SetGraphRange(m_lAxis, dVelocity);	
//
//	if(bySignal < 8)
//	{
//		dwEdge	 = 0;
//		bySignal = m_cboDetect.GetCurSel();
//	}else
//	{
//		dwEdge	 = 1;
//		bySignal = m_cboDetect.GetCurSel() - 8;
//	}
//
//	if(lDirect == 0)
//		AxmMoveSignalCapture(m_lAxis, dVelocity, dAccel, bySignal, dwEdge, COMMAND, lSignalMethod);
//	else
//		AxmMoveSignalCapture(m_lAxis, -dVelocity, dAccel, bySignal, dwEdge, COMMAND, lSignalMethod);	
//}

void CCAMC_QIDlg::OnBtnContiLine() 
{
	long    lAxis[3];
	double  dPos[3];
	double	dVelocity, dAccel, dDecel;

	dVelocity	= GetDlgItemDouble(IDC_EDT_VELOCITY);
	dAccel		= GetDlgItemDouble(IDC_EDT_ACCEL);
	dDecel		= GetDlgItemDouble(IDC_EDT_DECEL);
	
	lAxis[0]	= AXIS_N04(m_lAxis, 0); 
	lAxis[1]	= AXIS_N04(m_lAxis, 1); 
	lAxis[2]	= AXIS_N04(m_lAxis, 2); 

	SetGraphRange(lAxis[0], dVelocity);	
	SetGraphRange(lAxis[2], dVelocity);	


	AxmContiSetAxisMap(COORD_NO, 3, lAxis);
	AxmContiWriteClear(COORD_NO);
	AxmContiSetAbsRelMode(COORD_NO, POS_ABS_MODE);

	AxmContiBeginNode(COORD_NO);

	dPos[0] = 0 , dPos[1] = 0, dPos[2] = 0;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	dPos[0] = 0 , dPos[1] = 2000, dPos[2] = 0;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	dPos[0] = 0 , dPos[1] = 2000, dPos[2] = 2000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	dPos[0] = 0 , dPos[1] = 0, dPos[2] = 2000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	dPos[0] = 0 , dPos[1] = 0, dPos[2] = 0;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	//dPos[0] = -2000 , dPos[1] = 0, dPos[2] = 2000;
	//AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	//dPos[0] = 0 , dPos[1] = 2000, dPos[2] = 2000;
	//AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	//dPos[0] = 0 , dPos[1] = 2000, dPos[2] = 0;
	//AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	//dPos[0] = 0 , dPos[1] = 0, dPos[2] = 0;
	//AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	AxmContiEndNode(COORD_NO);
}

void CCAMC_QIDlg::OnBnClickedBtnSetHome()
{
	AxmStatusSetActPos(AXIS_N04(m_lAxis, 0), 0.0);
	AxmStatusSetActPos(AXIS_N04(m_lAxis, 1), 0.0);
	AxmStatusSetCmdPos(AXIS_N04(m_lAxis, 2), 0.0);
	AxmStatusSetCmdPos(AXIS_N04(m_lAxis, 3), 0.0);

	AxmStatusSetCmdPos(AXIS_N04(m_lAxis, 0), 0.0);
	AxmStatusSetCmdPos(AXIS_N04(m_lAxis, 1), 0.0);
	AxmStatusSetActPos(AXIS_N04(m_lAxis, 2), 0.0);
	AxmStatusSetActPos(AXIS_N04(m_lAxis, 3), 0.0);
}

void CCAMC_QIDlg::OnBnClickedBtnGoHome()
{
	CONFIG_RUN_LINE(x, y, z, a, b, f);
	AxmContiBeginNode(COORD_NO);
	RUN_MAX_SPEED(0, 0, 0, 0, 0);
	AxmContiEndNode(COORD_NO);
	OnBtnContiStart();
}

void CCAMC_QIDlg::OnBtnContiCircle() 
{
	long    lAxis[2];
	double	dVelocity, dAccel, dDecel;
	double  dCenPos[2], dEndPos[2];
	double  dPos[3];

	dVelocity	= GetDlgItemDouble(IDC_EDT_VELOCITY);
	dAccel		= GetDlgItemDouble(IDC_EDT_ACCEL);
	dDecel		= GetDlgItemDouble(IDC_EDT_DECEL);
	
	lAxis[0]	= AXIS_N04(m_lAxis, 0); 
	lAxis[1]	= AXIS_N04(m_lAxis, 1); 

	SetGraphRange(lAxis[0], dVelocity);	

	AxmContiSetAxisMap(COORD_NO, 2, lAxis);
	AxmContiWriteClear(COORD_NO);
	AxmContiSetAbsRelMode(COORD_NO, POS_ABS_MODE);

	AxmContiBeginNode(COORD_NO);

	dCenPos[0] = 1000 , dCenPos[1] = 1000; dEndPos[0] = 0; dEndPos[1] = 0;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CCW);

	dCenPos[0] = -1000 , dCenPos[1] = 1000; dEndPos[0] = 0; dEndPos[1] = 0;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CCW);

	dPos[0] = 0, dPos[1] = 0, dPos[2] = 0;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	dCenPos[0] = -1000 , dCenPos[1] = -1000; dEndPos[0] = 0; dEndPos[1] = 0;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CCW);

	dCenPos[0] = 1000 , dCenPos[1] = -1000; dEndPos[0] = 0; dEndPos[1] = 0;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CCW);

	dPos[0] = 0, dPos[1] = 0, dPos[2] = 0;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);

	AxmContiEndNode(COORD_NO);	
}

void CCAMC_QIDlg::OnBtnContiSpline() 
{
	long    lAxis[2];
	double  dPosX[5];
	double  dPosY[5];
	double	dVelocity, dAccel, dDecel;

	dVelocity	= GetDlgItemDouble(IDC_EDT_VELOCITY);
	dAccel		= GetDlgItemDouble(IDC_EDT_ACCEL);
	dDecel		= GetDlgItemDouble(IDC_EDT_DECEL);

	lAxis[0]	= AXIS_N04(m_lAxis, 0); 
	lAxis[1]	= AXIS_N04(m_lAxis, 1); 

	SetGraphRange(lAxis[0], dVelocity);	

	AxmContiSetAxisMap(COORD_NO, 2, lAxis);
	AxmContiWriteClear(COORD_NO);
	AxmContiSetAbsRelMode(COORD_NO, POS_ABS_MODE);

	dPosX[0] = 0   , dPosY[0] = 0;
	dPosX[1] = 450,  dPosY[1] = 100;
	dPosX[2] = 750,  dPosY[2] = 450;
	dPosX[3] = 1080, dPosY[3] = 750;
	dPosX[4] = 1300, dPosY[4] = 700;
	AxmContiBeginNode(COORD_NO);

	AxmSplineWrite(COORD_NO, 5, dPosX, dPosY, dVelocity, dAccel, dAccel, 0, 100);
	AxmContiEndNode(COORD_NO);
}

void CCAMC_QIDlg::OnBtnContiBlend() 
{
	long    lAxis[2];
	double  dPos[2];
	double  dCenPos[2];	
	double  dEndPos[2];
	double	dVelocity, dAccel, dDecel;

	dVelocity	= GetDlgItemDouble(IDC_EDT_VELOCITY);
	dAccel		= GetDlgItemDouble(IDC_EDT_ACCEL);
	dDecel		= GetDlgItemDouble(IDC_EDT_DECEL);

	lAxis[0]	= AXIS_N04(m_lAxis, 0); 
	lAxis[1]	= AXIS_N04(m_lAxis, 1); 

	SetGraphRange(lAxis[0], dVelocity);	

	AxmContiSetAxisMap(COORD_NO, 2, lAxis);
	AxmContiWriteClear(COORD_NO);
	AxmContiSetAbsRelMode(COORD_NO, POS_ABS_MODE);

	AxmContiBeginNode(COORD_NO); 	
	dPos[0] = 0 , dPos[1] = 2000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);	
	
	dPos[0] = 1800 , dPos[1] = 2000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dDecel);	
	
	dCenPos[0] = 1800 , dCenPos[1] = 1800; dEndPos[0] = 2000; dEndPos[1] = 1800;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);
	
	dPos[0] = 2000 , dPos[1] = -1800;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);	
	
	dCenPos[0] = 1800 , dCenPos[1] = -1800; dEndPos[0] = 1800; dEndPos[1] = -2000;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);

	dPos[0] = -1800 , dPos[1] = -2000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);	
	
	dCenPos[0] = -1800 , dCenPos[1] = -1800; dEndPos[0] = -2000; dEndPos[1] = -1800;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);

	dPos[0] = -2000 , dPos[1] = 1800;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);	
	
	dCenPos[0] = -1800 , dCenPos[1] = 1800; dEndPos[0] = -1800; dEndPos[1] = 2000;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);

	dPos[0] = 0 , dPos[1] = 2000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);	
	
	AxmContiEndNode(COORD_NO);
}

void CCAMC_QIDlg::OnBtnContiStart() 
{

	AxmContiStart(COORD_NO, 0, 0);
}

void CCAMC_QIDlg::OnChkGantry() 
{
	CString strMsg;
	DWORD	uErrorCode;	
	/*if( m_chkGantry.GetCheck())
	{
		uErrorCode = AxmGantrySetEnable(AXIS_EVN(m_lAxis), AXIS_ODD(m_lAxis), m_chkGantrySlave.GetCheck(), 0.0, 100000.0);
		strMsg.Format("Gantry Enable ErrCode %d", uErrorCode);	
		m_lstLog.AddString(strMsg);
	}
	else
	{
		AxmGantrySetDisable(AXIS_EVN(m_lAxis), AXIS_ODD(m_lAxis));
		m_lstLog.AddString("Gantry Disable");
	}*/
}

void CCAMC_QIDlg::OnBtnContiClr() 
{
	AxmContiWriteClear(COORD_NO);
}

LRESULT CCAMC_QIDlg::OnControlMessage(WPARAM wParam, LPARAM lParam)
{
	CString strData;
	int		nBoard = HIBYTE(wParam);		// Interrupt generation board number.
	long	lAxisNo = LOBYTE(wParam);		// Interrupt generation axis number.
	int		nIntrFlag = (int)lParam;		// Interrupt generation axis location.
	
	DWORD IntBank0, IntBank1;
	AxmInterruptReadAxisFlag(lAxisNo, 0, &IntBank0);
	AxmInterruptReadAxisFlag(lAxisNo, 1, &IntBank1);

	g_nIntCnt++;
	strData.Format("Msg[%02d]Axis[%02d]Flag[0x%02X]", g_nIntCnt, lAxisNo, nIntrFlag);
	m_lstLog.AddString(strData);

	return	TRUE;
}

BOOL ThreadProc(LPVOID lpData)
{
	CCAMC_QIDlg *pDlg	= (CCAMC_QIDlg *)lpData;

	pDlg->ThreadData();
	return TRUE;
}

//void CCAMC_QIDlg::OnBtnIntCallback() 
//{
//	CString strData;
//	DWORD dInterruptNum;
//	
//	g_nIntCnt = 0;
//	AxlInterruptEnable();
//	AxmInterruptSetAxisEnable(m_lAxis, ENABLE);
//
//	// Setup whether interrupt is generated which user of the designated axis set.
//	// lBank : Possible to setup interrupt bank number (0 - 1).
//	// lInterruptNum : Setup interrupt
//	AxmInterruptSetUserEnable(m_lAxis, 0, QIINTBANK1_1);			// When running is finished
//	AxmInterruptSetAxis(m_lAxis, NULL, NULL, KeMotionInterruptCallback, NULL);
//
//	AxmInterruptGetUserEnable(m_lAxis, 0, &dInterruptNum);
//	strData.Format("Done Int Enable[0][%08X]", dInterruptNum);
//	m_lstLog.AddString(strData);
//}

//void CCAMC_QIDlg::OnBtnIntMessage() 
//{
//	CString strData;
//	DWORD dwInterruptNum;
//
//	g_nIntCnt = 0;
//	AxlInterruptEnable();
//	AxmInterruptSetAxisEnable(m_lAxis, ENABLE);
//
//	// Setup whether interrupt is generated which user of the designated axis set.
//	// lBank : Possible to setup interrupt bank number (0 - 1).
//	// lInterruptNum : Setup interrupt
//	AxmInterruptSetUserEnable(m_lAxis, 1, QIINTBANK2_29);			// Input signal of limit signal (PELM, NELM).
//	AxmInterruptSetAxis(m_lAxis, m_hWnd, WM_CAMC_INTERRUPT, NULL, NULL);
//
//	AxmInterruptGetUserEnable(m_lAxis, 1, &dwInterruptNum);	
//	strData.Format("Limit Int Enable[1][%08X]", dwInterruptNum);
//	m_lstLog.AddString(strData);
//}

//void CCAMC_QIDlg::OnBtnIntEvent() 
//{
//	CString strData;
//	DWORD dwInterruptNum;
//
//	g_nIntCnt = 0;
//	AxlInterruptEnable();
//	AxmInterruptSetAxisEnable(m_lAxis, ENABLE);
//	// Setup whether interrupt is generated which user of the designated axis set.
//	// lBank : Possible to setup interrupt bank number (0 - 1).
//	// lInterruptNum : Setup interrupt
//	AxmInterruptSetUserEnable(m_lAxis, 0, QIINTBANK1_29);			// Accepted server alarm signal
//	AxmInterruptSetAxis(m_lAxis, NULL, NULL, NULL, &m_hInterrupt[m_lAxis]);
//
//	AxmInterruptGetUserEnable(m_lAxis, 0, &dwInterruptNum);	
//	strData.Format("Alarm Int Enable[0][%08X]", dwInterruptNum);
//	m_lstLog.AddString(strData);
//
//	if(m_hHandle[m_lAxis])
//	{
//		m_bThread[m_lAxis]	= FALSE;
//		m_hHandle[m_lAxis]	= NULL;
//	}
//	
//	if (!m_bThread[m_lAxis])
//	{
//		m_bThread[m_lAxis]	= TRUE;
//		m_hHandle[m_lAxis]	= CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, this, NULL, NULL);
//	}
//}

//void CCAMC_QIDlg::OnBtnIntDisable() 
//{
//	if (m_hHandle[m_lAxis])
//	{
//		m_bThread[m_lAxis]	= FALSE;
//		m_hHandle[m_lAxis]	= NULL;
//	}
//	
//	g_nIntCnt = 0;											// Interrupt count clear
//	AxlInterruptDisable();
//	AxmInterruptSetAxis(m_lAxis, m_hWnd, NULL, NULL, NULL); // Cancel interrupt method
//	AxmInterruptSetAxisEnable(m_lAxis, DISABLE);			// Interrupt DISABLE
//}

//void CCAMC_QIDlg::OnBtnCrcOn() 
//{
//	// Level   : LOW(0), HIGH(1), UNUSED(2), USED(3)
//	// uMethod : Remove remaining pulse, possible to setup output signal pulse range of 0 - 6
//	// 0: Don't care , 1: Don't care, 2: 500 uSec, 3: 1 mSec, 4: 10 mSec, 5: 50 mSec, 6: 100 mSec
//	AxmCrcSetMaskLevel(m_lAxis, HIGH, 6);
//}

//void CCAMC_QIDlg::OnBtnCrcOff() 
//{
//	AxmCrcSetMaskLevel(m_lAxis, UNUSED, 6);
//}

//void CCAMC_QIDlg::OnBtnMpgOn() 
//{
//	double dVelocity, dAccel;
//
//	dVelocity	= GetDlgItemDouble(IDC_EDT_VELOCITY);
//	dAccel		= GetDlgItemDouble(IDC_EDT_ACCEL);
//
//	long   lInputMethod = 3;
//	long   lDriveMode   = 0;
//
//	double dMPGPosition		= 1000;
//	double dMPGdenominator	= 4096;		// MPG(Manual Pulse Generation device Input) divide value when running (Calculated to add 1 to input value)
//	double dMPGnumerator	= 1;		// MPG(Manual Pulse Generation device Input) multiply value when running (Calculated to add 1 to input value)
//
//    // dwNumerator   : Possible to setup maximum (1 to 64).
//	// dwDenominator : Possible to setup maximum (1 to 4096).
//	AxmMPGSetEnable(m_lAxis, lInputMethod, lDriveMode, dMPGPosition, dVelocity, dAccel);
//	AxmMPGSetRatio(m_lAxis, dMPGnumerator, dMPGdenominator);
//}

//void CCAMC_QIDlg::OnBtnMpgOff() 
//{
//	AxmMPGReset(m_lAxis);
//}
//
//void CCAMC_QIDlg::OnChkGearOnoff() 
//{
//	double dRatio = GetDlgItemDouble(IDC_EDT_GEAR_RATIO);
//
//	// It is a function to setup gear rate of Master axis and Slave axis on Electric Gear mode.
//	if(m_chkGearOnOff.GetCheck())	AxmLinkSetMode(AXIS_EVN(m_lAxis), AXIS_ODD(m_lAxis), dRatio); 
//	else							AxmLinkResetMode(AXIS_EVN(m_lAxis));
//}

void CCAMC_QIDlg::OnBtncontiTest() 
{
	double dVelocity, dAccel;
	long    lAxis[2];
	double  dPos[2];
	long    lPosSize = 2;
	double  dCenPos[2];	
	double  dEndPos[2];
	
	lAxis[0]	= 0;
	lAxis[1]	= 1;
	dVelocity	= GetDlgItemDouble(IDC_EDT_VELOCITY);
	dAccel		= GetDlgItemDouble(IDC_EDT_ACCEL);
	SetGraphRange(lAxis[0], dVelocity);	

	AxmContiSetAxisMap(COORD_NO, lPosSize, lAxis);
	AxmContiWriteClear(COORD_NO);
	AxmContiSetAbsRelMode(COORD_NO, POS_REL_MODE);

	AxmContiBeginNode(COORD_NO); dPos[0] = -15000 , dPos[1] = 0;

	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//1
	dCenPos[0] = 0 , dCenPos[1] = 5000; dEndPos[0] = -5000; dEndPos[1] = 5000;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);  //2	
	dPos[0] = 0 , dPos[1] = 30000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//3
	dCenPos[0] = 5000 , dCenPos[1] = 0; dEndPos[0] = 5000; dEndPos[1] = 5000;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);  //4
	dPos[0] = 30000 , dPos[1] = 0;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//5
	dCenPos[0] = 0 , dCenPos[1] = -5000; dEndPos[0] = 5000; dEndPos[1] = -5000;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos,  dVelocity, dAccel, dAccel, DIR_CW);	//6
	dPos[0] = 0 , dPos[1] = -30000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//7
	dCenPos[0] = -5000 , dCenPos[1] = 0; dEndPos[0] = -5000; dEndPos[1] = -5000;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);	//8
	dPos[0] = -15000 , dPos[1] = 0;

	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//9
	dPos[0] = -10000 , dPos[1] = 0;

	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//10
	dCenPos[0] = 0 , dCenPos[1] = 10000; dEndPos[0] = -10000; dEndPos[1] = 10000;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);	//11
	dPos[0] = 0 , dPos[1] = 20000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//12
	dCenPos[0] = 10000 , dCenPos[1] = 0; dEndPos[0] = 10000; dEndPos[1] = 10000;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);	//13
	dPos[0] = 20000 , dPos[1] = 0;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//14
	dCenPos[0] = 0 , dCenPos[1] = -10000; dEndPos[0] = 10000; dEndPos[1] = -10000;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);	//15
	dPos[0] = 0 , dPos[1] = -20000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//16
	dCenPos[0] = -10000 , dCenPos[1] = 0; dEndPos[0] = -10000; dEndPos[1] = -10000;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);	//17
	dPos[0] = -10000 , dPos[1] = 0;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//18
	dCenPos[0] = 0 , dCenPos[1] = 20000; dEndPos[0] = 0; dEndPos[1] = 0;
	AxmCircleCenterMove(COORD_NO, lAxis, dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);  //19
	dCenPos[0] = 0 , dCenPos[1] = 10000; dEndPos[0] = -7071; dEndPos[1] = 2929;
	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW); //20

	dPos[0] = -10000 , dPos[1] = 10000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//21
	dCenPos[0] = 7071 , dCenPos[1] = 7071; dEndPos[0] =0; dEndPos[1] = 14142;
	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW); //22
	dPos[0] = 10000 , dPos[1] = 10000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//23
	dCenPos[0] = 7071 , dCenPos[1] = -7071; dEndPos[0] = 14142; dEndPos[1] = 0;
	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW); //24
	dPos[0] = 10000 , dPos[1] = -10000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//25
	dCenPos[0] = -7071 , dCenPos[1] = -7071; dEndPos[0] = 0; dEndPos[1] = -14142;
	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW); //26
	dPos[0] = -10000 , dPos[1] = -10000;
	AxmLineMove(COORD_NO, dPos, dVelocity, dAccel, dAccel);										//27
	dCenPos[0] = -7071 , dCenPos[1] = 7071; dEndPos[0] = -7071; dEndPos[1] = -2929;	

	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW);	//28
	dCenPos[0] = 0 , dCenPos[1] = 10000; dEndPos[0] = 0; dEndPos[1] = 20000;
	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW); //29
	dCenPos[0] = 0 , dCenPos[1] = 10000; dEndPos[0] = 0; dEndPos[1] = 20000;	
	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CCW);//30
	dCenPos[0] = 0 , dCenPos[1] = -5000; dEndPos[0] = 0; dEndPos[1] = -10000;
	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CCW);//31

	dCenPos[0] = 0 , dCenPos[1] = -5000; dEndPos[0] = 0; dEndPos[1] = -10000;
	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW); //32
	dCenPos[0] = 0 , dCenPos[1] = -5000; dEndPos[0] = 0; dEndPos[1] = -10000;
	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CCW);//33
	dCenPos[0] = 0 , dCenPos[1] = -5000; dEndPos[0] = 0; dEndPos[1] = -10000;
	AxmCircleCenterMove(COORD_NO, lAxis,  dCenPos, dEndPos, dVelocity, dAccel, dAccel, DIR_CW); //34

	AxmContiEndNode(COORD_NO);
}

void CCAMC_QIDlg::OnBtnLoad() 
{
	CString	temp;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY,
		"Data File (*.mot)|*.mot|All Files (*.*)|*.*||");
	
	if (dlg.DoModal() == IDOK)
	{
		temp = dlg.GetPathName();
		LPTSTR nFilename = temp.GetBuffer(0);
		if (AXT_RT_SUCCESS != AxmMotLoadParaAll(nFilename))
			m_lstLog.AddString("File load fail!");
		m_lstLog.SetTopIndex(m_lstLog.GetCount() - 1);
		temp.ReleaseBuffer();	
	}
	
	UpdateAxisInfo();
}

void CCAMC_QIDlg::OnBtnSave() 
{
	CString temp;
	CFileDialog dlg(FALSE, "mot", NULL, OFN_HIDEREADONLY,
		"Data File (*.mot)|*.mot|All Files (*.*)|*.*||");
	
	if(dlg.DoModal() == IDOK)
	{
		temp = dlg.GetPathName();
		LPTSTR nFilename = temp.GetBuffer(0);
		if (AXT_RT_SUCCESS != AxmMotSaveParaAll(nFilename))
			AfxMessageBox( "File save fail!");
		temp.ReleaseBuffer();	
	}				
}

// Signal Search running thread part
UINT SearchThread(LPVOID pFuncData)
{
	BOOL	bError;
	
	DWORD   dwEdge;
	DWORD   dwBusyStatus;
	DWORD   dwEndStatus;
	char	szSignalMethod[30];	
	CString strLog;

	CCAMC_QIDlg		*pQI = (CCAMC_QIDlg *)pFuncData;
	long lCurSel = pQI->m_cboAxisSet.GetCurSel();

	short nDir, nSignal, nStopM;
	double dVelocity, dAccel;

	//nDir		= pQI->m_cboDirection	.GetCurSel();
	/*if(pQI->m_cboDetect.GetCurSel() < 2)
		nSignal = pQI->m_cboDetect.GetCurSel();
	else if(pQI->m_cboDetect.GetCurSel() > 1 && pQI->m_cboDetect.GetCurSel() < 6)
		nSignal = pQI->m_cboDetect.GetCurSel() + 2;
	else
		nSignal = pQI->m_cboDetect.GetCurSel() - 2;

	dwEdge		= pQI->m_cboDetect		.GetCurSel()/6;*/
	//nStopM		= pQI->m_cboStopM		.GetCurSel();
	dVelocity	= pQI->GetDlgItemDouble(IDC_EDT_VELOCITY);
	dAccel		= pQI->GetDlgItemDouble(IDC_EDT_ACCEL);

	bError	= FALSE;

	// Re-setup of the maximum value in chart for displaying running speed of each axis on the chart.
	pQI->SetGraphRange(lCurSel, dVelocity);

	AxmStatusReadStop(lCurSel, &dwEndStatus);
	if(0 == nSignal) // Positive End Limit.
		AxmSignalSetLimit(lCurSel, EMERGENCY_STOP, UNUSED, USED);
	else if(1 == nSignal) // Negative End Limit.
		AxmSignalSetLimit(lCurSel, EMERGENCY_STOP, USED, UNUSED);

	// Setup running direction (-) direction
	if(nDir == 1)	AxmMoveSignalSearch(lCurSel, -dVelocity, dAccel, nSignal, dwEdge, nStopM);
	else				AxmMoveSignalSearch(lCurSel, dVelocity, dAccel, nSignal, dwEdge, nStopM);

	// Standby until running is finished
	do{
		AxmStatusReadInMotion(lCurSel, &dwBusyStatus);
		Sleep(1);

	//	if(pQI->m_bTestActive[pQI->m_lAxis] == FALSE)	AxmMoveSStop(pQI->m_lAxis);
	}while(dwBusyStatus);
	// Check how running was stopped on certain condition by referring End Status Register. 

  	AxmStatusReadStop(lCurSel, &dwEndStatus);

	if(nSignal > 1)
	{
		if(0x0 == (dwEndStatus & 0x40000) )
		{
			strLog.Format("%d Axis Search failed.", lCurSel);
			pQI->m_lstLog.AddString(strLog);
		}
		else
		{
			//pQI->m_cboDetect.GetLBText(pQI->m_cboDetect.GetCurSel(), szSignalMethod);		
			strLog.Format("%d Axis %s search complete.", lCurSel, szSignalMethod);
			pQI->m_lstLog.AddString(strLog);
		}
	}
	else if(nSignal < 2)
	{
		if(dwEndStatus & 0x7FFF)
		{
			pQI->m_lstLog.AddString("Search failed.");
		}
		else
		{
			//pQI->m_cboDetect.GetLBText(pQI->m_cboDetect.GetCurSel(), szSignalMethod);		
			strLog.Format("%d Axis %s search complete.", lCurSel, szSignalMethod);
			pQI->m_lstLog.AddString(strLog);
		}
	}

	AxmSignalSetLimit(lCurSel, EMERGENCY_STOP, USED, USED);
	pQI->m_lstLog.SetCurSel(pQI->m_lstLog.GetCount() - 1);	
	pQI->m_bTestActive[lCurSel]	= FALSE;

	CloseHandle(pQI->m_hTestThread[lCurSel]);
	pQI->m_hTestThread[lCurSel]	= NULL;

	return 0;
}	

// Repeated running thread part
UINT RepeatThread(LPVOID pFuncData)
{
	double	dCurPos;
	DWORD	dwMode;
	DWORD	dwBusyStatus;
	
	CCAMC_QIDlg		*pQI = (CCAMC_QIDlg *)pFuncData;
	int nCurSel = pQI->m_cboAxisSet.GetCurSel();

	double dPosition, dVelocity, dAccel, dDecel;
	
	dPosition	= pQI->GetDlgItemDouble(IDC_EDT_POSITION);
	dVelocity	= fabs(pQI->GetDlgItemDouble(IDC_EDT_VELOCITY));
	dAccel		= fabs(pQI->GetDlgItemDouble(IDC_EDT_ACCEL));
	dDecel		= fabs(pQI->GetDlgItemDouble(IDC_EDT_DECEL));

	AxmStatusGetCmdPos(nCurSel, &dCurPos);
	AxmMotGetAbsRelMode(nCurSel, &dwMode);
	
	// Re-setup of the maximum value in chart for displaying running speed of each axis on the chart.
	pQI->SetGraphRange(nCurSel, dVelocity);
	while(pQI->m_bTestActive[nCurSel])
	{
		AxmMoveStartPos(nCurSel, dPosition, dVelocity, dAccel, dAccel);
		do{
			AxmStatusReadInMotion(nCurSel, &dwBusyStatus);
			Sleep(1);
		}while((pQI->m_bTestActive[nCurSel]) && dwBusyStatus);
		if(!pQI->m_bTestActive[nCurSel])
			break;

		if(dwMode == POS_ABS_MODE)
		{
			if(dCurPos == dPosition)	break;

			AxmMoveStartPos(nCurSel, dCurPos, dVelocity, dAccel, dAccel);
		}else
		{
			if(0 == dPosition)		break;
			AxmMoveStartPos(nCurSel, -dPosition, dVelocity, dAccel, dAccel);
		}

		do{
			AxmStatusReadInMotion(nCurSel, &dwBusyStatus);
			Sleep(1);
		}while((pQI->m_bTestActive[nCurSel]) && dwBusyStatus);
		
	}
	pQI->m_bTestActive[nCurSel]	= FALSE;
	CloseHandle(pQI->m_hTestThread[nCurSel]);
	pQI->m_hTestThread[nCurSel]	= NULL;
	return 0;
}

CString	g_strData;
BOOL CCAMC_QIDlg::ThreadData()
{
	long	lAxisNo;
	DWORD	dwFlag=0;	
	DWORD	IntBank0, IntBank1;

	lAxisNo = m_lAxis;
	while(m_bThread[lAxisNo])
	{
		if (WaitForSingleObject(m_hInterrupt[lAxisNo], INFINITE) == WAIT_OBJECT_0)
		{
            AxmInterruptReadAxisFlag(lAxisNo, 0, &IntBank0);
        	AxmInterruptReadAxisFlag(lAxisNo, 1, &IntBank1);
			
			g_nIntCnt++;
			g_strData.Format("Event[%02d]Axis[%02d]Flag[0x%02X,0x%02X]", g_nIntCnt, lAxisNo, IntBank0, IntBank1);
			m_lstLog.AddString(g_strData);
		}
	}

	return TRUE;
}

void CCAMC_QIDlg::OnDblclkLstLog() 
{
	m_lstLog.ResetContent();	
}

//void CCAMC_QIDlg::OnBtnReadCapture() 
//{
//	double	dCapPos =0.0;
//	CString strData;
//
//	AxmMoveGetCapturePos(m_lAxis, &dCapPos);
//	strData.Format("%lf", dCapPos);
//	SetDlgItemText(IDC_STC_CAPTURE_POS, strData);	
//}

void CCAMC_QIDlg::OnBtn3dgraph() 
{
	if(m_b3DGraph)
	{
		if (m_pGL3DGraph == NULL)
		{
			m_pGL3DGraph = new GL3DGraph(this, m_lAxis);
			m_pGL3DGraph->Create(IDD_3DGRAPH, GetDesktopWindow());
		}
		m_b3DGraph = TRUE;
		m_pGL3DGraph->UpdateAxis(m_lAxis);	
		m_pGL3DGraph->ShowWindow(SW_SHOW);	
		m_pGL3DGraph->SetFocus();
	}
	else
	{
		m_pGL3DGraph = FALSE;
		m_pGL3DGraph->ShowWindow(SW_HIDE);
	}			
}

//void CCAMC_QIDlg::OnChkGantrySlave() 
//{
//	CString str;
//
//	if (m_chkGantrySlave.GetCheck() == 0)
//	{
//		str.Format("Do not Search");
//	}
//	else if (m_chkGantrySlave.GetCheck() == 1)
//	{
//		str.Format("Do origin revision after Search");
//	}
//	else if (m_chkGantrySlave.GetCheck() == 2)
//	{
//		str.Format("Do not origin revision after Search");
//	}
//	m_chkGantrySlave.SetWindowText(str);	
//}

void CCAMC_QIDlg::OnBnClickedBtnLoadgcode()
{
	int iRet;
	CFileDialog l_fDlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, "Text Files (*.txt)|*.txt|Comma Separated Values(*.csv)|*.csv||");
	iRet = l_fDlg.DoModal();
    l_strFileName = l_fDlg.GetPathName();
	m_lstLoggcode.ResetContent();
    if(iRet == IDOK) {
        try 
        {
            CStdioFile file(_T(l_strFileName), CFile::modeRead);
            CString str,contentstr = _T("");

            while(file.ReadString(str))
            {
                contentstr += str;
                contentstr += _T("\n");
				m_lstLoggcode.AddString(str);
            }
        }
        catch(CException* e)
        {
            MessageBox(_T("Error"));
            e->Delete();
        }
    }
}

void CCAMC_QIDlg::OnBnClickedBtnStartgcode()
{
	//thread_post_product = AfxBeginThread(Mythread_post_product, this);
	DWORD code = AxlOpen(7);
	if (AxlIsOpened());

	CStdioFile file(_T(l_strFileName), CFile::modeRead);
	CString str, contentstr = _T("");
	CONFIG_RUN_LINE(x, y, z, a, b, f);
	AxmContiWriteClear(COORD_NO);
	AxmContiBeginNode(COORD_NO);
	while (file.ReadString(str))
	{
		

		contentstr += str;
		contentstr += _T("\n");
		char* c = str.GetBuffer(str.GetLength());
		dich_dong(c);
		// ///////////bật spindle///////////// 
		if (spindle == false)
		{
			SPINDLE_ON(spindle_speed);
			Sleep(1000);
			spindle = true;
		}
		//////////////////////////////////////
		// các lệnh tiến hành gia công
		if (check_run == true)
		{
			switch (g)
			{
			case 0:
				RUN_MAX_SPEED(x, y, z, a, b);

				break;
			case 1:
				RUN_LINE(x, y, z, a, b, f);
				break;
			case 2:
				if (cirle == true)
				{
					RUN_CW_1(x, y, z, r, f);

				}
				else
				{
					RUN_CW_2(x, y, z, i, j, f);

				}
				break;
			case 3:
				if (cirle == true)
				{
					RUN_CCW_3(x, y, z, r, f);

				}
				else
				{
					RUN_CCW_4(x, y, z, i, j, f);
				}
				break;
			}
		}
		/////////////////////////////////////////
	}
	AxmContiEndNode(COORD_NO);
	OnBtnContiStart();
	
}

void CCAMC_QIDlg::autostartgcode()
{
	thread_post_product = AfxBeginThread(Mythread_post_product, this);
	m_lstLoggcode.ResetContent();
	DWORD code = AxlOpen(7);
	if (AxlIsOpened());
	fstream newfile;
	newfile.open("C:/Users/Admin/Desktop/g_code_1.txt", ios::in);
	/*OnBtnContiLine();
	AxmContiStart(COORD_NO, 0, 0);*/
	if (newfile.is_open())
	{
		string tp;
		CONFIG_RUN_LINE(x, y, z, a, b, f);
		AxmContiBeginNode(COORD_NO);
		while (getline(newfile, tp))
		{
			char* c = const_cast<char*>(tp.c_str());
			dich_dong(c);
			m_lstLoggcode.AddString(c);
			if (spindle == false)
			{
				SPINDLE_ON(spindle_speed);
				Sleep(1000);
				spindle = true;
			}
			// các lệnh tiến hành gia công
			if (check_run == true)
			{
				switch (g)
				{
				case 0:
					RUN_MAX_SPEED(x, y, z, a, b);
					
					break;
				case 1:
					RUN_LINE(x, y, z, a, b, f);
					break;
				case 2:
					if (cirle == true)
					{ 
						RUN_CW_1(x, y, z, r, f);
						
					}	
					else
					{
						RUN_CW_2(x, y, z, i, j, f);
						
					}
					break;
				case 3:
					if (cirle == true)
					{
						RUN_CCW_3(x, y, z, r, f);
						
					}
					else
					{
						RUN_CCW_4(x, y, z, i, j, f);
					}
					break;
				}
			}
			//////////////////////////////////////
		}
		AxmContiEndNode(COORD_NO);
		OnBtnContiStart();
		newfile.close();
	}
}


////////////////////////////////// chuong trinh G CODE///////////////////////////////////
float CCAMC_QIDlg::value_block(char* line, uint8_t char_counter)
{
	bool check = true;
	uint8_t temp = char_counter;
	string fs;
	// tach chuỗi lấy số trị của G
	while (check == true)
	{
		fs = fs + line[temp];
		temp++;
		if ((int(line[temp]) >= 97 && int(line[temp]) <= 122) || (int(line[temp]) >= 65 && int(line[temp]) <= 90) || int(line[temp]) == 59 || temp == strlen(line))     // kiểm tra cuối line hoặc cuối block
			check = false;
	}
	float value = std::stof(fs);  // hàm chuyển string sang float
	return value;
}

void CCAMC_QIDlg::dich_dong(char *line)
{
	uint8_t char_counter = 0;
	char letter;
	while (line[char_counter] != 0)
	{
		letter = line[char_counter];
		char_counter++;
		switch (letter)
		{
		case 'N': case 'n':
			break;
		case 'M': case 'm':
			switch ((int)value_block(line, char_counter))
			{
			case 3:              // M03
				spindle = false;
				break;
			case 30:
				stop_code = true;
				break;
			}
			check_run = false;
			break;
		case 'S': case 's':
			spindle_speed = value_block(line, char_counter);
			check_run = false;
			break;
		case 'G': case 'g':
			switch ((int)value_block(line, char_counter))
			{
			case 0:              // G00 Chạy dao nhanh với tốc độ lớn nhất của bàn máy.
				g = 0;
				check_run = true;
				break;
			case 1:              // G01 Gia công theo đường thẳng.
				g = 1;
				check_run = true;
				break;
			case 2:              // G02 Gia công theo cung tròn thuận chiều kim đồng hồ.
				g = 2;
				check_run = true;
				break;
			case 3:              // G03 Gia công theo cung tròn ngược chiều kim đồng hồ.
				g = 3;
				check_run = true;
				break;
			case 20:			// G20 inch 
				don_vi = 7.874016 * 200;
				break;
			case 21:			//G21 mm
				don_vi = 200;
				break;
			case 90:			// G90 lập trình tuyêt đối
				SET_RELATY = false;
				break;
			case 91:			// G91 lập trình tương đối
				SET_RELATY = true;
				break;
			}
			break;
		case 'X': case 'x':
			x = value_block(line, char_counter)*don_vi;
			break;
		case 'Y': case 'y':
			y = value_block(line, char_counter)*don_vi;
			break;
		case 'Z':case 'z':
			z = value_block(line, char_counter)*don_vi;
			break;
		case 'A': case 'a':
			a = value_block(line, char_counter)*don_vi;
			break;
		case 'B': case 'b':
			b = value_block(line, char_counter)*don_vi;
			break;
		case 'I': case 'i':
			i = value_block(line, char_counter)*don_vi;
			break;
		case 'J': case 'j':
			j = value_block(line, char_counter)*don_vi;
			break;
		case 'F': case 'f':
			f = value_block(line, char_counter);
			break;
		case 'R': case 'r':
			cirle = true;
			r = value_block(line, char_counter)*don_vi;
			break;
		}
	}
}

void CCAMC_QIDlg::RUN_MAX_SPEED(float x, float y, float z, float a, float b)
{
	RUN_LINE(x, y, z, a, b, 5000);
}

void CCAMC_QIDlg::CONFIG_RUN_LINE(float x, float y, float z, float a, float b, float f)
{
	long lCoordinate = 0;
	long lAxis2[3];
	long lPosSize = 3;
	/*lAxis2[0] = AXIS_N04(m_lAxis, 0);
	lAxis2[1] = AXIS_N04(m_lAxis, 2);
	lAxis2[2] = AXIS_N04(m_lAxis, 3);
	lAxis1[0] = AXIS_N04(m_lAxis, 2);
	lAxis1[1] = AXIS_N04(m_lAxis, 3);*/

	lAxis2[0] = AXIS_N04(m_lAxis, 0);
	lAxis2[1] = AXIS_N04(m_lAxis, 1);
	lAxis2[2] = AXIS_N04(m_lAxis, 2);
	lAxis1[0] = AXIS_N04(m_lAxis, 0);
	lAxis1[1] = AXIS_N04(m_lAxis, 1);
	double dVelocity, dAccel, dDecel;
	dVelocity = f;
	dAccel =50000;
	dDecel = 50000;

	for (int i = 0; i < 3; i++)
	{
		AxmMotSetPulseOutMethod(lAxis2[i], OneHighLowHigh);
		AxmMotSetProfileMode(lAxis2[i], 4);
	}

	SetGraphRange(lAxis2[3], f);
	SetGraphRange(lAxis2[2], f);
	AxmContiWriteClear(COORD_NO);
	AxmContiSetAxisMap(COORD_NO, lPosSize, lAxis2);
	if (SET_RELATY == true)
		AxmContiSetAbsRelMode(COORD_NO, 1);			// 1: chạy tương đối
	else
		AxmContiSetAbsRelMode(COORD_NO, 0);			// 0: chạy tuyệt đối
}


void CCAMC_QIDlg::RUN_LINE(float x, float y, float z, float a, float b, float f)
{
	//double dPlace[3] = { static_cast<double>(z), static_cast<double>(y), static_cast<double>(x) };
	double dPlace[3] = { static_cast<double>(x), static_cast<double>(y), static_cast<double>(z) };
	if (SET_RELATY == true)
		AxmContiSetAbsRelMode(COORD_NO, 1);			// 1: chạy tương đối
	else
		AxmContiSetAbsRelMode(COORD_NO, 0);			// 0: chạy tuyệt đối
	AxmLineMove(COORD_NO, dPlace, f, 50000, 50000);	
	//axmline = AxmLineMove(COORD_NO, dPlace, f, 50000, 50000);
}

void CCAMC_QIDlg::RUN_CW(float x, float y, float r, DWORD dir, float f)
{
	double lPosSize1 = 2;
	double dRadius = r;
	//double dEndPos[2] = { static_cast<double>(y),static_cast<double>(x) };
	double dEndPos[2] = { static_cast<double>(x),static_cast<double>(y) };
	double dCenPos[2];
	DWORD uCWDir = dir;                  // [0] Cw direction, [1] Ccw direction 
	DWORD uShortDistance = 0;        // [0]: small(circular)distance,[1] big(circular)distance  
	if (SET_RELATY == true)
		AxmContiSetAbsRelMode(COORD_NO, 1);			// 1: chạy tương đối
	else
		AxmContiSetAbsRelMode(COORD_NO, 0);			// 0: chạy tuyệt đối
	AxmCircleRadiusMove(COORD_NO, lAxis1, dRadius, dEndPos, f, 50000, 50000, uCWDir, uShortDistance);
	axmline = AxmCircleRadiusMove(COORD_NO, lAxis1, dRadius, dEndPos, f, 50000, 50000, uCWDir, uShortDistance);
}
void CCAMC_QIDlg::RUN_CW_1(float x, float y, float z, float r, float f)
{
	/*if (z == 0)
		RUN_CW(x, y, r, (DWORD)0, f);
	if (x == 0)
		RUN_CW(y, z, r, (DWORD)0, f);
	if (y == 0)
		RUN_CW(x, z, r, (DWORD)0, f);*/
	RUN_CW(x, y, r, (DWORD)1, f);
}

void CCAMC_QIDlg::RUN_CW_2(float x, float y, float z, float i, float j, float f)
{
	float bk = sqrt(i * i + j * j);
	RUN_CW(x, y, bk, (DWORD)1, f);
	/*if (z == 0)
		RUN_CW(x, y, bk, (DWORD)0, f);
	if (x == 0)
		RUN_CW(y, z, bk, (DWORD)0, f);
	if (y == 0)
		RUN_CW(x, z, bk, (DWORD)0, f);*/
}
void CCAMC_QIDlg::RUN_CCW_3(float x, float y, float z, float r, float f)
{/*
	if (z == 0)
		RUN_CW(x, y, r, (DWORD)1, f);
	if (x == 0)
		RUN_CW(y, z, r, (DWORD)1, f);
	if (y == 0)
		RUN_CW(x, z, r, (DWORD)1, f);*/
	RUN_CW(x, y, r, (DWORD)0, f);
}

void CCAMC_QIDlg::RUN_CCW_4(float x, float y, float z, float i, float j, float f)
{
	float bk = sqrt(i * i + j * j);
	RUN_CW(x, y, bk, (DWORD)0, f);
	/*if (z == 0)
		RUN_CW(x, y, bk, (DWORD)1, f);
	if (x == 0)
		RUN_CW(y, z, bk, (DWORD)1, f);
	if (y == 0)
		RUN_CW(x, z, bk, (DWORD)1, f);*/
}


void CCAMC_QIDlg::SPINDLE_ON(float spindle_speed)
{
	SetDlgItemDouble(IDC_EDT_XCEN, spindle_speed);
	OnBnClickedBtnSetSpd();
	Sleep(1000);
	OnBnClickedBtnSpl();
	Sleep(2000);
}
///////////////////////////////////////////////////////////////////////////////////

void CCAMC_QIDlg::OnBnClickedBtnSpl()
{
	HANDLE hSerial;
	hSerial = CreateFile(_T("COM3"), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
	}
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hSerial, &timeouts)) {
	}
	char* szBuff;
	if (spindle == false)
	{
		szBuff = "off";
		spindle = true;
	}
	else
	{
		szBuff = "on";
		spindle = false;
	}
	DWORD dwBytesRead = 0;
	//m_lstLog.AddString(szBuff);
	WriteFile(hSerial, szBuff, 4, &dwBytesRead, NULL);
	CloseHandle(hSerial);
}


void CCAMC_QIDlg::OnBnClickedBtnSetSpd()
{
	double spl_speed = GetDlgItemDouble(IDC_EDT_XCEN);
	string test = std::to_string(spl_speed);
	char* c = const_cast<char*>(test.c_str());
	m_lstLog.AddString(c);


	HANDLE hSerial;
	hSerial = CreateFile(_T("COM3"), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
	}
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hSerial, &timeouts)) {
	}

	DWORD dwBytesRead = 0;
	WriteFile(hSerial, c, 4, &dwBytesRead, NULL);
	CloseHandle(hSerial);
}


void CCAMC_QIDlg::OnBnClickedBtnCntIot()
{

	connect_iot = true;
	m_lstLog.AddString("Connecting ...");
	/*thread_get = AfxBeginThread(Mythread_iot_connect_get, this);
	thread_post = AfxBeginThread(Mythread_iot_connect_post, this);
	thread_data_post = AfxBeginThread(Mythread_iot_data_post, this);
	thread_data_get = AfxBeginThread(Mythread_iot_data_get, this);*/
}



size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

size_t WriteCallback2(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

UINT Mythread_iot_connect_get(LPVOID Pram)
{
	
	CCAMC_QIDlg* ptr = (CCAMC_QIDlg*)Pram;
	//ptr->number = 0;
	while (true)
	{
		CURL *curl100;
		CURLcode res;
		string readBuffer;
		if (connect_iot == true && internet_connect == true)
		{
			curl100 = curl_easy_init();
			if (curl100) {

				curl_easy_setopt(curl100, CURLOPT_URL, "https://j3o7u7tdak.execute-api.ap-southeast-1.amazonaws.com/v1/connect");
				curl_easy_setopt(curl100, CURLOPT_WRITEFUNCTION, WriteCallback);
				curl_easy_setopt(curl100, CURLOPT_WRITEDATA, &readBuffer);
				res = curl_easy_perform(curl100);
				curl_easy_cleanup(curl100);
				const char *cstr = readBuffer.c_str();
				mess_time_pas = mess_time;
				mess = "";
				
				for (int i = 84; i < 100; i++)
				{
					if (cstr[i] != '\\')
						mess = mess + cstr[i];
					else
						i = 100;
				}
				// tach time
				//ptr->m_lstLog.AddString(status.c_str());

				auto json = nlohmann::json::parse(cstr);
				if (dem_str == 50) dem_str = 1;
				str_time[dem_str] = json["LastEvaluatedKey"]["time"]["S"];
				mess_time = str_time[dem_str];
				dem_str++;
				rece = true;
			}
		}
	}
	return 0;
	
}


UINT Mythread_iot_connect_post(LPVOID Pram)
{
	CCAMC_QIDlg* ptr = (CCAMC_QIDlg*)Pram;
	
	while (TRUE)
	{
		CURL *curl1;
		CURLcode res1;
		//CURL *curl2;
		//CURL *curl3;
		if (internet_connect == true)
		{
			if ((connect_iot == true) && (mess != "CONNECT"))
			{
				str_post = "{\"MES\" :\"ALLOW CONNECT\"}";
				curl1 = curl_easy_init();
				if (curl1) {
					curl_easy_setopt(curl1, CURLOPT_URL, "https://5s8kziy1vk.execute-api.ap-southeast-1.amazonaws.com/v1/connect");
					curl_easy_setopt(curl1, CURLOPT_POSTFIELDS, str_post.c_str());
					res1 = curl_easy_perform(curl1);
					curl_easy_cleanup(curl1);
				}
			}
			if (connect_iot == false)
			{

				str_post = "{\"MES\" :\"NOT ALLOW CONNECT\"}";
				curl1 = curl_easy_init();
				if (curl1) {
					curl_easy_setopt(curl1, CURLOPT_URL, "https://5s8kziy1vk.execute-api.ap-southeast-1.amazonaws.com/v1/connect");
					curl_easy_setopt(curl1, CURLOPT_POSTFIELDS, str_post.c_str());
					res1 = curl_easy_perform(curl1);
					curl_easy_cleanup(curl1);
				}
			}

			if ((mess == "CONNECT") && (connect_iot == true))
			{
				connect_sucess = true;
				str_post = "{\"MES\" :\"CONNECT SUCCESFULLY\"}";
				curl1 = curl_easy_init();
				if (curl1) {
					curl_easy_setopt(curl1, CURLOPT_URL, "https://5s8kziy1vk.execute-api.ap-southeast-1.amazonaws.com/v1/connect");
					curl_easy_setopt(curl1, CURLOPT_POSTFIELDS, str_post.c_str());
					res1 = curl_easy_perform(curl1);
					curl_easy_cleanup(curl1);
				}
			}
			/*if ((disconnect == true) && (connect_iot == true))
			{
				CURL *curl3;
				CURLcode res;
				connect_sucess = true;
				str_post = "{\"MES\" :\"CONNECT LOST\"}";
				curl3 = curl_easy_init();
				if (curl3) {
					curl_easy_setopt(curl3, CURLOPT_URL, "https://fo87n46x8c.execute-api.ap-southeast-1.amazonaws.com/test/post");
					curl_easy_setopt(curl3, CURLOPT_POSTFIELDS, str_post.c_str());
					res = curl_easy_perform(curl3);
					curl_easy_cleanup(curl3);
				}
			}*/
		}
		
	}
		
	return 0;
}



UINT Mythread_iot_data_post(LPVOID Pram)
{
	CCAMC_QIDlg* ptr = (CCAMC_QIDlg*)Pram;
	double dCurVelX, dCurVelY, dCurVelZ, dCurVelA, dCurVelB;
	double  dCmdPos[4] = { 0 }, dActPos[4] = { 0 }, dpCapPotition;
	string sp_status, pos_status, vel_status, name, id;
	while (true)
	{
		if (mess == "CONNECT")
		{
			AxmStatusGetCmdPos(0, &dCmdPos[0]);
			AxmStatusGetCmdPos(1, &dCmdPos[1]);
			AxmStatusGetCmdPos(2, &dCmdPos[2]);
			AxmStatusGetCmdPos(4, &dCmdPos[3]);
			AxmStatusGetCmdPos(5, &dCmdPos[4]);

			AxmStatusReadVel(0, &dCurVelX);
			AxmStatusReadVel(1, &dCurVelY);
			AxmStatusReadVel(2, &dCurVelZ);
			AxmStatusReadVel(4, &dCurVelA);
			AxmStatusReadVel(5, &dCurVelB);

			double spl_speed = ptr->GetDlgItemDouble(IDC_EDT_XCEN);

			name = "\"Machine\" : \"CNC MACHINE TechK\"";
			id = "\"id\" : \"1\"";
			pos_status = "\"X\" :\"" + to_string(dCmdPos[0] / 200) + "\"," "\"Y\" :\"" + to_string(dCmdPos[1] / 200) + "\"," + "\"Z\" :\"" + to_string(dCmdPos[2] / 200) + "\"," + "\"A\" :\"" + to_string(dCmdPos[3] / 200) + "\"," + "\"B\" :\"" + to_string(dCmdPos[4] / 200);
			vel_status = "\"VelX\" :\"" + to_string(dCurVelX) + "\"," + "\"VelY\" :\"" + to_string(dCurVelY) + "\"," + "\"VelZ\" :\"" + to_string(dCurVelZ) + "\"," + "\"VelA\" :\"" + to_string(dCurVelA) + "\"," + "\"VelB\" :\"" + to_string(dCurVelB);
			if (spindle == true)
			{
				sp_status = "\"SPINDLE\" : \"ON\", \"speed\" : \"" + to_string(spl_speed) + "\"";
			}
			else
			{
				sp_status = "\"SPINDLE\" : \"OFF\"";
			}
			CURL *curl2;
			CURLcode res2;
			
			str_post_2 = "{"+ pos_status + "\"," + vel_status + "\"," + sp_status +"}";
			curl2 = curl_easy_init();
			if (curl2) {
				curl_easy_setopt(curl2, CURLOPT_URL, "https://n3jxc9bfzg.execute-api.ap-southeast-1.amazonaws.com/v1/data");
				curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, (str_post_2).c_str());
				res2 = curl_easy_perform(curl2);
				curl_easy_cleanup(curl2);
			}
		}
	}
	return 0;
}

UINT Mythread_post_product(LPVOID Pram)
{
	//CCAMC_QIDlg* ptr = (CCAMC_QIDlg*)Pram;


	string str_product = "{\"id\" : \"1\"}";
	/*while (true)
	{*/
		CURL *curl_product;
		CURLcode res_product;
		curl_product = curl_easy_init();
		if (curl_product) {
			curl_easy_setopt(curl_product, CURLOPT_URL, "https://h4txkiq5k8.execute-api.ap-southeast-1.amazonaws.com/v1/product");
			curl_easy_setopt(curl_product, CURLOPT_POSTFIELDS, str_product.c_str());
			res_product = curl_easy_perform(curl_product);
			curl_easy_cleanup(curl_product);
		}
	//}
	return 0;
}



void CCAMC_QIDlg::OnBnClickedBtnDiscntIot()
{
	CString	strData;

	DWORD   wMechanicalStatus = 0;

	lsByte  bMechanic;


	connect_iot = false;
	AxmStatusReadMechanical(m_lAxis, &wMechanicalStatus);
	bMechanic.wWord = (WORD)wMechanicalStatus;
	m_ledPelm.SetStatus(bMechanic.wbit.b0);
	m_lstLog.AddString("Disconnect Successfully");
	mess_pas = "";
	mess_time_pas = "";
}

UINT Mythread_iot_data_get(LPVOID Pram)
{
	CCAMC_QIDlg* ptr = (CCAMC_QIDlg*)Pram;
	while (true)
	{
		if (connect_sucess == true)
		{
			CURL *curl0;
			CURLcode res;
			std::string readBuffer0;
			curl0 = curl_easy_init();
			if (curl0) {
				curl_easy_setopt(curl0, CURLOPT_URL, "https://f5y4tjriah.execute-api.ap-southeast-1.amazonaws.com/v1/data");
				curl_easy_setopt(curl0, CURLOPT_WRITEFUNCTION, WriteCallback2);
				curl_easy_setopt(curl0, CURLOPT_WRITEDATA, &readBuffer0);
				res = curl_easy_perform(curl0);
				curl_easy_cleanup(curl0);
				const char *cstr0 = readBuffer0.c_str();
				//ptr->m_lstLog2.AddString(readBuffer0.c_str());
				mess_data_pas = "";
				mess_data_pas = mess_data;
				mess_data = "";

				for (int i = 84; i < 100; i++)
				{
					if (cstr0[i] != '\\')
						mess_data = mess_data + cstr0[i];
					else
						i = 100;
				}
				rece1 = true;
			}
		}
		
	}
	return 0;
}

UINT Mythread_check_connect(LPVOID Pram)
{
	//CCAMC_QIDlg* ptr_check = (CCAMC_QIDlg*)Pram;
	internet_connect = true;
	
	/*while (true)
	{
		CURL *curl_check;
		CURLcode res_check;
		curl_check = curl_easy_init();
		if (curl_check) {

			curl_easy_setopt(curl_check, CURLOPT_URL, "https://2av14g0fv2.execute-api.ap-southeast-1.amazonaws.com/v1/v1");
			res_check = curl_easy_perform(curl_check);
			if (res_check != CURLE_OK)
			{
				curl_easy_setopt(curl_check, CURLOPT_URL, "https://2av14g0fv2.execute-api.ap-southeast-1.amazonaws.com/v1/v1");
				res_check = curl_easy_perform(curl_check);
				if (res_check != CURLE_OK)
				{				
					internet_connect = false;
				}	
			}
			else
			{
				internet_connect = true;
			}
			curl_easy_cleanup(curl_check);
		}
	}*/
	return 0;
}
void CCAMC_QIDlg::Spindle_Run(float spindle_speed)
{
	SetDlgItemDouble(IDC_EDT_XCEN, spindle_speed);
	clickonsetspindle();
	Sleep(1000);
	clickonspindle();
	Sleep(2000);
	
}
void CCAMC_QIDlg::clickonsetspindle()
{
	double spl_speed = GetDlgItemDouble(IDC_EDT_XCEN);
	string test = std::to_string(spl_speed);
	char* c = const_cast<char*>(test.c_str());
	m_lstLog.AddString(c);


	HANDLE hSerial;
	hSerial = CreateFile(_T("COM3"), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
	}
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hSerial, &timeouts)) {
	}

	DWORD dwBytesRead = 0;
	WriteFile(hSerial, c, 4, &dwBytesRead, NULL);
	CloseHandle(hSerial);
	
}
void CCAMC_QIDlg::clickonspindle()
{
	HANDLE hSerial;
	hSerial = CreateFile(_T("COM3"), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
	}
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hSerial, &timeouts)) {
	}
	char* szBuff;
	if (spindle == false)
	{
		szBuff = "off";
		spindle = true;
	}
	else
	{
		szBuff = "on";
		spindle = false;
	}
	DWORD dwBytesRead = 0;
	//m_lstLog.AddString(szBuff);
	WriteFile(hSerial, szBuff, 4, &dwBytesRead, NULL);
	CloseHandle(hSerial);
	

}
 //Tach chuoi
//void  CCAMC_QIDlg::Tachchuoi(char chuoi,double Xcnc,double Ycnc, double Zcnc,double M)
//{
//	char X1[30], Y1[30], Z1[30], M1[30];
//	int count = 0,dem3 = 0;
//	for (int i = 0; i < 30; i++)
//	{
//		if (buf[i] == ' ')
//		{
//			count = count + 1;
//			dem3 = i + 1;
//
//		}
//		else {
//			if (count == 0)
//			{
//				X1[i] = buf[i];
//			}
//			if (count == 1)
//			{
//				Z1[i - dem3] = buf[i];
//			}
//			if (count == 2)
//			{
//				Y1[i - dem3] = buf[i];
//			}
//			if (count == 3)
//			{
//				M1[i - dem3] = buf[i];
//			}
//		}
//
//
//	}
//	count = 0;
//	dem3 = 0;
//	double X = atof(X1);
//	double Y = atof(Y1);
//	double Z = atof(Z1);
//	double M = atof(M1);
//
//	double Xcnc = ((-2000.0 - X)*(600.0 / 700.0) * 200.0);
//	double Ycnc = ((-650.0 - Y)*(550.0 / 650.0) * 200.0);
//	double Zcnc = ((Z + 1250.0) * 200.0);
//	//double a = (M);
//	//double* tro1 = &Xcnc;
//	m_lstLog.AddString("Xin chao");
//}

void  CCAMC_QIDlg::CONFIG_RUN_LINE_TCPIP( float vel)
{
	
	long lCoordinate = 0;
	long lAxis2[3];
	long lAxis1[2];
	long lPosSize = 3;
	lAxis2[0] = AXIS_N04(m_lAxis, 0);
	lAxis2[1] = AXIS_N04(m_lAxis, 1);
	lAxis2[2] = AXIS_N04(m_lAxis, 2);
	double dVelocity, dAccel, dDecel;
	dVelocity = vel;
	dAccel = 30000;
	dDecel = 30000;

	for (int i = 0; i < 3; i++)
	{
		AxmMotSetPulseOutMethod(lAxis2[i], OneHighLowHigh);
		AxmMotSetProfileMode(lAxis2[i], 4);
	}

	SetGraphRange(lAxis2[3], vel);
	SetGraphRange(lAxis2[2], vel);
	AxmContiWriteClear(COORD_NO);
	AxmContiSetAxisMap(COORD_NO, lPosSize, lAxis2);
	//if (SET_RELATY == true)
	//	AxmContiSetAbsRelMode(COORD_NO, 1);			// 1: chạy tương đối
	//else
	//	AxmContiSetAbsRelMode(COORD_NO, 0);			// 0: chạy tuyệt đối
	AxmContiSetAbsRelMode(COORD_NO, 0);
	//m_Mutex.Unlock();
}
void CCAMC_QIDlg::RUN_LINE_TCPIP(float x, float y, float z, float a, float b, float vel)
{
	//CMutex m_Mutex;
	//m_Mutex.Lock();
	//GetTimeData();
	//getCurrentTime();
	double dPlace[3] = { x, y, z };
	//m_Mutex.Lock(AxmLineMove(COORD_NO, dPlace, 2000, 30000, 30000));
	//double dPlace[3] = { z, y, x };
	AxmLineMove(COORD_NO, dPlace, vel, 30000, 30000);
	//getCurrentTime();
	m_lstLog.AddString("Hello");
	//GetTimeData();
	//m_Mutex.Unlock();
	
}
void CCAMC_QIDlg::OnBnClickedBtnTcpIp()
{
	thread_TCP_IP = AfxBeginThread(Mythread_TCP_IP, this);
	counterall = true;
}

string CCAMC_QIDlg::convertToString(float f1, float f2,float f3,float f4)
{
	stringstream ss;
	ss<<f1<<" "<<f2<<" "<<f3<<" "<<f4 ;
	return ss.str();
}
void CCAMC_QIDlg::Eto_up()
{
	HANDLE hSerial;
	hSerial = CreateFile(_T("COM3"), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
	}
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hSerial, &timeouts)) {
	}
	char* szBuff;
	szBuff = "Up";
	DWORD dwBytesRead = 0;
	//m_lstLog.AddString(szBuff);
	WriteFile(hSerial, szBuff, 6, &dwBytesRead, NULL);
	CloseHandle(hSerial);
}
void CCAMC_QIDlg::Eto_stop()
{
	HANDLE hSerial;
	hSerial = CreateFile(_T("COM3"), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
	}
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hSerial, &timeouts)) {
	}
	char* szBuff;
	szBuff ="Stop";
	DWORD dwBytesRead = 0;
	//m_lstLog.AddString(szBuff);
	WriteFile(hSerial, szBuff, 6, &dwBytesRead, NULL);
	CloseHandle(hSerial);
}
void CCAMC_QIDlg::Eto_back()
{
	HANDLE hSerial;
	hSerial = CreateFile(_T("COM3"), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
	}
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hSerial, &timeouts)) {
	}
	char* szBuff;
	szBuff = "Back";
	DWORD dwBytesRead = 0;
	//m_lstLog.AddString(szBuff);
	WriteFile(hSerial, szBuff, 6, &dwBytesRead, NULL);
	CloseHandle(hSerial);
}
void  CCAMC_QIDlg::GetTimeData()
{
	// Lấy thời gian hiện tại
	CTime currentTime = CTime::GetCurrentTime();

	// Chuyển đổi thời gian sang chuỗi
	CString timeString = currentTime.Format(_T("%Y-%m-%d %H:%M:%S"));

	// Ghi giá trị thời gian vào file
	CStdioFile file;
	if (file.Open(_T("C:\\Users\\Admin\\Desktop\\Timesends.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		// Di chuyển con trỏ đến cuối file
		file.SeekToEnd();

		// Ghi giá trị thời gian vào file
		file.WriteString(timeString);
		file.WriteString(_T("\n"));

		// Đóng file
		file.Close();
	}
}
void CCAMC_QIDlg::getCurrentTime()
{
	// Lấy thời gian hiện tại của hệ thống với đơn vị thời gian là mili giây
	auto currentTime = time_point_cast<milliseconds>(system_clock::now());
	// Chuyển đổi sang dạng chuỗi thời gian chuẩn
	auto currentTimeMS = currentTime.time_since_epoch().count();
	time_t currentTimeSeconds = currentTimeMS / 1000;

	// Chuyển đổi sang dạng cấu trúc tm
	tm* localTime = localtime(&currentTimeSeconds);

	// Định dạng chuỗi thời gian theo định dạng giờ:phút:giây.mili giây
	char timeString[20];
	strftime(timeString, 20, "%H:%M:%S.", localTime);

	// Ghi thêm đơn vị mili giây vào chuỗi thời gian
	char msString[4];
	sprintf(msString, "%03d", static_cast<int>(currentTimeMS % 1000));
	strcat(timeString, msString);

	// Mở file để ghi kết quả
	ofstream outfile;
	outfile.open("C:\\Users\\Admin\\Desktop\\Time_nhan.txt", ios::app);
	if (outfile.is_open()) {
		// In ra chuỗi thời gian vào file
		outfile << "Current time: " << timeString << endl;
		outfile.close(); // Đóng file sau khi ghi xong
	}
	else {
		//cerr << "Unable to open file!" << endl;
	}
}

//void CCAMC_QIDlg::GetActPos()
//{   
//	double Xact,Yact,Zact;
//	string strText;
//	long lAxis2[3];
//	long lPosSize = 3;
//	//long lAxis1[2];
//	lAxis2[0] = { 4 };
//	lAxis2[1] = { 6 };
//	lAxis2[2] = { 7 };
//
//	
//	AxmStatusGetActPos(lAxis2[0], &Xact);
//	AxmStatusGetActPos(lAxis2[1], &Yact);
//	AxmStatusGetActPos(lAxis2[2], &Zact);
//
//	
//	//strText= convertToString(Xact, Yact, Zact);
//	
//	
//}
UINT Mythread_TCP_IP(LPVOID Pram)
{    

	string m_sendserver;
	CCAMC_QIDlg* ptrtcp = (CCAMC_QIDlg*)Pram;
	
	
	//CEdit* ptrtcp1 = (CEdit*)GetDlgItem(HWND(1288),1288);
	//bool  counter11 = false;
	
	string tcpip;
	string server;
	

		string ipAddress = "192.168.1.3";            // IpAddress of the server 
		int port = 54000;                          //Listening port # on the server

		// Initialize Winsock
		WSAData data;
		WORD ver = MAKEWORD(2, 2);
		int wsResult = WSAStartup(ver, &data);
		if (wsResult != 0)
		{
			ptrtcp->m_lstLog.AddString(_T("Can't start Winsock"));
			return 0;
		}

		// create Socket
		SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET)
		{
			ptrtcp->m_lstLog.AddString(_T(" Can't Create Socket, Err #"));
			WSACleanup();
			return 0;
		}

		// Fill in structure
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	
		// Connect to Server
		int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
		
		if (connResult == SOCKET_ERROR)
		{
			ptrtcp->m_lstLog.AddString(_T("Can't connect Server, Err #"));
			closesocket(sock);
			WSACleanup();
			return 0;
		}
		ptrtcp->m_lstLog.AddString("Connected to Server");
		// Do while loop to send and receive data
		char buf[4096] ;
		string userInput;
		CString str2,str,str1;
		int count=0, dem3=0;
		char X1[30], Y1[30], Z1[30],M1[30];
		//double dPlace[3] = {};
		//bool counter = false;
		ptrtcp->CONFIG_RUN_LINE_TCPIP(5000);
		float k1, k2, k3;
		double a = 0;
		double Xactpul, Yactpul, Zactpul,Xcmdpul, Ycmdpul, Zcmdpul;
		double Xact, Yact, Zact;
		double Xcnc=0, Ycnc=0, Zcnc=0;
		double X, Y, Z, M;
		string strText;
		long lAxis2[3];
		long lPosSize = 3;
		//bool sendtopos = false;
		/*myfiledata0.open("C:\\Users\\Admin\\Desktop\\Data_Cmd_X.txt");
		myfiledata1.open("C:\\Users\\Admin\\Desktop\\Data_Act_X.txt");
		myfiledata2.open("C:\\Users\\Admin\\Desktop\\Data_Cmd_Y.txt");
		myfiledata3.open("C:\\Users\\Admin\\Desktop\\Data_Act_Y.txt");
		myfiledata4.open("C:\\Users\\Admin\\Desktop\\Data_Cmd_Z.txt");
		myfiledata5.open("C:\\Users\\Admin\\Desktop\\Data_Act_Z.txt");*/
		while (true)
			
		{ 
			
			
			// wait for response
			while (ptrtcp->counter11)
			{
				//ptrtcp->m_lstLog.AddString("helo");
				ZeroMemory(buf, 4096);

				 
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived == 0)
				{
					str2 = "Dont received";
					ptrtcp->m_lstLog.ResetContent();
					ptrtcp->m_lstLog.AddString(str2);
				}
				if (bytesReceived == -1)
				{
					str2 = 'b';
					ptrtcp->m_lstLog.ResetContent();
					ptrtcp->m_lstLog.AddString(str2);
				}
				//ptrtcp->getCurrentTime();
				if (bytesReceived > 0)
				{    
					//ptrtcp->GetTimeData();
					//ptrtcp->getCurrentTime();
					str2 = buf;
					ptrtcp->m_lstLog.ResetContent();
					ptrtcp->m_lstLog.AddString(str2);

					//Eto tien
					if (str2 == '1')
					{    
						ptrtcp->getCurrentTime();
						//ptrtcp->m_lstLog.AddString("Hi`");
						ptrtcp->Eto_up();
						break;
					}
					// Eto dung
					if (str2 == '2')
					{ 
						ptrtcp->getCurrentTime();
						//ptrtcp->m_lstLog.AddString("Hii");
						ptrtcp->Eto_stop();
						break;
					}
					// Eto lui
					if (str2 == '3')
					{   
						ptrtcp->getCurrentTime();
						ptrtcp->Eto_back();
						break;
					}

					if (str2 == '4')
					{   
						ptrtcp->getCurrentTime();
						//spindle = true;
						ptrtcp->Spindle_Run(100);
						spindle =true;
						break;
						
					}

					if (str2 == '5')
					{   
						ptrtcp->getCurrentTime();
						//spindle = false;
						ptrtcp->Spindle_Run(spindle_speed);
						spindle = false;
						break;
					}

					
					for (int i = 0; i < 30; i++)
					{
						if (buf[i] == ' ')
						{
							count = count + 1;
							dem3 = i + 1;

						}
						else {
							if (count == 0)
							{
								X1[i] = buf[i];
							}
							if (count == 1)
							{
								Z1[i - dem3] = buf[i];
							}
							if (count == 2)
							{
								Y1[i - dem3] = buf[i];
							}
							if (count == 3)
							{
								M1[i - dem3] = buf[i];
							}
						}


					}
					count = 0;
					dem3 = 0;
					double X = atof(X1);
					double Y = atof(Y1);
					double Z = atof(Z1);
					double M = atof(M1); 

					double Xcnc = ((-2000.0 - X)*(600.0 / 700.0) * 200.0);
					double Ycnc = ((-800.0 -Y)*(550.0 / 650.0) * 200.0);
					double Zcnc = ((Z + 1300.0) * 200.0);


					str.Format(_T("%0.f %0.f %0.f"), Xcnc / 200.0, Ycnc / 200.0, Zcnc / 200.0);
					ptrtcp->RUN_LINE_TCPIP(Xcnc, Ycnc, Zcnc, 0, 0, 5000);
					ptrtcp->m_lstLog.AddString(str);

				}
			}
					
					/*ptrtcp->GetActPos();
					ptrtcp->m_lstLog.AddString(strText);*/
				while (ptrtcp->sendtopos)
				{    
					/* 
					AxmStatusGetCmdPos(0, &Xcmdpul);
					AxmStatusGetCmdPos(1, &Ycmdpul);
					AxmStatusGetCmdPos(2, &Zcmdpul);*/
					//ptrtcp->m_lstLog.AddString("Hii");
					AxmStatusGetActPos(0, &Xactpul);
					AxmStatusGetActPos(1, &Yactpul); 
					AxmStatusGetActPos(2, &Zactpul);
					double Xact = round(-1900.0 +((Xactpul / 600.0)*(600.0 / 600.0)));
					double Yact = round(-800.0 + ((Yactpul / 600.0)*(650.0 / 550.0)));
					double Zact = round((Zactpul / 600.0) - 1300.0);
					strText = ptrtcp->convertToString(Xact, Yact, Zact, 0);//(-Xact/100.0, -Yact/100.0, -Zact/100.0,0);
					str1.Format(_T("%0.f %0.f %0.f "), Xact, Yact, Zact);
					ptrtcp->m_lstLog.ResetContent();
					ptrtcp->m_lstLog.AddString(str1);
					//Sleep(22.22);
					int sendtoserver = send(sock, strText.c_str(), strText.size() + 1, 0);

					
					
				/*	myfiledata0 << Xcmdpul << endl;
					myfiledata1 << Xactpul << endl;
					myfiledata2 << Ycmdpul << endl;
					myfiledata3 << Yactpul << endl;
					myfiledata4 << Zcmdpul << endl;
					myfiledata5 << Zactpul << endl;
					Sleep(1000);
					*/
					
					ptrtcp->GetTimeData();
					//ptrtcp->getCurrentTime();
				}
					
					////if (M != a) {

					//	if (M == 11 && spindle == true)
					//	{
					//		//ptrtcp->m_lstLog.AddString("HIIIII");
					//		
					//		ptrtcp->Spindle_Run(spindle_speed);
					//		//ptrtcp->counterall = false;
					//		//spindle = false;
					//		//ptrtcp->CONFIG_RUN_LINE_TCPIP(2000);
					//		//return true;
					//	}
					//	if (M == 2 && spindle ==false)
					//	{
					//		//ptrtcp->m_lstLog.AddString("HIIIII");
					//		
					//		ptrtcp->Spindle_Run(spindle_speed);

					//		spindle = true;
					//	 // return true;
					//	}
						

							

					//}
					
					//double a = M;
					//ptrtcp->CONFIG_RUN_LINE_TCPIP(2000);
					
					//ptrtcp->m_lstLog.AddString("HIIIII");
				//}

		


		}
	//	// Gracefull close down everything
		closesocket(sock);
		WSACleanup();	
		/*myfiledata0.close();
		myfiledata1.close();
		myfiledata2.close();
		myfiledata3.close();
		myfiledata4.close();
		myfiledata5.close();*/
		return 0;
}


void CCAMC_QIDlg::OnEnChangeEdit1()
{
	//thread_TCP_IP = AfxBeginThread(Mythread_TCP_IP, this);
}


void CCAMC_QIDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	  //counter = true;// nhap
	  sendtopos = true;
	//thread_TCP_IP = AfxBeginThread(Mythread_TCP_IP, this);

}


void CCAMC_QIDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	HANDLE hSerial;
	hSerial = CreateFile(_T("COM3"), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
	}
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hSerial, &timeouts)) {
	}
	char* szBuff;
	szBuff = "Stop";
	DWORD dwBytesRead = 0;
	//m_lstLog.AddString(szBuff);
	WriteFile(hSerial, szBuff, 6, &dwBytesRead, NULL);
	CloseHandle(hSerial);
}


void CCAMC_QIDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	counter11 = true;
	//thread_TCP_IP = AfxBeginThread(Mythread_TCP_IP, this);
}


void CCAMC_QIDlg::OnBnClickedButton4()
{ 
	HANDLE hSerial;
	hSerial = CreateFile(_T("COM3"), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
	}
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hSerial, &timeouts)) {
	}
	char* szBuff;
	szBuff = "Up";
	DWORD dwBytesRead = 0;
	//m_lstLog.AddString(szBuff);
	WriteFile(hSerial, szBuff, 6, &dwBytesRead, NULL);
	CloseHandle(hSerial);
	
	
}


void CCAMC_QIDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	counterrun = true;

}


void CCAMC_QIDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	HANDLE hSerial;
	hSerial = CreateFile(_T("COM3"), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		}
	}
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams)) {
	}
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 10;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hSerial, &timeouts)) {
	}
	char* szBuff;
	szBuff = "Back";
	DWORD dwBytesRead = 0;
	//m_lstLog.AddString(szBuff);
	WriteFile(hSerial, szBuff, 6, &dwBytesRead, NULL);
	CloseHandle(hSerial);
}
