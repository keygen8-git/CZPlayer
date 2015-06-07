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
 * \file   MinMusicWidget.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-21
 * \brief  �������ʵ���ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2014-12-21    by chengxuan
 *
 * \endverbatim
 *
 */

#include "MinMusicWidget.h"
#include "TR.h"
#include "Global.h"
#include <QPropertyAnimation>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QPushButton>
#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QContextMenuEvent>

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if GLOBAL_VERSION < 0x030000
#error  "Global version error."
#endif

#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

/*****************************************************************************
  ȫ�ֱ�������
 *****************************************************************************/
const int Radius = 112;							/*!< ר��ͼƬ�뾶*/

MinMusicWidget::MinMusicWidget( QWidget *mainWidget, QWidget *parent /*= NULL*/ )
	: QWidget(parent),
	  m_mainWidget(mainWidget)
{
	this->createUI();
	this->createConnect();
}

MinMusicWidget::~MinMusicWidget()
{
	/*Do nothing.*/
}

void MinMusicWidget::handleOpenMainWidget()
{
    if (m_mainWidget->isHidden())
    {
        QPropertyAnimation *mainWidgetAnimation = new QPropertyAnimation(m_mainWidget, "windowOpacity");
        mainWidgetAnimation->setDuration(500);
        mainWidgetAnimation->setStartValue(0);
        mainWidgetAnimation->setEndValue(1);
        mainWidgetAnimation->start();
        m_mainWidget->show();
        emit sigShowMusicPanel();

        QPropertyAnimation *minWidgetAnimation = new QPropertyAnimation(this, "windowOpacity");
        minWidgetAnimation->setDuration(500);
        minWidgetAnimation->setStartValue(1);
        minWidgetAnimation->setEndValue(0);
        minWidgetAnimation->start();
        connect(minWidgetAnimation, SIGNAL(finished()), this, SLOT(hide()));
    }
	/*Else do nothing, and continue.*/
}

void MinMusicWidget::contextMenuEvent(QContextMenuEvent *event)
{
    m_rightHandMenu->exec(event->globalPos());
    event->accept();
}


void MinMusicWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap backgroundImage;
    backgroundImage.load(ImagesDir + "minMainBg2.png");

    //��ͨ��pix�ķ������ͼƬ�Ĺ��˵�͸���Ĳ��ֵõ���ͼƬ����ΪloginPanel�Ĳ�����߿�
    this->setMask(backgroundImage.mask());
    painter.drawPixmap(0, 0, 200, 159, backgroundImage);
    event->accept();
}

void MinMusicWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
	/*Else do nothing, and continue.*/
}

void MinMusicWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        this->move(event->globalPos() - m_dragPosition);//�ƶ�����
        event->accept();
    }
	/*Else do nothing, and continue.*/
}

void MinMusicWidget::setWork( bool isWork )
{
	m_minPlayButton->setEnabled(isWork);
	m_minPauseButton->setEnabled(isWork);
	m_minStopButton->setEnabled(isWork);
	m_minNextButton->setEnabled(isWork);
	m_minLastButton->setEnabled(isWork);
}

void MinMusicWidget::setMinMusicLrcActionText( const QString &text )
{
	m_minMusicLrcAction->setText(text);
}

