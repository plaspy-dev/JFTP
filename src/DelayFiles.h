#pragma once
#include "ProgressDlg.h"

#define BUF_SIZE 4096

class CDelayFiles
{
	CInternetSession m_InternetSession;
	CFtpConnection *m_pFtpConnection;
	CFile m_File;
	CString m_strResult;
	void DownloadFile(CString & source, CString & dest);
public:

	void Init();
	CDelayFiles();
	~CDelayFiles();
	CWnd m_wndDummy;
	BOOL m_bTransferFailed;
	DWORD m_dwTransferType;
	BOOL CreateLocalDirectory(LPCTSTR lpszDirectory);
	void WaitForProgressDialog();
	CWnd *m_pTransferManager;
	CString m_strCurrentDirectory;
	CString GetLastError();

	CStringArray m_strLocalNames;
	CStringArray m_strRemoteNames;

	CString m_strLocalName;
	CString m_strRemoteName;
	CString m_strPassword;
	CString m_strUserName;
	CString m_strServerName;
	int		m_nRetries;
	int		m_nRetryDelay;
	int		m_nPort;
	int		m_bUsePASVMode;

	DWORD m_nConnectionTimeout;
	DWORD m_dwFileLength;

	CProgressDlg m_ProgressDlg;
	char m_szStatus[1024];
	BOOL m_bDirectoryCreated;
	void PostDownloadStatus(LPCTSTR lpszStatus);
};
