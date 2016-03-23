// SidelightTestBenchDoc.cpp : implementation of the CSidelightTestBenchDoc class
//

#include "stdafx.h"
#include "SidelightTestBench.h"

#include "SidelightTestBenchDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSidelightTestBenchDoc

IMPLEMENT_DYNCREATE(CSidelightTestBenchDoc, CDocument)

BEGIN_MESSAGE_MAP(CSidelightTestBenchDoc, CDocument)
	//{{AFX_MSG_MAP(CSidelightTestBenchDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSidelightTestBenchDoc construction/destruction

CSidelightTestBenchDoc::CSidelightTestBenchDoc()
{
	// TODO: add one-time construction code here

}

CSidelightTestBenchDoc::~CSidelightTestBenchDoc()
{
}

BOOL CSidelightTestBenchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSidelightTestBenchDoc serialization

void CSidelightTestBenchDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSidelightTestBenchDoc diagnostics

#ifdef _DEBUG
void CSidelightTestBenchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSidelightTestBenchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSidelightTestBenchDoc commands
