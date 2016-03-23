#if !defined(AFX_DLGADDTYPE_H__25DF6D12_4D2D_4DB0_ADC4_A84EA011C15B__INCLUDED_)
#define AFX_DLGADDTYPE_H__25DF6D12_4D2D_4DB0_ADC4_A84EA011C15B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddType dialog

class CDlgAddType : public CDialog
{
// Construction
public:
	CDlgAddType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddType)
	enum { IDD = IDD_ADD_TYPE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddType)
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDTYPE_H__25DF6D12_4D2D_4DB0_ADC4_A84EA011C15B__INCLUDED_)
