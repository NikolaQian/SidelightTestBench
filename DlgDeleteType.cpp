// DlgDeleteType.cpp : implementation file
//

#include "stdafx.h"
#include "sidelighttestbench.h"
#include "DlgDeleteType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDeleteType dialog


CDlgDeleteType::CDlgDeleteType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeleteType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDeleteType)
	//}}AFX_DATA_INIT
}


void CDlgDeleteType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeleteType)
	DDX_Control(pDX, IDC_COMBO_DELETE_TYPE, m_comboDeleteTypeCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDeleteType, CDialog)
	//{{AFX_MSG_MAP(CDlgDeleteType)
	ON_BN_CLICKED(IDC_BTN_DELETE_TYPE_DELETE, OnBtnDeleteTypeDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDeleteType message handlers



void CDlgDeleteType::OnBtnDeleteTypeDelete() 
{
	CString strTypeName = "";
	CString strTmp;
	int nIndex;
	
	nIndex = m_comboDeleteTypeCtrl.GetCurSel();
	m_comboDeleteTypeCtrl.GetLBText(nIndex, strTypeName);
	
	strTmp.Format("是否删除型号%s及其参数？", strTypeName);
	if(IDOK == MessageBox(strTmp, NULL, MB_OKCANCEL))
	{
		WritePrivateProfileSection(strTypeName, NULL, g_strSetupIniPath);
		SendMessage(WM_CLOSE);
	}
}

BOOL CDlgDeleteType::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CStringArray strArrayTypeName;
	GetSections(strArrayTypeName);
	
//	if(0 == strArrayTypeName.GetSize())
//	{
//		MessageBox("注意当前无任何产品型号信息，请添加");
//	}

	for(int i=0; i<strArrayTypeName.GetSize(); i++)
	{
		m_comboDeleteTypeCtrl.InsertString(i, strArrayTypeName.GetAt(i));
	}
	
	m_comboDeleteTypeCtrl.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
