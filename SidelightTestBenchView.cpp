// SidelightTestBenchView.cpp : implementation of the CSidelightTestBenchView class
//

#include "stdafx.h"
#include "ReportCtrl.h"
#include "SidelightTestBench.h"
#include "SerialPort.h"
#include "SidelightTestBenchDoc.h"
#include "SidelightTestBenchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSidelightTestBenchView

IMPLEMENT_DYNCREATE(CSidelightTestBenchView, CFormView)

BEGIN_MESSAGE_MAP(CSidelightTestBenchView, CFormView)
	//{{AFX_MSG_MAP(CSidelightTestBenchView)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_COMMAND(IDM_ADD_TYPE, OnAddType)
	ON_COMMAND(IDM_DELETE_TYPE, OnDeleteType)
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommunication)
	ON_COMMAND(IDM_MODIFY_TYPE, OnModifyType)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSidelightTestBenchView construction/destruction

CSidelightTestBenchView::CSidelightTestBenchView()
	: CFormView(CSidelightTestBenchView::IDD)
{
	//{{AFX_DATA_INIT(CSidelightTestBenchView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	for(int i=0; i<connSendBufferLen; i++)
	{
		m_uchSendBuffer[i] = 0;
	}
	m_uchSendBuffer[1] = 0x09;

	m_nAMMeterCount = eAMMeterLink;
	
	m_bAMMeterStateFlag = true;
	m_bHeaderFlag = FALSE;
	m_bEnableFlag = TRUE;
	m_nRecAmount = 0;
	for(i=0; i<20; i++)
	{
		m_ucRecCharArray[i] = 0;
	}
	m_strTestResult = "FAIL";
}

CSidelightTestBenchView::~CSidelightTestBenchView()
{
}

void CSidelightTestBenchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSidelightTestBenchView)
	DDX_Control(pDX, IDC_STATIC_TYPE, m_staticTypeCtrl);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboTypeCtrl);
	DDX_Control(pDX, IDC_CWB_MCULINK, m_cwbMCULink);
	DDX_Control(pDX, IDC_CWB_AMPEREMETER, m_cwbAmperemeterLink);
	DDX_Control(pDX, IDC_CWB_QUALIFIED, m_cwbQualfiied);
	DDX_Control(pDX, IDC_CWB_RESULT, m_cwbResult);
	DDX_Control(pDX, IDC_CWB_AMMETER_VALUE, m_cwbAmmeterValue);
	//}}AFX_DATA_MAP
}

BOOL CSidelightTestBenchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSidelightTestBenchView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	//	IniAppProject();
	g_strSetupIniPath = "./Setup.ini";
	InitUI();
	InitialPort();
	
	
	SetTimer(TIMER_MCU, connTimeMCU, NULL);
	SetTimer(TIMER_QUERY_AMMETER, connTimeQueryAMMeter, NULL);

}

/////////////////////////////////////////////////////////////////////////////
// CSidelightTestBenchView printing

BOOL CSidelightTestBenchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSidelightTestBenchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSidelightTestBenchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSidelightTestBenchView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CSidelightTestBenchView diagnostics

#ifdef _DEBUG
void CSidelightTestBenchView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSidelightTestBenchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

//CSidelightTestBenchDoc* CSidelightTestBenchView::GetDocument() // non-debug version is inline
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSidelightTestBenchDoc)));
//	return (CSidelightTestBenchDoc*)m_pDocument;
//}
#endif //_DEBUG


void CSidelightTestBenchView::InitUI()
{	
	InitWindow();
	InitComboBoxType();
	InitList();
}

void CSidelightTestBenchView::InitGetRange()
{
	CString strTmp, strTypeName;
	int nIndex;

	nIndex = m_comboTypeCtrl.GetCurSel();
	m_comboTypeCtrl.GetLBText(nIndex, strTypeName);

	GetPrivateProfileString(strTypeName, "MaxElectricity", "", strTmp.GetBuffer(50), 50, g_strSetupIniPath);
	strTmp.ReleaseBuffer();
	m_dbMaxElectricity = atof(strTmp);

	GetPrivateProfileString(strTypeName, "MinElectricity", "", strTmp.GetBuffer(50), 50, g_strSetupIniPath);
	strTmp.ReleaseBuffer();
	m_dbMinElectricity = atof(strTmp);
}

