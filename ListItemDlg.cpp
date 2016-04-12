// ListItemDlg.cpp : implementation file

#include "stdafx.h"
#include "MagicWord.h"
#include "ListItemDlg.h"

#include "WordDaoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListItemDlg dialog


CListItemDlg::CListItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListItemDlg)
	m_word = _T("");
	m_Display = _T("");
	m_bChecked = TRUE;
	//}}AFX_DATA_INIT
}


void CListItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListItemDlg)
	DDX_Control(pDX, IDC_LIST, m_ListCtrl);
	DDX_Text(pDX, IDC_WORD, m_word);
	DDV_MaxChars(pDX, m_word, 5);
	DDX_Text(pDX, IDC_DISPLAY, m_Display);
	DDX_Check(pDX, IDC_CHECK, m_bChecked);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListItemDlg, CDialog)
	//{{AFX_MSG_MAP(CListItemDlg)
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListItemDlg message handlers
BOOL CListItemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

   m_ListCtrl.SetExtendedStyle( LVS_EX_GRIDLINES );
   m_ListCtrl.InsertColumn( 0, _T( "����ƥ��ĵ���" ), LVCFMT_LEFT, 115 );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ��ʾ���з��������ĵ���
void CListItemDlg::OnGo() 
{
   m_ListCtrl.DeleteAllItems();
   m_Display.Empty();
   UpdateData();
   
   if ( m_word.IsEmpty() )
   {
      MessageBox( _T( "ͬѧ��Ҫ�����뵥�ʵ�Ŷ��" ),
                  _T( "����!" ), MB_OK | MB_ICONASTERISK );
      return;
   }
   
   if ( !m_word.Find( ' ' ) )
   {
      MessageBox( _T( "�����в����пո�!" ),
                  _T( "����" ), MB_OK | MB_ICONASTERISK );
      return;
   }

   if ( m_word.GetLength() == 1 )
      MatchSingleCharacter();
   else
      MatchString();
}

/////////////////////////////////////////////////////////////////////////////
// ƥ�䵥���ַ�
void CListItemDlg::MatchSingleCharacter()
{
   CWordDaoSet WordSet;
   CString     strLower;
   CString     strUpper;

   try
   {
      if ( WordSet.IsOpen() )
         WordSet.Close();
      
      WordSet.Open();
      
      while ( !WordSet.IsEOF() )
      {
         m_word.MakeLower();
         strLower = m_word;
         m_word.MakeUpper();
         strUpper = m_word;
         
         // �Ե����ַ������ִ�Сд��ֻ�뵥�ʵĵ�һ����ĸ�Ƚ�
         if ( WordSet.m_Word.GetAt(0) == strLower || 
              WordSet.m_Word.GetAt(0) == strUpper )
            m_ListCtrl.InsertItem( 0, WordSet.m_Word );

         WordSet.MoveNext();
      }
   }
   catch ( CDaoException *exception )
   {
      exception->ReportError();
      return;
   }
}

/////////////////////////////////////////////////////////////////////////////
// ƥ���ַ���
void CListItemDlg::MatchString()
{
   CWordDaoSet WordSet;

   try
   {
      if ( WordSet.IsOpen() )
         WordSet.Close();
      
      WordSet.Open();
      
      while ( !WordSet.IsEOF() )
      {
         if ( m_bChecked )
         {
            if ( WordSet.m_Word.Find( m_word ) != -1 )
               m_ListCtrl.InsertItem( 0, WordSet.m_Word );
         }
         else
         {
            // ���Ƚ�˫����ת��ΪСд״̬
            WordSet.m_Word.MakeLower();
            m_word.MakeLower();

            if ( WordSet.m_Word.Find( m_word ) != -1 )
            {
               // ƥ���򽫵�һ����ĸת��Ϊ��д״̬
               WordSet.m_Word.SetAt( 0, WordSet.m_Word.GetAt( 0 ) - 32 );
               m_ListCtrl.InsertItem( 0, WordSet.m_Word );
            }
         }
         WordSet.MoveNext();
      }
   }
   catch ( CDaoException *exception )
   {
      exception->ReportError();
      return;
   }
}

/////////////////////////////////////////////////////////////////////////////
// ˫������ʾ��ʾ��Ϣ
void CListItemDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   CWordDaoSet WordSet;
   CString     strSQL;
   CString     strNewLine( "\r\n" );
   char        szTemp[27] = { '\0' };

   POSITION Pos = m_ListCtrl.GetFirstSelectedItemPosition();
   if ( Pos == NULL )   return;
   int nCurIndex = m_ListCtrl.GetNextSelectedItem( Pos );

   m_Display.Empty();
   m_ListCtrl.GetItemText( nCurIndex, 0, szTemp, 26 );

   strSQL.Format( "SELECT * FROM  WordList WHERE word = '%s'", szTemp );

   if ( WordSet.IsOpen() )
      WordSet.Close();

   WordSet.Open( AFX_DAO_USE_DEFAULT_TYPE, strSQL, 0 );
   
   if ( !WordSet.IsEOF() )
   {
      if ( !WordSet.m_Explain0.IsEmpty() )
         m_Display += WordSet.m_Explain0 ;
      if ( !WordSet.m_Explain1.IsEmpty() )
         m_Display += ( strNewLine + WordSet.m_Explain1 );
      if ( !WordSet.m_Explain2.IsEmpty() )
         m_Display += ( strNewLine + WordSet.m_Explain2 );
      if ( !WordSet.m_Phrase0.IsEmpty() )
         m_Display += ( strNewLine + WordSet.m_Phrase0 );
      if ( !WordSet.m_Phrase1.IsEmpty() )
         m_Display += ( strNewLine + WordSet.m_Phrase1 );
      if ( !WordSet.m_Phrase2.IsEmpty() )
         m_Display += ( strNewLine + WordSet.m_Phrase2 );
      if ( !WordSet.m_Sentence0.IsEmpty() )
         m_Display += ( strNewLine + WordSet.m_Sentence0 );
      if ( !WordSet.m_Sentence1.IsEmpty() )
         m_Display += ( strNewLine + WordSet.m_Sentence1 );
   }

   if ( WordSet.IsOpen() )
      WordSet.Close();

   UpdateData( FALSE );
	
   *pResult = 0;
}