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
 * \file   RadioInfoEntity.h
 * \author chengxuan   787280310@qq.com
 * \date   2015-03-06
 * \brief  ��̨��Ϣʵ��ͷ�ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2015-03-06    by chengxuan
 *
 * \endverbatim
 *
 */

#ifndef RADIOINFOENTITY_H
#define RADIOINFOENTITY_H

/*! \def RADIOINFOENTITY_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define RADIOINFOENTITY_VERSION   0x030000

#include <QString>

/*! ��̨��Ϣʵ��
*/
class RadioInfoEntity
{
public:
    /*! ���캯��.*/
    RadioInfoEntity();

    /*! ���캯��
     * \param name �����̨��
     * \param url �����̨url
     */
    RadioInfoEntity(const QString &name, const QString &url);

    /*! ��������.*/
    ~RadioInfoEntity();

    /*! �õ������̨��
     * \return ��̨��
     */
    QString name() const;

    /*! ���������̨��
     * \param name ��̨��
     */
    void setName(const QString &name);

    /*! �õ������̨url
     * \return ��̨url
     */
    QString url() const;

    /*! ���������̨url
     * \param name ��̨url
     */
    void setUrl(const QString &url);

private:
    QString m_name;     /*!< �����̨��*/
    QString m_url;      /*!< �����̨url*/
};

#endif // RADIOINFOENTITY_H
