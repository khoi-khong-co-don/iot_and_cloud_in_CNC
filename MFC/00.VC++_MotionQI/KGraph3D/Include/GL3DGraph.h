#if !defined(AFX_GL3DGRAPH_H__F42A3470_E6F5_44D6_8FC0_D23562F06420__INCLUDED_)
#define AFX_GL3DGRAPH_H__F42A3470_E6F5_44D6_8FC0_D23562F06420__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GL3DGraph.h : header file
//
#include "GLMouseRotate.h"
#include "afxtempl.h"
#define  ORTHOGRAPHICS		0
#define PERSPECTIVE			1
enum LineStyle {LINE, DOTTED, DOUBLE_DOTTED, LINE_DOTTED, DASHED, DOUBLE_DASHED, DASH_DOT_DASH};



/////////////////////////////////////////////////////////////////////////////
// CGL3DGraph window

class CGL3DGraph : public CGLMouseRotate
{
// Construction
public:
	 __declspec(dllexport) CGL3DGraph();

// Attributes
public:

protected:
	BYTE m_ProjType;		// 0 = Orthographics,	1 = Perspective

	float m_MaxX;
	float m_MaxY;
	float m_MaxZ;
	float m_MinX;
	float m_MinY;
	float m_MinZ;
	BOOL m_bAutoScaleX;
	BOOL m_bAutoScaleY;
	BOOL m_bAutoScaleZ;

	BOOL m_bClear;

	BOOL m_bBoxEnable;

	int m_Count;
	float *m_pDat;
	COLORREF	m_Colour;
	COLORREF	*m_pColList;

	COLORREF    m_XAxisCol;
	COLORREF    m_YAxisCol;
	COLORREF	m_ZAxisCol;

	COLORREF m_XGridCol;
	COLORREF m_YGridCol;
	COLORREF m_ZGridCol;

	COLORREF m_bColor;

	COLORREF m_XRangeCol;
	COLORREF m_YRangeCol;
	COLORREF m_ZRangeCol;

	CString		m_XAxisName;
	CString		m_YAxisName;
	CString		m_ZAxisName;

	CString		m_strMaxX;
	CString		m_strMinX;
	CString		m_strMaxY;
	CString		m_strMinY;
	CString		m_strMaxZ;
	CString		m_strMinZ;

	BYTE m_StyleX;
	BYTE m_StyleY;
	BYTE m_StyleZ;

	int  m_iDivideX;
	int  m_iDivideY;
	int  m_iDivideZ;

	GLint m_iPatternX;
	GLint m_iPatternY;
	GLint m_iPatternZ;

	GLint m_nboxPattern;

// Operations
public:
	CGLDispList m_GraphBox;
	CArray<CPoint3D, CPoint3D&>	m_aPoint3D;
/*
count = number of points
col = color of points, used if pColList = NULL
pCoords = x, y, z coordinates of each point, length = count * 3
pColList = pointer to count COLORREFs, each point has the color if not NULL
*/
	/* 
	__declspec(dllexport) void SetMaxX(float x); 
	__declspec(dllexport) void SetMaxY(float y); 
	__declspec(dllexport) void SetMaxZ(float z); 
	__declspec(dllexport) void SetMinX(float x); 
	__declspec(dllexport)  void SetMinY(float y); 
	__declspec(dllexport)  void SetMinZ(float z); 

	__declspec(dllexport)  float GetMaxX();	
	__declspec(dllexport)  float GetMaxY();	
	__declspec(dllexport)  float GetMaxZ();	
	__declspec(dllexport)  float GetMinX();
	__declspec(dllexport)  float GetMinY();
	__declspec(dllexport)  float GetMinZ();	
*/

	__declspec(dllexport) void SetRangeX(float x);
	__declspec(dllexport) void SetRangeY(float y);
	__declspec(dllexport) void SetRangeZ(float z);
	__declspec(dllexport) void SetRange3Axis(float x, float y, float z);
	
	__declspec(dllexport)  float GetRangeX();
	__declspec(dllexport)  float GetRangeY();
	__declspec(dllexport)  float GetRangeZ();
	__declspec(dllexport) void GetRange3Axis(float &x, float &y, float &z);

	__declspec(dllexport)  void SetAutoScaleX(BOOL scl);	
	__declspec(dllexport)  void SetAutoScaleY(BOOL scl); 
	__declspec(dllexport)  void SetAutoScaleZ(BOOL scl);
	
	

	 __declspec(dllexport) BOOL SetProjection(BYTE type);
	 __declspec(dllexport) void SetSymbolSize(float size);

	//Adding Functions
	 __declspec(dllexport) void SetAxisColorX(COLORREF XAxisCol);
	 __declspec(dllexport) void SetAxisColorY(COLORREF YAxisCol);
	 __declspec(dllexport) void SetAxisColorZ(COLORREF ZAxiscol);
	 __declspec(dllexport) COLORREF GetAxisColorX();
	 __declspec(dllexport) COLORREF GetAxisColorY();
	 __declspec(dllexport) COLORREF GetAxisColorZ();


