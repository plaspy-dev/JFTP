#include "stdafx.h"
#include "delayfiles.h"

CDelayFiles::CDelayFiles(void)
{
	m_dwFileLength = 0;
	m_bTransferFailed = FALSE;
	m_bDirectoryCreated  = FALSE;

	m_nConnectionTimeout = 3000;
	m_pFtpConnection = NULL;
	m_nRetries = 1;
	m_nRetryDelay = 10;
	m_nPort = 21;
	m_bUsePASVMode = FALSE;
	m_dwTransferType = FTP_TRANSFER_TYPE_BINARY;
}

CDelayFiles::~CDelayFiles(void)
{
	if (m_pFtpConnection)
	{
		m_pFtpConnection->Close();

		// delete ftp connection
		delete m_pFtpConnection;
		m_pFtpConnection = NULL;
	}

	// Close this session
	m_InternetSession.Close();

    m_ProgressDlg.DestroyWindow();
	m_wndDummy.DestroyWindow();
}

void CDelayFiles::Init() {

	PostDownloadStatus("Inicializando");

	// set animation to 'Downloading'
	m_ProgressDlg.m_nAnimationID = IDR_AVI1;
	
	// create dummy window as parent for the progress dialog
	if (!m_wndDummy.CreateEx(0, AfxRegisterWndClass(0), "Ventana de descargas",
			WS_OVERLAPPED, 0, 0, 0, 0, NULL, NULL))
		return;

	// Create the progress dialog box.
	if (!m_ProgressDlg.Create(&m_wndDummy, NULL))
		return;
	
	// wait until dialog is created
	WaitForProgressDialog();

	// when reducing the timeout connection, the internet connection speed is faster.
	if (m_nConnectionTimeout) 
	{
		m_InternetSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, m_nConnectionTimeout);
		m_InternetSession.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, m_nConnectionTimeout);
		m_InternetSession.SetOption(INTERNET_OPTION_SEND_TIMEOUT, m_nConnectionTimeout);
	}

	// catch all exceptions
	try	
	{	
		// start receiving file 
		DownloadFile(m_strRemoteName, m_strLocalName);
	}
	catch(char *pszError)
	{ 		
		m_strResult = pszError; 		
	}
	catch (CFileException * pEx)
	{ 	
		// file can't be opened
		m_strResult.Format("Error de Archivo %d %s", pEx->m_cause, pEx->m_strFileName); 		
	}
	catch (CInternetException* pEx)
	{
		// internet exception
		m_strResult.Format("Internet Exception Error %d", pEx->m_dwError);
		if (pEx->m_dwError == ERROR_INTERNET_EXTENDED_ERROR)
		{
			char szBuffer[1024];
			DWORD dwBufferLength = 1024;
			DWORD dwError = 0;
			::InternetGetLastResponseInfo(&dwError, szBuffer, &dwBufferLength);
			m_strResult += szBuffer;
		}
	}
	// fix error message
	m_strResult.Replace('\n', ' ');
	m_strResult.Remove('\r');

	if (!m_strResult.IsEmpty())
	{
		// exception was thrown
		m_bTransferFailed = TRUE;
	}	
	if (m_bDirectoryCreated)
	{
			// successfull created folder
		m_strResult = "\"" + m_strLocalName + "\" carpeta creada.";
	}
	else
	{
			// successfull downloaded file
		m_strResult = "\"" + m_strRemoteName + "\" descargado.";
	}
	// avoid entering standard message loop by returning FALSE
	m_ProgressDlg.DestroyWindow();
}

