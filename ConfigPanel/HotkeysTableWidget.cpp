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
* \file   HotKeysTableWidget.cpp
* \author chengxuan   787280310@qq.com
* \date   2015-01-24
* \brief  �ȼ�ҳ��ʵ���ļ���
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

#include "HotkeysTableWidget.h"
#include "NoFocusDelegate.h"
#include "TR.h"
#include <QHeaderView>

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

HotKeysTableWidget::HotKeysTableWidget(QWidget *parent) 
	: QTableWidget(parent)
{
    //���ô��ڻ�������
    this->setRowCount(0);//��ʼ��������Ϊ0
    this->setColumnCount(2);//��ʼ��������Ϊ2

    QStringList headList;
	headList << TR("����") << TR("ȫ���ȼ�");
    this->setHorizontalHeaderLabels(headList);								//����ͷ��Ϣ

    this->verticalHeader()->setVisible(false);
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);	//���������Զ�����������������
    this->horizontalHeader()->setHighlightSections(false);					//�����ʱ���Ա�ͷ�й�������ȡ���㣩
	this->horizontalHeader()->setSectionsClickable(false);					//����Ӧ��굥��
    this->setSelectionMode(QAbstractItemView::SingleSelection);				//����ֻ��ѡ�е���
    this->setSelectionBehavior(QAbstractItemView::SelectRows);				//����ѡ��ϰ��Ϊѡ����
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);				//�������ݲ��ɱ༭
    this->setShowGrid(false);												//���ò���ʾ����
    this->setItemDelegate(new NoFocusDelegate());							//ȥ��ѡ�е�Ԫ�������

    this->setStyleSheet("color: black;");
}

HotKeysTableWidget::~HotKeysTableWidget()
{
	/*Do nothing.*/
}
