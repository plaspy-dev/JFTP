// ActualizacionesPage.cpp : implementation file
//

#include "stdafx.h"
#include "FTPWanderer.h"
#include "ActualizacionesPage.h"
# include "Atlbase.h"

// CActualizacionesPage dialog

IMPLEMENT_DYNAMIC(CActualizacionesPage, CPropertyPage)
CActualizacionesPage::CActualizacionesPage()
	: CPropertyPage(CActualizacionesPage::IDD)
{
	m_dwOldSel= 0;
}

CActualizacionesPage::~CActualizacionesPage()
{
}

void CActualizacionesPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_BBuscar);
	DDX_Control(pDX, IDC_COMBO1, m_CBActualizaciones);
	DDX_Control(pDX, IDC_STATICHELP, m_SHelp);
}


BEGIN_MESSAGE_MAP(CActualizacionesPage, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CActualizacionesPage message handlers

BOOL CActualizacionesPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	HKEY hRootKey = HKEY_LOCAL_MACHINE;
	CRegKey hReg;

	m_szPathUpdate= _T("");
	if( ERROR_SUCCESS== hReg.Open( hRootKey, _T("software\\Herramientas FTP\\JUpdater"), KEY_READ)) {

		TCHAR szEXEPath[MAX_PATH];
		ULONG	tamano= MAX_PATH;

		if( hReg.QueryStringValue( "JUpdaterPath", szEXEPath, &tamano)== ERROR_SUCCESS) 

			m_szPathUpdate= szEXEPath;
		hReg.Close();
	}
	m_CBActualizaciones.AddString("DesHabilitadas");
	if( m_szPathUpdate.IsEmpty()) {

		m_CBActualizaciones.SetCurSel(0);
		m_BBuscar.EnableWindow(false);
	} else {

		m_CBActualizaciones.AddString("Automaticas");
		m_CBActualizaciones.AddString("Descargar");
		m_CBActualizaciones.AddString("Notificar");
		m_dwOldSel=AfxGetApp()->GetProfileInt( "", "Actualizacion", 1);
		m_CBActualizaciones.SetCurSel( m_dwOldSel);
	}
	OnCbnSelchangeCombo1();
	return TRUE;
}

void CActualizacionesPage::OnCbnSelchangeCombo1()
{
	int sel= m_CBActualizaciones.GetCurSel();
	switch( sel) {

		case 0:
			m_SHelp.SetWindowText("DesHabilita las actualizaciones Automaticas de JFTP");
			break;
		case 1:
			m_SHelp.SetWindowText("Descarga e Instala automaticamente las nuevas actualizaciones (Recomendado)");
			break;
		case 2:
			m_SHelp.SetWindowText("Descarga, pero solicita confirmacion para instalar las actualizaciones");
			break;
		case 3:
			m_SHelp.SetWindowText("Informa de nuevas actualizaciones. Solicita confirmacion para descargar e instalar");
			break;
	}
	SetModified((sel!=m_dwOldSel));
}

void CActualizacionesPage::OnOK() 
{
	m_dwOldSel= m_CBActualizaciones.GetCurSel();
	AfxGetApp()->WriteProfileInt("", "Actualizacion", m_dwOldSel);
	CPropertyPage::OnOK();
}

void CActualizacionesPage::OnBnClickedButton1()
{
	CString temp;
	temp.Format( "\"%s\" %d jftp",m_szPathUpdate, 8);
	WinExec( temp, NULL);
}