void CSidelightTestBenchView::InitialPort()
{
	CString strTmp = "";
	//��λ��ͨ�Ŵ��ڳ�ʼ��
	if(m_spMCU.InitPort(this, connComMCU, connBaundMCU, 'N', 8, 1, EV_RXCHAR | EV_RXFLAG, 512))
	{
		m_spMCU.StartMonitoring();
	}
	else
	{
		strTmp.Format("����%d��ʧ��, �ÿ�������λ��!", connComMCU);
		MessageBox(strTmp, "COMM��ʧ��", MB_ICONERROR);
	}
	//���ܵ������ڳ�ʼ��
	if(m_spAMmeter.InitPort(this, connComAMmeter, connBaundAMmeter, 'N', 8, 1, EV_RXCHAR | EV_RXFLAG, 512))
	{
		m_spAMmeter.StartMonitoring();
	}
	else
	{
		strTmp.Format("����%d��ʧ��, �ÿ����ӵ�����!", connComAMmeter);
		MessageBox(strTmp, "COMM��ʧ��", MB_ICONERROR);
	}
}

void CSidelightTestBenchView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case TIMER_MCU:
		  {
			m_uchSendBuffer[0] = 0x30;
			m_uchSendBuffer[2] = 0x20;
			UartSendBuffer(&m_spMCU, m_uchSendBuffer, connSendBufferLen);
			SetTimer(TIMER_TIMEOUT_MCU, max(50, connTimeMCU-100), NULL);
		  }
		  break;
	case TIMER_QUERY_AMMETER:
		{
			QueryAMMeter(m_nAMMeterCount);
			m_nAMMeterCount++;
			SetTimer(TIMER_TIMEOUT_QUERY_AMMETER, connTimeOut, NULL);
		}
		break;
	case TIMER_TIMEOUT_MCU:
		{
			KillTimer(TIMER_TIMEOUT_MCU);
			//��ʱ״̬��ʾ
			m_cwbMCULink.SetOnColor(RGB(255, 0, 0));
			m_cwbMCULink.OnText = "��MCUʧȥ����!";
		}
		break;
	case TIMER_TIMEOUT_QUERY_AMMETER:
		{
			KillTimer(TIMER_TIMEOUT_QUERY_AMMETER);
			//��ʱ״̬��ʾ
			DisplayAMMeterState(false);
		}
		break;
	default: break;
	}
	
	CFormView::OnTimer(nIDEvent);
}

void CSidelightTestBenchView::UartSendBuffer(CSerialPort *port, unsigned char buffer[], int length)
{
	if(port->m_hComm != 0)
		port->WriteToPort(buffer,length);
}

void CSidelightTestBenchView::QueryAMMeter(int nNum)
{
	switch(nNum)
	{
		case eAMMeterLink:	UartSendBuffer(&m_spAMmeter, "0103");
		case eAMMeterQuery:	UartSendBuffer(&m_spAMmeter, "01030062000265D5");
	}
}

void CSidelightTestBenchView::UartSendBuffer(CSerialPort *port, CString strSend)
{
	unsigned char SendBuf[100];
	memset(&SendBuf, 0, sizeof(SendBuf));
	int nLen = strSend.GetLength()/2;
	int nTmp = 0;

	for(int i =0 ; i <nLen;i++)
	{
		sscanf(strSend.Mid(i*2,2),"%x",&nTmp);
		SendBuf[i] = nTmp;
	}
	if(port->m_hComm != 0)
		port->WriteToPort(SendBuf,nLen);
}

