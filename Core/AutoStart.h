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
* \file   AutoStart.h
* \author chengxuan   787280310@qq.com
* \date   2015-05-01
* \brief  ����������ͷ�ļ���
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

#ifndef AUTOSTART_H
#define AUTOSTART_H

/*! \def AUTOSTART_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define AUTOSTART_VERSION   0x030000

#include <Windows.h>

/*! ������������
 */
class AutoStart
{
public:
    /*! ���캯��.*/
    AutoStart();

    /*! ��������.*/
    ~AutoStart();

public:
    /*! ���ÿ���������
     * \param value ע���ֵ
     */
    static void autoStart(WCHAR *value);

    /*! ȡ������������
     * \param value ע���ֵ
     */
    static void cancelAutoStart(WCHAR *value);

    /*! �жϳ����Ƿ�������
     * \param value ע���ֵ
     * \return true������������
     */
    static bool isAutoStart(WCHAR *value);
};

#endif // AUTOSTART_H

