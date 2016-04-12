// SearchDlg.cpp : implementation file


#include "stdafx.h"
#include "MagicWord.h"
#include "SearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog


CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDlg)
	m_word = _T("");
	//}}AFX_DATA_INIT
}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDlg)
	DDX_Text(pDX, IDC_WORD, m_word);
	DDV_MaxChars(pDX, m_word, 26);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers

void CSearchDlg::OnOK() 
{
   UpdateData();

   if ( m_word.IsEmpty() )
   {
      MessageBox( _T( "~~ͬѧ�����Ȼ�������뵥��<(�����)>!" ), 
                  _T( "����!" ), MB_OK | MB_ICONINFORMATION );
      return;
   }
   
   if ( !m_word.Find( ' ' ) )
   {
      MessageBox( _T( "~~�����в����пո��Ŷ������~*!" ),
                  _T( "����" ), MB_OK | MB_ICONINFORMATION );
      return;
   }

	CDialog::OnOK();
}
