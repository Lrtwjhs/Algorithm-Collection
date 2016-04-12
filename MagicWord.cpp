// MagicWord.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "MagicWord.h"
#include "MagicWordDlg.h"
#include "StudyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMagicWordApp

BEGIN_MESSAGE_MAP(CMagicWordApp, CWinApp)
	//{{AFX_MSG_MAP(CMagicWordApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicWordApp construction

CMagicWordApp::CMagicWordApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMagicWordApp object

CMagicWordApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMagicWordApp initialization

BOOL CMagicWordApp::InitInstance()
{
	AfxEnableControlContainer();

   // �˳���ֻ������һ�Σ��û������жϳ����Ƿ��Ѿ�����
   HANDLE m_hMutex = CreateMutex( NULL, TRUE, m_pszAppName );

   if ( GetLastError() == ERROR_ALREADY_EXISTS )
   {
      AfxMessageBox( "�����Ѿ�����!" );
      return FALSE;
   }

#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	CMagicWordDlg dlg;
	m_pMainWnd = &dlg;

   // ���öԻ��򱳾�ɫ���ı�ɫ
 SetDialogBkColor( RGB( 255, 255, 255 ),  RGB( 87, 96, 105 ) );
   //SetDialogBkColor( RGB( 40, 120, 240 ), RGB( 255, 255, 255 ) );

	int nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	return FALSE;
}
