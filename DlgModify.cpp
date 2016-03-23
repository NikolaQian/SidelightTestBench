// DlgModify.cpp : implementation file
//

#include "stdafx.h"
#include "sidelighttestbench.h"
#include "DlgModify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgModify dialog


CDlgModify::CDlgModify(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgModify::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgModify)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgModify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgModify)
	DDX_Control(pDX, IDC_COMBO_MODIFY, m_comboModifyCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgModify, CDialog)
	//{{AFX_MSG_MAP(CDlgModify)
	ON_BN_CLICKED(IDC_BTN_MODFIY, OnBtnModfiy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgModify message handlers

BOOL CDlgModify::OnInitDialog() 
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
		m_comboModifyCtrl.InsertString(i, strArrayTypeName.GetAt(i));
	}
	
	m_comboModifyCtrl.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgModify::OnBtnModfiy() 
{
	CString strType = "";
	CString strElecMin = "";
	CString strElecMax = "";
	CString strTmp;
	int nIndex;

	double dbElecMin = 0.0;
	double dbElecMax = 0.0;
	
	nIndex = m_comboModifyCtrl.GetCurSel();
	m_comboModifyCtrl.GetLBText(nIndex, strType);
		
	GetDlgItemText(IDC_EDIT_MODIFY_MIN_ELEC, strElecMin.GetBuffer(20), 20);
	strElecMin.ReleaseBuffer();
	GetDlgItemText(IDC_EDIT_MODIFY_MAX_ELEC, strElecMax.GetBuffer(20), 20);
	strElecMax.ReleaseBuffer();

	dbElecMin = atof(strElecMin);
	dbElecMax = atof(strElecMax);
	
	if(dbElecMin < 0.000001)
	{
		dbElecMin = 0;
		
	}
	if(dbElecMax < 0.000001)
	{
		dbElecMax = 0;
	}
	
	strTmp = "";
	strTmp.Format("是否修改型号:%s的值？\n电流最小值:%.1fmA\n电流最大值:%.1fmA", strType, dbElecMin, dbElecMax);
	
	if(IDOK == MessageBox(strTmp, NULL, MB_OKCANCEL))
	{
		strElecMin.Format("%.1f", dbElecMin);
		WritePrivateProfileString(strType, "MinElectricity", strElecMin, g_strSetupIniPath);
		strElecMax.Format("%.1f", dbElecMax);
		WritePrivateProfileString(strType, "MaxElectricity", strElecMax, g_strSetupIniPath);
		SendMessage(WM_CLOSE);
	}
}
