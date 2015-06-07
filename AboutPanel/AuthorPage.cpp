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
 * \file   AuthorPage.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-22
 * \brief  ����ҳ��ʵ���ļ���
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

#include "AuthorPage.h"
#include "TR.h"
#include <QVBoxLayout>
#include <QLabel>

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

AuthorPage::AuthorPage(QWidget *parent)
	: QWidget(parent)
{
	m_mainAuthorLabel = new QLabel;
	m_mainAuthorLabel->setText(TR("���Ŀ�����\n		���� <787280310@qq.com>"));

	m_plugAuthorLabel = new QLabel;
	m_plugAuthorLabel->setText(TR("���������\n		���� <787280310@qq.com>"));

	m_artAuthorLabel = new QLabel;
	m_artAuthorLabel->setText(TR("������\n		���� <787280310@qq.com>"));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_mainAuthorLabel);
	mainLayout->addWidget(m_plugAuthorLabel);
	mainLayout->addWidget(m_artAuthorLabel);
	mainLayout->addStretch();
	this->setLayout(mainLayout);
}


AuthorPage::~AuthorPage(void)
{
	/*Do nothing.*/
}
