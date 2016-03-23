// stdafx.cpp : source file that includes just the standard includes
//	SidelightTestBench.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
CString g_strSetupIniPath = "";

int IniAppProject(void)
{	
	/****E-��ȡ���̵����·����������·����char*ת��ΪCString����****/

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
������������
GetPrivateProfileSectionNames - �� ini �ļ��л�� Section ������
��� ini �������� Section: [sec1] �� [sec2]���򷵻ص��� 'sec1',0,'sec2',0,0 �����㲻֪�� 
ini ������Щ section ��ʱ���������� api ����ȡ���� 
*/
    int i; 
    int iPos=0; 
    int iMaxCount;
    TCHAR chSectionNames[2048]={0}; //�ܵ���������ַ���
    TCHAR chSection[64]={0}; //���һ��������
    GetPrivateProfileSectionNames(chSectionNames,2048,g_strSetupIniPath);

    //����ѭ�����ضϵ�����������0
    for(i=0;i<2048;i++)
	{
        if (chSectionNames[i]==0)
        if (chSectionNames[i]==chSectionNames[i+1])
        break;
	}

    iMaxCount=i+1; //Ҫ��һ��0��Ԫ�ء����ҳ�ȫ���ַ����Ľ������֡�
    //arrSection.RemoveAll();//���ԭ����

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



