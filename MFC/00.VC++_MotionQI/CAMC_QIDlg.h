// CAMC_QIDlg.h : header file
//
#if !defined(AFX_CAMC_QIDLG_H__0F7529AF_37FA_4FF6_9B77_4556650D3051__INCLUDED_)
#define AFX_CAMC_QIDLG_H__0F7529AF_37FA_4FF6_9B77_4556650D3051__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_AXIS_COUNT 64
#define CURL_STATICLIB


/////////////////////////////////////////////////////////////////////////////
// CCAMCIPDlg dialog
#include "stdafx.h"
#include <afxmt.h>
#include "CAMC_QIDlg.h"
#include "CSXButton.h"
#include "xShadeButton.h"
#include "OScopeCtrl.h"
#include "CSGraph.h"
#include "Led.h"
#include "EditEx.h"
#include "StautsView.h"
#include "ManualSet.h"
#include "GL3DGraph.h"


#include <Windows.h>
#include <iostream>
#include "math.h"
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <Windows.h>
#include <fstream>
#include <string>
#include <tchar.h>
#include <curl/curl.h>
using namespace std;


#define WM_CAMC_INTERRUPT				(WM_USER + 2009)

/////////////////////////////////////////////////////////////////////////////
// CCAMC_QIDlg dialog

UINT Mythread_iot_connect_get(LPVOID Pram);
UINT Mythread_iot_connect_post(LPVOID Pram);
UINT Mythread_iot_data_post(LPVOID Pram);
UINT Mythread_iot_data_get(LPVOID Pram);
UINT Mythread_check_connect(LPVOID Pram);
UINT Mythread_TCP_IP(LPVOID Pram);
UINT Mythread_post_product(LPVOID Pram);

class CCAMC_QIDlg : public CDialog
{
// Construction
public:
	CCAMC_QIDlg(CWnd* pParent = NULL);

public:
	BOOL			m_bStatus;
	BOOL			m_b3DGraph;
	BOOL			m_bManualSet;

	// Interrupt Event
	BOOL			m_bThread[MAX_AXIS_COUNT];
	HANDLE			m_hHandle[MAX_AXIS_COUNT];
	HANDLE			m_hInterrupt[MAX_AXIS_COUNT];

	long			m_lAxisCounts;
	BOOL			m_bTestActive[MAX_AXIS_COUNT];
	BOOL			m_bEstop, m_bContiFlag;

	long			m_lAxis;
	long			m_lRange;

	CCSGraph		m_XYGraph;
	COScopeCtrl		m_GraphX, m_GraphY;
	CFont			m_sFont, m_sFont1, m_sFont2;
	CString			m_strFont1, m_strFont2;	

	CEditEx			m_edtCmdPos[4], m_edtActPos[4], m_edtCmdVel[4];
	CEditEx			m_edtPosition, m_edtVelocity, m_edtAccel, m_edtDecel, m_edtspl;
	CEditEx			m_edtHomeVelFirst, m_edtHomeVelAfter, m_edtHomeVelAgain, m_edtHomeVelLast;

	CEditEx			m_edtSearchVelocity, m_edtSearchAccel;
	CEditEx			m_edtMoveUnit, m_edtStartSpeed;
	CEditEx			m_edtUnit, m_edtPulse;
	CEditEx			m_edtXend, m_edtYend, m_edtAngle;

	ManualSet		*m_pManualSet;
	HANDLE			m_hTestThread[MAX_AXIS_COUNT];									
	CStautsView		*m_pStatus;	
	GL3DGraph  		*m_pGL3DGraph;

	BOOL			m_bA4NAxis;

public:
	BOOL			InitLibrary();
	BOOL			ThreadData();
	BOOL			InitControl();
	
	void			SetCoordMovePara();
	void			UpdateAxisInfo();
	void			SetTitleBar(long axis);
	void Tachchuoi(char chuoi,double &Xcnc,double &Ycnc,double &Zcnc,double &M);
	void RUN_LINE_TCPIP(float x, float y, float z, float a, float b, float vel);
	void CONFIG_RUN_LINE_TCPIP( float vel);
	void Spindle_Run(float spindle_speed);
	void clickonspindle();
	void clickonsetspindle();
	void GetActPos();
	void GetTimeData();
	void getCurrentTime();
	void Eto_up();
	void Eto_stop();
	void Eto_back();
	ofstream myfiledata0;
	ofstream myfiledata1;
	ofstream myfiledata2;
	ofstream myfiledata3;
	ofstream myfiledata4;
	ofstream myfiledata5;

	BOOL			SetGraphRange(long nAxis, double dVelocity);

	double			GetDlgItemDouble(int nID);
	void			SetDlgItemDouble(int nID, double value, int nPoint = 3);
	string          convertToString(float f1, float f2,float f3,float f4);

