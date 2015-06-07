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
* \file   ConfigDialog.cpp
* \author chengxuan   787280310@qq.com
* \date   2015-01-24
* \brief  ȫ������ʵ���ļ���
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

#include "ConfigDialog.h"
#include "GeneralSettingsPage.h"
#include "DownloadSettingsPage.h"
#include "LrcSettingsPage.h"
#include "HotkeysSettingsPage.h"
#include "UpdatePage.h"
#include "Global.h"
#include "TR.h"
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QDir>
#include <QCloseEvent>
#ifdef CZ_DEBUG
#include <QDebug>
#endif

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if GENERALSETTINGSPAGE_VERSION < 0x030000
#error  "GeneralSettingsPage version error."
#endif

#if DOWNLOADSETTINGSPAGE_VERSION < 0x030000
#error  "DownloadSettingsPage version error."
#endif

#if LRCSETTINGSPAGE_VERSION < 0x030000
#error  "LrcSettingsPage version error."
#endif

#if HOTKEYSSETTINGSPAGE_VERSION < 0x030000
#error  "HotkeysSettingsPage version error."
#endif

#if UPDATEPAGE_VERSION < 0x030000
#error  "UpdatePage version error."
#endif

#if GLOBAL_VERSION < 0x030000
#error  "Global version error."
#endif

#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

ConfigDialog::ConfigDialog(QWidget *parent) 
	: QDialog(parent),
	  m_generalSettingsPage(NULL),
	  m_downloadSettingsPage(NULL),
	  m_lrcSettingsPage(NULL),
	  m_hotKeysSettingsPage(NULL),
	  m_updatePage(NULL),
	  m_isGeneralSettingsChanged(false),
	  m_isDownloadSettingsChanged(false),
	  m_isLrcSettingsChanged(false),
	  m_isHotKeysSettingsChanged(false)
{
	this->createUI();
	this->createConnect();
}

ConfigDialog::~ConfigDialog()
{
	//��������
	if (m_generalSettingsPage != NULL)
	{
		m_generalSettingsPage->deleteLater();
		m_generalSettingsPage = NULL;
	}
	/*Else do nothing, and continue.*/

	//��������
	if (m_downloadSettingsPage != NULL)
	{
		m_downloadSettingsPage->deleteLater();
		m_downloadSettingsPage = NULL;
	}
	/*Else do nothing, and continue.*/

	//�������
	if (m_lrcSettingsPage != NULL)
	{
		m_lrcSettingsPage->deleteLater();
		m_lrcSettingsPage = NULL;
	}
	/*Else do nothing, and continue.*/

	//�ȼ�����
	if (m_hotKeysSettingsPage != NULL)
	{
		m_hotKeysSettingsPage->deleteLater();
		m_hotKeysSettingsPage = NULL;
	}
	/*Else do nothing, and continue.*/

	//����ҳ��
	if (m_updatePage != NULL)
	{
		m_updatePage->deleteLater();
		m_updatePage = NULL;
	}
	/*Else do nothing, and continue.*/
}

//����ͼ��
void ConfigDialog::createIcons()
{
    //��������
    QListWidgetItem *generalSettingsItem = new QListWidgetItem(m_contentsWidget);
    generalSettingsItem->setIcon(QIcon(ImagesDir + "generalSettingsButton.png"));
    generalSettingsItem->setText(TR("��������"));
    generalSettingsItem->setTextAlignment(Qt::AlignCenter);
    generalSettingsItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    //��������
    QListWidgetItem *downloadSettingsItem = new QListWidgetItem(m_contentsWidget);
    downloadSettingsItem->setIcon(QIcon(ImagesDir + "downloadSettingsButton.png"));
    downloadSettingsItem->setText(TR("��������"));
    downloadSettingsItem->setTextAlignment(Qt::AlignCenter);
    downloadSettingsItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    //�������
    QListWidgetItem *lrcSettingsItem = new QListWidgetItem(m_contentsWidget);
    lrcSettingsItem->setIcon(QIcon(ImagesDir + "lrcSettingsButton.png"));
    lrcSettingsItem->setText(TR("�������"));
    lrcSettingsItem->setTextAlignment(Qt::AlignCenter);
    lrcSettingsItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    //�ȼ�����
    QListWidgetItem *hotKeysSettingsItem = new QListWidgetItem(m_contentsWidget);
    hotKeysSettingsItem->setIcon(QIcon(ImagesDir + "hotKeysSettingsButton.png"));
    hotKeysSettingsItem->setText(TR("�ȼ�����"));
    hotKeysSettingsItem->setTextAlignment(Qt::AlignCenter);
    hotKeysSettingsItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	//����ҳ��
	QListWidgetItem *updateItem = new QListWidgetItem(m_contentsWidget);
    updateItem->setIcon(QIcon(ImagesDir + "updateButton.png"));
	updateItem->setText(TR("�������"));
	updateItem->setTextAlignment(Qt::AlignCenter);
	updateItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

//�ı�ҳ��
void ConfigDialog::handleChangePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
    {
        current = previous;
    }
	/*Else do nothing, and continue.*/
    m_pagesWidget->setCurrentIndex(m_contentsWidget->row(current));
}

void ConfigDialog::handleOkFunc()
{
    this->handleAppFunc();
	this->close();
}

void ConfigDialog::handleAppFunc()
{
	if (m_isGeneralSettingsChanged)
	{
		m_generalSettingsPage->apply();
	}
	/*Else do nothing, and continue.*/

	if (m_isDownloadSettingsChanged)
	{
		m_downloadSettingsPage->apply();
	}
	/*Else do nothing, and continue.*/

	if (m_isLrcSettingsChanged)
	{
		m_lrcSettingsPage->apply();
	}
	/*Else do nothing, and continue.*/

	if (m_isHotKeysSettingsChanged)
	{
		m_hotKeysSettingsPage->apply();
	}
	/*Else do nothing, and continue.*/

	m_appButton->setEnabled(false);
}

