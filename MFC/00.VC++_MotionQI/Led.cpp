// Led.cpp : implementation file
//

#include "stdafx.h"
#include "Led.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLed
CLed::CLed()
{
	m_bOffColor[0] = RGB(100, 0, 0);
	m_bOnColor[0]	= RED;
	m_bOffColor[1] = DKYELLOW; //RGB(255, 253, 208);
	m_bOnColor[1]	= YELLOW;
	m_bOffColor[2] = DKGREEN;
	m_bOnColor[2] = GREEN;

	m_LedColor = m_bOffColor[0];
	bLedStatus = FALSE;
	m_bSensor = LIMIT_SENSOR;
}

CLed::~CLed()
{
}


BEGIN_MESSAGE_MAP(CLed, CStatic)
	//{{AFX_MSG_MAP(CLed)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLed message handlers

void CLed::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectctrl;
	GetClientRect(&rectctrl);

	CBitmap *pOldTempBitmap;
    CDC tempDC;
	tempDC.CreateCompatibleDC(&dc);

	CBitmap tempBitmap;
	tempBitmap.CreateCompatibleBitmap(&dc, rectctrl.Width(), rectctrl.Height());
	
	pOldTempBitmap = tempDC.SelectObject(&tempBitmap);

	tempDC.FillRect(rectctrl, &CBrush(m_LedColor));

	dc.BitBlt(rectctrl.left, rectctrl.top, rectctrl.right, rectctrl.bottom,
			&tempDC, 0, 0, SRCCOPY);

	tempDC.SelectObject(pOldTempBitmap);

		
	// Do not call CStatic::OnPaint() for painting messages
}

void CLed::On()
{
	m_LedColor = m_bOnColor[m_bSensor];
	bLedStatus = TRUE;
	Invalidate();
}

void CLed::Off()
{
	m_LedColor = m_bOffColor[m_bSensor];
	bLedStatus = FALSE;
	Invalidate();
}

BOOL CLed::GetStatus()
{
	return bLedStatus;
}

void CLed::SetType(int type)
{
	m_bSensor = type;
	if ( bLedStatus )	On();
	else				Off();
}

void CLed::SetStatus(BOOL bStatus)
{
	if ( bStatus ) 	On();
	else			Off();
}
