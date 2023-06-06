// CSGraph.cpp : implementation file
//

#include "stdafx.h"
#include "CSGraph.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCSGraph
CCSGraph::CCSGraph()
{
	// since plotting is based on a LineTo for each new point
	// we need a starting point (i.e. a "previous" point)
	// use 0.0 as the default first point.
	// these are public member variables, and can be changed outside
	// (after construction).  Therefore m_perviousPosition could be set to
	// a more appropriate value prior to the first call to SetPosition.
	m_dPreviousPositionY =   0.0;
	m_dPreviousPositionX =   0.0;
	
	// public variable for the number of decimal places on the y axis
	m_nYDecimals = 3 ;
	m_nXDecimals = 3 ;
	
	// set some initial values for the scaling until "SetRange" is called.
	// these are protected varaibles and must be set with SetRange
	// in order to ensure that m_dRangeY is updated accordingly
	m_dLowerLimit = -10.0 ;
	m_dRightLimit =  10.0 ;
	m_dLeftLimit  = -10.0 ;
	m_dUpperLimit =  10.0 ;
	m_dRangeY      =  m_dUpperLimit - m_dLowerLimit ;   // protected member variable
	m_dRangeX		 =  m_dRightLimit - m_dLeftLimit ;
	
	// m_nShiftPixels determines how much the plot shifts (in terms of pixels) 
	// with the addition of a new data point
	m_nShiftPixels     = 4 ;
	m_nHalfShiftPixels = m_nShiftPixels/2 ;                     // protected
	m_nPlotShiftPixels = m_nShiftPixels + m_nHalfShiftPixels ;  // protected
	
	// background, grid and data colors
	// these are public variables and can be set directly
	m_crBackColor  = RGB(  0,   0,   0) ;  // see also SetBackgroundColor
	m_crGridColor  = RGB(  0, 255, 255) ;  // see also SetGridColor
	m_crPlotColor  = RGB(255, 255, 255) ;  // see also SetPlotColor
	
	// protected variables
	m_penPlot.CreatePen(PS_SOLID, 0, m_crPlotColor) ;
	m_brushBack.CreateSolidBrush(m_crBackColor) ;
	
	// public member variables, can be set directly 
	m_strXUnitsString.Format("X units") ;  // can also be set with SetXUnits
	m_strYUnitsString.Format("Y units") ;  // can also be set with SetYUnits
	
	// protected bitmaps to restore the memory DC's
	m_pbitmapOldGrid = NULL ;
	m_pbitmapOldPlot = NULL ;
	
	m_nMaxPointCnt	= 10000;
	m_dNZoomRange	= 100.0;
	m_dMZoomRange	= 1000.0;
	
}  // CCSGraph

/////////////////////////////////////////////////////////////////////////////
CCSGraph::~CCSGraph()
{
	// just to be picky restore the bitmaps for the two memory dc's
	// (these dc's are being destroyed so there shouldn't be any leaks)
	if (m_pbitmapOldGrid != NULL)
		m_dcGrid.SelectObject(m_pbitmapOldGrid) ;  
	if (m_pbitmapOldPlot != NULL)
		m_dcPlot.SelectObject(m_pbitmapOldPlot) ;  
	
} // ~CCSGraph


BEGIN_MESSAGE_MAP(CCSGraph, CWnd)
//{{AFX_MSG_MAP(CCSGraph)
ON_WM_PAINT()
ON_WM_SIZE()
ON_WM_LBUTTONDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCSGraph message handlers

/////////////////////////////////////////////////////////////////////////////
BOOL CCSGraph::Create(DWORD dwStyle, const RECT& rect, 
					  CWnd* pParentWnd, UINT nID) 
{
	BOOL result ;
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW) ;
	
	result = CWnd::CreateEx(WS_EX_STATICEDGE, 
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU)nID) ;
	if (result != 0)
		InvalidateCtrl() ;
	
	return result ;
	
} // Create