	//ND EDit;

// Dialog Data
	//{{AFX_DATA(CCAMC_QIDlg)
	enum { IDD = IDD_CAMC_QI_DIALOG };
	CButton	m_btnTrigReset;
	CButton	m_btnTrigPeriod;
	CButton	m_btnTrigOneshot;
	CButton	m_btnTrigABS;
	CEdit	m_edtTrigCycle;
	CEdit	m_edtTrigEndPos;
	CEdit	m_edtTrigPulseWidth;
	CEdit	m_edtTrigStartPos;
	CButton	m_chkGearOnOff;
	CButton	m_chkXYsync;
	CButton	m_chkGantry;
	CLed	m_ledZphase;
	CComboBox	m_cboEncInputM;
	CButton	m_chkHomeLevel;
	CButton	m_chkScurve;
	CxShadeButton	m_btnJogPx;
	CxShadeButton	m_btnJogNx;
	CxShadeButton	m_btnJogPy;
	CxShadeButton	m_btnJogNy;
	CxShadeButton	m_btnJogPz;
	CxShadeButton	m_btnJogNz;
	CxShadeButton	m_btnJogPu;
	CxShadeButton	m_btnJogNu;
	CComboBox	m_cboDetect;
	CComboBox	m_cboDirection;
	CComboBox	m_cboStopM;
	CComboBox	m_cboPulseOutM;
	CComboBox	m_cboHomeSignal;
	CComboBox	m_cboHomeDir;
	CButton	m_chkRelative;
	CButton	m_chkPelmLevel;
	CButton	m_chkNelmLevel;
	CButton	m_chkInpLevel;
	CButton	m_chkCwCcw;
	CButton	m_chkGantrySlave;
	CButton	m_chkZphaseLevel;
	CButton	m_chkAsym;
	CButton	m_chkAlarmUse;
	CButton	m_chkAlarmLevel;
	CButton	m_chkAbsolute;
	CButton m_chkEmgLevel;

