// BoardView.cpp : implementation file
//

#include "stdafx.h"
#include "MonitoringServer.h"
#include "BoardView.h"


// CBoardView

IMPLEMENT_DYNAMIC(CBoardView, CWnd)

CBoardView::CBoardView()
{
	m_pViewWnd = NULL;
}

CBoardView::~CBoardView()
{
	if (m_pViewWnd) delete m_pViewWnd;
}


BEGIN_MESSAGE_MAP(CBoardView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CBoardView message handlers




void CBoardView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r, RGB(255, 255, 0));
}

void CBoardView::SetViewWnd(CWnd *pViewWnd) {
	if (this->m_pViewWnd != NULL) {
		m_pViewWnd->DestroyWindow();
		delete m_pViewWnd;
	}
	this->m_pViewWnd = pViewWnd;
	m_pViewWnd->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 35002);
	CRect r;
	GetClientRect(&r);
	this->PostMessageW(WM_SIZE, r.Width(), r.Height());
}


int CBoardView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	this->m_pViewWnd = new CGraphWnd;
	m_pViewWnd->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 35001);
	
	return 0;
}


void CBoardView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect r;
	GetClientRect(&r);

	m_pViewWnd->SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), 0);
	m_pViewWnd->PostMessageW(UM_COMMAND_CHNAGED, 0, 0);
	
}