
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
 * \file   RankingPanel.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2015-02-23
 * \brief  �����ʵ���ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2015-02-23    by chengxuan
 *
 * \endverbatim
 *
 */
#include "RankingPanel.h"
#include "TR.h"
#include <QLabel>
#include <QVBoxLayout>

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

RankingPanel::RankingPanel(QWidget *parent)
    : QWidget(parent)
{
    this->createUI();
    this->createConnect();
}

RankingPanel::~RankingPanel()
{
    /*Do nothing.*/
}

void RankingPanel::createUI()
{
    m_tipLabel = new QLabel(TR("�񵥽������ڿ�����..."), this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_tipLabel);
    mainLayout->addStretch();
    this->setLayout(mainLayout);
}

void RankingPanel::createConnect()
{

}
