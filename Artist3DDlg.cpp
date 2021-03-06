// Artist3DDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Artist3D.h"
#include "Artist3DDlg.h"


#include <gl\gl.h> 
#include <gl\glu.h> 
#include <gl\glut.h> 
#include <gl\glaux.h> 


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CArtist3DDlg 对话框




CArtist3DDlg::CArtist3DDlg(CWnd* pParent /*=NULL*/)
: CDialog(CArtist3DDlg::IDD, pParent)
{
	PixelFormat=0; 
	m_yRotate=0;
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CArtist3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CArtist3DDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CArtist3DDlg::OnBnClickedButtonBrowse)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_XSCALE, &CArtist3DDlg::OnNMCustomdrawSliderXscale)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_YSCALE, &CArtist3DDlg::OnNMCustomdrawSliderYscale)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ZSCALE, &CArtist3DDlg::OnNMCustomdrawSliderZscale)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_XROTA, &CArtist3DDlg::OnNMCustomdrawSliderXrota)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_YROTA, &CArtist3DDlg::OnNMCustomdrawSliderYrota)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ZROTA, &CArtist3DDlg::OnNMCustomdrawSliderZrota)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_XTRAN, &CArtist3DDlg::OnNMCustomdrawSliderXtran)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_YTRAN, &CArtist3DDlg::OnNMCustomdrawSliderYtran)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ZTRAN, &CArtist3DDlg::OnNMCustomdrawSliderZtran)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MAXSCALE, &CArtist3DDlg::OnNMCustomdrawSliderMaxscale)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_NORMALLOOK, &CArtist3DDlg::OnBnClickedRadioNormallook)
	ON_BN_CLICKED(IDC_RADIO_LINEHIDDEN, &CArtist3DDlg::OnBnClickedRadioLinehidden)
	ON_BN_CLICKED(IDC_RADIO_REAL, &CArtist3DDlg::OnBnClickedRadioReal)
	ON_BN_CLICKED(IDC_BUTTON_SHOW, &CArtist3DDlg::OnBnClickedButtonShow)
	ON_BN_CLICKED(IDC_RADIO_ORTH, &CArtist3DDlg::OnBnClickedRadioOrth)
	ON_BN_CLICKED(IDC_RADIO_PRO, &CArtist3DDlg::OnBnClickedRadioPro)
	ON_BN_CLICKED(IDC_BUTTON_ZBUFFER, &CArtist3DDlg::OnBnClickedButtonZbuffer)
	ON_BN_CLICKED(IDC_BUTTON_XBUFFER, &CArtist3DDlg::OnBnClickedButtonXbuffer)
	ON_BN_CLICKED(IDC_BUTTON_YBUFFER, &CArtist3DDlg::OnBnClickedButtonYbuffer)
END_MESSAGE_MAP()


// CArtist3DDlg 消息处理程序

BOOL CArtist3DDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 初始化参数及控制控件
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_XSCALE))->SetRange(-100, 100, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_YSCALE))->SetRange(-100, 100, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_ZSCALE))->SetRange(-100, 100, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_XSCALE))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_YSCALE))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_ZSCALE))->SetPos(0);

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_XROTA))->SetRange(-180, 180, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_YROTA))->SetRange(-180, 180, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_ZROTA))->SetRange(-180, 180, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_XROTA))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_YROTA))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_ZROTA))->SetPos(0);

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_XTRAN))->SetRange(-100, 100, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_YTRAN))->SetRange(-100, 100, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_ZTRAN))->SetRange(-100, 100, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_XTRAN))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_YTRAN))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_ZTRAN))->SetPos(0);

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_MAXSCALE))->SetRange(1, 1000, TRUE);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_MAXSCALE))->SetPos(100);

	((CButton*)GetDlgItem(IDC_RADIO_ORTH))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_NORMALLOOK))->SetCheck(TRUE);

	xScale = yScale = zScale = 1.0;
	xRota = yRota = zRota = 0.0;
	xTran = yTran = zTran = 0.0;
	MaxScale = 100;
	MaxRota = 180;
	MaxTran = 100;
	CB = NULL;

	CB = new COLORREF*[HJQ_UPPER + 1];
	for(int i = 0; i <= HJQ_UPPER; i++)
	{
		CB[i] = new COLORREF[HJQ_UPPER + 1];
	}

	/////////////初始化OpenGL/////////////
	Renderer = GetDlgItem(IDC_RENDER); 
	hrenderDC = ::GetDC(Renderer->m_hWnd);

	if(SetWindowPixelFormat(hrenderDC) == FALSE) 
		return 0; 

	if(CreateViewGLContext(hrenderDC) == FALSE) 
		return 0; 

	spin = 0.0;
	Renderer->GetClientRect(&Canvas);

	InitOpenGL();

	return TRUE;		// 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
// 来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
// 这将由框架自动完成。

void CArtist3DDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		if(ShowImagePattern != PATTERN1)
		{
			CRect ClientRect;
			CPaintDC dc(this);
			GetClientRect(ClientRect);

			CDC memDC;
			memDC.CreateCompatibleDC(&dc);

			CBitmap memBitmap, *oldmemBitmap;
			CBitmap* BackupCanvas = GetBitmap(dc , 0, 0, ClientRect.Width(), ClientRect.Height());
			CopyBitmap(*BackupCanvas, memBitmap);
			ReleaseBitmap(BackupCanvas);
			oldmemBitmap = memDC.SelectObject(&memBitmap);

			switch(ShowImagePattern)
			{
			case PATTERN2:
				{
					DrawImage(memDC);
					ShowImagePattern = PATTERN1;
					break;
				}
			}

			BitBlt(dc, 0, 0, ClientRect.Width(), ClientRect.Height(), memDC, 0, 0, SRCCOPY);

			memDC.SelectObject(oldmemBitmap);
		}
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。


