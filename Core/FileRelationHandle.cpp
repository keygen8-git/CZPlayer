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
* \file   FileRelationHandle.cpp
* \author chengxuan   787280310@qq.com
* \date   2015-05-02
* \brief  �ļ�����������ʵ���ļ���
* \version 3.0.0
*
* \verbatim
* ��ʷ
*          3.0.0   ����,
*          2015-05-02    by chengxuan
*
* \endverbatim
*
*/

#include "FileRelationHandle.h"
#include "FileRelation.h"
#include "GlobalConfig.h"
#ifdef CZ_DEBUG
#include <QDebug>
#endif

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if GLOBALCONFIG_VERSION < 0x030000
#error  "GlobalConfig version error."
#endif

#if FILERELATION_VERSION < 0x030000
#error  "FileRelation version error."
#endif

FileRelationHandle::FileRelationHandle(QObject *parent)
    : QObject(parent)
{
    this->createConnect();
}

FileRelationHandle::~FileRelationHandle()
{
    /*Do nothing.*/
}

void FileRelationHandle::handleFileRelation(bool isRelationFile)
{
    if (isRelationFile)
    {
        WCHAR filePath[MAX_PATH];	//�ļ�������·��
        WCHAR icoPath[MAX_PATH];	//ͼ��·��

        //�õ���ǰִ���ļ���ȫ·��
        HMODULE hModule = GetModuleHandle(NULL);
        GetModuleFileName(hModule, filePath, sizeof(filePath));
        wsprintf(icoPath, (wchar_t*)QString("%s,0").utf16(), filePath);

        FileRelation::registerFileRelation((wchar_t*)QString(".mp3").utf16(), filePath,
                                           (wchar_t*)QString("CZPlayer.MP3").utf16(),
                                           icoPath, (wchar_t*)QString("MP3�ļ�").utf16());
        FileRelation::registerFileRelation((wchar_t*)QString(".wma").utf16(), filePath,
                                           (wchar_t*)QString("CZPlayer.WMA").utf16(),
                                           icoPath, (wchar_t*)QString("WMA�ļ�").utf16());
        FileRelation::registerFileRelation((wchar_t*)QString(".wav").utf16(), filePath,
                                           (wchar_t*)QString("CZPlayer.WAV").utf16(),
                                           icoPath, (wchar_t*)QString("WAV�ļ�").utf16());
        FileRelation::registerFileRelation((wchar_t*)QString(".ogg").utf16(), filePath,
                                           (wchar_t*)QString("CZPlayer.OGG").utf16(),
                                           icoPath, (wchar_t*)QString("OGG�ļ�").utf16());
    }
    else
    {
        FileRelation::cancelFileRelation((wchar_t*)QString(".mp3").utf16(), (wchar_t*)QString("CZPlayer.MP3").utf16());
        FileRelation::cancelFileRelation((wchar_t*)QString(".wma").utf16(), (wchar_t*)QString("CZPlayer.WMA").utf16());
        FileRelation::cancelFileRelation((wchar_t*)QString(".wav").utf16(), (wchar_t*)QString("CZPlayer.WAV").utf16());
        FileRelation::cancelFileRelation((wchar_t*)QString(".ogg").utf16(), (wchar_t*)QString("CZPlayer.OGG").utf16());
    }
}

void FileRelationHandle::createConnect()
{
    GlobalConfig *config = GlobalConfig::instance();
    connect(config, SIGNAL(sigDefaultPlayerChanged(bool)), this, SLOT(handleFileRelation(bool)));
}
