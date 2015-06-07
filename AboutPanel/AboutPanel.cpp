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
 * \file   AboutPanel.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-22
 * \brief  �������ʵ���ļ���
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

#include "AboutPanel.h"
#include "AboutPage.h"
#include "AuthorPage.h"
#include "ThanksPage.h"
#include "Global.h"
#include "TR.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if ABOUTPAGE_VERSION < 0x030000
#error  "AboutPage version error."
#endif

#if AUTHORPAGE_VERSION < 0x030000
#error  "AuthorPage version error."
#endif

#if THANKSPAGE_VERSION < 0x030000
#error  "ThanksPage version error."
#endif

#if GLOBAL_VERSION < 0x030000
#error  "Global version error."
#endif

#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

AboutPanel::AboutPanel(QWidget *parent)
	: QDialog(parent),
	m_aboutPage(NULL),
	m_authorPage(NULL),
	m_thanksPage(NULL)
{
	//���ô��ڻ�������
	this->resize(530, 535);//���ô����С
	this->setMinimumSize(530, 535);
	this->setWindowTitle(TR("����CZPlayer"));

	m_logoLabel = new QLabel(this);
	m_logoLabel->setPixmap(QPixmap(ImagesDir + "CZPlayerWhite.png"));

	//����ҳ��
	m_aboutPage = new AboutPage(this);

	//����ҳ��
	m_authorPage = new AuthorPage(this);

	//��лҳ��
	m_thanksPage = new ThanksPage(this);

	m_tabWidget = new QTabWidget(this);
	m_tabWidget->addTab(m_aboutPage, TR("����"));
	m_tabWidget->addTab(m_authorPage, TR("����"));
	m_tabWidget->addTab(m_thanksPage, TR("��л"));

	m_okButton = new QPushButton(this);
	m_okButton->setText(TR("ȷ��"));

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_okButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_logoLabel);
	mainLayout->addWidget(m_tabWidget);
	mainLayout->addLayout(bottomLayout);
	this->setLayout(mainLayout);

	connect(m_okButton, SIGNAL(clicked()), this, SLOT(close()));
}


AboutPanel::~AboutPanel(void)
{
	if (m_aboutPage != NULL)
	{
		m_aboutPage->deleteLater();
		m_aboutPage = NULL;
	}
	/*Else do nothing, and continue.*/

	if (m_authorPage != NULL)
	{
		m_authorPage->deleteLater();
		m_authorPage = NULL;
	}
	/*Else do nothing, and continue.*/

	if (m_thanksPage != NULL)
	{
		m_thanksPage->deleteLater();
		m_thanksPage = NULL;
	}
	/*Else do nothing, and continue.*/
}

void AboutPanel::init()
{
	m_tabWidget->setCurrentIndex(0);
}