bool CArtist3DDlg::CopyBitmap( const CBitmap &bmpSrc, CBitmap &bmpDest )
{
	bool bResult = false;
	BITMAP bm;

	// Attempt to retrieve the existing bitmap structure.
	if ( 0 == bmpSrc.GetObject( sizeof(BITMAP), &bm ) )
	{
		return bResult;
	}

	// Get a handle to the current device context.
	HDC hDC = ::GetDC( NULL );

	// Prepare a new bitmap info structure.
	// Note this function allocates the memory for the structure,
	// so make sure that the memory gets freed.
	BITMAPINFO *pBmpInfo = new BITMAPINFO;
	::ZeroMemory( pBmpInfo, sizeof(BITMAPINFO) );

	pBmpInfo->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	pBmpInfo->bmiHeader.biWidth        = bm.bmWidth;
	pBmpInfo->bmiHeader.biHeight    = bm.bmHeight ;
	pBmpInfo->bmiHeader.biPlanes    = 1;
	pBmpInfo->bmiHeader.biBitCount    = 24;

	// This calculation was taken from Ivaylo Byalkov's article about smooth bitmap scaling.
	pBmpInfo->bmiHeader.biSizeImage    = ((3 * bm.bmWidth + 3) & ~3) * bm.bmHeight;

	// Don't try to use a NULL pointer.
	if ( NULL != pBmpInfo )
	{
		// Allocate a buffer to store the device independent bits from the source bitmap.
		BYTE *pData = new BYTE[pBmpInfo->bmiHeader.biSizeImage];

		if ( NULL != pData )
		{
			// Get the device independent bits from the source bitmap.
			::GetDIBits( hDC, (HBITMAP)bmpSrc, 0, bm.bmHeight, pData, pBmpInfo, DIB_RGB_COLORS );

			// Make sure that the destination bitmap is empty.
			bmpDest.DeleteObject();

			// Create a temporary bitmap handle with the same dimensions of the source bitmap.
			HBITMAP hTmpBmp = ::CreateCompatibleBitmap( hDC, bm.bmWidth, bm.bmHeight );

			// Set the device independent bits from the source bitmap into the temporary bitmap handle.
			::SetDIBits( hDC, hTmpBmp, 0, bm.bmHeight, pData, pBmpInfo, DIB_RGB_COLORS );

			// Detach the old bitmap.
			bmpDest.Detach();

			// Attach the temporary bitmap handle to the destination bitmap.
			bmpDest.Attach( hTmpBmp );

			// Set the dimensions of the bitmap so that they can be used later.
			// Otherwise, they will be invalid.
			bmpDest.SetBitmapDimension( bm.bmWidth, bm.bmHeight );

			// Free the buffer used to store the bits.
			delete [] pData;

			// The bitmap was successfully copied.
			bResult = true;
		}

		// Free the memory for the bitmap info structure.
		delete pBmpInfo;
	}

	// Release the device context.
	::ReleaseDC( NULL, hDC );

	return bResult;
}
CBitmap* CArtist3DDlg::GetBitmap(CDC& dc, int x1, int y1, int x2, int y2)
{
	CDC memDC;//内存DC
	memDC.CreateCompatibleDC(&dc);

	CBitmap *memBitmap, *oldmemBitmap;
	memBitmap = new CBitmap();
	memBitmap->CreateCompatibleBitmap(&dc, x2 - x1, y2 - y1);

	oldmemBitmap = memDC.SelectObject(memBitmap);
	memDC.BitBlt(0, 0, x2 - x1, y2 - y1, &dc, x1, y1, SRCCOPY);
	memDC.SelectObject(oldmemBitmap);

	return memBitmap;
}

void CArtist3DDlg::ReleaseBitmap(CBitmap* bitmap)
{
	delete bitmap;
}

//
shape* CArtist3DDlg::CopyShape(shape s, int index)
{
	shape* res = new shape;
	res->faceAmount = s.faceAmount;
	res->pointAmount = s.pointAmount;
	res->faces = new face[res->faceAmount];
	res->points = new point[res->pointAmount];
	switch (index)
	{
	case 0://z
		{
			res->maxx = s.maxx;
			res->maxy = s.maxy;
			res->maxz = s.maxz;
			res->minx = s.minx;
			res->miny = s.miny;
			res->minz = s.minz;
			for(int i = 0; i < res->pointAmount; i++)
			{
				res->points[i].x = s.points[i].x;
				res->points[i].y = s.points[i].y;
				res->points[i].z = s.points[i].z;
			}
			for (int i = 0; i < res->faceAmount; i++)
			{
				res->faces[i].maxx = s.faces[i].maxx;
				res->faces[i].maxy = s.faces[i].maxy;
				res->faces[i].maxz = s.faces[i].maxz;
				res->faces[i].minx = s.faces[i].minx;
				res->faces[i].miny = s.faces[i].miny;
				res->faces[i].minz = s.faces[i].minz;
				res->faces[i].p1 = s.faces[i].p1;
				res->faces[i].p2 = s.faces[i].p2;
				res->faces[i].p3 = s.faces[i].p3;
				res->faces[i].r = s.faces[i].r;
				res->faces[i].g = s.faces[i].g;
				res->faces[i].b = s.faces[i].b;
				res->faces[i].et.SetSize(s.faces[i].et.GetSize());
				for(int j = 0; j < res->faces[i].et.GetSize(); j++)
				{
					res->faces[i].et.SetAt(j, s.faces[i].et.GetAt(j));
				}
			}
			break;
		}
	case 1://y
		{
			res->maxz = s.maxx;
			res->maxx = s.maxy;
			res->maxy = s.maxz;
			res->minz = s.minx;
			res->minx = s.miny;
			res->miny = s.minz;
			for(int i = 0; i < res->pointAmount; i++)
			{
				res->points[i].z = s.points[i].x;
				res->points[i].x = s.points[i].y;
				res->points[i].y = s.points[i].z;
			}
			for (int i = 0; i < res->faceAmount; i++)
			{
				res->faces[i].maxz = s.faces[i].maxx;
				res->faces[i].maxx = s.faces[i].maxy;
				res->faces[i].maxy = s.faces[i].maxz;
				res->faces[i].minz = s.faces[i].minx;
				res->faces[i].minx = s.faces[i].miny;
				res->faces[i].miny = s.faces[i].minz;
				res->faces[i].p1 = s.faces[i].p1;
				res->faces[i].p2 = s.faces[i].p2;
				res->faces[i].p3 = s.faces[i].p3;
				res->faces[i].r = s.faces[i].r;
				res->faces[i].g = s.faces[i].g;
				res->faces[i].b = s.faces[i].b;
				res->faces[i].et.SetSize(s.faces[i].et.GetSize());
				for(int j = 0; j < res->faces[i].et.GetSize(); j++)
				{
					res->faces[i].et.SetAt(j, s.faces[i].et.GetAt(j));
				}
			}
			break;
		}
	case 2:
		{
			res->maxy = s.maxx;
			res->maxz = s.maxy;
			res->maxx = s.maxz;
			res->miny = s.minx;
			res->minz = s.miny;
			res->minx = s.minz;
			for(int i = 0; i < res->pointAmount; i++)
			{
				res->points[i].y = s.points[i].x;
				res->points[i].z = s.points[i].y;
				res->points[i].x = s.points[i].z;
			}
			for (int i = 0; i < res->faceAmount; i++)
			{
				res->faces[i].maxy = s.faces[i].maxx;
				res->faces[i].maxz = s.faces[i].maxy;
				res->faces[i].maxx = s.faces[i].maxz;
				res->faces[i].miny = s.faces[i].minx;
				res->faces[i].minz = s.faces[i].miny;
				res->faces[i].minx = s.faces[i].minz;
				res->faces[i].p1 = s.faces[i].p1;
				res->faces[i].p2 = s.faces[i].p2;
				res->faces[i].p3 = s.faces[i].p3;
				res->faces[i].r = s.faces[i].r;
				res->faces[i].g = s.faces[i].g;
				res->faces[i].b = s.faces[i].b;
				res->faces[i].et.SetSize(s.faces[i].et.GetSize());
				for(int j = 0; j < res->faces[i].et.GetSize(); j++)
				{
					res->faces[i].et.SetAt(j, s.faces[i].et.GetAt(j));
				}
			}
			break;
		}
	}
	return res;
}
//
void CArtist3DDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	for(int i = 0; i < s.faceAmount; i++)
	{
		ET* et = &(s.faces[i].et);
		for(int j = et->GetCount() - 1; j >=0; j--)
		{
			CList<ETElement*>* ete = et->GetAt(j);
			for(int k = ete->GetCount() - 1; k >= 0; k--)
			{
				delete ete->GetAt(ete->FindIndex(k));
				ete->RemoveAt(ete->FindIndex(k));
			}
			delete ete;
			et->RemoveAt(j);
		}
	}
	delete[] s.faces;
	delete[] s.points;
	for(int i = 0; i <= HJQ_UPPER; i++)
	{
		delete[] CB[i];
	}
	delete[] CB;

	CDialog::OnClose();
}

