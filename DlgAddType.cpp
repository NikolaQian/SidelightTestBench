// DlgAddType.cpp : implementation file
//

#include "stdafx.h"
#include "sidelighttestbench.h"
#include "DlgAddType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddType dialog


CDlgAddType::CDlgAddType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddType)
	//}}AFX_DATA_INIT
}


void CDlgAddType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddType)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddType, CDialog)
	//{{AFX_MSG_MAP(CDlgAddType)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddType message handlers

void CDlgAddType::OnBtnSave() 
{
	CString strTmp = "";
	CString strType = "";
	CString strElecMin = "";
	CString strElecMax = "";

	double dbElecMin = 0.0;
	double dbElecMax = 0.0;

	GetDlgItemText(IDC_EDIT_ADD_TYPE_TYPE, strType.GetBuffer(20), 20);
	strType.ReleaseBuffer();
	GetDlgItemText(IDC_EDIT_ADD_TYPE_MIN_ELEC, strElecMin.GetBuffer(20), 20);
	strElecMin.ReleaseBuffer();
	GetDlgItemText(IDC_EDIT_ADD_TYPE_MAX_ELEC, strElecMax.GetBuffer(20), 20);
	strElecMax.ReleaseBuffer();

	if(strType == "")
	{
		MessageBox("型号不能为空!");
		return;
	}

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
	strTmp.Format("是否保存以下值?\n型号:%s\n电流最小值:%.1fmA\n电流最大值:%.1fmA", strType, dbElecMin, dbElecMax);
	
	if(IDOK == MessageBox(strTmp, NULL, MB_OKCANCEL))
	{
		strElecMin.Format("%.1f", dbElecMin);
		WritePrivateProfileString(strType, "MinElectricity", strElecMin, g_strSetupIniPath);
		strElecMax.Format("%.1f", dbElecMax);
		WritePrivateProfileString(strType, "MaxElectricity", strElecMax, g_strSetupIniPath);
		SendMessage(WM_CLOSE);
	}
		
}