/////////////////////////////////////////////////////////////////////////////
void CCSGraph::SetRange(double dLeft, double dRight, double dLower, double dUpper, int nDecimalPlaces)
{
	if(dUpper < dLower) return;

	if(dUpper != m_dUpperLimit){	
		m_dLeftLimit		= dLeft ;
		m_dRightLimit		= dRight ;
		m_dLowerLimit		= dLower ;
		m_dUpperLimit		= dUpper ;
		m_nYDecimals		= nDecimalPlaces ;
		m_nXDecimals		= nDecimalPlaces ;
		m_dRangeX			= m_dRightLimit - m_dLeftLimit ;
		m_dRangeY			= m_dUpperLimit - m_dLowerLimit ;
		m_dVerticalFactor	= (double)m_nPlotHeight / m_dRangeY ; 
		m_dHorizonFactor	= (double)m_nPlotWidth / m_dRangeX ; 
	
		// clear out the existing garbage, re-start with a clean plot
		InvalidateCtrl();
		ReCreateGraph();	
	}
}

/////////////////////////////////////////////////////////////////////////////
void CCSGraph::SetXUnits(CString string)
{
	m_strXUnitsString = string ;
	
	// clear out the existing garbage, re-start with a clean plot
	InvalidateCtrl() ;
	
}  // SetXUnits

/////////////////////////////////////////////////////////////////////////////
void CCSGraph::SetYUnits(CString string)
{
	m_strYUnitsString = string ;
	
	// clear out the existing garbage, re-start with a clean plot
	InvalidateCtrl() ;
	
}  // SetYUnits

/////////////////////////////////////////////////////////////////////////////
void CCSGraph::SetGridColor(COLORREF color)
{
	m_crGridColor = color ;
	
	// clear out the existing garbage, re-start with a clean plot
	InvalidateCtrl() ;
	
}  // SetGridColor


/////////////////////////////////////////////////////////////////////////////
void CCSGraph::SetPlotColor(COLORREF color)
{
	m_crPlotColor = color ;
	
	m_penPlot.DeleteObject() ;
	m_penPlot.CreatePen(PS_SOLID, 0, m_crPlotColor) ;
	
	// clear out the existing garbage, re-start with a clean plot
	InvalidateCtrl() ;
	
}  // SetPlotColor


/////////////////////////////////////////////////////////////////////////////
void CCSGraph::SetBackgroundColor(COLORREF color)
{
	m_crBackColor = color ;
	
	m_brushBack.DeleteObject() ;
	m_brushBack.CreateSolidBrush(m_crBackColor) ;
	
	// clear out the existing garbage, re-start with a clean plot
	InvalidateCtrl() ;
	
}  // SetBackgroundColor

