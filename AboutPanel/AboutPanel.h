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
 * \file   AboutPanel.h
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-22
 * \brief  �������ͷ�ļ���
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

#ifndef ABOUTPANEL_H
#define ABOUTPANEL_H

/*! \def ABOUTPANEL_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define ABOUTPANEL_VERSION   0x030000

#include <QDialog>

class QLabel;
class QPushButton;
class QTabWidget;
class AboutPage;
class AuthorPage;
class ThanksPage;

/*! �������
 */
class AboutPanel : public QDialog
{
	Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
     */
	AboutPanel(QWidget *parent = NULL);

	/*! ��������.*/
	~AboutPanel(void);

	/*! ��ʼ�����ڶԻ���.
	 */
	void init();

private:
	QTabWidget *m_tabWidget;		/*!< tabҳwidget*/
	QPushButton *m_okButton;		/*!< ȷ����ť*/
	QLabel *m_logoLabel;			/*!< logo*/

	AboutPage *m_aboutPage;			/*!< ����ҳ��*/
	AuthorPage *m_authorPage;		/*!< ����ҳ��*/
	ThanksPage *m_thanksPage;		/*!< ��лҳ��*/
};

#endif // ABOUTPANEL_H

