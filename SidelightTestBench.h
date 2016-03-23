// SidelightTestBench.h : main header file for the SIDELIGHTTESTBENCH application
//

#if !defined(AFX_SIDELIGHTTESTBENCH_H__42C8DF29_590C_4F88_973E_5B3159A384FF__INCLUDED_)
#define AFX_SIDELIGHTTESTBENCH_H__42C8DF29_590C_4F88_973E_5B3159A384FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSidelightTestBenchApp:
// See SidelightTestBench.cpp for the implementation of this class
//

class CSidelightTestBenchApp : public CWinApp
{
public:
	CSidelightTestBenchApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSidelightTestBenchApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSidelightTestBenchApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIDELIGHTTESTBENCH_H__42C8DF29_590C_4F88_973E_5B3159A384FF__INCLUDED_)