LONG CSidelightTestBenchView::OnCommunication(WPARAM ch, LPARAM port)
{
	CString strTmp;
	float nTmp = 0;
	double dTmp = 0.0;
	float fCurrent = 0.0;

	switch(port)
	{
	case connComMCU:
		{
			if(0xAA == ch)
			{
				DataProcessMCU("");
			}

			if(0xBB == ch)
			{
				//	Sleep(1000);
				m_cwbAmmeterValue.OnText = m_strCurrentElec;
				m_cwbResult.OnText= m_strTestResult;
//				m_list.SetItemText(1, 2, m_strCurrentElec);
//				m_list.SetItemText(1, 3, m_strTestResult);
				
				if(0x00 == m_ucSendResult)
					m_cwbResult.SetOnColor(RGB(255,0,0));
					//	m_list.SetItemBkColor(1, 3, RGB(255,0,0));
				if(0x01 == m_ucSendResult)
					m_cwbResult.SetOnColor(RGB(0,255,0));
					//	m_list.SetItemBkColor(1, 3, RGB(0,255,0));

				m_uchSendBuffer[1] = m_ucSendResult;
				UartSendBuffer(&m_spMCU, m_uchSendBuffer, connSendBufferLen);
				m_uchSendBuffer[1] = 0x09;
			}
		}
		break;
	case connComAMmeter:
		{
			if((0x83 == ch && m_bEnableFlag))
			{
				KillTimer(TIMER_TIMEOUT_QUERY_AMMETER);
				DisplayAMMeterState(true);
				m_bAMMeterStateFlag = false;
			}
			

			if(0x04 == ch && m_bEnableFlag)
			{
				m_bHeaderFlag = TRUE;
			}
			if(m_bHeaderFlag)		//��ʼ����
			{
				m_ucRecCharArray[m_nRecAmount++] = ch;
				if(m_nRecAmount >= 6)
				{
					m_bEnableFlag = FALSE;
					m_bHeaderFlag = FALSE;
					m_nRecAmount = 0;
				}
			}

			if(!m_bEnableFlag && !m_bHeaderFlag)
			{
				CString strValueTmp;
				
				dTmp = (double)(m_ucRecCharArray[1] * 256) + m_ucRecCharArray[2];
				dTmp += ((m_ucRecCharArray[3] * 256) + m_ucRecCharArray[4])/65536.0;
				
				if(dTmp > 32767)
				{
					dTmp = (dTmp - 32768) * -1;
				}

				fCurrent = (float)dTmp;
		

				DataProcessAMmeter(fCurrent);
				m_bEnableFlag = TRUE;
			}else if(0xFF == ch && m_bEnableFlag){
				m_bAMMeterStateFlag = true;
			}
		}
		break;
	default : 
		break;
	}

	return 0;
}

void CSidelightTestBenchView::DataProcessMCU(CString strData)
{
	KillTimer(TIMER_TIMEOUT_MCU);
	m_cwbMCULink.SetOnColor(RGB(0, 255, 0));
	m_cwbMCULink.OnText = "��MCU��������!";
}

void CSidelightTestBenchView::DataProcessAmmeter()
{
	DisplayAMMeterState(true);
}

void CSidelightTestBenchView::DataProcessAMmeter(float fCurrent)
{
	KillTimer(TIMER_TIMEOUT_QUERY_AMMETER);
	//���ܵ��������ݴ���
	//���б������ʾ�������жϽ��
	GetAMMeterValueAndResult(fCurrent);
}

void CSidelightTestBenchView::GetAMMeterValueAndResult(float fCurrent)
{
	CString strCurTemp = "";
	CString strResult = "";

	strCurTemp.Format("%.3fmA", fCurrent);
	if((fCurrent >= m_dbMinElectricity) && (fCurrent <= m_dbMaxElectricity))
	{
		m_strTestResult = "PASS";
		m_ucSendResult = 0x01;
	}else
	{
		m_strTestResult = "FAIL";
		m_ucSendResult = 0x00;
	}
	
	m_strCurrentElec = strCurTemp;
}

void CSidelightTestBenchView::DisplayAMMeterState(bool bFlag)
{
	if(bFlag)
	{
		m_cwbAmperemeterLink.SetOnColor(RGB(0, 255, 0));
		m_cwbAmperemeterLink.OnText = "���������������!";
	}else
	{
		//��ʱ״̬��ʾ
		m_cwbAmperemeterLink.SetOnColor(RGB(255, 0, 0));
		m_cwbAmperemeterLink.OnText = "�������ʧȥ����!";
	}

	if(eAMMeterQuery < m_nAMMeterCount)			
	{
		m_nAMMeterCount = eAMMeterLink;
	}
}

void CSidelightTestBenchView::InitComboBoxType()
{
	CFont tFont;
	//tFont.CreateFont(18,14,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,\
	//				OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,\
	//				DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"����");
	tFont.CreateFont(20,10,0,0,FW_THIN,FALSE,FALSE,0,DEFAULT_CHARSET,\
						NULL,NULL,\
						NULL,NULL,"����"); 
	
	//��ʼ�������б�
	m_comboTypeCtrl.SetFont(&tFont);
	m_staticTypeCtrl.SetFont(&tFont);
	
	RefreshCombox();
}

