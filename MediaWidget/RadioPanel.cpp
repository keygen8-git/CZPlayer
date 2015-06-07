
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
 * \file   RadioPanel.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2015-02-23
 * \brief  ��̨���ʵ���ļ���
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

#include "RadioPanel.h"
#include "NoFocusDelegate.h"
#include "Global.h"
#include "TR.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QFile>
#include <QHeaderView>
#include <QtXml>
#include <QUrl>
#include <QPushButton>
#ifdef CZ_DEBUG
//#define XML_DEBUG
#include <QDebug>
#endif

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if GLOBAL_VERSION < 0x030000
#error  "Global version error."
#endif

#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

RadioPanel::RadioPanel(QWidget *parent)
    : QWidget(parent),
      m_currentRow(0),
      m_playStatus(Stoped)
{
    this->createUI();
    this->createConnect();
}

RadioPanel::~RadioPanel()
{
    m_radioPlayer->stop();
}

void RadioPanel::handlePlayRadio(const int &row)
{
    m_currentRow = row;
    m_radioInfo = m_radioInfoMap[m_currentRow];
    m_radioPlayer->stop();
    m_radioPlayer->setMedia(QUrl(m_radioInfo.url()));
    m_radioPlayer->play();
    m_currentRadioLabel->setText(TR("��ǰ���ŵ�̨��%1").arg(m_radioInfo.name()));
    m_radioTable->selectRow(m_currentRow);
    m_playButton->setStyleSheet(QString("QPushButton:!hover{border-image: url(%1audioPause.png);}"
        "QPushButton:hover{border-image: url(%1audioPause2.png);}"
        "QPushButton:pressed{border-image: url(%1audioPause.png);}").arg(ImagesDir));
    m_playStatus = Playing;
}

void RadioPanel::handlePlayRadio()
{
    if (m_radioTable->rowCount() == 0)
    {
        return;
    }
    /*Else do nothing, and continue.*/

    if (m_playStatus == Playing)
    {
        m_playButton->setStyleSheet(QString("QPushButton:!hover{border-image: url(%1audioPlay.png);}"
            "QPushButton:hover{border-image: url(%1audioPlay2.png);}"
            "QPushButton:pressed{border-image: url(%1audioPlay.png);}").arg(ImagesDir));
        m_playStatus = Stoped;
        m_radioPlayer->stop();
        m_currentRadioLabel->setText(TR("��ǰ���ŵ�̨��"));
    }
    else if (m_playStatus == Stoped)
    {
        m_playButton->setStyleSheet(QString("QPushButton:!hover{border-image: url(%1audioPause.png);}"
            "QPushButton:hover{border-image: url(%1audioPause2.png);}"
            "QPushButton:pressed{border-image: url(%1audioPause.png);}").arg(ImagesDir));
        m_playStatus = Playing;

        if (m_radioInfo.name().isEmpty() || m_radioInfo.url().isEmpty())
        {
            this->handlePlayRadio(0);
        }
        else
        {
            m_radioPlayer->stop();
            m_radioPlayer->setMedia(QUrl(m_radioInfo.url()));
            m_radioPlayer->play();
            m_currentRadioLabel->setText(TR("��ǰ���ŵ�̨��%1").arg(m_radioInfo.name()));
        }
    }
    /*Else do nothing, and continue.*/
}

void RadioPanel::handlePreRadio()
{
    if (m_radioTable->rowCount() == 0)
    {
        return;
    }
    /*Else do nothing, and continue.*/

    if (m_currentRow + 1 == 1)
    {
        m_currentRow = m_radioTable->rowCount() - 1;

    }
    else
    {
        --m_currentRow;
    }
    this->handlePlayRadio(m_currentRow);
}

void RadioPanel::handleNextRadio()
{
    if (m_radioTable->rowCount() == 0)
    {
        return;
    }
    /*Else do nothing, and continue.*/

    if (m_currentRow + 1 == m_radioTable->rowCount())
    {
        m_currentRow = 0;
    }
    else
    {
        ++m_currentRow;
    }
    this->handlePlayRadio(m_currentRow);
}

