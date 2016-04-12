// MagicWordDlg.cpp : implementation file

#include "stdafx.h"
#include "MagicWord.h"

#include "MagicWordDlg.h"
#include "ListItemDlg.h"
#include "WordInfoDlg.h"
#include "SearchDlg.h"
#include "StudyDlg.h"
#include "StyleDlg.h"

#include "WordDaoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicWordDlg dialog

CMagicWordDlg::CMagicWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMagicWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMagicWordDlg)
	m_sentences = _T("");
	m_explains = _T("");
	m_word = _T("");
	m_jump = _T("");
	m_goto = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   // ʵ����m_pSet
   m_pSet = new CWordDaoSet();
}

void CMagicWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMagicWordDlg)
	DDX_Text(pDX, IDC_EDIT_SENTENCE, m_sentences);
	DDX_Text(pDX, IDC_EDIT_EXPLAIN, m_explains);
	DDX_Text(pDX, IDC_STATIC_WORD, m_word);
	DDV_MaxChars(pDX, m_word, 26);
	DDX_Text(pDX, IDC_STATIC_JUMP, m_jump);
	DDV_MaxChars(pDX, m_jump, 26);
	DDX_Text(pDX, IDC_EDIT_GOTO, m_goto);
	DDV_MaxChars(pDX, m_goto, 26);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMagicWordDlg, CDialog)
	//{{AFX_MSG_MAP(CMagicWordDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SETTING, OnSetting)
	ON_BN_CLICKED(IDC_STUDY, OnStudy)
	ON_BN_CLICKED(IDC_KILLSTUDY, OnKillstudy)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_JIEMIAN, OnJiemian)
	ON_BN_CLICKED(IDC_CIDIAN, OnCidian)
	ON_BN_CLICKED(IDC_TIANJIA, OnTianjia)
	ON_BN_CLICKED(IDC_SHANCHU, OnShanchu)
	ON_BN_CLICKED(IDC_SOUSUO, OnSousuo)
	ON_BN_CLICKED(IDC_XIUGAI, OnXiugai)
	ON_BN_CLICKED(IDC_GUANYU, OnGuanyu)
	ON_BN_CLICKED(IDC_TUICHU, OnTuichu)
	ON_BN_CLICKED(IDC_LISHI, OnLishi)
	ON_BN_CLICKED(IDC_TIAO, OnTiao)
	ON_BN_CLICKED(IDC_ZUIQIAN, OnZuiqian)
	ON_BN_CLICKED(IDC_SHANGYI, OnShangyi)
	ON_BN_CLICKED(IDC_XIAYI, OnXiayi)
	ON_BN_CLICKED(IDC_ZUIHOU, OnZuihou)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicWordDlg message handlers

BOOL CMagicWordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);

		if (!strAboutMenu.IsEmpty())
		{
         // �ı�AboutMenu�Ĳ˵���ʾ
         // strAboutMenu = _T( "���ڹ���������!" );

			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);

         // ɾ���������
         pSysMenu->DeleteMenu( 4, MF_BYPOSITION );
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

   // �����ClassWizard����Button����(�ٸ�������ΪCButtonStyle)
   // ����InitBuffonStyle()�ڲ�SubclassDlgItem()
   // ��Ҫ�Ի�����ʾ���������������
   // ����Debugģʽ�»��쳣(Releaseģʽ����ȷ)
   // �����жϣ�������ȷ��
   InitButtonStyle();
   HistroyVisitWord();
   DisplayFirstRecord();

	return TRUE;
}

void CMagicWordDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CMagicWordDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	CRect rect;
	CPaintDC dc(this);
	GetClientRect(rect);
	switch(m_nColor)
	{
	case 0:
		dc.FillSolidRect(rect, RGB(202, 204, 169));
		break;
	case 1:
		dc.FillSolidRect(rect, RGB(34, 145, 185));
		break;
	case 2:
		dc.FillSolidRect(rect, RGB(0, 150, 0));
		break;
	case 3:
		dc.FillSolidRect(rect, RGB(78,29,76));
		break;
	case 4:
		dc.FillSolidRect(rect, RGB(102, 34, 0));
		break;
	case 5:	
		dc.FillSolidRect(rect, RGB(25,24,22));
		break;
	}

		CDialog::OnPaint();
	}
}