void CSidelightTestBenchView::InitList()
{
	//��ʼ�����
	//m_LIST1.MoveWindow(400, 0, 600, 600);
//	//	m_list.MoveWindow(450, 102, 880, 600);
//	m_list.MoveWindow(600, 157, 682, 232);
//	
//	//����tColumn
//	LVCOLUMN tColumn;
//	tColumn.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
//	tColumn.fmt = LVCFMT_LEFT;
//	//����font
//	CFont tFont;
//	//tFont.CreateFont(18,14,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,\
//	//				OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,\
//	//				DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"����");
//	tFont.CreateFont(20,10,0,0,FW_THIN,FALSE,FALSE,0,DEFAULT_CHARSET,\
//						NULL,NULL,\
//						NULL,NULL,"����"); 
//	  
//	m_list.SetFont(&tFont);
	//	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP);

//	tFont.CreatePointFont(160, "����");
//	m_list.SetFont(&tFont);
	//�����б�����	
	//�����Ŀ
//	tColumn.cx = 180;
//	tColumn.iSubItem = 0;
//	tColumn.pszText = "�����Ŀ";
//	m_list.InsertColumn(0,&tColumn);
//	//�ϸ��׼
//	tColumn.cx = 180;
//	tColumn.iSubItem = 1;
//	tColumn.pszText = "�ϸ��׼";
//	m_list.InsertColumn(1,&tColumn);
//	//����ֵ��ȡ
//	tColumn.cx = 142;
//	tColumn.iSubItem = 2;
//	tColumn.pszText = "����ֵ��ȡ";
//	m_list.InsertColumn(2,&tColumn);
//	//�����
//	tColumn.cx = 180;
//	tColumn.iSubItem = 3;
//	tColumn.pszText = "�����";
//	m_list.InsertColumn(3,&tColumn);

//	int nRowSave, nRow, nColumn, nItemID;
//	//
//	for(nRow=0; nRow<8; nRow++)
//	{
//		m_list.InsertItem(nRow, "");
//		for(nColumn=0; nColumn<4; nColumn++)
//		{
//			m_list.SetItemText(nRow, nColumn, "");
//			m_list.SetItemBkColor(nRow, nColumn, RGB(220,220,220));
//		}
//	}
//	//
//	for(nRow=0; nRow<256; nRow++)
//	{
//		for(nColumn=0; nColumn<256; nColumn++)
//		{
//			nDetItemRow[nRow][nColumn]=-1;
//		}
//	}
//
//	CString strTmp;
//	nRowSave=1;
//	nItemID=1;
//	//�ߵƵ�������
//	nRow=nRowSave;
//	nDetItemRow[0x02][1]=nRow;
//	strTmp.Format("%d.�ߵƹ�������", nItemID++);
//	m_list.SetItemText(nRow++, 0, strTmp);
//	nRow=nRowSave;
//	strTmp.Format("%0.3f-%0.3f",m_dbMinElectricity, m_dbMaxElectricity);
//	m_list.SetItemText(nRow++, 1, strTmp+"mA");
//	nRowSave=nRow;
//	nRow=nRowSave;
}

/**
 *��ȡ�����ļ��нڵ���
 */


void CSidelightTestBenchView::OnSelchangeComboType() 
{
	CString strTmp = "";

	InitGetRange();
	
	strTmp.Format("%0.3f-%0.3f",m_dbMinElectricity, m_dbMaxElectricity);
	m_cwbQualfiied.OnText = strTmp+"mA";
	m_cwbAmmeterValue.OnText = "";
	m_cwbResult.OnText = "";
//	m_list.SetItemText(1, 1, strTmp+"mA");
//	m_list.SetItemText(1, 2, "");
//	m_list.SetItemText(1, 3, "");
	
}

void CSidelightTestBenchView::OnAddType() 
{
	m_dlgAddType.DoModal();
	
	m_comboTypeCtrl.ResetContent();
	RefreshCombox();
}

void CSidelightTestBenchView::OnDeleteType() 
{
	m_dlgDeleteType.DoModal();
	
	m_comboTypeCtrl.ResetContent();
	RefreshCombox();
}

void CSidelightTestBenchView::OnModifyType() 
{
	m_dlgModify.DoModal();

	m_comboTypeCtrl.ResetContent();
	RefreshCombox();
}

void CSidelightTestBenchView::RefreshCombox()
{
	CString strTmp;
	//��ȡ�������Ʋ���ӵ������б���
	CStringArray strArrayTypeName;
	GetSections(strArrayTypeName);
	
//	if(0 == strArrayTypeName.GetSize())
//	{
//		MessageBox("ע�⵱ǰ���κβ�Ʒ�ͺ���Ϣ�������");
//	}

	for(int i=0; i<strArrayTypeName.GetSize(); i++)
	{
		m_comboTypeCtrl.InsertString(i, strArrayTypeName.GetAt(i));
	}
	
	m_comboTypeCtrl.SetCurSel(0);

	InitGetRange();

	strTmp.Format("%0.3f-%0.3f",m_dbMinElectricity, m_dbMaxElectricity);
	m_cwbQualfiied.OnText = strTmp+"mA";
	m_cwbAmmeterValue.OnText = "";
	m_cwbResult.OnText = "";
	m_cwbResult.SetOnColor(RGB(220,220,220));

//	m_list.SetItemText(1, 1, strTmp+"mA");
//	
//	m_list.SetItemText(1, 2, "");
//	m_list.SetItemText(1, 3, "");
//	m_list.SetItemBkColor(1, 3, RGB(220,220,220));

}



