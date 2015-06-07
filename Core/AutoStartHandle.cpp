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
* \file   AutoStartHandle.cpp
* \author chengxuan   787280310@qq.com
* \date   2015-05-02
* \brief  ����������������ʵ���ļ���
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

#include "AutoStartHandle.h"
#include "GlobalConfig.h"
#include "AutoStart.h"
#ifdef CZ_DEBUG
#include <QDebug>
#endif

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if GLOBALCONFIG_VERSION < 0x030000
#error  "GlobalConfig version error."
#endif

#if AUTOSTART_VERSION < 0x030000
#error  "AutoStart version error."
#endif

AutoStartHandle::AutoStartHandle(QObject *parent)
    : QObject(parent)
{
    this->createConnect();
}

AutoStartHandle::~AutoStartHandle()
{
    /*Do nothing.*/
}

void AutoStartHandle::handleAutoStart(bool isAutoStart)
{
    if (isAutoStart)
    {
        AutoStart::autoStart((wchar_t*)QString("CZPlayer").utf16());
    }
    else
    {
        AutoStart::cancelAutoStart((wchar_t*)QString("CZPlayer").utf16());
    }
}

void AutoStartHandle::createConnect()
{
    GlobalConfig *config = GlobalConfig::instance();
    connect(config, SIGNAL(sigAutoRunPlayerChanged(bool)), this, SLOT(handleAutoStart(bool)));
}