/////////////////////////////////////////////////////////////////////////////
void CCSGraph::InvalidateCtrl()
{
	// There is a lot of drawing going on here - particularly in terms of 
	// drawing the grid.  Don't panic, this is all being drawn (only once)
	// to a bitmap.  The result is then BitBlt'd to the control whenever needed.
	int i ;
	//  int nCharacters ;
	int nTopGridPixX, nMidGridPixX, nBottomGridPixX ;
	int nTopGridPixY, nMidGridPixY, nBottomGridPixY ;
	
	CPen *oldPen ;
	CPen solidPen(PS_SOLID, 0, m_crGridColor) ;
	CFont axisFont, yUnitFont, *oldFont ;
	CString strTemp ;
	
	// in case we haven't established the memory dc's
	CClientDC dc(this) ;  
	
	// if we don't have one yet, set up a memory dc for the grid
	if (m_dcGrid.GetSafeHdc() == NULL)
	{
		m_dcGrid.CreateCompatibleDC(&dc) ;
		m_bitmapGrid.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldGrid = m_dcGrid.SelectObject(&m_bitmapGrid) ;
	}
	
	m_dcGrid.SetBkColor (m_crBackColor) ;
	
	// fill the grid background
	m_dcGrid.FillRect(m_rectClient, &m_brushBack) ;
	
	// draw the plot rectangle:
	// determine how wide the y axis scaling values are
	//  nCharacters = abs((int)log10(fabs(m_dUpperLimit))) ;
	// nCharacters = max(nCharacters, abs((int)log10(fabs(m_dLowerLimit)))) ;
	
	// add the units digit, decimal point and a minus sign, and an extra space
	// as well as the number of decimal places to display
	//  nCharacters = nCharacters + 4 + m_nYDecimals ;  
	
	// adjust the plot rectangle dimensions
	// assume 6 pixels per character (this may need to be adjusted)
	//  m_rectPlot.left = m_rectClient.left + 6*(nCharacters) ;
	m_nPlotWidth    = m_rectPlot.Width() - 20 ;
	m_nPlotHeight   = m_rectPlot.Height() ;
	
	// draw the plot rectangle
	oldPen = m_dcGrid.SelectObject (&solidPen) ; 
	m_dcGrid.MoveTo (m_rectPlot.left+20, m_rectPlot.top) ;
	m_dcGrid.LineTo (m_rectPlot.right, m_rectPlot.top) ;
	m_dcGrid.LineTo (m_rectPlot.right, m_rectPlot.bottom ) ;
	m_dcGrid.LineTo (m_rectPlot.left+20, m_rectPlot.bottom ) ;
	m_dcGrid.LineTo (m_rectPlot.left+20, m_rectPlot.top) ;
	m_dcGrid.SelectObject (oldPen) ; 
	
	// draw the dotted lines, 
	// use SetPixel instead of a dotted pen - this allows for a 
	// finer dotted line and a more "technical" look
	nMidGridPixX    = (m_rectPlot.right + m_rectPlot.left +20)/2 ;
	nTopGridPixX    = nMidGridPixX - m_nPlotHeight/4 ;
	nBottomGridPixX = nMidGridPixX + m_nPlotHeight/4 ;
	
	nMidGridPixY    = (m_rectPlot.top + m_rectPlot.bottom)/2 ;
	nTopGridPixY    = nMidGridPixY - m_nPlotWidth/4 ;
	nBottomGridPixY = nMidGridPixY + m_nPlotWidth/4 ;
	
	for (i=m_rectPlot.left+20; i< (m_rectPlot.right); i+=4)
	{
		m_dcGrid.SetPixel (i, nTopGridPixY,    m_crGridColor) ;
		m_dcGrid.SetPixel (i, nMidGridPixY,    m_crGridColor) ;
		m_dcGrid.SetPixel (i, nBottomGridPixY, m_crGridColor) ;
	}
	
	for (i=m_rectPlot.top; i<m_rectPlot.bottom ; i+=4)
	{
		m_dcGrid.SetPixel (nTopGridPixX, i,    m_crGridColor) ;
		m_dcGrid.SetPixel (nMidGridPixX, i,    m_crGridColor) ;
		m_dcGrid.SetPixel (nBottomGridPixX, i, m_crGridColor) ;
	}
	
	// create some fonts (horizontal and vertical)
	// use a height of 14 pixels and 300 weight 
	// (these may need to be adjusted depending on the display)
	axisFont.CreateFont (14, 0, 0, 0, 300,
		FALSE, FALSE, 0, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, 
		DEFAULT_PITCH|FF_SWISS, "Arial") ;
	
	yUnitFont.CreateFont (14, 0, 900, 0, 300,
		FALSE, FALSE, 0, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, 
		DEFAULT_PITCH|FF_SWISS, "Arial") ;
	
	// grab the horizontal font
	oldFont = m_dcGrid.SelectObject(&axisFont) ;
	
	// y max
	m_dcGrid.SetTextColor (m_crGridColor) ;
	m_dcGrid.SetTextAlign (TA_RIGHT|TA_TOP) ;
	strTemp.Format ("%.*lf", m_nYDecimals, m_dUpperLimit) ;
	//strTemp.Format ("%ld", (long)m_dUpperLimit) ;
	m_dcGrid.TextOut (m_rectPlot.left + 20, m_rectPlot.top, strTemp) ;
	
	// y min
	m_dcGrid.SetTextAlign (TA_RIGHT|TA_BASELINE) ;
	strTemp.Format ("%.*lf", m_nYDecimals, m_dLowerLimit) ;
	//strTemp.Format ("%d", (long)m_dLowerLimit) ;
	m_dcGrid.TextOut (m_rectPlot.left + 20, m_rectPlot.bottom, strTemp) ;
	
	// x min
	m_dcGrid.SetTextAlign (TA_LEFT|TA_TOP) ;
	strTemp.Format ("%.*lf", m_nXDecimals, m_dLeftLimit) ;
	m_dcGrid.TextOut (m_rectPlot.left , m_rectPlot.bottom + 5, strTemp) ;
	//  m_dcGrid.TextOut (m_rectPlot.right, m_rectPlot.right+4, "0") ;
	
	// x max
	m_dcGrid.SetTextAlign (TA_RIGHT|TA_TOP) ;
	strTemp.Format ("%.*lf", m_nXDecimals, m_dRightLimit) ;
	m_dcGrid.TextOut (m_rectPlot.right, m_rectPlot.bottom +5, strTemp) ;
	// strTemp.Format ("%d", m_nPlotWidth/m_nShiftPixels) ; 
	//  m_dcGrid.TextOut (m_rectPlot.right, m_rectPlot.bottom+4, strTemp) ;
	
	// x units
	m_dcGrid.SetTextAlign (TA_CENTER|TA_TOP) ;
	m_dcGrid.TextOut ((m_rectPlot.left+m_rectPlot.right)/2, 
		m_rectPlot.bottom+4, m_strXUnitsString) ;
	
	// restore the font
	m_dcGrid.SelectObject(oldFont) ;
	
	// y units
	oldFont = m_dcGrid.SelectObject(&yUnitFont) ;
	m_dcGrid.SetTextAlign (TA_CENTER|TA_BASELINE) ;
	m_dcGrid.TextOut (m_rectPlot.left + 10, 
		(m_rectPlot.bottom+m_rectPlot.top)/2, m_strYUnitsString) ;
	m_dcGrid.SelectObject(oldFont) ;
	
	CPen	epen, *old;
	CBrush	brh, *oldb;
	epen.CreatePen(PS_SOLID, 0, RGB(255,255,0));
	brh.CreateSolidBrush(RGB(150, 150, 255));
	
	oldb = m_dcGrid.SelectObject(&brh);
	old = m_dcGrid.SelectObject(&epen);       // ÁÂÇ¥ÃàÀÇ ±âÁØÀ» ±×¸²´Ù.
	
	m_dcGrid.Rectangle(m_rectMZoomP.left, m_rectMZoomP.top, m_rectMZoomP.right, m_rectMZoomP.bottom); // ÁÂÃø »ó´Ü
	m_dcGrid.MoveTo(m_rectMZoomP.left+3, m_rectMZoomP.top+6);
	m_dcGrid.LineTo(m_rectMZoomP.left+7,  m_rectMZoomP.top+2);
	m_dcGrid.LineTo(m_rectMZoomP.left+12, m_rectMZoomP.top+7);
	m_dcGrid.MoveTo(m_rectMZoomP.left+3, m_rectMZoomP.top+10);
	m_dcGrid.LineTo(m_rectMZoomP.left+7,  m_rectMZoomP.top+6);
	m_dcGrid.LineTo(m_rectMZoomP.left+12, m_rectMZoomP.top+11);
	
	m_dcGrid.Rectangle(m_rectNZoomP.left, m_rectNZoomP.top, m_rectNZoomP.right, m_rectNZoomP.bottom); // ÁÂÃø »ó´Ü
	m_dcGrid.MoveTo(m_rectNZoomP.left+3, m_rectNZoomP.top+6);
	m_dcGrid.LineTo(m_rectNZoomP.left+7,  m_rectNZoomP.top+2);
	m_dcGrid.LineTo(m_rectNZoomP.left+12, m_rectNZoomP.top+7);

	m_dcGrid.Rectangle(m_rectAZoomF.left, m_rectAZoomF.top, m_rectAZoomF.right, m_rectAZoomF.bottom); // ÁÂÃø »ó´Ü
	m_dcGrid.MoveTo(m_rectAZoomF.left+3, m_rectAZoomF.top+6);
	m_dcGrid.LineTo(m_rectAZoomF.right-3,  m_rectAZoomF.top+6);
	m_dcGrid.MoveTo(m_rectAZoomF.left+3, m_rectAZoomF.bottom-6);
	m_dcGrid.LineTo(m_rectAZoomF.right-3,  m_rectAZoomF.bottom-6);
	

	m_dcGrid.Rectangle(m_rectMZoomN.left, m_rectMZoomN.top, m_rectMZoomN.right, m_rectMZoomN.bottom); // ÁÂÃø ÇÏ´Ü	
	m_dcGrid.MoveTo(m_rectMZoomN.left+3, m_rectMZoomN.top+7);
	m_dcGrid.LineTo(m_rectMZoomN.left+7,  m_rectMZoomN.top+11);
	m_dcGrid.LineTo(m_rectMZoomN.left+12, m_rectMZoomN.top+6);	
	m_dcGrid.MoveTo(m_rectMZoomN.left+3, m_rectMZoomN.top+3);
	m_dcGrid.LineTo(m_rectMZoomN.left+7,  m_rectMZoomN.top+7);
	m_dcGrid.LineTo(m_rectMZoomN.left+12, m_rectMZoomN.top+2);
	
	m_dcGrid.Rectangle(m_rectNZoomN.left, m_rectNZoomN.top, m_rectNZoomN.right, m_rectNZoomN.bottom); // ÁÂÃø ÇÏ´Ü
	m_dcGrid.MoveTo(m_rectNZoomN.left+3, m_rectNZoomN.top+2);
	m_dcGrid.LineTo(m_rectNZoomN.left+7,  m_rectNZoomN.top+6);
	m_dcGrid.LineTo(m_rectNZoomN.left+12, m_rectNZoomN.top+1);
	
	m_dcGrid.SelectObject(oldb);
	brh.DeleteObject();
	m_dcGrid.SelectObject(old);
	epen.DeleteObject();
	
	// at this point we are done filling the the grid bitmap, 
	// no more drawing to this bitmap is needed until the setting are changed
	
	// if we don't have one yet, set up a memory dc for the plot
	if (m_dcPlot.GetSafeHdc() == NULL)
	{
		m_dcPlot.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = m_dcPlot.SelectObject(&m_bitmapPlot) ;
	}
	
	// make sure the plot bitmap is cleared
	m_dcPlot.SetBkColor (m_crBackColor) ;
	m_dcPlot.FillRect(m_rectClient, &m_brushBack) ;
	
	// finally, force the plot area to redraw
	InvalidateRect(m_rectClient) ;
	
} // InvalidateCtrl

