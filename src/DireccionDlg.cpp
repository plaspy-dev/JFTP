// DireccionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTPWanderer.h"
#include "DireccionDlg.h"


// CDireccionDlg dialog

IMPLEMENT_DYNAMIC(CDireccionDlg, CDialogBar)

CDireccionDlg::CDireccionDlg(CWnd* pParent /*=NULL*/)
{
}

CDireccionDlg::~CDireccionDlg()
{
}

void CDireccionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDireccionDlg, CDialogBar)
END_MESSAGE_MAP()
// CDireccionDlg message handlers

BOOL CDireccionDlg::PreTranslateMessage(MSG* pMsg)
{
	if (IsDialogMessage(pMsg))
		return TRUE;
	return CDialogBar::PreTranslateMessage(pMsg);
}

LONG CDireccionDlg::OnInitDialog(UINT wParam, LONG lParam)
{
	if (!HandleInitDialog(wParam, lParam) || !UpdateData(FALSE))
    {
		TRACE0("Warning: UpdateData failed during dialog init.\n");
        return FALSE;
	}
    return TRUE;
}