HCURSOR CMagicWordDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/////////////////////////////////////////////////////////////////////////////
// ���ð�ť���
void CMagicWordDlg::InitButtonStyle()
{
   CList< CButtonStyle*, CButtonStyle* > ButtonList;
   ButtonList.AddTail( &m_Setting );
   ButtonList.AddTail( &m_ListItem );
   ButtonList.AddTail( &m_Addition );
   ButtonList.AddTail( &m_Remove );
   ButtonList.AddTail( &m_Modify );
   ButtonList.AddTail( &m_Search );
   ButtonList.AddTail( &m_About );
   ButtonList.AddTail( &m_Exit );
   ButtonList.AddTail( &m_Previous );
   ButtonList.AddTail( &m_Next );
   ButtonList.AddTail( &m_End );
   ButtonList.AddTail( &m_Home );
   ButtonList.AddTail( &m_Goto );
   ButtonList.AddTail( &m_Jump );


   // ��ѭ��ʵ�ֱ����ֶ��Ķ�Resource.h�еĶ���
   for ( int nIco = IDI_JUMP, nBtn = IDC_JUMP; nBtn >= IDC_LISTITEM; nIco--, nBtn-- )
   {
      CButtonStyle *Button = ButtonList.RemoveTail();
      Button->SubclassDlgItem( nBtn, this );
      Button->SetIcon( nIco );
      Button->SetInactiveBgColor();
      Button->SetInactiveFgColor();
      Button->SetActiveBgColor();
   }
}

/////////////////////////////////////////////////////////////////////////////
// ��ʾ��һ����¼
void CMagicWordDlg::DisplayFirstRecord()
{
   try
   {
      if ( m_pSet->IsOpen() )
         m_pSet->Close();

      m_pSet->Open();
      PublicAssign();
   }
   catch( CDaoException *exception )
   {
      exception->ReportError();
      return;
   }
}