void ConfigDialog::init()
{
	m_contentsWidget->setCurrentRow(0);
	m_generalSettingsPage->init();
	m_downloadSettingsPage->init();
	m_lrcSettingsPage->init();
	m_hotKeysSettingsPage->init();

	m_isGeneralSettingsChanged = false;
	m_isDownloadSettingsChanged = false;
	m_isLrcSettingsChanged = false;
	m_isHotKeysSettingsChanged = false;

	m_appButton->setEnabled(false);
}

void ConfigDialog::createUI()
{
	//���ô��ڻ�������
	this->resize(665, 482);//���ô����С
	this->setMinimumSize(665, 482);
	this->setMaximumSize(665, 482);
	this->setWindowTitle(TR("CZPlayer ����"));

	//����ѡ��
    m_contentsWidget = new QListWidget(this);
	m_contentsWidget->setViewMode(QListView::ListMode);//IconMode
	m_contentsWidget->setIconSize(QSize(96, 84));
	m_contentsWidget->setMovement(QListView::Static);
	m_contentsWidget->setMaximumWidth(128);
	m_contentsWidget->setSpacing(12);
	this->createIcons();

	//��������
	if (m_generalSettingsPage == NULL)
	{
		m_generalSettingsPage = new GeneralSettingsPage(this);
	}
	/*Else do nothing, and continue.*/

	//��������
	if (m_downloadSettingsPage == NULL)
	{
		m_downloadSettingsPage = new DownloadSettingsPage(this);
	}
	/*Else do nothing, and continue.*/

	//�������
	if (m_lrcSettingsPage == NULL)
	{
		m_lrcSettingsPage = new LrcSettingsPage(this);
	}
	/*Else do nothing, and continue.*/

	//�ȼ�����
	if (m_hotKeysSettingsPage == NULL)
	{
		m_hotKeysSettingsPage = new HotKeysSettingsPage(this);
	}
	/*Else do nothing, and continue.*/

	//����ҳ��
	if (m_updatePage == NULL)
	{
		m_updatePage = new UpdatePage(this);
	}
	/*Else do nothing, and continue.*/

	//��ҳ��ʾ
    m_pagesWidget = new QStackedWidget(this);
	m_pagesWidget->addWidget(m_generalSettingsPage);
	m_pagesWidget->addWidget(m_downloadSettingsPage);
	m_pagesWidget->addWidget(m_lrcSettingsPage);
	m_pagesWidget->addWidget(m_hotKeysSettingsPage);
	m_pagesWidget->addWidget(m_updatePage);
	m_contentsWidget->setCurrentRow(0);

	//ȷ����ť
	m_okButton = new QPushButton(this);
	m_okButton->setObjectName(TR("m_okButton"));
	m_okButton->setText(TR("ȷ��"));

	//ȡ����ť
	m_cancelButton = new QPushButton(this);
	m_cancelButton->setObjectName(TR("m_cancelButton"));
	m_cancelButton->setText(TR("ȡ��"));

	//Ӧ�ð�ť
	m_appButton = new QPushButton(this);
	m_appButton->setObjectName(TR("m_appButton"));
	m_appButton->setText(TR("Ӧ��"));

	QHBoxLayout *horizontalLayout = new QHBoxLayout;
	horizontalLayout->addWidget(m_contentsWidget);
	horizontalLayout->addWidget(m_pagesWidget);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(m_okButton);
	buttonsLayout->addWidget(m_cancelButton);
	buttonsLayout->addWidget(m_appButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(horizontalLayout);
	//mainLayout->addStretch();
	mainLayout->addLayout(buttonsLayout);
	this->setLayout(mainLayout);
}

void ConfigDialog::createConnect()
{
	connect(m_contentsWidget,
		SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
		this, SLOT(handleChangePage(QListWidgetItem*, QListWidgetItem*)));

	connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_okButton, SIGNAL(clicked()), this, SLOT(handleOkFunc()));
	connect(m_appButton, SIGNAL(clicked()), this, SLOT(handleAppFunc()));

	connect(m_generalSettingsPage, SIGNAL(sigGeneralSettingsChanged()),
		this, SLOT(handleGeneralSettingsChanged()));
	connect(m_downloadSettingsPage, SIGNAL(sigDownloadSettingsChanged()),
		this, SLOT(handleDownloadSettingsChanged()));
	connect(m_hotKeysSettingsPage, SIGNAL(sigHotKeysSettingsChanged()),
		this, SLOT(handleHotKeysSettingsChanged()));
	connect(m_lrcSettingsPage, SIGNAL(sigLrcSettingsChanged()),
		this, SLOT(handleLrcSettingsChanged()));
}

void ConfigDialog::handleGeneralSettingsChanged()
{
	m_isGeneralSettingsChanged = true;
	m_appButton->setEnabled(true);
}

void ConfigDialog::handleDownloadSettingsChanged()
{
	m_isDownloadSettingsChanged = true;
	m_appButton->setEnabled(true);
}

void ConfigDialog::handleLrcSettingsChanged()
{
	m_isLrcSettingsChanged = true;
	m_appButton->setEnabled(true);
}

void ConfigDialog::handleHotKeysSettingsChanged()
{
	m_isHotKeysSettingsChanged = true;
	m_appButton->setEnabled(true);
}

void ConfigDialog::closeEvent(QCloseEvent *event)
{
	emit sigConfigDialogClosed();
	QDialog::closeEvent(event);
}