/////////////////////////////////////////////////////////////////////////////
double CCSGraph::AppendPoint(double dNewPointX, double dNewPointY, BOOL bAdd2List)
{
	// append a data point to the plot
	// return the previous point

	if(((dNewPointX + 0.1) > m_dCurrentPositionX) && ((dNewPointX - 0.1) < m_dCurrentPositionX) && ((dNewPointY + 0.1) > m_dCurrentPositionY) && ((dNewPointY - 0.1) < m_dCurrentPositionY))
		return 0.0;

	double dPreviousX, dPreviousY ;
	
	dPreviousX = m_dCurrentPositionX ;
	dPreviousY = m_dCurrentPositionY ;
	m_dCurrentPositionX = dNewPointX ;
	m_dCurrentPositionY = dNewPointY ;
	 
	if(bAdd2List == TRUE){
		m_aPointX.Add(m_dCurrentPositionX);
		m_aPointY.Add(m_dCurrentPositionY);

		while(m_aPointX.GetSize() > m_nMaxPointCnt){
			m_aPointX.RemoveAt(0);
			m_aPointY.RemoveAt(0);
		}	
	}
	
	DrawPoint();
	Invalidate();
	return 0.0 ;
	
} // AppendPoint

////////////////////////////////////////////////////////////////////////////
void CCSGraph::OnPaint() 
{
	CPaintDC dc(this) ;  // device context for painting
	CDC memDC ;
	CBitmap memBitmap ;
	CBitmap* oldBitmap ; // bitmap originally found in CMemDC
	
	// no real plotting work is performed here, 
	// just putting the existing bitmaps on the client
	
	// to avoid flicker, establish a memory dc, draw to it 
	// and then BitBlt it to the client
	memDC.CreateCompatibleDC(&dc) ;
	memBitmap.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
	oldBitmap = (CBitmap *)memDC.SelectObject(&memBitmap) ;
	
	if (memDC.GetSafeHdc() != NULL)
	{
		// first drop the grid on the memory dc
		memDC.BitBlt(0, 0, m_nClientWidth, m_nClientHeight, 
			&m_dcGrid, 0, 0, SRCCOPY) ;
		// now add the plot on top as a "pattern" via SRCPAINT.
		// works well with dark background and a light plot
		memDC.BitBlt(0, 0, m_nClientWidth, m_nClientHeight, 
			&m_dcPlot, 0, 0, SRCPAINT) ;  //SRCPAINT
		// finally send the result to the display
		dc.BitBlt(0, 0, m_nClientWidth, m_nClientHeight, 
			&memDC, 0, 0, SRCCOPY) ;
	}
	
	memDC.SelectObject(oldBitmap) ;
	
} // OnPaint