void CDelayFiles::DownloadFile(CString &source, CString &dest)
{

	m_ProgressDlg.SetWindowTitle("recibiendo " + source);
	m_ProgressDlg.SetPos(0);
	m_ProgressDlg.SetSecondStatus("");

	// only a directory name was specified
	if (dest.Right(1) == "\\")
	{
		// try to create directory structure
		CreateLocalDirectory(dest);

		m_bDirectoryCreated = TRUE;
		return;
	}

	PostDownloadStatus("Conectando");

	// try x times to connect
	int nRetries = m_nRetries;
	while (nRetries > 0)
	{
		nRetries--;
		try
		{
			// Create new ftp connection to retrieve file
			wsprintf(m_szStatus, "Conectando a %s (Intento %d de %d)", m_strServerName, m_nRetries - nRetries, m_nRetries); 
			m_ProgressDlg.SetStatus(m_szStatus);

			DoEvents();
			
			// Connect to FTP Server
			m_pFtpConnection = m_InternetSession.GetFtpConnection(m_strServerName, m_strUserName, m_strPassword, m_nPort, m_bUsePASVMode);
			nRetries = 0;
		}
		catch (CInternetException* pEx)
		{
			m_pFtpConnection = NULL;

			// catch errors from WinINet
			pEx->GetErrorMessage(m_szStatus, sizeof(m_szStatus));
			pEx->Delete();

			if (nRetries > 0)
			{
				wsprintf(m_szStatus, "Falla al conectar a %s (intento %d de %d)", m_strServerName, m_nRetries - nRetries, m_nRetries); 
				m_ProgressDlg.SetStatus(m_szStatus);
				 
				wsprintf(m_szStatus, "Reintentando despues de %d segundos...", m_nRetryDelay); 
				m_ProgressDlg.SetSecondStatus(m_szStatus);

				PostDownloadStatus("Reintentado");
				m_ProgressDlg.SetSecondStatus("");
			}
			else
			{
				throw m_szStatus; 
			}
		}
	}

	// split folder and file (if complete path is given)
	int nPos = source.ReverseFind('/');
	if (nPos != -1)
	{
		m_strCurrentDirectory = source.Left(nPos+1);
		source = source.Mid(nPos+1);
	}

	// set current directory
	if (!m_pFtpConnection->SetCurrentDirectory(m_strCurrentDirectory))
	{
		DWORD dwLength = 255, dwError;
		CString strInfo;
		InternetGetLastResponseInfo(&dwError, strInfo.GetBuffer(dwLength), &dwLength);
		strInfo.ReleaseBuffer();
		strInfo.Remove('\n');
		strInfo.Remove('\r');

		wsprintf(m_szStatus, "%s", strInfo);
		throw m_szStatus; 
	}


	lstrcpy(m_szStatus, source); 
	// Show source file name
	m_ProgressDlg.SetStatus(m_szStatus);
	// Show destination file name
	m_ProgressDlg.SetSecondStatus("para: " + dest);

	// open destination file
	if (m_File.Open(dest, CFile::modeCreate | CFile::modeWrite, NULL) == FALSE)
	{
		wsprintf(m_szStatus, "No se puede crear archivo %s", dest); 
		throw m_szStatus; 
	}
	
	wsprintf(m_szStatus, "Abriendo %s", source); 
	m_ProgressDlg.SetStatus(m_szStatus);

	CInternetFile* pInternetFile = m_pFtpConnection->OpenFile(source, GENERIC_READ, m_dwTransferType);
	if (!pInternetFile)
	{
		wsprintf(m_szStatus, "No se puede abrir archivo remoto %s", source); 
		throw m_szStatus; 
	}
	
	PostDownloadStatus("Descargando");

	// set max to 100%
	m_ProgressDlg.SetUpper(100);

	char buffer[BUF_SIZE];
	unsigned int nRead = BUF_SIZE;
	unsigned int nTotalRead = 0;
	while (nRead == BUF_SIZE)
	{
		// read remote data into buffer
		nRead = pInternetFile->Read(buffer, BUF_SIZE);
		// write buffer to data file
		m_File.Write(buffer, nRead);
		nTotalRead += nRead;
		wsprintf(m_szStatus, "%s (%d de %d  bytes transferidos)", source, nTotalRead, m_dwFileLength); 	
		m_ProgressDlg.SetStatus(m_szStatus);

		if (m_dwFileLength > 0)
		{
			int nPos = (nTotalRead*100)/m_dwFileLength;
			m_ProgressDlg.SetPos(nPos);
		}
		else
		{
			m_ProgressDlg.SetPos(0);
		}
	}

	// close the file
	m_File.Close();

	// close internet file
	pInternetFile->Close();

	delete pInternetFile;
	
	// close FTP connection
	wsprintf(m_szStatus, "Cerrando Conexion a %s", m_strServerName); 
	m_ProgressDlg.SetStatus(m_szStatus);

	PostDownloadStatus("Terminado");
}


/********************************************************************/
/*																	*/
/* Function name : GetLastError										*/
/* Description   : Get last error string.							*/
/*																	*/
/********************************************************************/
CString CDelayFiles::GetLastError()
{
	return m_strResult;
}


/********************************************************************/
/*																	*/
/* Function name : CreateLocalDirectory								*/
/* Description   : Create directory tree.							*/
/*																	*/
/********************************************************************/
BOOL CDelayFiles::CreateLocalDirectory(LPCTSTR lpszDirectory)
{
	CString strResult = lpszDirectory;
	
	CString strDir;
	BOOL bResult;
	// create directory structure one part at a time
	while (strResult != "")
	{
		strDir += strResult.Left(strResult.Find("\\")+1);
		strResult = strResult.Mid(strResult.Find("\\")+1);
		bResult = CreateDirectory(strDir, 0);
	}
	return bResult;
}


/********************************************************************/
/*																	*/
/* Function name : WaitForProgressDialog							*/
/* Description   : If the thread has just started, it may not have	*/
/*				   had time yet to initialize the dialog window.	*/
/*																	*/
/********************************************************************/
void CDelayFiles::WaitForProgressDialog()
{
	if(m_ProgressDlg.m_hWnd == NULL)
	{
		while(m_ProgressDlg.m_hWnd == NULL)
		{
			DoEvents();
		}
	}
	if(!::IsWindow(m_ProgressDlg.m_hWnd))
	{
		while(!::IsWindow(m_ProgressDlg.m_hWnd))
		{
			DoEvents();
		}
	}
}


/********************************************************************/
/*																	*/
/* Function name : PostDownloadStatus								*/
/* Description   : Post status to Transfer Manager.					*/
/*																	*/
/********************************************************************/
void CDelayFiles::PostDownloadStatus(LPCTSTR lpszStatus)
{
	/*int nLength = lstrlen(lpszStatus);
	// dynamically allocate memory for status message (receiver will delete it!)
	LPSTR lpszData = new char[nLength+1];
	lstrcpy(lpszData, lpszStatus);*/
}