/////////////////////////////////////////////////////////////////////////////
// Ϊ��ʾ����Ҫ�ĸ�ֵ����
void CMagicWordDlg::PublicAssign()
{
   m_word.Empty();
   m_explains.Empty();
   m_sentences.Empty();

   CString strNewLine( "\r\n" );

   // ��ǰ����
   m_word = m_pSet->m_Word;

   // �������
   if ( !m_pSet->m_Explain0.IsEmpty() )
      m_explains += m_pSet->m_Explain0;
   if ( !m_pSet->m_Explain1.IsEmpty() )
      m_explains += ( strNewLine + m_pSet->m_Explain1 );
   if ( !m_pSet->m_Explain2.IsEmpty() )
      m_explains += ( strNewLine + m_pSet->m_Explain2 );

   // ���Ｐ������
   if ( !m_pSet->m_Phrase0.IsEmpty() )
      m_sentences += m_pSet->m_Phrase0;
   if ( !m_pSet->m_Phrase1.IsEmpty() )
      m_sentences += ( strNewLine + m_pSet->m_Phrase1 );
   if ( !m_pSet->m_Phrase2.IsEmpty() )
      m_sentences += ( strNewLine + m_pSet->m_Phrase2 );
   if ( !m_pSet->m_Sentence0.IsEmpty() )
      m_sentences += ( strNewLine + m_pSet->m_Sentence0 );
   if ( !m_pSet->m_Sentence1.IsEmpty() )
      m_sentences += ( strNewLine + m_pSet->m_Sentence1 );

   UpdateData( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// �������ù���
void CMagicWordDlg::OnSetting() 
{
}

/////////////////////////////////////////////////////////////////////////////
//�ʵ�
void CMagicWordDlg::OnCidian() 
{
	// TODO: Add your control notification handler code here
	CListItemDlg ListItemDlg;
    ListItemDlg.DoModal();	
}

/////////////////////////////////////////////////////////////////////////////
//���
void CMagicWordDlg::OnTianjia() 
{
	// TODO: Add your control notification handler code here
	 CWordInfoDlg WordInfoDlg;
   CWordDaoSet  TempSet;
   CString      strSQL;

   // ��������ȡ����ť����ִ����Ӳ�����
   if ( WordInfoDlg.DoModal() != IDOK )
      return;

   // ��ѯ��ǰ�����Ƿ��Ѿ�����¼�����ݿ���
   if ( TempSet.IsOpen() )
      TempSet.Close();
   
   strSQL.Format( "SELECT * FROM WordList WHERE word = '%s'", 
                  WordInfoDlg.m_word.operator LPCTSTR() );
   TempSet.Open( AFX_DAO_USE_DEFAULT_TYPE, strSQL, 0 );

   if ( !TempSet.IsEOF() )
   {
      MessageBox( _T( "��ǰ���ʼ�¼�Ѵ���,û����ӵı�Ҫ!" ),
                  _T( "�Ѿ�����!" ), MB_OK | MB_ICONASTERISK );
      return;
   }

   if ( TempSet.IsOpen() )
      TempSet.Close();

   // ִ����Ӳ���
   try
   {
      m_pSet->AddNew();

      m_pSet->m_Word      = WordInfoDlg.m_word;
      m_pSet->m_Explain0  = WordInfoDlg.m_explain0;
      m_pSet->m_Explain1  = WordInfoDlg.m_explain1;
      m_pSet->m_Explain2  = WordInfoDlg.m_explain2;
      m_pSet->m_Phrase0   = WordInfoDlg.m_phrase0;
      m_pSet->m_Phrase1   = WordInfoDlg.m_phrase1;
      m_pSet->m_Phrase2   = WordInfoDlg.m_phrase2;
      m_pSet->m_Sentence0 = WordInfoDlg.m_sentence0;
      m_pSet->m_Sentence1 = WordInfoDlg.m_sentence1;

      if ( m_pSet->CanUpdate() )
      {
         m_pSet->Update();
         MessageBox( _T( "����µ������!" ), 
                     _T( "��ӳɹ�!" ), MB_OK | MB_ICONASTERISK );
      }
   }
   catch( CDaoException *exception )
   {
      exception->ReportError();
      // ����ָ���ָ������쳣�ļ�¼
      m_pSet->MoveNext();
      m_pSet->MovePrev();
      return;
   }
}

/////////////////////////////////////////////////////////////////////////////
//ɾ��
void CMagicWordDlg::OnShanchu() 
{
	// TODO: Add your control notification handler code here
	   try
   {
      if ( MessageBox( _T( "����Ĳ�Ҫ����ô?%>_<%" ),
                       _T( "ɾ��ȷ��?" ), MB_OKCANCEL | MB_ICONQUESTION ) == IDOK )
      {         
         m_pSet->Delete();
         MessageBox( _T( "�õ�����Ϣ�Ѿ����ɹ�ɾ��!" ),
                     _T( "ɾ���ɹ�!" ), MB_OK | MB_ICONASTERISK );
         OnXiayi();
      }
   }
   catch( CDaoException *exception )
   {
      exception->ReportError();
      m_pSet->MoveNext();
      m_pSet->MovePrev();
      return;
   }
}

/////////////////////////////////////////////////////////////////////////////
//�޸�
void CMagicWordDlg::OnXiugai() 
{
	// TODO: Add your control notification handler code here
	   CWordInfoDlg WordInfoDlg;
   WordInfoDlg.m_windowTitle = _T( "�޸ĵ�����Ϣ" );

   WordInfoDlg.m_word      = m_pSet->m_Word;
   WordInfoDlg.m_explain0  = m_pSet->m_Explain0;
   WordInfoDlg.m_explain1  = m_pSet->m_Explain1;
   WordInfoDlg.m_explain2  = m_pSet->m_Explain2;
   WordInfoDlg.m_phrase0   = m_pSet->m_Phrase0;
   WordInfoDlg.m_phrase1   = m_pSet->m_Phrase1;
   WordInfoDlg.m_phrase2   = m_pSet->m_Phrase2;
   WordInfoDlg.m_sentence0 = m_pSet->m_Sentence0;
   WordInfoDlg.m_sentence1 = m_pSet->m_Sentence1;

   if ( WordInfoDlg.DoModal() != IDOK )
      return;

   try
   {
      m_pSet->Edit();
      
      m_pSet->m_Word      = WordInfoDlg.m_word;
      m_pSet->m_Explain0  = WordInfoDlg.m_explain0;
      m_pSet->m_Explain1  = WordInfoDlg.m_explain1;
      m_pSet->m_Explain2  = WordInfoDlg.m_explain2;
      m_pSet->m_Phrase0   = WordInfoDlg.m_phrase0;
      m_pSet->m_Phrase1   = WordInfoDlg.m_phrase1;
      m_pSet->m_Phrase2   = WordInfoDlg.m_phrase2;
      m_pSet->m_Sentence0 = WordInfoDlg.m_sentence0;
      m_pSet->m_Sentence1 = WordInfoDlg.m_sentence1;
      
      if ( m_pSet->CanUpdate() )
      {
         m_pSet->Update();
         PublicAssign();
      }
   }
   catch( CDaoException *exception )
   {
      exception->ReportError();
      m_pSet->MoveNext();
      m_pSet->MovePrev();
      return;
   }	
}

/////////////////////////////////////////////////////////////////////////////
//����
void CMagicWordDlg::OnSousuo() 
{
	// TODO: Add your control notification handler code here
	  CWordInfoDlg WordInfoDlg;
   CSearchDlg   SearchDlg;
   CWordDaoSet  TempSet;
   CString      strSQL;

   if ( SearchDlg.DoModal() != IDOK )
      return;

   if ( TempSet.IsOpen() )
      TempSet.Close();
   
   // ����SELECT word�ϳ���Ϊʲô��*���ǶԵ��أ�
   strSQL.Format( "SELECT * FROM WordList WHERE word = '%s'",
                  SearchDlg.m_word.operator LPCTSTR() );
   TempSet.Open( AFX_DAO_USE_DEFAULT_TYPE, strSQL, 0 );
   
   if ( !TempSet.IsEOF() )
   {
      WordInfoDlg.m_windowTitle = _T( "��ʾ��ѯ������Ϣ" );
      // ���ڻ�û��ʾ�����ñ��⣬�ֲ�����������Ƿ�����
      // ��DoModal֮ǰ�����OnInitDialog��������Ѿ�����������Ĳ���
      //WordInfoDlg.SetWindowText( WordInfoDlg.m_windowTitle );
   
      WordInfoDlg.m_word      = TempSet.m_Word;
      WordInfoDlg.m_explain0  = TempSet.m_Explain0;
      WordInfoDlg.m_explain1  = TempSet.m_Explain1;
      WordInfoDlg.m_explain2  = TempSet.m_Explain2;
      WordInfoDlg.m_phrase0   = TempSet.m_Phrase0;
      WordInfoDlg.m_phrase1   = TempSet.m_Phrase1;
      WordInfoDlg.m_phrase2   = TempSet.m_Phrase2;
      WordInfoDlg.m_sentence0 = TempSet.m_Sentence0;
      WordInfoDlg.m_sentence1 = TempSet.m_Sentence1;

      WordInfoDlg.DoModal();
   }
   else
   {
      MessageBox( _T( "~~���ʿ���û��������ʣ��Ͽ���ӣ��ݨ���y !" ),
                  _T( "��ѯʧ��!" ), MB_OK | MB_ICONASTERISK );
      return;
   }

   if ( TempSet.IsOpen() )
      TempSet.Close();
	
}

/////////////////////////////////////////////////////////////////////////////
// ����
void CMagicWordDlg::OnJiemian() 
{
	// TODO: Add your control notification handler code here
	CStyleDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_nColor = dlg.m_nColor;
	}
	else
	{
	}
//	UpdateData(FALSE);
	Invalidate();	
}

/////////////////////////////////////////////////////////////////////////////
// ����
void CMagicWordDlg::OnGuanyu() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg AboutDlg;
    AboutDlg.DoModal();
	
}

