#if !defined(AFX_DLGMODIFY_H__BFF3C1FE_BD7A_4990_BEE8_737A8A6C3508__INCLUDED_)
#define AFX_DLGMODIFY_H__BFF3C1FE_BD7A_4990_BEE8_737A8A6C3508__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgModify.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgModify dialog

class CDlgModify : public CDialog
{
// Construction
public:
	CDlgModify(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgModify)
	enum { IDD = IDD_DLG_MODIFY };
	CComboBox	m_comboModifyCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgModify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgModify)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnModfiy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMODIFY_H__BFF3C1FE_BD7A_4990_BEE8_737A8A6C3508__INCLUDED_)