/////////////////////////////////////////////////////////////////////////////
void CCSGraph::DrawPoint()
{
	// this does the work of "scrolling" the plot to the left
	// and appending a new data point all of the plotting is 
	// directed to the memory based bitmap associated with m_dcPlot
	// the will subsequently be BitBlt'd to the client in OnPaint
	
	int currX, prevX, currY, prevY ;
	
	CPen *oldPen ;
	CRect rectCleanUp ;
	
	if (m_dcPlot.GetSafeHdc() != NULL)
	{
		// shift the plot by BitBlt'ing it to itself 
		// note: the m_dcPlot covers the entire client
		//       but we only shift bitmap that is the size 
		//       of the plot rectangle
		// grab the right side of the plot (exluding m_nShiftPixels on the left)
		// move this grabbed bitmap to the left by m_nShiftPixels
		m_dcPlot.BitBlt(m_rectPlot.left, m_rectPlot.top+1, 
			m_nPlotWidth, m_nPlotHeight, &m_dcPlot, 
			m_rectPlot.left, m_rectPlot.top+1, 
			SRCCOPY) ;
		
		// draw the next line segement
		// grab the plotting pen
		oldPen = m_dcPlot.SelectObject(&m_penPlot) ;
		
		// move to the previous point
		prevX = (int)((m_dPreviousPositionX * ( m_nPlotWidth / (m_dRightLimit * 2))) +((m_rectPlot.right + m_rectPlot.left +20) / 2));
		prevY = (int)((-m_dPreviousPositionY * ( m_nPlotHeight / (m_dUpperLimit * 2))) +(( m_rectPlot.bottom + m_rectPlot.top) / 2));
		m_dcPlot.MoveTo (prevX, prevY) ;
		
		// draw to the current point
		currX = (int)((m_dCurrentPositionX * ( m_nPlotWidth / (m_dRightLimit * 2) )) +((m_rectPlot.right + m_rectPlot.left +20) / 2));
		currY = (int)((-m_dCurrentPositionY * ( m_nPlotHeight / (m_dUpperLimit * 2 ))) + (( m_rectPlot.bottom + m_rectPlot.top) / 2));
		
		if ( m_dPreviousPositionX <= m_dRightLimit && m_dPreviousPositionX >= m_dLeftLimit 
			&& m_dPreviousPositionY <= m_dUpperLimit && m_dPreviousPositionY >= m_dLowerLimit
			&& m_dCurrentPositionX <= m_dRightLimit && m_dCurrentPositionX >= m_dLeftLimit 
			&& m_dCurrentPositionY <= m_dUpperLimit && m_dCurrentPositionY >= m_dLowerLimit)
			m_dcPlot.LineTo (currX, currY) ;
		
		// restore the pen 
		m_dcPlot.SelectObject(oldPen) ;
		
		// store the current point for connection to the next point
		m_dPreviousPositionX = m_dCurrentPositionX ;
		m_dPreviousPositionY = m_dCurrentPositionY ;		
	}
	
} // end DrawPoint

