// SidelightTestBenchView.h : interface of the CSidelightTestBenchView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "NiButton.h"
//}}AFX_INCLUDES

#if !defined(AFX_SIDELIGHTTESTBENCHVIEW_H__1775C0E7_B376_46D4_9173_1F5A80CCA222__INCLUDED_)
#define AFX_SIDELIGHTTESTBENCHVIEW_H__1775C0E7_B376_46D4_9173_1F5A80CCA222__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReportCtrl.h"
#include "SerialPort.h"
#include "DlgDeleteType.h"
#include "DlgAddType.h"
#include "DlgModify.h"

//定时器标识宏定义
#define TIMER_MCU							10001			//定时向下位机发送LED状态帧
#define TIMER_QUERY_AMMETER					10002			//查询精密电流表

#define TIMER_TIMEOUT_MCU					10005			//下位机连接超时
#define TIMER_TIMEOUT_QUERY_AMMETER			10006			//精密电流表连接超时

//定时器常亮
const int connTimeMCU = 500;					//MCU
const int connTimeQueryAMMeter = 100;			//电流表
const int connTimeOut = 80;				//

//串口常量定义
const int connComMCU = 8;					//与下位机通信串口
const int connBaundMCU = 19200;
const int connComAMmeter = 7;				//与精密电流表通信串口
const int connBaundAMmeter = 9600;
const int connSendBufferLen = 3;			//与MCU通信帧长度

typedef enum _TestResult
{
	FAIL = 0,
	PASS = 1,
}TestResult, *lpTestResult;

typedef enum _ENAMMeterState
{
	eAMMeterLink = 0,
	eAMMeterQuery = 1,
}
ENAMMeterState, *lpENAMMeterState;

#include "DlgModify.h"	// Added by ClassView
class CSidelightTestBenchView : public CFormView
{
protected: // create from serialization only
	CSidelightTestBenchView();
	DECLARE_DYNCREATE(CSidelightTestBenchView)

public:
	//{{AFX_DATA(CSidelightTestBenchView)
	enum { IDD = IDD_SIDELIGHTTESTBENCH_FORM };
	CStatic	m_staticTypeCtrl;
	CComboBox	m_comboTypeCtrl;
	CNiButton	m_cwbMCULink;
	CNiButton	m_cwbAmperemeterLink;
	CNiButton	m_cwbQualfiied;
	CNiButton	m_cwbResult;
	CNiButton	m_cwbAmmeterValue;
	//}}AFX_DATA

// Attributes
public:
	CSidelightTestBenchDoc* GetDocument();
	int nDetItemRow[256][256];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSidelightTestBenchView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool GetMyClientRect(RECT rectPage, LPRECT lpClientRect);
	void InitWindow();
	bool m_bAMMeterStateFlag;
	CDlgModify m_dlgModify;
	void RefreshCombox();
	CDlgDeleteType m_dlgDeleteType;
	CDlgAddType m_dlgAddType;
	void InitList();
	void InitComboBoxType();
	void DisplayAMMeterState(bool bFlag);
	unsigned char m_ucSendResult;
	CString m_strCurrentElec;
	CString m_strTestResult;
	void GetAMMeterValueAndResult(float fCurrent);
	void DataProcessAMmeter(float fCurrent);
	void DataProcessAmmeter();
	int m_nRecAmount;
	unsigned char m_ucRecCharArray[20];
	bool m_bHeaderFlag;
	bool m_bEnableFlag;
	void DataProcessMCU(CString strData);
	LONG OnCommunication(WPARAM ch, LPARAM port);
	int m_nAMMeterCount;
	void UartSendBuffer(CSerialPort *port, CString strSend);
	void QueryAMMeter(int nNum);
	void UartSendBuffer(CSerialPort *port, unsigned char buffer[],int length);
	unsigned char m_uchSendBuffer[connSendBufferLen];
	CSerialPort m_spAMmeter;
	CSerialPort m_spMCU;
	void InitialPort();
	double m_dbMinElectricity;
	double m_dbMaxElectricity;
	void InitGetRange();
	void InitUI();
	CString m_code;
	virtual ~CSidelightTestBenchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSidelightTestBenchView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeComboType();
	afx_msg void OnAddType();
	afx_msg void OnDeleteType();
	afx_msg void OnModifyType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

#ifndef _DEBUG  // debug version in SidelightTestBenchView.cpp
inline CSidelightTestBenchDoc* CSidelightTestBenchView::GetDocument()
   { return (CSidelightTestBenchDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIDELIGHTTESTBENCHVIEW_H__1775C0E7_B376_46D4_9173_1F5A80CCA222__INCLUDED_)