HCURSOR CArtist3DDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CArtist3DDlg::SetWindowPixelFormat(HDC hDC) 
{ 
	PIXELFORMATDESCRIPTOR pixelDesc; 

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR); 
	pixelDesc.nVersion = 1; 

	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW |  
		PFD_SUPPORT_OPENGL | 
		PFD_DOUBLEBUFFER | 
		PFD_TYPE_RGBA; 

	pixelDesc.iPixelType = PFD_TYPE_RGBA; 
	pixelDesc.cColorBits = 32; 
	pixelDesc.cRedBits = 0; 
	pixelDesc.cRedShift = 0; 
	pixelDesc.cGreenBits = 0; 
	pixelDesc.cGreenShift = 0; 
	pixelDesc.cBlueBits = 0; 
	pixelDesc.cBlueShift = 0; 
	pixelDesc.cAlphaBits = 0; 
	pixelDesc.cAlphaShift = 0; 
	pixelDesc.cAccumBits = 0; 
	pixelDesc.cAccumRedBits = 0; 
	pixelDesc.cAccumGreenBits = 0; 
	pixelDesc.cAccumBlueBits = 0; 
	pixelDesc.cAccumAlphaBits = 0; 
	pixelDesc.cDepthBits = 0; 
	pixelDesc.cStencilBits = 1; 
	pixelDesc.cAuxBuffers = 0; 
	pixelDesc.iLayerType = PFD_MAIN_PLANE; 
	pixelDesc.bReserved = 0; 
	pixelDesc.dwLayerMask = 0; 
	pixelDesc.dwVisibleMask = 0; 
	pixelDesc.dwDamageMask = 0; 

	PixelFormat = ChoosePixelFormat(hDC,&pixelDesc); 
	if(PixelFormat == 0) // Choose default 
	{ 
		PixelFormat = 1; 
		if(DescribePixelFormat(hDC,PixelFormat, 
			sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc) == 0) 
		{ 
			return FALSE; 
		} 
	} 

	if(SetPixelFormat(hDC,PixelFormat,&pixelDesc) == FALSE) 
	{  
		return FALSE; 
	} 

	return TRUE; 
} 


BOOL CArtist3DDlg::CreateViewGLContext(HDC hDC) 
{ 
	hrenderRC = wglCreateContext(hDC); 

	if(hrenderRC == NULL) 
		return FALSE; 

	if(wglMakeCurrent(hDC,hrenderRC) == FALSE) 
		return FALSE; 

	return TRUE; 
} 