void RadioPanel::handleError(QMediaPlayer::Error error)
{
    QString errorStr = this->errorCodeToString(error);
#ifdef CZ_DEBUG
    qDebug() << errorStr;
#endif
}

void RadioPanel::createUI()
{
    //��ǰ��̨
    m_currentRadioLabel = new QLabel(this);
    m_currentRadioLabel->setObjectName(tr("searchInfoLabel"));
    m_currentRadioLabel->setText(TR("��ǰ���ŵ�̨��"));

    //����/��ͣ��ť
    m_playButton = new QPushButton(this);
    m_playButton->setFixedSize(32, 32);
    m_playButton->setToolTip(TR("����"));
    m_playButton->setStyleSheet(QString("QPushButton:!hover{border-image: url(%1audioPlay.png);}"
        "QPushButton:hover{border-image: url(%1audioPlay2.png);}"
        "QPushButton:pressed{border-image: url(%1audioPlay.png);}").arg(ImagesDir));

    //��һ��
    m_preButton = new QPushButton(this);
    m_preButton->setFixedSize(32, 32);
    m_preButton->setToolTip(TR("��һ��"));
    m_preButton->setStyleSheet(QString("QPushButton:!hover{border-image: url(%1audioRew.png);}"
        "QPushButton:hover{border-image: url(%1audioRew2.png);}"
        "QPushButton:pressed{border-image: url(%1audioRew.png);}").arg(ImagesDir));

    //��һ��
    m_nextButton = new QPushButton(this);
    m_nextButton->setFixedSize(32, 32);
    m_nextButton->setToolTip(TR("��һ��"));
    m_nextButton->setStyleSheet(QString("QPushButton:!hover{border-image: url(%1audioFwd.png);}"
        "QPushButton:hover{border-image: url(%1audioFwd2.png);}"
        "QPushButton:pressed{border-image: url(%1audioFwd.png);}").arg(ImagesDir));

    QHBoxLayout *buttonhLayout = new QHBoxLayout;
    buttonhLayout->addWidget(m_preButton);
    buttonhLayout->addWidget(m_playButton);
    buttonhLayout->addWidget(m_nextButton);

    //��̨�б�
    m_radioTable = new QTableWidget(this);
    this->setTableWidgetStyle();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_currentRadioLabel);
    mainLayout->addLayout(buttonhLayout);
    mainLayout->addWidget(m_radioTable);
    this->setLayout(mainLayout);

    QList<RadioInfoEntity> radioInfos = this->readXML("./RadioInfo.xml");
    foreach (RadioInfoEntity entity, radioInfos)
    {
        this->addRadioInfo(entity);
    }

    m_radioPlayer = new QMediaPlayer;
}

void RadioPanel::createConnect()
{
    connect(m_playButton, SIGNAL(clicked()), this, SLOT(handlePlayRadio()));
    connect(m_preButton, SIGNAL(clicked()), this, SLOT(handlePreRadio()));
    connect(m_nextButton, SIGNAL(clicked()), this, SLOT(handleNextRadio()));
    connect(m_radioTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(handlePlayRadio(int)));
    connect(m_radioPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handleError(QMediaPlayer::Error)));
}

void RadioPanel::addRadioInfo(const RadioInfoEntity &entity)
{
    //��̨����
    QTableWidgetItem *radioNameItem = new QTableWidgetItem;
    radioNameItem->setTextAlignment(Qt::AlignCenter);
    radioNameItem->setText(entity.name());
    radioNameItem->setToolTip(entity.name());

    int currentRows = m_radioTable->rowCount();
    m_radioTable->insertRow(currentRows);
    m_radioTable->setItem(currentRows, 0, radioNameItem);
    m_radioInfoMap[currentRows] = entity;
}

