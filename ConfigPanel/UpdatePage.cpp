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
* \file   UpdatePage.cpp
* \author chengxuan   787280310@qq.com
* \date   2015-01-24
* \brief  �������ҳ��ʵ���ļ���
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

#include "UpdatePage.h"
#include "TR.h"
#include <Windows.h>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QProcess>
#include <QMessageBox>
#ifdef CZ_DEBUG
#include <QDebug>
#endif

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

/*****************************************************************************
ȫ�ֱ�������
*****************************************************************************/
const QString AutoUpdatePath = "./AutoUpdate/AutoUpdate.exe";	/*!< ������������·��*/

UpdatePage::UpdatePage(QWidget *parent) 
	: QWidget(parent)
{
	this->createUI();
	this->createConnect();
}

UpdatePage::~UpdatePage(void)
{
	/*Do nothing.*/
}

void UpdatePage::createUI()
{
	QGroupBox *updateGB = new QGroupBox(TR("�������"), this);

	//������Ϣ
	m_updateInfoLabel = new QLabel(this);
	m_updateInfoLabel->setText(TR("������ʹ�õİ汾��V3.0 ����ʱ��:2014��07��18��"));

	//��ʼ���°�ť
	m_updateButton = new QPushButton(this);
	m_updateButton->setText(TR("�ֶ�������°汾"));

	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->addWidget(m_updateInfoLabel);
	hLayout->addStretch();

	QHBoxLayout *hLayout2 = new QHBoxLayout;
	hLayout2->addWidget(m_updateButton);
	hLayout2->addStretch();

	QVBoxLayout *vLayout = new QVBoxLayout;
	vLayout->addLayout(hLayout);
	vLayout->addLayout(hLayout2);
	updateGB->setLayout(vLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(updateGB);
	mainLayout->addStretch();
	this->setLayout(mainLayout);
}

void UpdatePage::createConnect()
{
	connect(m_updateButton, SIGNAL(clicked()), this, SLOT(handleUpdate()));
}

void UpdatePage::handleUpdate()
{
    unsigned long processId = GetCurrentProcessId();
    QStringList idList;
    idList << QString::number(processId);

    if (!QProcess::startDetached(AutoUpdatePath, idList))
    {
        QMessageBox::information(this, TR("��Ϣ"), TR("����������������ʧ�ܣ���ȷ�ϳ���·���Ƿ���ȷ��"), QMessageBox::Yes);
    }
    /*Else do nothing, and continue.*/
}
