#pragma once
#include "afxwin.h"


// CActualizacionesPage dialog

class CActualizacionesPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CActualizacionesPage)

public:
	CActualizacionesPage();
	virtual ~CActualizacionesPage();

// Dialog Data
	enum { IDD = IDD_ACTUALIZACIONES_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CString		m_szPathUpdate;
	DWORD		m_dwOldSel;
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_BBuscar;
	CComboBox m_CBActualizaciones;
	CStatic m_SHelp;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
};
