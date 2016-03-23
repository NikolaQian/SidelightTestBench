// SidelightTestBenchDoc.h : interface of the CSidelightTestBenchDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIDELIGHTTESTBENCHDOC_H__DDB48765_676C_4EE8_B0B1_9747C8BF917E__INCLUDED_)
#define AFX_SIDELIGHTTESTBENCHDOC_H__DDB48765_676C_4EE8_B0B1_9747C8BF917E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSidelightTestBenchDoc : public CDocument
{
protected: // create from serialization only
	CSidelightTestBenchDoc();
	DECLARE_DYNCREATE(CSidelightTestBenchDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSidelightTestBenchDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSidelightTestBenchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSidelightTestBenchDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIDELIGHTTESTBENCHDOC_H__DDB48765_676C_4EE8_B0B1_9747C8BF917E__INCLUDED_)
