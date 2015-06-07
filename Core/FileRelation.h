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
* \file   FileRelation.h
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

#ifndef FILERELATION_H
#define FILERELATION_H

/*! \def FILERELATION_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define FILERELATION_VERSION   0x030000

#include <Shlobj.h>
#include <Windows.h>

/*! �ļ�������
 */
class FileRelation
{
public:
    /*! ���캯��.*/
    FileRelation();

    /*! ��������.*/
    ~FileRelation();

public:
    /*! ע���ļ�����
     * \param wExt Ҫ������չ��(����: ".wav")
     * \param wAppPath Ҫ������Ӧ�ó�����(����: "C:/MyApp/MyApp.exe")
     * \param wAppKey wExt��չ����ע����еļ�ֵ(����: "CZPlayer2.WAV")
     * \param wDefaultIcon ��չ��ΪwAppPath��ͼ���ļ�(����: "D:/visual studio 2010 Projects/spectrum/debug/spectrum.exe,0")
     * \param wDescribe �ļ���������
     */
	static void registerFileRelation(WCHAR *wExt, WCHAR *wAppPath, WCHAR *wAppKey, 
        WCHAR *wDefaultIcon, WCHAR *wDescribe);

    /*! ȡ���ļ�����
     * \param wExt Ҫ������չ��(����: ".wav")
     * \param wAppKey ExeName��չ����ע����еļ�ֵ(����: "CZPlayer2.0.WAV")
     */
    static void cancelFileRelation(WCHAR *wExt, WCHAR *wAppKey);

    /*! �ж��ļ�����
     * \param wExt Ҫ������չ��(����: ".wav")
     * \param wAppKey ExeName��չ����ע����еļ�ֵ(����: "CZPlayer2.0.WAV")
     * \return ����true: ��ʾ�ѹ�����false: ��ʾδ����
     */
    static bool checkFileRelation(const WCHAR* wExt, const WCHAR *wAppKey);
};

#endif //FILERELATION_H

