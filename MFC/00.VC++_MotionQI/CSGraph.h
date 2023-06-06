#ifndef __CSGraph_H__
#define __CSGraph_H__

#include "math.h"
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CCSGraph window

/////////////////////////////////////////////////////////////////////////////
// CCSGraph window

class CCSGraph : public CWnd
{
	// Construction
public:
	CCSGraph();
	
	// Attributes
public:
	double	AppendPoint(double dNewPointX, double dNewPointY, BOOL bAdd2List = TRUE);
	void	SetRange(double dLeft, double dRight, double dLower, double dUpper, int nDecimalPlaces=1);
	void	SetXUnits(CString string);
	void	SetYUnits(CString string);
	void	SetGridColor(COLORREF color);
	void	SetPlotColor(COLORREF color);
	void	SetBackgroundColor(COLORREF color);
	void	InvalidateCtrl();
	void	DrawPoint();
	void	Reset(double dCurPosX = 0.0, double dCurPosY = 0.0);
	
	void	SetZoomRange(double dNZoomRange, double dMZoomRange) { m_dNZoomRange = fabs(dNZoomRange);	m_dMZoomRange = fabs(dMZoomRange);	};
	void	SetZoomInOut(BOOL bZoomIn, double dZoomRange);
	void	SetZoomFit();
	int		ReCreateGraph(void);

	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSGraph)
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID=NULL);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	int m_nShiftPixels;          // amount to shift with each new point 
	int m_nXDecimals;
	int m_nYDecimals;
	
	CString m_strXUnitsString;
	CString m_strYUnitsString;
	
	COLORREF m_crBackColor;        // background color
	COLORREF m_crGridColor;        // grid color
	COLORREF m_crPlotColor;        // data color  
	
	double m_dCurrentPositionX;   // current position
	double m_dPreviousPositionX;  // previous position
	double m_dCurrentPositionY;   // current position
	double m_dPreviousPositionY;  // previous position
	
	//++	
	double	m_dMZoomRange;
	double	m_dNZoomRange;
	int		m_nMaxPointCnt;

	CArray<double, double> m_aPointX;
	CArray<double, double> m_aPointY;

	virtual ~CCSGraph();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CCSGraph)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy); 
	//}}AFX_MSG
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
		
	int		m_nHalfShiftPixels;
	int		m_nPlotShiftPixels;
	int		m_nClientHeight;
	int		m_nClientWidth;
	int		m_nPlotHeight;
	int		m_nPlotWidth;
	
	double	m_dLowerLimit;        // lower bounds
	double	m_dUpperLimit;        // upper bounds
	double	m_dRightLimit;        // lower bounds
	double	m_dLeftLimit;        // upper bounds
	double	m_dRangeX;
	double	m_dRangeY;
	double	m_dVerticalFactor;
	double	m_dHorizonFactor;
	
	CRect	m_rectClient;
	CRect	m_rectPlot;
	//++
	CRect	m_rectMZoomP;
	CRect	m_rectNZoomP;
	CRect	m_rectMZoomN;
	CRect	m_rectNZoomN;
	CRect	m_rectAZoomF;
	
	CPen	m_penPlot;
	CBrush	m_brushBack;
	
	CDC     m_dcGrid;
	CDC     m_dcPlot;
	CBitmap *m_pbitmapOldGrid;
	CBitmap *m_pbitmapOldPlot;
	CBitmap m_bitmapGrid;
	CBitmap m_bitmapPlot;	
};

/////////////////////////////////////////////////////////////////////////////
#endif