/////////////////////////////////////////////////////////////////////////////
// �˳�
void CMagicWordDlg::OnTuichu() 
{
	// TODO: Add your control notification handler code here
	   CDialog::OnOK();
	
}

/////////////////////////////////////////////////////////////////////////////
//��ʼѧϰ
void CMagicWordDlg::OnStudy() 
{
	// TODO: Add your control notification handler code here
	CStudyDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_WAY = dlg.m_Way;
		SetTimer(1,dlg.m_nTime*1000,NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////
//��ͣѧϰ
void CMagicWordDlg::OnKillstudy() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1); 
}


/////////////////////////////////////////////////////////////////////////////
// ��ʾ��һ��������Ϣ
void CMagicWordDlg::OnXiayi() 
{
	// TODO: Add your control notification handler code here
	   try
   {
      m_pSet->MoveNext();

      if ( m_pSet->IsEOF() )
         m_pSet->MoveFirst();

      PublicAssign();
   }
   catch( CDaoException *exception )
   {
      exception->ReportError();
      m_pSet->MovePrev();
      return;
   }
	
}

/////////////////////////////////////////////////////////////////////////////
// ��ʾ��һ��������Ϣ
void CMagicWordDlg::OnShangyi() 
{
	// TODO: Add your control notification handler code here
	  try
   {
      m_pSet->MovePrev();

      if ( m_pSet->IsBOF() )
         m_pSet->MoveLast();

      PublicAssign();
   }
   catch(  CDaoException *exception )
   {
      exception->ReportError();
      m_pSet->MoveNext();
      return;
   }
	
}

