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
 * \file   CollectionPanel.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2015-02-23
 * \brief  �ղ����ʵ���ļ���
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

#include "CollectionPanel.h"
#include "NoFocusDelegate.h"
#include "TR.h"
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

CollectionPanel::CollectionPanel(QWidget *parent)
    : QWidget(parent)
{
    this->createUI();
    this->createConnect();
}

CollectionPanel::~CollectionPanel()
{
    /*Do nothing.*/
}

void CollectionPanel::handleAddCollectMusic(const QString &musicName, const QString &artist)
{
    //��������
    QTableWidgetItem *musicNameItem = new QTableWidgetItem;
    musicNameItem->setTextAlignment(Qt::AlignCenter);
    musicNameItem->setText(musicName);
    musicNameItem->setToolTip(musicName);

    //������
    QTableWidgetItem *artistItem = new QTableWidgetItem;
    artistItem->setTextAlignment(Qt::AlignCenter);
    artistItem->setText(artist);
    artistItem->setToolTip(artist);

    int currentRows = m_collectTable->rowCount();
    m_collectTable->insertRow(currentRows);
    m_collectTable->setItem(currentRows, 0, musicNameItem);
    m_collectTable->setItem(currentRows, 1, artistItem);
}

void CollectionPanel::createUI()
{
    //�Ѳ��б�
    m_collectTable = new QTableWidget(this);
    this->setTableWidgetStyle();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_collectTable);
    this->setLayout(mainLayout);
}

void CollectionPanel::createConnect()
{

}

void CollectionPanel::setTableWidgetStyle()
{
    m_collectTable->setRowCount(0);
    m_collectTable->setColumnCount(2);

    QStringList headList;
    headList << TR("��������") << TR("������");
    m_collectTable->setHorizontalHeaderLabels(headList);

    m_collectTable->setSelectionMode(QAbstractItemView::SingleSelection);              //����ֻ��ѡ�е���
    m_collectTable->setSelectionBehavior(QAbstractItemView::SelectRows);               //����ѡ��ϰ��Ϊѡ����
    m_collectTable->setEditTriggers(QAbstractItemView::NoEditTriggers);                //�������ݲ��ɱ༭
    m_collectTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //���������Զ�����������������
    m_collectTable->setFrameStyle(QFrame::NoFrame);                                    //ȥ���߿�
    m_collectTable->setShowGrid(false);                                                //���ò���ʾ����
    m_collectTable->setItemDelegate(new NoFocusDelegate());                            //ȥ��ѡ�е�Ԫ�������
    m_collectTable->horizontalHeader()->setHighlightSections(false);                   //�����ʱ���Ա�ͷ�й�������ȡ���㣩
    m_collectTable->verticalHeader()->setVisible(false);                               //���ô�ֱͷ���ɼ�
    m_collectTable->horizontalHeader()->setSectionsClickable(false);                   //����Ӧ��굥��
}