void MinMusicWidget::createUI()
{
	//���ô��ڻ�������
	this->resize(200, 159);//���ô����С
	this->setWindowFlags(Qt::FramelessWindowHint);//ȥ������߿�
	this->setAttribute(Qt::WA_TranslucentBackground);//���ñ���͸��
	this->setWindowIcon(QIcon(ImagesDir + "CZPlayer.png"));//����logo
	this->setAcceptDrops(true);//�����Ϸ��ļ�
	
	//ר��ͼƬ
	m_albumImage = new QLabel(this);
	this->changeAlbumImage(ImagesDir + "albumImage.png");

	//����
	m_minPlayButton = new QPushButton(this);
	m_minPlayButton->setObjectName("minPlayButton");
	m_minPlayButton->setToolTip(TR("����"));

	//��ͣ
	m_minPauseButton = new QPushButton(this);
	m_minPauseButton->setObjectName("minPauseButton");
	m_minPauseButton->setToolTip(TR("��ͣ"));

	//ֹͣ
	m_minStopButton = new QPushButton(this);
	m_minStopButton->setObjectName("minStopButton");
	m_minStopButton->setToolTip(TR("ֹͣ"));

	//��һ��
	m_minNextButton = new QPushButton(this);
	m_minNextButton->setObjectName("minNextButton");
	m_minNextButton->setToolTip(TR("��һ��"));

	//��һ��
	m_minLastButton = new QPushButton(this);
	m_minLastButton->setObjectName("minLastButton");
	m_minLastButton->setToolTip(TR("��һ��"));

	//���ļ�
	m_minOpenFileButton = new QPushButton(this);
	m_minOpenFileButton->setObjectName("minOpenFileButton");
	m_minOpenFileButton->setToolTip(TR("���ļ�"));

	//������
	m_minMusicLrcAction = new QAction(this);
    m_minMusicLrcAction->setIcon(QIcon(ImagesDir + "lrc.png"));
	m_minMusicLrcAction->setText(TR("��ʾ������"));

	//�Ҽ��˵�
	m_rightHandMenu = new QMenu(this);
	m_rightHandMenu->addAction(QIcon(ImagesDir + "minMainWidget.png"), TR("����������"), this, SLOT(handleOpenMainWidget()));
	m_rightHandMenu->addAction(m_minMusicLrcAction);

	//���ø��������λ�úʹ�С
	m_albumImage->setGeometry(44, 1, Radius, Radius);
	m_minPlayButton->setGeometry(2, 33, 37, 37);
	m_minPauseButton->setGeometry(10, 78, 40, 37);
	m_minStopButton->setGeometry(45, 109, 41, 37);
	m_minNextButton->setGeometry(91, 114, 40, 37);
	m_minLastButton->setGeometry(134, 94, 40, 39);
	m_minOpenFileButton->setGeometry(161, 55, 39, 39);
}

void MinMusicWidget::createConnect()
{
	connect(m_minPlayButton, SIGNAL(clicked()), m_mainWidget, SLOT(handleSetPlay()));			
	connect(m_minPauseButton, SIGNAL(clicked()), m_mainWidget, SLOT(handleSetPause()));			
	connect(m_minStopButton, SIGNAL(clicked()), m_mainWidget, SLOT(handleSetStop()));			
	connect(m_minNextButton, SIGNAL(clicked()), m_mainWidget, SLOT(handleSetNext()));			
	connect(m_minLastButton, SIGNAL(clicked()), m_mainWidget, SLOT(handleSetPre()));			
	connect(m_minOpenFileButton, SIGNAL(clicked()), m_mainWidget, SLOT(handleOpenFile()));			
	connect(m_minMusicLrcAction, SIGNAL(triggered()), m_mainWidget, SLOT(handleOpenMusicLrc()));	
}

void MinMusicWidget::changeAlbumImage( const QString &albumFilePath )
{
	QImage image(albumFilePath);
    if (image.isNull())
    {
        m_albumImage->setPixmap(QPixmap(ImagesDir + "albumImage.png"));
        return;
    }
    /*Else do nothing, and continue.*/

	int width = image.width();
	int height = image.height();
	int radius = width > height ? height : width;

	QImage tempImage(radius, radius, QImage::Format_ARGB32);
	tempImage.fill(Qt::transparent);

	QBrush brush(image);
	QPainter painter(&tempImage);
	painter.setPen(Qt::NoPen);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(brush);
	painter.drawEllipse(0, 0, radius, radius);

	QImage newImage = tempImage.scaled(Radius, Radius, 
		Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	m_albumImage->setPixmap(QPixmap::fromImage(newImage));
}