/////////////////////////////////////////////////////////////////////////////
// ��ʾ���һ��������Ϣ
void CMagicWordDlg::OnZuihou() 
{
	// TODO: Add your control notification handler code here
	  try
   {
      m_pSet->MoveLast();
      PublicAssign();
   }
   catch(  CDaoException *exception )
   {
      exception->ReportError();
      m_pSet->MoveNext();
      m_pSet->MovePrev();
      return;
   }
	
}

/////////////////////////////////////////////////////////////////////////////
// ��ʾ��ǰһ��������Ϣ
void CMagicWordDlg::OnZuiqian() 
{
	// TODO: Add your control notification handler code here
	  try
   {
      m_pSet->MoveFirst();
      PublicAssign();
   }
   catch(  CDaoException *exception )
   {
      exception->ReportError();
      m_pSet->MoveNext();
      m_pSet->MovePrev();
      return;
   }   
	
}

/////////////////////////////////////////////////////////////////////////////
//��ʷ��ת
void CMagicWordDlg::OnLishi() 
{
	// TODO: Add your control notification handler code here
	  HKEY hKey = 0;
   BYTE szBuffer[26] = { '\0' };
   DWORD dwType = REG_SZ;
   DWORD dwSize = 27;

   memset( szBuffer, 0, dwSize );

   // �����ע���ɹ�����ȡ��ֵ��ʵ����ת��
   if ( RegOpenKeyEx( HKEY_CURRENT_USER, "SOFTWARE\\MagicWord",
                      NULL, KEY_ALL_ACCESS, &hKey ) == ERROR_SUCCESS )
   {
      if ( RegQueryValueEx( hKey, "CurrentWord", NULL, &dwType, szBuffer, &dwSize ) == ERROR_SUCCESS )
      {
         CWordDaoSet TempSet;
         CString     strSQL;

         if ( TempSet.IsOpen() )
            TempSet.Close();
            
         strSQL.Format( "SELECT * from WordList WHERE word = '%s'", szBuffer );
         TempSet.Open( AFX_DAO_USE_DEFAULT_TYPE, strSQL, 0 );
            
         // û���ҵ����ƶ�m_pSet����֤��OnNext/OnModify()�ȿ�����������
         if ( TempSet.IsEOF() )
         {
            MessageBox( _T( "~~���ʿ���û��������ʣ��Ͽ���ӣ��ݨ���y !" ),
                        _T( "��תʧ��!" ), MB_OK | MB_ICONASTERISK );
            return;
         }
      }
   }
   
   // �ҵ��Ļ�����m_pSet��ת���ô���
   m_pSet->MoveFirst();
   
   while ( !m_pSet->IsEOF() )
   {
      if ( m_pSet->m_Word == szBuffer )
      {
         PublicAssign();
         break;
      }
      m_pSet->MoveNext();
   }
	
}