void CSidelightTestBenchView::InitWindow()
{
	CString strTmp;

	bool bFlag = FALSE;
	RECT rectPage = CRect(0, 0, 0, 0);
	RECT rectClient;

	GetClientRect(&rectPage);

	bFlag = GetMyClientRect(rectPage, &rectClient);

	if(!bFlag)
	{
		strTmp.Format("��ȡ�ͻ�����ȳ�����ȷ�������ʾ���ߴ��Ƿ��С!(ע��: Page��СΪ: ��%d����%d����%d����%d)",
			rectPage.left, rectPage.top, rectPage.right, rectPage.bottom);
		MessageBox(strTmp, "Warning!", MB_OK | MB_ICONWARNING);
	}
	
	MoveWindow(&rectClient);
	ShowWindow(TRUE);
}

bool CSidelightTestBenchView::GetMyClientRect(RECT rectPage, LPRECT lpClientRect)
{
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	int nLeftFrame = GetSystemMetrics(SM_CXDLGFRAME);
	int nRightFrame = GetSystemMetrics(SM_CXDLGFRAME);
	int nBottomFrame = GetSystemMetrics(SM_CYDLGFRAME);
	int nTopFrame = GetSystemMetrics(SM_CYDLGFRAME);
	int nCaption = GetSystemMetrics(SM_CYSMCAPTION);

	int nClientWidth = cx - nLeftFrame - nRightFrame;
	HWND hWnd = FindWindow("Shell_TrayWnd", NULL)->m_hWnd;;
    RECT rc;
    ::GetWindowRect(hWnd, &rc);
    int nTaskbarHeight = rc.bottom -rc.top;
	int nClientHeight = cy - nCaption - nTopFrame - nBottomFrame - nTaskbarHeight;
	//	int nClientHeight = cy - nCaption - nTopFrame - nBottomFrame - 50;			//�ô�50Ϊ�������߶ȣ���֪��ô��ȡ����д���ˡ�

	int nClientLeft = 0;		//�ͻ��������������λ��
	int nClientTop = 0;			//�ͻ���������������λ��
	int nPageWidth = 0;			//ҳ����
	int nPageHeight = 0;		//ҳ��߶�
	
	nPageWidth = rectPage.right - rectPage.left;
	nPageHeight = rectPage.bottom - rectPage.top;

	if((nPageWidth > nClientWidth) || (nPageHeight > nClientHeight))
	{
		CString strTemp = "";
		strTemp.Format("ҳ����%d���ڿͻ������%d������ҳ��߶�%d���ڿͻ����߶�%d���ú������ú���ʾЧ�����ܽϲ�!", 
			nPageWidth, nClientWidth, nPageHeight, nClientHeight);
		MessageBox(strTemp, "�������þ���", MB_OK | MB_ICONERROR);

		nClientLeft = (nClientWidth - nPageWidth)/2;
		nClientTop = (nClientHeight - nPageHeight)/2;

		if(nClientLeft > 0)
		{
			lpClientRect->left = nClientLeft + nLeftFrame;
		}
		else
		{
			lpClientRect->left = nLeftFrame;
		}
		if(nClientTop >= 0)
		{
			lpClientRect->top = nClientTop + nTopFrame;
		}
		else
		{
			lpClientRect->top = nTopFrame;
		}

		lpClientRect->right = lpClientRect->left + nPageWidth;
		lpClientRect->bottom = lpClientRect->top + nPageHeight;

		return FALSE;
	}
	else
	{
		nClientLeft = (nClientWidth - nPageWidth)/2;
		nClientTop = (nClientHeight - nPageHeight)/2;

		lpClientRect->left = nClientLeft + nLeftFrame;
		lpClientRect->right = lpClientRect->left + nPageWidth;
		lpClientRect->top = nClientTop;
		lpClientRect->bottom = lpClientRect->top + nPageHeight;
	
		return TRUE;
	}
}
