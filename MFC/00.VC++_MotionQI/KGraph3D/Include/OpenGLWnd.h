#if !defined(AFX_OPENGLWND_H__908E674B_AD49_4D4C_BFAD_AD8C1BB51D8A__INCLUDED_)
#define AFX_OPENGLWND_H__908E674B_AD49_4D4C_BFAD_AD8C1BB51D8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenGLWnd.h : header file
#include "gl\gl.h"
#include "glut.h"

//#define GLdouble double
/////////////////////////////////////////////////////////////////////////////
// Global type definitions
	enum InfoField {VENDOR,RENDERER,VERSION,ACCELERATION,EXTENSIONS};
	enum ColorsNumber{INDEXED,THOUSANDS,MILLIONS,MILLIONS_WITH_TRANSPARENCY};
	enum ZAccuracy{NORMAL,ACCURATE};
/////////////////////////////////////////////////////////////////////////////
// general 3D classes

class __declspec(dllexport) CPoint3D
{
public:
	float x, y, z;
	 CPoint3D() {x=y=z = 0;}
	 CPoint3D(float c1, float c2, float c3)
	{
		x= c1;	y = c2;		z = c3;
	}	
	 CPoint3D& operator=(const CPoint3D& pt)
	{
		x = pt.x;		y = pt.y;		z = pt.z;
		return *this;
	}

	 CPoint3D (const CPoint3D &pt)
	{
		*this = pt;
	}
	 void Translate(float cx, float cy, float cz)
	{
		x += cx;
		y += cy;
		z += cz;
	}
};



/////////////////////////////////////////////////////////////////////////////
// COpenGLWnd window
class COpenGLWnd : public CWnd
{
// Construction
public:
	 COpenGLWnd();

/** CGLDispList
DESC: This is an helper class which elt you create "display list objects",
      use these objects to define the key elements in your scene(a disp. list
	  is faster than the corresponding GL commands)
	  - Through the class members functions you have all total control on 
	  a single display list.
	  - An isolated display list save OGL parameters before execution
	  (So it's not affected by preceding tranformations or setting)
*******/
	class  CGLDispList
	{
		friend class COpenGLWnd;
	private:
		BOOL m_bIsolated;
		int m_glListId;
	public:
		 CGLDispList();		//Constructor
		~CGLDispList();
		 void StartDef(BOOL bImmediateExec = FALSE);	//enclose a disp.list def.
		 void EndDef();
		 void Draw();	//execute display list GL commands
		 void SetIsolation(BOOL bValue){m_bIsolated = bValue;}	//Set Isolation property
	};

// Attributes
public:

// Operations
public:
	 void DrawBox(CPoint3D org, float x, float y, float z);

	/*Stock Display lists functions
	DESC. : These display lists are internally organized in a vector(20 max),
			you have control on definition and redrawing only.
			Use them for background elements which are to be draw everytime
			all together
	        Between BeginStockDispList and EndStockDispList should be present
			OpenGL calls only(see documetation for which are allowed how are them treated)
	*/
	
	 void StartStockDListDef();		//allocates a new stock display list entry and opens a display list definition
	 void EndStockListDef();			//Close a stock display list definition
	 void DrawStockDispLists();		//Execute all the stock display lists
	 void ClearStockDispLists();		//deletes all the stock display lists

	//Information retrieval function
	 const CString GetInformation(InfoField type);
	//Mouse cursor function
	 void SetMouseCursor(HCURSOR mcursor = NULL);
	//Attribute retrieval function
	 double GetAspectRatio() {return m_dAspectRatio;};
	//Rendering Context switching
	void BeginGLCommands();		//use to issue GL commands outside Overriables
	 void EndGLCommands();		//i.e: in menu event handlers, button events handler etc.
	//Font stuff
	 void MakeFont();
	 void PrintString(const char* str);

//Overriables
	 virtual void OnCreateGL();		//Override to set bg color, activate z-buffer, and other global settings
	 virtual void OnSizeGL(int cx, int cy);	//Override to adapt the viewport to the window
	 virtual void OnDrawGL();		//Override to issue drawing functions
	 virtual void OnDrawGDI(CPaintDC *pDC);	//Override to issue GDI drawing functions
	 virtual void VideoMode(ColorsNumber &c, ZAccuracy &z, BOOL &dbuf);	//Override to specify some video mode parameters

// Overrides
//NOTE: These have been declared private because theu shouldn't be 
//		overridden, use the provided virtual functions instead
private:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	 void CopyToClipboard();
	 __declspec(dllexport) void SetBackgroundColor(COLORREF rgb);
	 virtual ~COpenGLWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(COpenGLWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	 afx_msg void OnDestroy();
	 afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	 afx_msg void OnSize(UINT nType, int cx, int cy);
	 afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	 afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//member variables
private:
	CDC* m_pCDC;		//Win GDI Device Context
	HGLRC m_hRC;		//OpenGL Rendering Context
	HCURSOR m_hMouseCursor;			//mouse cursor handle for the view
	CPalette m_CurrentPalette;		//Palettes
	CPalette* m_pOldPalette;
	CRect m_ClientRect;				//Client Area Size
	double m_dAspectRatio;			//Aspect
	int m_DispListVector[20];		//Internal stock display list vector
	BOOL m_bInsideDispList;			//Disp List definition semaphore
	BOOL m_bExternGLCall;
	BOOL m_bExternDispListCall;
	GLuint m_FontListBase;
	BOOL m_bGotFont;
	//initialization helper functions
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
	void CreateRGBPalette();
	BOOL bSetupPixelFormat();
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLWND_H__908E674B_AD49_4D4C_BFAD_AD8C1BB51D8A__INCLUDED_)