/////////////////////////////////////////////////////////////////////////////
//ֱ����ת
void CMagicWordDlg::OnTiao() 
{
	// TODO: Add your control notification handler code here
	  CWordDaoSet TempSet;
   CString     strSQL;
   UpdateData();

   if ( m_goto.IsEmpty() )
   {
      MessageBox( _T( "~~ͬѧ�����Ȼ�������뵥��<(�����)>!" ),
                  _T( "�����뵥��!" ), MB_OK | MB_ICONASTERISK );
      return;
   }
     if ( !m_goto.Find( ' ' ) )
   {
      MessageBox( _T( "~~�����в����пյ�Ŷ������~*!" ),
                  _T( "����" ), MB_OK | MB_ICONINFORMATION );
      return;
   }

   // ������CWordDaoSet��ʱ��������ѯ
   if ( TempSet.IsOpen() )
      TempSet.Close();
   
   strSQL.Format( "SELECT * from WordList WHERE word = '%s'", m_goto.operator LPCTSTR() );
   TempSet.Open( AFX_DAO_USE_DEFAULT_TYPE, strSQL, 0 );

   // û���ҵ����ƶ�m_pSet����֤��OnNext()�ȿ�����������
   if ( TempSet.IsEOF() )
   {
      MessageBox( _T( "~~���ʿ���û��������ʣ��Ͽ���ӣ��ݨ���y !" ),
                  _T( "��תʧ��!" ), MB_OK | MB_ICONASTERISK );
      return;
   }
   
   // �ҵ��Ļ�����m_pSet��ת���ô���
   m_pSet->MoveFirst();
   
   while ( !m_pSet->IsEOF() )
   {
      if ( !m_pSet->m_Word.CompareNoCase( m_goto ) )
      {
         PublicAssign();
         break;
      }
      m_pSet->MoveNext();
   }

   // ���m_goto����
   m_goto.Empty();   
	
}

/////////////////////////////////////////////////////////////////////////////
// ��ʾ�ϴ��˳�ʱע��ĵ���
void CMagicWordDlg::HistroyVisitWord()
{
   HKEY hKey = 0;
   BYTE szBuffer[26] = { '\0' };
   DWORD dwType = REG_SZ;
   DWORD dwSize = 27;

   memset( szBuffer, 0, dwSize );

   if ( RegOpenKeyEx( HKEY_CURRENT_USER, "SOFTWARE\\MagicWord",
                      NULL, KEY_ALL_ACCESS, &hKey ) == ERROR_SUCCESS )
   {
      if ( RegQueryValueEx( hKey, "CurrentWord", NULL, &dwType, szBuffer, &dwSize ) == ERROR_SUCCESS )
         m_jump = szBuffer;
   }
}

/////////////////////////////////////////////////////////////////////////////
// ���ڱ�����ʱע�ᵱǰ����
BOOL CMagicWordDlg::DestroyWindow() 
{
   RegCurrentRecord();

   if ( m_pSet->IsOpen() )
      m_pSet->Close();

   if ( m_pSet )
      delete m_pSet;

	return CDialog::DestroyWindow();
}


/////////////////////////////////////////////////////////////////////////////
// ���WM_CLOSE����(ע�ᵱǰ����)
void CMagicWordDlg::OnClose() 
{
	CDialog::OnClose();
}

/////////////////////////////////////////////////////////////////////////////
// ע�����һ������ʾ�ĵ�����Ϣ
void CMagicWordDlg::RegCurrentRecord()
{
   HKEY hKey = 0;
   char szStatus[26] = { '\0' };
   DWORD dwSize = 27;

   if ( RegOpenKeyEx( HKEY_CURRENT_USER, "SOFTWARE\\MagicWord", 
                      NULL, KEY_ALL_ACCESS, &hKey ) == ERROR_SUCCESS )
   {
      wsprintf( szStatus, "%s", m_pSet->m_Word );
      RegSetValueEx( hKey, "CurrentWord", 0, REG_SZ, (CONST BYTE*) szStatus, dwSize );
      RegCloseKey( hKey );
   }
   else
   {
      RegCreateKey( HKEY_CURRENT_USER, "SOFTWARE\\MagicWord", &hKey );
      wsprintf( szStatus, "%s", m_pSet->m_Word );
      RegSetValueEx( hKey, "CurrentWord", 0, REG_SZ, (CONST BYTE*) szStatus, dwSize );
      RegCloseKey( hKey );
   }
}

/////////////////////////////////////////////////////////////////////////////
// ʹ�س�����Ч
void CMagicWordDlg::OnOK() 
{
}

//��ʱ����Ӧ����
void CMagicWordDlg::OnTimer(UINT nIDEvent) 
{
	switch(m_WAY)
	{
	case 0:

		OnXiayi();
		break;
	case 1:
		OnShangyi();
		break;
	case 2:
     MessageBox( _T( "~~�����ĺ���è���Ҷ�˵�˲�Ҫ��!!! ������(>�n<)~~" ), 
                  _T( "����!" ), MB_OK | MB_ICONINFORMATION );
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}
































