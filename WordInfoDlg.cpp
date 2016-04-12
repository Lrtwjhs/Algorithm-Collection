// WordInfoDlg.cpp : implementation file
// Download by http://www.NewXing.com

#include "stdafx.h"
#include "MagicWord.h"
#include "WordInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordInfoDlg dialog


CWordInfoDlg::CWordInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWordInfoDlg::IDD, pParent)
{
   m_windowTitle = _T( "����µ���" );
	//{{AFX_DATA_INIT(CWordInfoDlg)
	m_word = _T("");
	m_explain0 = _T("");
	m_explain1 = _T("");
	m_explain2 = _T("");
	m_phrase0 = _T("");
	m_phrase1 = _T("");
	m_phrase2 = _T("");
	m_sentence0 = _T("");
	m_sentence1 = _T("");
	//}}AFX_DATA_INIT
}


void CWordInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWordInfoDlg)
	DDX_Text(pDX, IDC_WORD, m_word);
	DDV_MaxChars(pDX, m_word, 26);
	DDX_Text(pDX, IDC_EXPLAIN0, m_explain0);
	DDX_Text(pDX, IDC_EXPLAIN1, m_explain1);
	DDX_Text(pDX, IDC_EXPLAIN2, m_explain2);
	DDX_Text(pDX, IDC_PHRASE0, m_phrase0);
	DDX_Text(pDX, IDC_PHRASE1, m_phrase1);
	DDX_Text(pDX, IDC_PHRASE2, m_phrase2);
	DDX_Text(pDX, IDC_SENTENCE0, m_sentence0);
	DDX_Text(pDX, IDC_SENTENCE1, m_sentence1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWordInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CWordInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordInfoDlg message handlers

BOOL CWordInfoDlg::OnInitDialog() 
{
   // ���ô��ڱ���Ϊm_windowTitle
   SetWindowText( m_windowTitle );

	CDialog::OnInitDialog();
	
	return TRUE;
}

void CWordInfoDlg::OnOK() 
{
   UpdateData();

   if ( m_word.IsEmpty() )
   {
      MessageBox( _T( "ͬѧ�����Ȼ�������뵥��!" ), 
                  _T( "����!" ), MB_OK | MB_ICONINFORMATION );
      return;
   }
   
   if ( !m_word.Find( ' ' ) )
   {
      MessageBox( _T( "�����в����пո�Ŷ!" ),
                  _T( "����" ), MB_OK | MB_ICONASTERISK );
      return;
   }

	CDialog::OnOK();
}
