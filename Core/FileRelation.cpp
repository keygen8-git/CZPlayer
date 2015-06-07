/***************************************************************************
*   Copyright (C) 2012-2015 Highway-9 Studio.                             *
*   787280310@qq.com									                   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   CUIT Highway-9 Studio, China.									       *
***************************************************************************/

/*!
* \file   FileRelation.cpp
* \author chengxuan   787280310@qq.com
* \date   2015-05-01
* \brief  ����������ʵ���ļ���
* \version 3.0.0
*
* \verbatim
* ��ʷ
*          3.0.0   ����,
*          2015-05-01    by chengxuan
*
* \endverbatim
*
*/

#include "FileRelation.h"
#include <tchar.h>
#include <QString>

FileRelation::FileRelation()
{
    /*Do nothing.*/
}

FileRelation::~FileRelation()
{
    /*Do nothing.*/
}

void FileRelation::registerFileRelation( WCHAR *wExt, WCHAR *wAppPath, WCHAR *wAppKey, 
	WCHAR *wDefaultIcon, WCHAR *wDescribe )
{
	WCHAR wTemp[MAX_PATH];  
	HKEY hKey;  

	//������Ϊ.wav,��������ֵΪCZPlayer2.WAV
	RegCreateKey(HKEY_CLASSES_ROOT, wExt, &hKey);							//.wav
    RegSetValue(hKey, (wchar_t*)QString("").utf16(), REG_SZ, wAppKey, lstrlen(wAppKey) + 1);		//CZPlayer2.WAV
	RegCloseKey(hKey);  

	//������ΪCZPlayer2.WAV,��������ֵΪWAV�ļ�
	RegCreateKey(HKEY_CLASSES_ROOT, wAppKey, &hKey);						 //CZPlayer2.WAV
    RegSetValue(hKey, (wchar_t*)QString("").utf16(), REG_SZ, wDescribe, lstrlen(wDescribe) + 1);	 //WAV�ļ�
	RegCloseKey(hKey);  

	//����Ĭ��ͼ��(����:D:/visual studio 2010 Projects/spectrum/debug/spectrum.exe,0)
    wsprintf(wTemp, (wchar_t*)QString("%s\\DefaultIcon").utf16(), wAppKey);
	RegCreateKey(HKEY_CLASSES_ROOT, wTemp, &hKey);  
    RegSetValue(hKey, (wchar_t*)QString("").utf16(), REG_SZ, wDefaultIcon, lstrlen(wDefaultIcon) + 1);
	RegCloseKey(hKey);  

	//SHCNE_ASSOCCHANGED:�޸��ļ�����   
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);//�þ�Ϊˢ��ϵͳ����

    wsprintf(wTemp, (wchar_t*)QString("%s\\Shell\\Open").utf16(), wAppKey);
	RegCreateKey(HKEY_CLASSES_ROOT, wTemp, &hKey);  
    RegSetValue(hKey, (wchar_t*)QString("").utf16(), REG_SZ, (wchar_t*)QString("ʹ�� CZPlayer ����(&O)").utf16(), strlen("ʹ�� CZPlayer ����(&O)") + 1);
	RegCloseKey(hKey);  

	//���ù�������(����:"D:/visual studio 2010 Projects/spectrum/debug/spectrum.exe" "%1")
    wsprintf(wTemp, (wchar_t*)QString("%s\\Shell\\Open\\Command").utf16(), wAppKey);
	RegCreateKey(HKEY_CLASSES_ROOT, wTemp, &hKey);  
    wsprintf(wTemp ,(wchar_t*)QString("\"%s\" \"%%1\"").utf16(), wAppPath);
    RegSetValue(hKey, (wchar_t*)QString("").utf16(), REG_SZ, wTemp, lstrlen(wTemp) + 1);
	RegCloseKey(hKey);
}

void FileRelation::cancelFileRelation( WCHAR *wExt, WCHAR *wAppKey )
{
	WCHAR wTemp[MAX_PATH];  
	HKEY hKey;  

	//������Ϊ.wav,��������ֵΪCZPlayer2.WAV
	RegCreateKey(HKEY_CLASSES_ROOT, wExt, &hKey);		//.wav
    RegSetValue(hKey, (wchar_t*)QString("").utf16(), REG_SZ, (wchar_t*)QString("").utf16(), 2);		//CZPlayer2.WAV
	RegCloseKey(hKey);  

	//����Ĭ��ͼ��
    wsprintf(wTemp, (wchar_t*)QString("%s\\DefaultIcon").utf16(), wAppKey);
	RegCreateKey(HKEY_CLASSES_ROOT, wTemp, &hKey);  
    RegSetValue(hKey, (wchar_t*)QString("").utf16(), REG_SZ, (wchar_t*)QString("").utf16(), 2 + 1);
	RegCloseKey(hKey);  

	//SHCNE_ASSOCCHANGED:�޸��ļ�����   
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);//�þ�Ϊˢ��ϵͳ���� 
}

bool FileRelation::checkFileRelation( const WCHAR* wExt, const WCHAR *wAppKey )
{
	bool isRelation = false;
	HKEY hKey;

	if(RegOpenKey(HKEY_CLASSES_ROOT, wExt, &hKey)==ERROR_SUCCESS)
	{
		WCHAR wData[MAX_PATH];
		DWORD dwLen = MAX_PATH * sizeof(WCHAR);
		if (RegQueryValueEx(hKey, 0, 0, 0, (BYTE*)wData, &dwLen) == ERROR_SUCCESS)
		{
			if (lstrcmp(wData, wAppKey) == 0)
			{
				isRelation = true;
			}
            /*Else do nothing, and continue.*/
		}
        /*Else do nothing, and continue.*/

		RegCloseKey(hKey);
		return isRelation;
	}
    /*Else do nothing, and continue.*/

	return isRelation;
}
