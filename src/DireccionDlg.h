#pragma once


// CDireccionDlg dialog

class CDireccionDlg : public CDialogBar
{
	DECLARE_DYNAMIC(CDireccionDlg)

public:
	CDireccionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDireccionDlg();

// Dialog Data
	enum { IDD = IDD_DIRECCION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnInitDialog(UINT, LONG);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
