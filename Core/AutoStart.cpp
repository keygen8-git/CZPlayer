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
* \file   AutoStart.cpp
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

#include "AutoStart.h"
#include <tchar.h>
#include <QString>
#ifdef CZ_DEBUG
#include <QDebug>
#endif

/*****************************************************************************
ȫ�ֱ�������
*****************************************************************************/
/*! ��ע���:·������*/
const QString Path = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

AutoStart::AutoStart()
{
    /*Do nothing.*/
}

AutoStart::~AutoStart()
{
    /*Do nothing.*/
}

void AutoStart::autoStart(WCHAR *value)
{
	WCHAR system[MAX_PATH];		//ϵͳĿ¼·��
	WCHAR filePath[MAX_PATH];	//Ҫ�������е��ļ�������·��
	WCHAR fileName[MAX_PATH];	//�ļ���(\CZPlayer.exe)

	//�õ���ǰִ���ļ���ȫ·��
	HMODULE hModule = GetModuleHandle(NULL);
	GetModuleFileName(hModule, filePath, sizeof(filePath));

	//�õ��ļ���
	for (int i = lstrlen(filePath) - 1; i >= 0; --i)
	{
		if (filePath[i] == '\\')
		{
			lstrcpy(fileName, &filePath[i]);
			break;
		}
        /*Else do nothing, and continue.*/
	}

	//�õ�ϵͳ�ļ�����Ŀ¼��·������c:\windows\system32
	GetSystemDirectory(system, sizeof(system));

	//�γ�Ҫ���Ƶ���ȫ·������c:\windows\system32\CZPlayer.exe
	wcscat_s(system, fileName);

	//���Ҹ��Ƶ�Ŀ��·��
	CopyFile(filePath, system, false);

	//д��ע����Ա㿪���Զ�����
	HKEY hKey;

    //��ע���
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, (wchar_t*)Path.utf16(), 0, KEY_SET_VALUE, &hKey ) == ERROR_SUCCESS)
	{
		//����һ��ֵ,������������,ֵΪҪ�������е��ļ�������·��
		RegSetValueEx(hKey, value, 0, REG_SZ, (const unsigned char*)system, sizeof(system));
		//�ر�ע���:
		RegCloseKey(hKey);

#ifdef CZ_DEBUG
        qDebug() << "���ÿ����������ɹ���";
#endif
	}
	else
	{
#ifdef CZ_DEBUG
        qDebug() << "��ע���ʧ�ܣ�";
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
#endif
	}
}

void AutoStart::cancelAutoStart(WCHAR *value)
{
	WCHAR system[MAX_PATH];		//ϵͳĿ¼·��
	WCHAR filePath[MAX_PATH];	//Ҫ�������е��ļ�������·��
	WCHAR fileName[MAX_PATH];	//�ļ���(\CZPlayer.exe)

	//�õ���ǰִ���ļ���ȫ·��
	HMODULE hModule = GetModuleHandle(NULL);
	GetModuleFileName(hModule, filePath, sizeof(filePath));

	//�õ��ļ���
	for (int i = lstrlen(filePath) - 1; i >= 0; --i)
	{
		if (filePath[i] == '\\')
		{
			lstrcpy(fileName, &filePath[i]);
			break;
		}
        /*Else do nothing, and continue.*/
	}

	//�õ�ϵͳ�ļ�����Ŀ¼��·������c:\windows\system32
	GetSystemDirectory(system, sizeof(system));

	//�γ�Ҫ���Ƶ���ȫ·������c:\windows\system32\CZPlayer.exe
	wcscat_s(system, fileName);

	HKEY hKey;
	DeleteFile(filePath);	//ɾ����Ӧ���ļ�
    //��ע���
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, (wchar_t*)Path.utf16(), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
	{
		//ɾ����ֵ
		RegDeleteValue(hKey, value);
		//�ر�ע���
		RegCloseKey(hKey);

#ifdef CZ_DEBUG
        qDebug() << "ȡ�������������ɹ���";
#endif
	}
	else
	{
#ifdef CZ_DEBUG
        qDebug() << "��ע���ʧ�ܣ�";
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
#endif
	}
}

bool AutoStart::isAutoStart(WCHAR *value)
{
	WCHAR system[MAX_PATH];		//ϵͳĿ¼·��
	WCHAR filePath[MAX_PATH];	//Ҫ�������е��ļ�������·��
	WCHAR fileName[MAX_PATH];	//�ļ���(\CZPlayer.exe)

	//�õ���ǰִ���ļ���ȫ·��
	HMODULE hModule = GetModuleHandle(NULL);
	GetModuleFileName(hModule, filePath, sizeof(filePath));

	//�õ��ļ���
	for (int i = lstrlen(filePath) - 1; i >= 0; --i)
	{
		if (filePath[i] == '\\')
		{
			lstrcpy(fileName, &filePath[i]);
			break;
		}
        /*Else do nothing, and continue.*/
	}

	//�õ�ϵͳ�ļ�����Ŀ¼��·������c:\windows\system32
	GetSystemDirectory(system, sizeof(system));

	//�γ�Ҫ���Ƶ���ȫ·������c:\windows\system32\CZPlayer.exe
	wcscat_s(system, fileName);

	HKEY hKey;
	bool bIsAutoStart =false;
    //��ע���
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, (wchar_t*)Path.utf16(), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		WCHAR wData[MAX_PATH];
		DWORD dwLen = MAX_PATH * sizeof(WCHAR);
		if (RegQueryValueEx(hKey, value, 0, 0, (BYTE*)wData, &dwLen) == ERROR_SUCCESS)
		{
			bIsAutoStart =  true;				//�ó���������������
		}
		else
		{
			bIsAutoStart =  false;				//�ó���û������������
		}
	}
	else
	{
#ifdef CZ_DEBUG
        qDebug() << "��ע���ʧ�ܣ�";
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
#endif
	}

	RegCloseKey(hKey);
	return bIsAutoStart;
}