void CArtist3DDlg::InitGraph()
{
	xScale = yScale = zScale = 1.0;
	xRota = yRota = zRota = 0.0;
	xTran = yTran = zTran = 0.0;
	MaxScale = 100;
	MaxRota = 180;
	MaxTran = 100;

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_XSCALE))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_YSCALE))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_ZSCALE))->SetPos(0);

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_XROTA))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_YROTA))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_ZROTA))->SetPos(0);

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_XTRAN))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_YTRAN))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_ZTRAN))->SetPos(0);

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_MAXSCALE))->SetPos(100);

	InitOpenGL();
}
void CArtist3DDlg::InitOpenGL()
{
	glShadeModel(GL_FLAT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);

	glViewport(0, 0, Canvas.Width(), Canvas.Height());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(((CButton*)GetDlgItem(IDC_RADIO_ORTH))->GetCheck())
	{
		glOrtho(-200.0, 200.0, -200.0, 200.0, -200.0, 200.0);
	}else if(((CButton*)GetDlgItem(IDC_RADIO_PRO))->GetCheck())
	{
		gluPerspective(90, 1, 0.1, 100000.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);

}


void CArtist3DDlg::RenderScene()    
{

	if(((CButton*)GetDlgItem(IDC_RADIO_NORMALLOOK))->GetCheck())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPushMatrix();
		glTranslated(xTran, yTran, zTran);
		glRotated(xRota, 1.0, 0, 0);
		glRotated(yRota, 0, 1.0, 0);
		glRotated(zRota, 0, 0, 1.0);
		glScaled(xScale, yScale, zScale);
		glColor3d(1.0, 1.0, 1.0);
		for(int i = 0; i < s.faceAmount; i++)
		{
			glBegin(GL_TRIANGLES);
			glVertex3f(s.points[s.faces[i].p1].x, s.points[s.faces[i].p1].y, s.points[s.faces[i].p1].z);
			glVertex3f(s.points[s.faces[i].p2].x, s.points[s.faces[i].p2].y, s.points[s.faces[i].p2].z);
			glVertex3f(s.points[s.faces[i].p3].x, s.points[s.faces[i].p3].y, s.points[s.faces[i].p3].z);
			glEnd();
		}
		glPopMatrix();
		SwapBuffers(hrenderDC);
	} else if (((CButton*)GetDlgItem(IDC_RADIO_LINEHIDDEN))->GetCheck())
	{
		glClearDepth(1.0f);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPushMatrix();
		glTranslated(xTran, yTran, zTran);
		glRotated(xRota, 1.0, 0, 0);
		glRotated(yRota, 0, 1.0, 0);
		glRotated(zRota, 0, 0, 1.0);
		glScaled(xScale, yScale, zScale);

		glEnable(GL_DEPTH_TEST);
		glColor3d(1.0, 1.0, 1.0);
		for(int i = 0; i < s.faceAmount; i++)
		{
			glBegin(GL_TRIANGLES);
			glVertex3f(s.points[s.faces[i].p1].x, s.points[s.faces[i].p1].y, s.points[s.faces[i].p1].z);
			glVertex3f(s.points[s.faces[i].p2].x, s.points[s.faces[i].p2].y, s.points[s.faces[i].p2].z);
			glVertex3f(s.points[s.faces[i].p3].x, s.points[s.faces[i].p3].y, s.points[s.faces[i].p3].z);
			glEnd();
		}

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPushMatrix();

 		glEnable(GL_POLYGON_OFFSET_FILL); 
 		glPolygonOffset(1.0, 1.0);

		glColor3d(0.0, 0.0, 0.0);
 		for(int i = 0; i < s.faceAmount; i++)
 		{
 			glBegin(GL_TRIANGLES);
 			glVertex3f(s.points[s.faces[i].p1].x, s.points[s.faces[i].p1].y, s.points[s.faces[i].p1].z);
 			glVertex3f(s.points[s.faces[i].p2].x, s.points[s.faces[i].p2].y, s.points[s.faces[i].p2].z);
 			glVertex3f(s.points[s.faces[i].p3].x, s.points[s.faces[i].p3].y, s.points[s.faces[i].p3].z);
 			glEnd();
 		}
		glDisable(GL_POLYGON_OFFSET_FILL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPopMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPopMatrix();
		SwapBuffers(hrenderDC);

	}else if (((CButton*)GetDlgItem(IDC_RADIO_REAL))->GetCheck())
	{
		glClearDepth(1.0f);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 1.0);
		glPushMatrix();
		glShadeModel(GL_SMOOTH);
		glTranslated(xTran, yTran, zTran);
		glRotated(xRota, 1.0, 0, 0);
		glRotated(yRota, 0, 1.0, 0);
		glRotated(zRota, 0, 0, 1.0);
		glScaled(xScale, yScale, zScale);
		for(int i = 0; i < s.faceAmount; i++)
		{
			glBegin(GL_POLYGON);
			glVertex3f(s.points[s.faces[i].p1].x, s.points[s.faces[i].p1].y, s.points[s.faces[i].p1].z);
			glVertex3f(s.points[s.faces[i].p2].x, s.points[s.faces[i].p2].y, s.points[s.faces[i].p2].z);
			glVertex3f(s.points[s.faces[i].p3].x, s.points[s.faces[i].p3].y, s.points[s.faces[i].p3].z);
			glEnd();
		}

		glPopMatrix();




		GLfloat mat_diffuse[4] = {1.0f, 0.5f, 0.5f ,1.0f};
		GLfloat mat_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat mat_shininess[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat mat_ambient[4] = {1.0f, 0.5f, 0.5f, 1.0f};

		//光源 1
		GLfloat light_position0[4]={0.0f, 100.0f, 100.0f, 0.0f};
		GLfloat light_ambient[4] = {0.0f, 1.0f, 0.1f, 1.0f};

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		
		//glLightf( GL_LIGHT0,GL_SPOT_CUTOFF , 45.0 );  
		GLfloat spot_direction[]={ -1.0 , -1.0 , 0.0 };
		glLightfv( GL_LIGHT0 , GL_SPOT_DIRECTION , spot_direction ); 


		//使模型能接受光照

		glEnable(GL_LIGHTING); 
		glEnable(GL_LIGHT0);	


		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
 		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);

		//计算定点法线
		glEnable(GL_AUTO_NORMAL);
		glEnable(GL_NORMALIZE);


		SwapBuffers(hrenderDC);
	}
} 

void CArtist3DDlg::Reshape()
{
}