/////////////////////////////////////////////////////////////////////////////
void CCSGraph::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy) ;
	
	GetClientRect(m_rectClient) ;
	
	// set some member variables to avoid multiple function calls
	m_nClientHeight = m_rectClient.Height() ;
	m_nClientWidth  = m_rectClient.Width() ;
	
	// the "left" coordinate and "width" will be modified in 
	// InvalidateCtrl to be based on the width of the y axis scaling
	m_rectPlot.left   = 40 ;  
	m_rectPlot.top    = 10 ;
	
	m_rectPlot.right  = m_rectClient.right-10 ;
	m_rectPlot.bottom = m_rectClient.bottom-29 ;
	
	// set some member variables to avoid multiple function calls
	m_nPlotHeight = m_rectPlot.Height() ;
	m_nPlotWidth  = m_rectPlot.Width() ;
	
	// set the scaling factor for now, this can be adjusted 
	// in the SetRange functions
	m_dVerticalFactor = (double)m_nPlotHeight / m_dRangeY ; 
	m_dHorizonFactor = (double) m_nPlotWidth / m_dRangeX ; 
	
	m_rectMZoomP.SetRect(m_rectPlot.left + 22, m_rectPlot.top+2, m_rectPlot.left + 37, m_rectPlot.top + 17);
	m_rectNZoomP.SetRect(m_rectPlot.left + 22, m_rectPlot.top+19, m_rectPlot.left + 37, m_rectPlot.top + 30);
	
	m_rectAZoomF.SetRect(m_rectPlot.left + 22, m_rectPlot.top + (m_rectPlot.Height() / 2) - 7, m_rectPlot.left + 37, m_rectPlot.top + (m_rectPlot.Height() / 2) + 8);

	m_rectMZoomN.SetRect(m_rectPlot.left + 22, m_rectPlot.bottom- 16, m_rectPlot.left + 37, m_rectPlot.bottom-1);
	m_rectNZoomN.SetRect(m_rectPlot.left + 22, m_rectPlot.bottom- 28, m_rectPlot.left + 37, m_rectPlot.bottom-17);
	
} // OnSize