void RadioPanel::setTableWidgetStyle()
{
    m_radioTable->setRowCount(0);
    m_radioTable->setColumnCount(1);

    QStringList headList;
    headList << TR("��̨����");
    m_radioTable->setHorizontalHeaderLabels(headList);

    m_radioTable->setSelectionMode(QAbstractItemView::SingleSelection);              //����ֻ��ѡ�е���
    m_radioTable->setSelectionBehavior(QAbstractItemView::SelectRows);               //����ѡ��ϰ��Ϊѡ����
    m_radioTable->setEditTriggers(QAbstractItemView::NoEditTriggers);                //�������ݲ��ɱ༭
    m_radioTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //���������Զ�����������������
    m_radioTable->setFrameStyle(QFrame::NoFrame);                                    //ȥ���߿�
    m_radioTable->setShowGrid(false);                                                //���ò���ʾ����
    m_radioTable->setItemDelegate(new NoFocusDelegate());                            //ȥ��ѡ�е�Ԫ�������
    m_radioTable->horizontalHeader()->setHighlightSections(false);                   //�����ʱ���Ա�ͷ�й�������ȡ���㣩
    m_radioTable->verticalHeader()->setVisible(false);                               //���ô�ֱͷ���ɼ�
    m_radioTable->horizontalHeader()->setSectionsClickable(false);                   //����Ӧ��굥��
}

QList<RadioInfoEntity> RadioPanel::readXML(const QString &filePath)
{
    //�ж��ļ��Ƿ����
    QFile file;
    bool isExist = file.exists(filePath);
    if (!isExist)
    {
#ifdef XML_DEBUG
        qDebug() << filePath << "Not exits.";
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
#endif
        return QList<RadioInfoEntity>();
    }
    /*Else do nothing, and continue.*/

    QString errorStr;
    int errorLine;
    int errorColumn;

    file.setFileName(filePath);
    file.open(QFile::ReadOnly);
    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
        file.close();
#ifdef XML_DEBUG
        qDebug() << "Read xml file error, line = " << QString::number(errorLine)
                 << ", column = " << QString::number(errorColumn)
                 << ", error string = " << errorStr;
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
#endif
        return QList<RadioInfoEntity>();
    }
    /*Else do nothing , and continue*/

    //��ȡ��Ԫ��
    QDomElement root = doc.documentElement();
    if (root.tagName() != "RadioInfo")
    {
        file.close();
        return QList<RadioInfoEntity>();
    }
    /*Else do nothing , and continue*/

    QList<RadioInfoEntity> radioInfos;
    //���root�����ӽڵ���б�
    QDomNodeList nodeList = root.childNodes();
    for (int i = 0; i < nodeList.count(); ++i)
    {
        QDomNode node = nodeList.at(i);
        if (node.isNull())
        {
            file.close();
            return QList<RadioInfoEntity>();
        }
        /*Else do nothing , and continue*/

        if (node.nodeType() != QDomNode::ElementNode)
        {
            continue;
        }
        /*Else do nothing , and continue*/

        //ת����Ԫ��
        QDomElement element = node.toElement();
        if (element.tagName() == "Radio")
        {
            RadioInfoEntity radioInfo(element.attribute("name"), element.text());
            radioInfos.append(radioInfo);
#ifdef XML_DEBUG
            qDebug() << element.attribute("name") << element.text();
#endif
        }
        /*Else do nothing, and continue.*/
    }

    file.close();
    return radioInfos;
}

QString RadioPanel::errorCodeToString(QMediaPlayer::Error error)
{
    QString codeStr;
    switch (error)
    {
    case QMediaPlayer::NoError:
        codeStr = "QMediaPlayer::NoError";
        break;
    case QMediaPlayer::ResourceError:
        codeStr = "QMediaPlayer::ResourceError";
        break;
    case QMediaPlayer::FormatError:
        codeStr = "QMediaPlayer::FormatError";
        break;
    case QMediaPlayer::NetworkError:
        codeStr = "QMediaPlayer::NetworkError";
        break;
    case QMediaPlayer::AccessDeniedError:
        codeStr = "QMediaPlayer::AccessDeniedError";
        break;
    case QMediaPlayer::ServiceMissingError:
        codeStr = "QMediaPlayer::ServiceMissingError";
        break;
    default:
        codeStr = "Unknown error.";
        break;
    }
    return codeStr;
}



