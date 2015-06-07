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
 * \file   ThanksPage.h
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-22
 * \brief  ��лҳ��ͷ�ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2014-12-22    by chengxuan
 *
 * \endverbatim
 *
 */

#ifndef THANKSPAGE_H
#define THANKSPAGE_H

/*! \def THANKSPAGE_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define THANKSPAGE_VERSION   0x030000

#include <QWidget>

class QLabel;

/*! ��лҳ��
 */
class ThanksPage: public QWidget
{
	Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
     */
	ThanksPage(QWidget *parent = NULL);

	/*! ��������.*/
	~ThanksPage(void);

	QLabel *m_thanksLabel;	/*!< ��л�ı�*/
};

#endif //THANKSPAGE_H