void CArtist3DDlg::ReadInFile(CString path)
{
	//CStdioFile file;
	//file.Open(path, CStdioFile::bufferRead);
	CompatibleFile file(path);
	CString line;

	//file.ReadString(line);	// 读入版本信息
	line = file.ReadLine(); // 读入版本信息
	line = line.Mid(line.FindOneOf(" ") + 1).Trim();
	if(line == "1.0")
	{
		version = 0;
	}else if(line == "1.1")
	{
		version = 1;
	}
	//file.ReadString(line);	// 读入顶点数
	line = file.ReadLine(); // 读入顶点数
	s.pointAmount = atoi(line.Mid(line.FindOneOf(" ") + 1).Trim());
	//file.ReadString(line);	// 读入平面数
	line = file.ReadLine(); // 读入平面数
	s.faceAmount = atoi(line.Mid(line.FindOneOf(" ") + 1).Trim());

	if(s.points)
		delete[] s.points;
	if(s.faces)
		delete[] s.faces;
	s.points = new point[s.pointAmount];
	s.faces = new face[s.faceAmount];
	s.maxx = s.maxy = s.maxz = LLONG_MIN;
	s.minx = s.miny = s.minz = LLONG_MAX;
	for(int i = 0; i < s.faceAmount; i++)
	{
		s.faces[i].minx = s.faces[i].miny = s.faces[i].minz = LLONG_MAX;
		s.faces[i].maxx = s.faces[i].maxy = s.faces[i].maxz = LLONG_MIN;
	}

	long pointi = 0;
	long facei = 0;
	while(!file.IsEOF())
	{
		//file.ReadString(line);
		line = file.ReadLine();
		line = line.Trim();
		if(line.IsEmpty())
			continue;

		switch (line[0])
		{
		case 'v':
			{
				line = line.Mid(line.FindOneOf(" ")).Trim();
				s.points[pointi].x = atof(line.Mid(0, line.FindOneOf(" ")).Trim());
				line = line.Mid(line.FindOneOf(" ")).Trim();
				s.points[pointi].y = atof(line.Mid(0, line.FindOneOf(" ")).Trim());
				line = line.Mid(line.FindOneOf(" ")).Trim();
				s.points[pointi].z = atof(line.Trim());

				if(s.points[pointi].x < s.minx) s.minx = s.points[pointi].x;
				if(s.points[pointi].y < s.miny) s.miny = s.points[pointi].y;
				if(s.points[pointi].z < s.minz) s.minz = s.points[pointi].z;

				if(s.points[pointi].x > s.maxx) s.maxx = s.points[pointi].x;
				if(s.points[pointi].y > s.maxy) s.maxy = s.points[pointi].y;
				if(s.points[pointi].z > s.maxz) s.maxz = s.points[pointi].z;

				pointi++;
			}
			break;
		case 'f':
			{
				line = line.Mid(line.FindOneOf(" ")).Trim();
				s.faces[facei].p1 = atoi(line.Mid(0, line.FindOneOf(" ")).Trim());
				line = line.Mid(line.FindOneOf(" ")).Trim();
				s.faces[facei].p2 = atoi(line.Mid(0, line.FindOneOf(" ")).Trim());
				line = line.Mid(line.FindOneOf(" ")).Trim();
				s.faces[facei].p3 = atoi(line.Trim());

				if(version == 1)
				{
					s.faces[facei].p1--;
					s.faces[facei].p2--;
					s.faces[facei].p3--;
				}

				if(s.points[s.faces[facei].p1].x < s.faces[facei].minx) s.faces[facei].minx = s.points[s.faces[facei].p1].x;
				if(s.points[s.faces[facei].p2].x < s.faces[facei].minx) s.faces[facei].minx = s.points[s.faces[facei].p2].x;
				if(s.points[s.faces[facei].p3].x < s.faces[facei].minx) s.faces[facei].minx = s.points[s.faces[facei].p3].x;
				if(s.points[s.faces[facei].p1].y < s.faces[facei].miny) s.faces[facei].miny = s.points[s.faces[facei].p1].y;
				if(s.points[s.faces[facei].p2].y < s.faces[facei].miny) s.faces[facei].miny = s.points[s.faces[facei].p2].y;
				if(s.points[s.faces[facei].p3].y < s.faces[facei].miny) s.faces[facei].miny = s.points[s.faces[facei].p3].y;
				if(s.points[s.faces[facei].p1].z < s.faces[facei].minz) s.faces[facei].minz = s.points[s.faces[facei].p1].z;
				if(s.points[s.faces[facei].p2].z < s.faces[facei].minz) s.faces[facei].minz = s.points[s.faces[facei].p2].z;
				if(s.points[s.faces[facei].p3].z < s.faces[facei].minz) s.faces[facei].minz = s.points[s.faces[facei].p3].z;

				if(s.points[s.faces[facei].p1].x > s.faces[facei].maxx) s.faces[facei].maxx = s.points[s.faces[facei].p1].x;
				if(s.points[s.faces[facei].p2].x > s.faces[facei].maxx) s.faces[facei].maxx = s.points[s.faces[facei].p2].x;
				if(s.points[s.faces[facei].p3].x > s.faces[facei].maxx) s.faces[facei].maxx = s.points[s.faces[facei].p3].x;
				if(s.points[s.faces[facei].p1].y > s.faces[facei].maxy) s.faces[facei].maxy = s.points[s.faces[facei].p1].y;
				if(s.points[s.faces[facei].p2].y > s.faces[facei].maxy) s.faces[facei].maxy = s.points[s.faces[facei].p2].y;
				if(s.points[s.faces[facei].p3].y > s.faces[facei].maxy) s.faces[facei].maxy = s.points[s.faces[facei].p3].y;
				if(s.points[s.faces[facei].p1].z > s.faces[facei].maxz) s.faces[facei].maxz = s.points[s.faces[facei].p1].z;
				if(s.points[s.faces[facei].p2].z > s.faces[facei].maxz) s.faces[facei].maxz = s.points[s.faces[facei].p2].z;
				if(s.points[s.faces[facei].p3].z > s.faces[facei].maxz) s.faces[facei].maxz = s.points[s.faces[facei].p3].z;

				s.faces[facei].et.SetSize(HJQ_UPPER + 1);
				for(int i = 0; i <= HJQ_UPPER; i++)
				{
					s.faces[facei].et.SetAt(i, new CList<ETElement*>);
					s.faces[facei].et.GetAt(i)->RemoveAll();
				}

				s.faces[facei].r = rand() % 256;
				s.faces[facei].g = rand() % 256;
				s.faces[facei].b = rand() % 256;
				facei++;
			}
			break;
		default:
			break;
		}
	}
	file.Close();
}
void CArtist3DDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	Reshape();
}

void CArtist3DDlg::OnBnClickedButtonBrowse()
{	
	CFileDialog cfd(TRUE);
	if(cfd.DoModal()==IDOK) 
	{
		SetDlgItemText(IDC_EDIT_PATH, cfd.GetPathName());
	}
}

void CArtist3DDlg::OnBnClickedButtonShow()
{
	// TODO: 在此添加控件通知处理程序代码
	CString path;
	GetDlgItemText(IDC_EDIT_PATH, path);
	ReadInFile(path);
	InitGraph();
	RenderScene();
}




double CArtist3DDlg::DistanceBetween(CPoint p1, CPoint p2)
{
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;
	return sqrt(0.0f + dx * dx + dy * dy);
}



// 参数修改
void CArtist3DDlg::OnNMCustomdrawSliderXscale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)(GetDlgItem(IDC_SLIDER_XSCALE));
	int pos = pSlider->GetPos();
	double k = (MaxScale - 1.0) / pSlider->GetRangeMax();
	if(pos > 0)
		xScale = k * pos + 1;
	else
		xScale = 1 / (-k * pos + 1);
	RenderScene();
	*pResult = 0;
}

void CArtist3DDlg::OnNMCustomdrawSliderYscale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)(GetDlgItem(IDC_SLIDER_YSCALE));
	int pos = pSlider->GetPos();
	double k = (MaxScale - 1.0) / pSlider->GetRangeMax();
	if(pos > 0)
		yScale = k * pos + 1;
	else
		yScale = 1 / (-k * pos + 1);
	RenderScene();
	*pResult = 0;
}

void CArtist3DDlg::OnNMCustomdrawSliderZscale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)(GetDlgItem(IDC_SLIDER_ZSCALE));
	int pos = pSlider->GetPos();
	double k = (MaxScale - 1.0) / pSlider->GetRangeMax();
	if(pos > 0)
		zScale = k * pos + 1;
	else
		zScale = 1 / (-k * pos + 1);
	RenderScene();
	*pResult = 0;
}