	CEdit m_sendserver;
	CComboBox	m_cboAxisSet;
	CSXButton	m_bthCircular;
	CSXButton	m_btnCountClr;
	CSXButton	m_btnEstop;
	CLed	m_ledAlarm;
	CLed	m_ledBusyY;
	CLed	m_ledBusyX;
	CLed	m_ledExmp;
	CLed	m_ledExpp;
	CListBox	m_lstLog, m_lstLoggcode, m_lstLog2;
	CLed	m_ledHome;
	CLed	m_ledPelm;
	CLed	m_ledOut5;
	CLed	m_ledOut4;
	CLed	m_ledOut3;
	CLed	m_ledOut2;
	CLed	m_ledOut1;
	CLed	m_ledOut0;
	CLed	m_ledNelm;
	CLed	m_ledInp;
	CLed	m_ledIn5;
	CLed	m_ledIn4;
	CLed	m_ledIn3;
	CLed	m_ledIn2;
	CLed	m_ledIn1;
	CLed	m_ledIn0;
	CLed	m_ledEmg;
	CSXButton	m_btnStop;
	CSXButton	m_btnStatus;
	CSXButton	m_btnRepeat;
	CSXButton	m_btnMove;
	CSXButton	m_btnLinear;
	CSXButton	m_btnHomeAll;
	CSXButton	m_btnHomeSingle;
	COScopeCtrl m_xaxisspd;
	COScopeCtrl m_yaxisspd;
	CSXButton	m_btnCrcOn;
	CSXButton	m_btnCrcOff;
	
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAMC_QIDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCAMC_QIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBtnHomeAll();
	afx_msg void OnBtnHomeSingle();
	afx_msg void OnBtnVelOverride();
	afx_msg void OnChkPelmLevel();
	afx_msg void OnChkNelmLevel();
	afx_msg void OnChkInpLevel();
	afx_msg void OnChkAlarmLevel();
	afx_msg void OnChkEmgLevel();
	afx_msg void OnLedOut0();
	afx_msg void OnLedOut1();
	afx_msg void OnLedOut2();
	afx_msg void OnLedOut3();
	afx_msg void OnLedOut4();
	afx_msg void OnLedOut5();
	afx_msg void OnBtnSearch();
	afx_msg void OnChkHomeLevel();
	afx_msg void OnChkAsym();
	afx_msg void OnChkAbsolute();
	afx_msg void OnChkRelative();
	afx_msg void OnBtnSetting();
	afx_msg void OnBtnRepeat();
	afx_msg void OnBtnEstop();
	afx_msg void OnChkZphaseLevel();
	afx_msg void OnBtnStatus();
	afx_msg void OnSelchangeCmbAxisset();
	afx_msg void OnSelchangeCmbPulseOutm();
	afx_msg void OnSelchangeCmbEncInputm();
	afx_msg void OnBtnMove();
	afx_msg void OnBtnLinear();
	afx_msg void OnBtnCircular();
	afx_msg void OnBtnCountClr();
	afx_msg void OnBtnContiLine();
	afx_msg void OnBtnContiSpline();
	afx_msg void OnBtnContiStart();
	afx_msg void OnChkGantry();
	afx_msg void OnBtnContiClr();
	afx_msg void OnBtnIntDisable();
	afx_msg void OnBtnCrcOff();
	afx_msg void OnBtnCrcOn();
	afx_msg void OnBtnMpgOff();
	afx_msg void OnBtnMpgOn();
	afx_msg void OnBtncontiTest();
	afx_msg void OnBtnManualset();
	afx_msg void OnChkScurve();
	afx_msg void OnBtnLoad();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnTrigReset();
	afx_msg void OnBtnTrigAbs();
	afx_msg void OnBtnTrigPeriod();
	afx_msg void OnBtnSigCapture();
	afx_msg void OnBtnIntMessage();
	afx_msg void OnBtnIntEvent();
	afx_msg void OnBtnIntCallback();
	afx_msg void OnBtnContiBlend();
	afx_msg void OnBtnContiCircle();
	afx_msg void OnBtnTrigOneshot();
	afx_msg void OnChkGearOnoff();
	afx_msg void OnDblclkLstLog();
	afx_msg void OnBtnReadCapture();
	afx_msg void OnBtn3dgraph();
	afx_msg void OnChkGantrySlave();
	afx_msg void OnBnClickedBtnLoadgcode();
	afx_msg void SPINDLE_ON(float spindle_speed);
	afx_msg void RUN_CCW_2(float x, float y, float z, float i, float j, float f);
	afx_msg void RUN_LINE(float x, float y, float z, float a, float b, float vel);
	afx_msg void dich_dong(char *line);
	afx_msg float value_block(char* line, uint8_t char_counter);
	afx_msg void RUN_MAX_SPEED(float x, float y, float z, float a, float b);
	afx_msg void RUN_CW(float x, float y, float r, DWORD dir, float f);
	afx_msg void RUN_CW_1(float x, float y, float z, float r, float f);
	afx_msg void RUN_CW_2(float x, float y, float z, float i, float j, float f);
	afx_msg void RUN_CCW_3(float x, float y, float z, float r, float f);
	afx_msg void RUN_CCW_4(float x, float y, float z, float i, float j, float f);
	afx_msg void OnBnClickedBtnStartgcode();
	afx_msg void CONFIG_RUN_LINE(float x, float y, float z, float a, float b, float vel);
	afx_msg void OnBnClickedBtnSpl();
	afx_msg void OnBnClickedBtnSetSpd();
	afx_msg void OnBnClickedBtnCntIot();
	afx_msg void OnBnClickedBtnDiscntIot();
	afx_msg void Cleanup(CURL* curl, curl_slist* headers);
	afx_msg void hien_du_lieu();
	afx_msg string GetRequest(const string url);
	afx_msg void OnBnClickedBtnTcpIp();
	afx_msg void OnBnClickedBtnSetHome();
	afx_msg void OnBnClickedBtnGoHome();
	afx_msg void autostartgcode();
	
	/*afx_msg	void Tachchuoi(CString string);
	afx_msg void RUN_LINE_TCPIP(float x, float y, float z, float a, float b, float vel);*/
	afx_msg void OnEnChangeEdit1();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();

	//afx_msg  size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
	//}}AFX_MSG
	afx_msg LRESULT OnControlMessage(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg size_t curl_callback(void* ptr, size_t size, size_t nmemb, std::string* data);
	CWinThread *thread_get;
	CWinThread *thread_post;
	CWinThread *thread_data_post;
	CWinThread *thread_data_get;
	CWinThread *thread_check_connect;
	CWinThread *thread_TCP_IP;
	CWinThread *thread_post_product;

	
	size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
	size_t WriteCallback2(void *contents, size_t size, size_t nmemb, void *userp);
	string tcpip;
	string server;
	bool counter, counter11=false, counterrun=false,sendtopos=false;
	int counterall;
	CString str2;

	#define IDC_EDIT1        1288
	//char buf[4096];
	//char X1[30], Y1[30], Z1[30],M1[30];
	int i,dem3=0,count=0;
	/*double X, Y, Z,a=0,M=0,Xcnc=0,Ycnc=0,Zcnc=0;*/
	bool finishline = false;
	
	
	
	
	

	afx_msg void OnBnClickedButton7();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMC_QIDLG_H__0F7529AF_37FA_4FF6_9B77_4556650D3051__INCLUDED_)