/////////////////////////////////////////////////////////////////////////////
void CCSGraph::Reset(double dCurPosX, double dCurPosY)
{
	// to clear the existing data (in the form of a bitmap)
	// simply invalidate the entire control
	m_dPreviousPositionX = dCurPosX;
	m_dPreviousPositionY = dCurPosY;

	m_aPointX.RemoveAll();
	m_aPointY.RemoveAll();
	InvalidateCtrl() ;
}

void CCSGraph::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);

	double dRangeLimit;
	double dNewRange, dDigit;

	dRangeLimit = m_dUpperLimit;
	if(m_rectMZoomP.PtInRect(point) == TRUE){
		dNewRange	= fabs(dRangeLimit) + 0.00001;
		dDigit		= floor(log(dNewRange) / log(10.0));
		dNewRange	= pow(10.0, dDigit);
		SetZoomInOut(TRUE, dNewRange);		
	}else if(m_rectNZoomP.PtInRect(point) == TRUE){
		dNewRange	= fabs(dRangeLimit) + 0.00001;
		dDigit		= floor(log(dNewRange) / log(10.0));
		if(dDigit > 0)	dDigit -= 1;

		dNewRange	= pow(10.0, dDigit);
		SetZoomInOut(TRUE, dNewRange);		
	}else if(m_rectMZoomN.PtInRect(point) == TRUE){
		dNewRange	= fabs(dRangeLimit) + 0.00001;
		dDigit		= floor(log(dNewRange) / log(10.0));
		dNewRange	= pow(10.0, dDigit);
		if(dNewRange > (dRangeLimit - dNewRange))
			dNewRange = pow(10.0, dDigit - 1);
		SetZoomInOut(FALSE, dNewRange);		
	}else if(m_rectNZoomN.PtInRect(point) == TRUE){
		dNewRange	= fabs(dRangeLimit) + 0.00001;
		dDigit		= floor(log(dNewRange) / log(10.0));
		if(dDigit > 0)	dDigit -= 1;

		dNewRange	= pow(10.0, dDigit);
		if(dNewRange > (dRangeLimit - dNewRange))
			dNewRange = pow(10.0, dDigit - 1);
		SetZoomInOut(FALSE, dNewRange);		
	}else if(m_rectAZoomF.PtInRect(point) == TRUE){
		SetZoomFit();
	}
}