void CArtist3DDlg::OnNMCustomdrawSliderXtran(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)(GetDlgItem(IDC_SLIDER_XTRAN));
	int pos = pSlider->GetPos();
	xTran = pos;
	RenderScene();
	*pResult = 0;
}
void CArtist3DDlg::OnNMCustomdrawSliderYtran(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)(GetDlgItem(IDC_SLIDER_YTRAN));
	int pos = pSlider->GetPos();
	yTran = pos;
	RenderScene();
	*pResult = 0;
}
void CArtist3DDlg::OnNMCustomdrawSliderZtran(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)(GetDlgItem(IDC_SLIDER_ZTRAN));
	int pos = pSlider->GetPos();
	zTran = pos;
	RenderScene();
	*pResult = 0;
}
void CArtist3DDlg::OnNMCustomdrawSliderXrota(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)(GetDlgItem(IDC_SLIDER_XROTA));
	int pos = pSlider->GetPos();
	xRota = pos;
	RenderScene();
	*pResult = 0;
}
void CArtist3DDlg::OnNMCustomdrawSliderYrota(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)(GetDlgItem(IDC_SLIDER_YROTA));
	int pos = pSlider->GetPos();
	yRota = pos;
	RenderScene();
	*pResult = 0;
}
void CArtist3DDlg::OnNMCustomdrawSliderZrota(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)(GetDlgItem(IDC_SLIDER_ZROTA));
	int pos = pSlider->GetPos();
	zRota = pos;
	RenderScene();
	*pResult = 0;
}

void CArtist3DDlg::OnNMCustomdrawSliderMaxscale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)(GetDlgItem(IDC_SLIDER_MAXSCALE));
	int pos = pSlider->GetPos();
	MaxScale = pos;
	OnNMCustomdrawSliderXscale(pNMHDR, pResult);
	OnNMCustomdrawSliderYscale(pNMHDR, pResult);
	OnNMCustomdrawSliderZscale(pNMHDR, pResult);
	RenderScene();
	*pResult = 0;
}


// 模式修改
void CArtist3DDlg::OnBnClickedRadioNormallook()
{
	InitOpenGL();
	RenderScene();
}

void CArtist3DDlg::OnBnClickedRadioLinehidden()
{
	InitOpenGL();
	RenderScene();
}

void CArtist3DDlg::OnBnClickedRadioReal()
{
	InitOpenGL();
	RenderScene();
}


void CArtist3DDlg::OnBnClickedRadioOrth()
{
	OnBnClickedButtonShow();
}

void CArtist3DDlg::OnBnClickedRadioPro()
{
	OnBnClickedButtonShow();
}

void CArtist3DDlg::OnBnClickedButtonZbuffer()
{
	SingleBuffer(0);
	CRect rect;
	((CStatic*)GetDlgItem(IDC_RENDER))->GetClientRect(&rect);
	ShowImagePattern = PATTERN2;
	InvalidateRect(rect, FALSE);
}
void CArtist3DDlg::OnBnClickedButtonYbuffer()
{
	SingleBuffer(1);
	CRect rect;
	((CStatic*)GetDlgItem(IDC_RENDER))->GetClientRect(&rect);
	ShowImagePattern = PATTERN2;
	InvalidateRect(rect, FALSE);
}

void CArtist3DDlg::OnBnClickedButtonXbuffer()
{
	SingleBuffer(2);
	CRect rect;
	((CStatic*)GetDlgItem(IDC_RENDER))->GetClientRect(&rect);
	ShowImagePattern = PATTERN2;
	InvalidateRect(rect, FALSE);
}


void CArtist3DDlg::DrawImage(CDC& dc)
{
	CRect rect;
	((CStatic*)GetDlgItem(IDC_RENDER))->GetWindowRect(&rect);
	ScreenToClient(rect);//转化为对话框上的相对位置
	int x0 = rect.left, y0 = rect.top;
	for(int i = 0; i <= HJQ_UPPER; i++)
	{
		for(int j = 0; j <= HJQ_UPPER; j++)
		{
			dc.SetPixel(CPoint(x0 + i, y0 + j), CB[i][j]);
		}
	}
}


