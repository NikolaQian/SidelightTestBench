// stdafx.cpp : source file that includes just the standard includes
//	SidelightTestBench.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
CString g_strSetupIniPath = "";

int IniAppProject(void)
{	
	/****E-获取工程的相对路径并将工程路径从char*转换为CString类型****/

	int nPos;
	CString strAbsolutePath, strAppFolderPath;
	GetModuleFileName(NULL, strAbsolutePath.GetBufferSetLength(MAX_PATH+1), MAX_PATH);
	strAbsolutePath.ReleaseBuffer(); 
	nPos = strAbsolutePath.ReverseFind('\\');
	strAppFolderPath = strAbsolutePath.Left(nPos);
	nPos = strAppFolderPath.ReverseFind('\\');
	strAppFolderPath = strAppFolderPath.Left(nPos);
	
	g_strSetupIniPath  = strAppFolderPath + "\\Setup.Ini";

	return 0;
}

int GetSections(CStringArray &arrSection)
{
	/*
本函数基础：
GetPrivateProfileSectionNames - 从 ini 文件中获得 Section 的名称
如果 ini 中有两个 Section: [sec1] 和 [sec2]，则返回的是 'sec1',0,'sec2',0,0 ，当你不知道 
ini 中有哪些 section 的时候可以用这个 api 来获取名称 
*/
    int i; 
    int iPos=0; 
    int iMaxCount;
    TCHAR chSectionNames[2048]={0}; //总的提出来的字符串
    TCHAR chSection[64]={0}; //存放一个段名。
    GetPrivateProfileSectionNames(chSectionNames,2048,g_strSetupIniPath);

    //以下循环，截断到两个连续的0
    for(i=0;i<2048;i++)
	{
        if (chSectionNames[i]==0)
        if (chSectionNames[i]==chSectionNames[i+1])
        break;
	}

    iMaxCount=i+1; //要多一个0号元素。即找出全部字符串的结束部分。
    //arrSection.RemoveAll();//清空原数组

    for(i=0;i<iMaxCount;i++)
	{
        chSection[iPos++]=chSectionNames[i];
        if(chSectionNames[i]==0 && 0 != i)
		{ 
            arrSection.Add(chSection);
            memset(chSection,0,i);
            iPos=0;
		}

	}

    return (int)arrSection.GetSize();
}



