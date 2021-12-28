// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PlanetaryMotionView.cpp : implementation of the CPlanetaryMotionView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PlanetaryMotion.h"
#endif

#include "PlanetaryMotionDoc.h"
#include "PlanetaryMotionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanetaryMotionView

IMPLEMENT_DYNCREATE(CPlanetaryMotionView, CView)

BEGIN_MESSAGE_MAP(CPlanetaryMotionView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlanetaryMotionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPlanetaryMotionView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_SUSPEND, &CPlanetaryMotionView::OnButtonSuspend)
	ON_COMMAND(ID_BUTTON_RESUME, &CPlanetaryMotionView::OnButtonResume)
END_MESSAGE_MAP()

// CPlanetaryMotionView construction/destruction

CPlanetaryMotionView::CPlanetaryMotionView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	m_pAngle = x1 = y1 = x2 = y2 = 0;
}

CPlanetaryMotionView::~CPlanetaryMotionView()
{
}

BOOL CPlanetaryMotionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlanetaryMotionView drawing

void CPlanetaryMotionView::OnDraw(CDC* pDC)
{
	CPlanetaryMotionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_pAngle > 0)
	{
		pDC->Ellipse(200, 100, 450, 350);

		pDC->Ellipse(250, 150, 400, 300);
		CBrush brush(RGB(253, 184, 19));
		CBrush* pBrush = pDC->SelectObject(&brush);
		//CreatePen
		CPen yellowPen;
		yellowPen.CreatePen(PS_SOLID, 0, RGB(253, 184, 19));
		CPen* pOldPen = pDC->SelectObject(&yellowPen);
		pDC->Ellipse(300, 200, 350, 250);
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pBrush);


		CBrush blueBrush(RGB(0, 0, 255));
		CBrush* bBrush = pDC->SelectObject(&blueBrush);

		pDC->Ellipse(x1 - 15, y1 - 15, x1 + 15, y1 + 15);
		pDC->SelectObject(bBrush);

		CBrush greyBrush(RGB(192, 192, 192));
		CBrush* gBrush = pDC->SelectObject(&greyBrush);
		pDC->Ellipse(x2 - 15, y2 - 15, x2 + 15, y2 + 15);
		pDC->SelectObject(gBrush);

	}
	// TODO: add draw code for native data here
}


// CPlanetaryMotionView printing


void CPlanetaryMotionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlanetaryMotionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanetaryMotionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanetaryMotionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlanetaryMotionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlanetaryMotionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlanetaryMotionView diagnostics

#ifdef _DEBUG
void CPlanetaryMotionView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanetaryMotionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanetaryMotionDoc* CPlanetaryMotionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanetaryMotionDoc)));
	return (CPlanetaryMotionDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlanetaryMotionView message handlers


void CPlanetaryMotionView::OnButtonStart()
{
	m_pCurrentThread =  AfxBeginThread(CPlanetaryMotionView::StartThread,this);
	// TODO: Add your command handler code here
}


void CPlanetaryMotionView::OnButtonSuspend()
{
	m_pCurrentThread->SuspendThread();	
}


void CPlanetaryMotionView::OnButtonResume()
{
	m_pCurrentThread->ResumeThread();
}


UINT CPlanetaryMotionView::StartThread(LPVOID param)
{
	
	CPlanetaryMotionView* pView = (CPlanetaryMotionView*)param;
	// TODO: Add your implementation code here.
	while (true)
	{
		pView->x1 = 325 + 125 * cos(pView->m_pAngle);
		pView->y1 = 225 + 125 * sin(pView->m_pAngle);
		pView->x2 = 325 + 75 * cos(pView->m_pAngle+ 10);
		pView->y2 = 225 + 75 * sin(pView->m_pAngle+ 10);		
		pView->m_pAngle = pView->m_pAngle + .10;
		
		pView->Invalidate();
		Sleep(100);

	}
	return 0;
}