void CArtist3DDlg::SingleBuffer(int index)
{
	shape* ss = CopyShape(s, index);
	// 恶搞s for z-buffer
	double xscale = HJQ_UPPER / (ss->maxx - ss->minx);
	double yscale = HJQ_UPPER / (ss->maxy - ss->miny);
	double scale = xscale > yscale ? yscale : xscale;
	for(int i = 0; i < ss->pointAmount; i++)
	{
		ss->points[i].x = (ss->points[i].x - ss->minx) * scale;
		ss->points[i].y = (ss->points[i].y - ss->miny) * scale;
		ss->points[i].x = (int)(ss->points[i].x + 0.5);
		ss->points[i].y = (int)(ss->points[i].y + 0.5);
	}
	for(int i = 0; i < ss->faceAmount; i++)
	{
		ss->faces[i].minx = (ss->faces[i].minx - ss->minx) * scale;
		ss->faces[i].miny = (ss->faces[i].miny - ss->miny) * scale;
		ss->faces[i].maxx = (ss->faces[i].maxx - ss->minx) * scale;
		ss->faces[i].maxy = (ss->faces[i].maxy - ss->miny) * scale;

		ss->faces[i].minx = (int)(ss->faces[i].minx + 0.5);
		ss->faces[i].miny = (int)(ss->faces[i].miny + 0.5);
		ss->faces[i].maxx = (int)(ss->faces[i].maxx + 0.5);
		ss->faces[i].maxy = (int)(ss->faces[i].maxy + 0.5);
	}
	ss->minx = (ss->minx - ss->minx) * scale;
	ss->miny = (ss->miny - ss->miny) * scale;
	ss->maxx = (ss->maxx - ss->minx) * scale;
	ss->maxy = (ss->maxy - ss->miny) * scale;
	ss->minx = (int)(ss->minx + 0.5);
	ss->miny = (int)(ss->miny + 0.5);
	ss->maxx = (int)(ss->maxx + 0.5);
	ss->maxy = (int)(ss->maxy + 0.5);
	// 	建多边形Y表；对每一个多边形根据顶点最小的y值，将多边形置入多边形Y表。
	CArray<CList<PolygonYListElement*>*> PolygonYList;
	PolygonYList.SetSize(HJQ_UPPER + 1);
	for(int i = 0; i <= HJQ_UPPER; i++)
		PolygonYList.SetAt(i, new CList<PolygonYListElement*>());

	aet.RemoveAll();
	for(int i = 0; i < ss->faceAmount; i++)
	{
		PolygonYListElement* element = new PolygonYListElement;
		element->IP = i;
		element->Ymax = ss->faces[i].maxy;
		PolygonYList[(int)(ss->faces[i].miny + 0.5)]->AddTail(element);
	}
	// 	活化多边形表APT，活化边对表AET初始化为空。
	CList<PolygonYListElement*> APT;
	double ZB[HJQ_UPPER + 1];
	APT.RemoveAll();
	aet.RemoveAll();
	// 	for(每条扫描线j，j从小到大)
	// 	{
	for(int j = 0; j <= HJQ_UPPER; j++)
	{
		// 		1. 帧缓存CB中相应单元置为背景色。
		for(int k = 0; k <= HJQ_UPPER; k++) CB[j][k] = RGB(0, 0, 0);
		// 		2. 深度缓存ZB (一维数组) 置为无穷小。
		for(int k = 0; k < HJQ_UPPER; k++)	ZB[k] = LLONG_MIN;
		// 		3. 将对应扫描线j的多边形Y表中的多边形加入到活化多边形表APT中。
		CList<PolygonYListElement*>* HandleList = PolygonYList[j];
		for(int k = 0; k < HandleList->GetCount(); k++)
		{
			PolygonYListElement* polygonInfo = HandleList->GetAt(HandleList->FindIndex(k));
			APT.AddTail(polygonInfo);
			// 		4. 对新加入的多边形，生成其相应的边Y表。
			face* f = &(ss->faces[polygonInfo->IP]);
			if(ss->points[f->p1].y > ss->points[f->p2].y)
			{
				ETElement* ete = new ETElement;
				ete->x = ss->points[f->p2].x;
				ete->z = ss->points[f->p2].z;
				ete->dx = (ss->points[f->p1].x - ss->points[f->p2].x) / (ss->points[f->p1].y - ss->points[f->p2].y);
				ete->Ymax = ss->points[f->p1].y;
				f->et[(int)(ss->points[f->p2].y + 0.5)]->AddTail(ete);
			}else
			{
				ETElement* ete = new ETElement;
				ete->x = ss->points[f->p1].x;
				ete->z = ss->points[f->p1].z;
				ete->dx = (ss->points[f->p2].x - ss->points[f->p1].x) / (ss->points[f->p2].y - ss->points[f->p1].y);
				ete->Ymax = ss->points[f->p2].y;
				f->et[(int)(ss->points[f->p1].y + 0.5)]->AddTail(ete);
			}
			if(ss->points[f->p1].y > ss->points[f->p3].y)
			{
				ETElement* ete = new ETElement;
				ete->x = ss->points[f->p3].x;
				ete->z = ss->points[f->p3].z;
				ete->dx = (ss->points[f->p1].x - ss->points[f->p3].x) / (ss->points[f->p1].y - ss->points[f->p3].y);
				ete->Ymax = ss->points[f->p1].y;
				f->et[(int)(ss->points[f->p3].y + 0.5)]->AddTail(ete);
			}else
			{
				ETElement* ete = new ETElement;
				ete->x = ss->points[f->p1].x;
				ete->z = ss->points[f->p1].z;
				ete->dx = (ss->points[f->p3].x - ss->points[f->p1].x) / (ss->points[f->p3].y - ss->points[f->p1].y);
				ete->Ymax = ss->points[f->p3].y;
				f->et[(int)(ss->points[f->p2].y + 0.5)]->AddTail(ete);
			}
			if(ss->points[f->p2].y > ss->points[f->p3].y)
			{
				ETElement* ete = new ETElement;
				ete->x = ss->points[f->p3].x;
				ete->z = ss->points[f->p3].z;
				ete->dx = (ss->points[f->p2].x - ss->points[f->p3].x) / (ss->points[f->p2].y - ss->points[f->p3].y);
				ete->Ymax = ss->points[f->p2].y;
				f->et[(int)(ss->points[f->p3].y + 0.5)]->AddTail(ete);
			}else
			{
				ETElement* ete = new ETElement;
				ete->x = ss->points[f->p2].x;
				ete->z = ss->points[f->p2].z;
				ete->dx = (ss->points[f->p3].x - ss->points[f->p2].x) / (ss->points[f->p3].y - ss->points[f->p2].y);
				ete->Ymax = ss->points[f->p3].y;
				f->et[(int)(ss->points[f->p2].y + 0.5)]->AddTail(ete);
			}
			// 		5. 对APT中每一个多边形，若其边Y表中对应扫描线j增加了新的边，将新的边配对，加到活化边对表AET中。
			AETElement* aete = new AETElement;
			{
				long p[3];
				p[0] = f->p1; p[1] = f->p2; p[2] = f->p3;
				// 找出最下坐标
				double miny = ss->points[p[0]].y;
				for(int i = 1; i < 3; i++)
					if(ss->points[p[i]].y < miny)
						miny = ss->points[p[i]].y;

				// 最下坐标有多少个点
				int countminy = 0;
				long hasminy[3];
				for(int i = 0; i < 3; i++)
					if(ss->points[p[i]].y == miny)
						hasminy[countminy++] = i;

				int asdfasdf = 1;
				if(countminy == 1)
				{
					long hasleft, hasright;
					int index = hasminy[0];
					long dp1 = p[(index + 1) % 3];
					long dp2 = p[(index + 2) % 3];
					hasminy[0] = p[index];
					if(ss->points[dp1].x == ss->points[dp2].x)
					{
						if(ss->points[dp1].y > ss->points[dp2].y)
						{
							hasleft = dp1;
							hasright = dp2;
						}else
						{
							hasleft = dp2;
							hasright = dp1;
						}
					}else if(ss->points[dp1].x > ss->points[dp2].x)
					{
						hasleft = dp2;
						hasright = dp1;
					}else
					{
						hasleft = dp1;
						hasright = dp2;
					}
					aete->xl = ss->points[hasminy[0]].x;
					aete->xr = ss->points[hasminy[0]].x;
					aete->ylmax = ss->points[hasleft].y;
					aete->yrmax = ss->points[hasright].y;
					aete->dxl = (ss->points[hasleft].x - ss->points[hasminy[0]].x) / (ss->points[hasleft].y - ss->points[hasminy[0]].y);
					aete->dxr = (ss->points[hasright].x - ss->points[hasminy[0]].x) / (ss->points[hasright].y - ss->points[hasminy[0]].y);
					aete->zl = ss->points[hasminy[0]].z;
					aete->IP = polygonInfo->IP;

					double vec1[3] = {
						ss->points[hasleft].x - ss->points[hasminy[0]].x,
						ss->points[hasleft].y - ss->points[hasminy[0]].y,
						ss->points[hasleft].z - ss->points[hasminy[0]].z
					}, vec2[3]={
						ss->points[hasright].x - ss->points[hasminy[0]].x,
						ss->points[hasright].y - ss->points[hasminy[0]].y,
						ss->points[hasright].z - ss->points[hasminy[0]].z
					};

						double a = vec1[1] * vec2[2] - vec2[1] * vec1[2];
						double b = vec2[0] * vec1[2] - vec1[0] * vec2[2];
						double c = vec1[0] * vec2[1] - vec2[0] * vec1[1];
						aete->dzx = -a / c;
						aete->dzy = -b / c;

						aete->left = ss->points[hasleft];
						aete->right = ss->points[hasright];
				}else if(countminy == 2)
				{
					long hasleft, hasright;
					hasminy[0] = p[hasminy[0]];
					hasminy[1] = p[hasminy[1]];
					if(ss->points[hasminy[0]].x < ss->points[hasminy[1]].x)
					{
						hasleft = hasminy[0];
						hasright = hasminy[1];
					}else
					{
						hasleft = hasminy[1];
						hasright = hasminy[0];
					}
					long hastop;
					for (int i = 0; i < 3; i++)
						if(p[i] != hasleft && p[i] != hasright)
							hastop = p[i];

					aete->xl = ss->points[hasleft].x;
					aete->xr = ss->points[hasright].x;
					aete->ylmax = ss->points[hastop].y;
					aete->yrmax = ss->points[hastop].y;
					aete->dxl = (ss->points[hastop].x - ss->points[hasleft].x) / (ss->points[hastop].y - ss->points[hasleft].y);
					aete->dxr = (ss->points[hastop].x - ss->points[hasright].x) / (ss->points[hastop].y - ss->points[hasright].y);
					aete->IP = polygonInfo->IP;
					aete->zl = ss->points[hasleft].z;

					double vec1[3] = {
						ss->points[hasleft].x - ss->points[hastop].x,
						ss->points[hasleft].y - ss->points[hastop].y,
						ss->points[hasleft].z - ss->points[hastop].z}, 
						vec2[3] = {
							ss->points[hasright].x - ss->points[hastop].x,
							ss->points[hasright].y - ss->points[hastop].y,
							ss->points[hasright].z - ss->points[hastop].z};

							double a = vec1[1] * vec2[2] - vec2[1] * vec1[2];
							double b = vec2[0] * vec1[2] - vec1[0] * vec2[2];
							double c = vec1[0] * vec2[1] - vec2[0] * vec1[1];
							aete->dzx = -a / c;
							aete->dzy = -b / c;
				}else
				{
					aete->ylmax = aete->yrmax = j;
					aete->xl = aete->xr = aete->dxl = aete->dxr = aete->dzx = aete->dzy = aete->zl = 0;
					aete->IP = polygonInfo->IP;
				}
				aet.AddTail(aete);
			}
		}
		// 		6. 对AET中的每一对边：
		for(int k = 0; k < aet.GetCount(); k++)
		{
			// 			6.1 对xl < x < xr 的每一个象素，按增量公式z = z+dzx算各点深度depth。
			AETElement* paete = aet.GetAt(aet.FindIndex(k));
			double z = paete->zl;
			for(int l = (int)(paete->xl + 0.5); l < (int)(paete->xr + 0.5); l++)
			{
				// 			6.2 与ZB中的量比较，depth > ZB(j), 则令ZB(j) =depth，并计算颜色值，写帧缓存。 
				if(z > ZB[l])
				{
					ZB[l] = z;
					CB[j][l] = RGB(ss->faces[paete->IP].r, ss->faces[paete->IP].g, ss->faces[paete->IP].b);
				}
				z += paete->dzx;
			}
		}
		// 		7. 删除APT中多边形顶点最大y坐标为j的多边形，并删除相应的边Y表ET 。
		int* record = new int[APT.GetCount()];
		int recindex = 0;
		for(int k = 0; k < APT.GetCount(); k++)
			if((int)(APT.GetAt(APT.FindIndex(k))->Ymax + 0.5) == j)
				record[recindex++] = k;

		for(int k = recindex - 1; k >= 0; k--)
		{
			//PolygonYListElement* pyle = APT.GetAt(APT.FindIndex(record[k]));
			//delete pyle;
			APT.RemoveAt(APT.FindIndex(record[k]));
		}

		delete[] record;

		// 		8. 对AET中的每一个边对，作如下处理：
		int* toBeDeleted = new int[aet.GetCount()];
		int toBeDeletedCount = 0;
		for(int k = 0; k < aet.GetCount(); k++)
		{
			// 			8.1 删除ylmax或yrmax已等于j的边。若一边对中只删除了其中一边，需对该多边形的边重新配对。   
			AETElement* aete = aet.GetAt(aet.FindIndex(k));
			int intYLMax = (int)(aete->ylmax + 0.5), intYRMax = (int)(aete->yrmax + 0.5);
			if ((intYLMax <= j) || (intYRMax <= j))
			{
				if (intYLMax <= j && intYRMax <= j)
				{
					toBeDeleted[toBeDeletedCount++] = k;
				}else
				{
					if(intYLMax <= j)
					{
						aete->dxl = (aete->right.x - aete->left.x) / (aete->right.y - aete->left.y);
						aete->ylmax = aete->yrmax;
					}else
					{
						aete->dxr = (aete->right.x - aete->left.x) / (aete->right.y - aete->left.y);
						aete->ylmax = aete->ylmax;
					}
				}
			}

			// 			8.2 用增量公式计算新的xl、xr和zl，更新边对中的信息；
			aete->xl = aete->xl + aete->dxl;
			aete->xr = aete->xr + aete->dxr;
			aete->zl = aete->zl + aete->dzy + aete->dzx * aete->dxl;
		}

		for(int i = toBeDeletedCount - 1; i >= 0; i--)
		{
			AETElement* aete = aet.GetAt(aet.FindIndex(toBeDeleted[i]));
			delete aete;
			aet.RemoveAt(aet.FindIndex(toBeDeleted[i]));
		}
		delete[] toBeDeleted;
	}
	// 	}
	int stoppoint = 1;
	// 清理内存	
	for(int i = PolygonYList.GetCount() - 1; i >= 0; i--)
	{
		CList<PolygonYListElement*>* pyle = PolygonYList.GetAt(i);
		for(int j = pyle->GetCount() - 1; j >= 0; j--)
		{
			delete pyle->GetAt(pyle->FindIndex(j));
			pyle->RemoveAt(pyle->FindIndex(j));
		}
		delete pyle;
		PolygonYList.RemoveAt(i);
	}

	for(int i = APT.GetCount() - 1; i >= 0; i--)
	{
		delete APT.GetAt(APT.FindIndex(i));
		APT.RemoveAt(APT.FindIndex(i));
	}
	delete[] ss->faces;
	delete[] ss->points;
	delete ss;
}