void CCSGraph::SetZoomInOut(BOOL bZoomIn, double dZoomRange)
{
	if(bZoomIn == TRUE){
		dZoomRange = fabs(dZoomRange);
		SetRange(m_dLeftLimit - dZoomRange, m_dRightLimit + dZoomRange, m_dLowerLimit - dZoomRange, m_dUpperLimit + dZoomRange);
	}else{
		dZoomRange = -fabs(dZoomRange);
		if(1.0 < (m_dUpperLimit - dZoomRange)){
			SetRange(m_dLeftLimit - dZoomRange, m_dRightLimit + dZoomRange, m_dLowerLimit - dZoomRange, m_dUpperLimit + dZoomRange);
		}
	}
}

void CCSGraph::SetZoomFit()
{
	double	dZoomRange	= 0;
	double	dMaxPos		= 0;
	
	for(int i = 0; i < m_aPointX.GetSize(); i++){
		dMaxPos = max(fabs(m_aPointY.GetAt(i)), dMaxPos);
		dMaxPos = max(fabs(m_aPointX.GetAt(i)), dMaxPos);
	}	

	dZoomRange = dMaxPos + (dMaxPos * 0.1);

	if(dZoomRange < 0.1)	dZoomRange = 1.0;
	SetRange(-dZoomRange, dZoomRange, -dZoomRange, dZoomRange);
}

int CCSGraph::ReCreateGraph(void)
{
	if(m_aPointX.GetSize() > 0)	m_dPreviousPositionX = m_aPointX.GetAt(0);
	if(m_aPointY.GetSize() > 0)	m_dPreviousPositionY = m_aPointY.GetAt(0);
	
	double	dAddPointX;
	double	dAddPointY;
	for( int i = 0; i < m_aPointX.GetSize(); i++){
		dAddPointX = m_aPointX.GetAt(i);
		dAddPointY = m_aPointY.GetAt(i);
		AppendPoint(dAddPointX, dAddPointY, FALSE);
	}
	return 0;
}