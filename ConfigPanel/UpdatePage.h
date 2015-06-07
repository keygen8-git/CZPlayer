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
* \file   UpdatePage.h
* \author chengxuan   787280310@qq.com
* \date   2015-01-24
* \brief  �������ҳ��ͷ�ļ���
* \version 3.0.0
*
* \verbatim
* ��ʷ
*          3.0.0   ����,
*          2015-01-24    by chengxuan
*
* \endverbatim
*
*/

#ifndef UPDATEPAGE_H
#define UPDATEPAGE_H

/*! \def UPDATEPAGE_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define UPDATEPAGE_VERSION   0x030000

#include <QWidget>

class QLabel;
class QPushButton;

/*! �������ҳ��
*/
class UpdatePage : public QWidget
{
	Q_OBJECT

public:
	/*! ���캯��
	*  \param parent ������ָ�룬Ĭ��ΪNULL
	*/
	UpdatePage(QWidget *parent = NULL);

	/*! ��������.*/
	~UpdatePage(void);

private slots:
	/*! �������
	 */
	void handleUpdate();

private:
	/*! ��������
	 */
	void createUI();

	/*! �ź����
	 */
	void createConnect();

private:
	QLabel *m_updateInfoLabel;		/*!< ������Ϣ*/
	QPushButton *m_updateButton;	/*!< ��ʼ���°�ť*/
};

#endif //UPDATEPAGE_H