	 __declspec(dllexport) void SetAxisTextX(CString strXAxis);
	 __declspec(dllexport) void SetAxisTextY(CString strYAxis);
	 __declspec(dllexport) void SetAxisTextZ(CString strZAxis);
	 __declspec(dllexport) void SetAxisText3Axis(CString strXAxis, CString strYAxis, CString strZAxis);
	 __declspec(dllexport) CString GetAxisTextX(); 
	 __declspec(dllexport) CString GetAxisTextY(); 
	 __declspec(dllexport) CString GetAxisTextZ(); 
	 __declspec(dllexport) void GetAxisText3Axis(CString &strXAxis, CString &strYAxis, CString &strZAxis);


	 __declspec(dllexport) void SetGridColorX(COLORREF XGridCol);
	 __declspec(dllexport) void SetGridColorY(COLORREF YGridCol);
	 __declspec(dllexport) void SetGridColorZ(COLORREF ZGridCol);

	 __declspec(dllexport) COLORREF GetGridColorX();
	 __declspec(dllexport) COLORREF GetGridColorY();
	 __declspec(dllexport) COLORREF GetGridColorZ();
	 __declspec(dllexport) void GetGridColor3Axis(COLORREF &XGridCol, COLORREF &YGridCol, COLORREF &ZGridCol);

	/*
	 __declspec(dllexport) void SetMax3Axis(float x, float y, float z);
	 __declspec(dllexport) void SetMin3Axis(float x, float y, float z);
	 __declspec(dllexport) void GetMax3Axis(float &x, float &y, float &z); 
	 __declspec(dllexport) void GetMin3Axis(float &x, float &y, float &z); 
	*/
	 __declspec(dllexport) void SetGridLineStyleX(BYTE Style); 
	 __declspec(dllexport) void SetGridLineStyleY(BYTE Style);	
	 __declspec(dllexport) void SetGridLineStyleZ(BYTE Style);	

	 __declspec(dllexport) BOOL SetGridTypeX(int iDivideX); 
	 __declspec(dllexport) BOOL SetGridTypeY(int iDivideY);	
	 __declspec(dllexport) BOOL SetGridTypeZ(int iDivideZ);
	__declspec(dllexport)  BOOL SetGridType3Axis(int iDivideX, int iDivideY, int iDivideZ);

	 __declspec(dllexport) int GetGridTypeX(); 
	 __declspec(dllexport) int GetGridTypeY(); 
	 __declspec(dllexport) int GetGridTypeZ(); 
	 __declspec(dllexport) void GetGridType3Axis(int &iDivideX,int &iDivideY,int &iDivideZ);
	 
	__declspec(dllexport) void SetAxisPatternX(int iPatternX);
	__declspec(dllexport) void SetAxisPatternY(int iPatternY);
	__declspec(dllexport) void SetAxisPatternZ(int iPatternZ);

	__declspec(dllexport) void AddPoint(float x, float y, float z);

	__declspec(dllexport) void SetDimensionXY();
	__declspec(dllexport) void SetDimensionYZ();
	__declspec(dllexport) void SetDimensionXZ();
	__declspec(dllexport) void SetDimensionXYZ();

	__declspec(dllexport) void SetBoxColor(COLORREF bCol);
	__declspec(dllexport) void SetBoxPattern(int nPattern);

	__declspec(dllexport) void SetRangeColorX(COLORREF xrCol);
	__declspec(dllexport) void SetRangeColorY(COLORREF yrCol);
	__declspec(dllexport) void SetRangeColorZ(COLORREF zrCol);

	__declspec(dllexport) void SetBoxEnable(BOOL bEnable);
	__declspec(dllexport) void SetPlotColor(COLORREF pCol);

	__declspec(dllexport) void Clear();

protected:
	 virtual void OnCreateGL();	//Override to set bg color, activate z-buffer, and another global setting, create 3D cubic coordinates
	 virtual void OnSizeGL(int cx, int cy);	//Override to adapte the viewport to the window
	 virtual void OnDrawGL();	//Override to issue drawing functions
	 virtual void OnDrawGDI(CPaintDC *pDC);	//Override to issue GDI drawing functions
	 float NextAbove(float val, int sig);
	 float NextBelow(float val, int sig);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGL3DGraph)
	//}}AFX_VIRTUAL

// Implementation
public:
	 __declspec(dllexport) virtual ~CGL3DGraph();

	// Generated message map functions
protected:
	/*Adding Functions*/
	 void CreateGL();
	 void SetGrid();
	/******************/

	 BOOL PtWithinAxis(float x, float y, float z);
	 __declspec(dllexport) void AutoScale(int *pDoList = NULL);
	 void RenderData();
	 float m_SymbolSize;
	//{{AFX_MSG(CGL3DGraph)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GL3DGRAPH_H__F42A3470_E6F5_44D6_8FC0_D23562F06420__INCLUDED_)
