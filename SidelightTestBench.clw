; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSidelightTestBenchView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "sidelighttestbench.h"
LastPage=0

ClassCount=9
Class1=CMainFrame
Class2=CReportCtrl
Class3=CSidelightTestBenchApp
Class4=CAboutDlg
Class5=CSidelightTestBenchDoc
Class6=CSidelightTestBenchView

ResourceCount=6
Resource1=IDD_DELETE_TYPE
Resource2=IDD_ADD_TYPE
Resource3=IDD_SIDELIGHTTESTBENCH_FORM
Class7=CDlgAddType
Resource4=IDR_MAINFRAME
Class8=CDlgDeleteType
Resource5=IDD_ABOUTBOX
Class9=CDlgModify
Resource6=IDD_DLG_MODIFY

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CReportCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=ReportCtrl.h
ImplementationFile=ReportCtrl.cpp

[CLS:CSidelightTestBenchApp]
Type=0
BaseClass=CWinApp
HeaderFile=SidelightTestBench.h
ImplementationFile=SidelightTestBench.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SidelightTestBench.cpp
ImplementationFile=SidelightTestBench.cpp
LastObject=CAboutDlg

[CLS:CSidelightTestBenchDoc]
Type=0
BaseClass=CDocument
HeaderFile=SidelightTestBenchDoc.h
ImplementationFile=SidelightTestBenchDoc.cpp

[CLS:CSidelightTestBenchView]
Type=0
BaseClass=CFormView
HeaderFile=SidelightTestBenchView.h
ImplementationFile=SidelightTestBenchView.cpp
LastObject=CSidelightTestBenchView
Filter=D
VirtualFilter=VWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SIDELIGHTTESTBENCH_FORM]
Type=1
Class=CSidelightTestBenchView
ControlCount=17
Control1=IDC_CWB_TITLE,{D940E4BE-6079-11CE-88CB-0020AF6845F6},1342242816
Control2=IDC_STATIC_TYPE,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_CWB_MCULINK,{D940E4BE-6079-11CE-88CB-0020AF6845F6},1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CWB_AMPEREMETER,{D940E4BE-6079-11CE-88CB-0020AF6845F6},1073807360
Control7=IDC_STATIC,static,1073872896
Control8=IDC_STATIC,button,1342177287
Control9=IDC_COMBO_TYPE,combobox,1344339971
Control10=IDC_CWB_QUALIFIED,{D940E4BE-6079-11CE-88CB-0020AF6845F6},1342242816
Control11=IDC_CWB_MCULINK3,{D940E4BE-6079-11CE-88CB-0020AF6845F6},1342242816
Control12=IDC_CWB_AMMETER_VALUE,{D940E4BE-6079-11CE-88CB-0020AF6845F6},1342242816
Control13=IDC_CWB_RESULT,{D940E4BE-6079-11CE-88CB-0020AF6845F6},1342242816
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CSidelightTestBenchView
Command1=IDM_ADD_TYPE
Command2=IDM_DELETE_TYPE
Command3=IDM_MODIFY_TYPE
Command4=ID_APP_ABOUT
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ADD_TYPE]
Type=1
Class=CDlgAddType
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_ADD_TYPE_MIN_ELEC,edit,1350639744
Control4=IDC_EDIT_ADD_TYPE_MAX_ELEC,edit,1350639744
Control5=IDC_BTN_SAVE,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_ADD_TYPE_TYPE,edit,1350631552

[CLS:CDlgAddType]
Type=0
HeaderFile=DlgAddType.h
ImplementationFile=DlgAddType.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_ADD_TYPE_TYPE
VirtualFilter=dWC

[DLG:IDD_DELETE_TYPE]
Type=1
Class=CDlgDeleteType
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO_DELETE_TYPE,combobox,1344339971
Control3=IDC_BTN_DELETE_TYPE_DELETE,button,1342242816

[CLS:CDlgDeleteType]
Type=0
HeaderFile=DlgDeleteType.h
ImplementationFile=DlgDeleteType.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO_DELETE_TYPE
VirtualFilter=dWC

[DLG:IDD_DLG_MODIFY]
Type=1
Class=CDlgModify
ControlCount=7
Control1=IDC_COMBO_MODIFY,combobox,1344339971
Control2=IDC_EDIT_MODIFY_MIN_ELEC,edit,1350639744
Control3=IDC_EDIT_MODIFY_MAX_ELEC,edit,1350639744
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BTN_MODFIY,button,1342242816

[CLS:CDlgModify]
Type=0
HeaderFile=DlgModify.h
ImplementationFile=DlgModify.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

