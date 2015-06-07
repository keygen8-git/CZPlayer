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
 * \file   MusicLrc.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-21
 * \brief  ��ʽ���ʵ���ļ���
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

#include "MusicLrc.h"
#include "TR.h"
#include "GlobalConfig.h"
#include "Global.h"
#include <QApplication>
#include <QMenu>
#include <QIcon>
#include <QDesktopWidget>
#include <QMessagebox>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QTimer>
#ifdef CZ_DEBUG
#include <QDebug>
#endif

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if GLOBALCONFIG_VERSION < 0x030000
#error  "GlobalConfig version error."
#endif

#if GLOBAL_VERSION < 0x030000
#error  "Global version error."
#endif

#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

MusicLrc::MusicLrc( QWidget *parent /*= NULL*/ )
	: QLabel(parent),
	m_isLrcLock(false),
	m_lrcMaskWidth(0.0),
	m_lrcMaskWidthInterval(0.0),
	m_shadow(255)
{
	this->createUI();
	this->createConnect();
}

MusicLrc::~MusicLrc()
{
	if (m_timer->isActive()) 
	{
		m_timer->stop();
	}
	/*Else do nothing, and continue.*/
}

void MusicLrc::createUI()
{
	//ȥ������߿��������ʾ����Ļ��ǰ��,��Ҫ��showNormalһ����
	this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint
		| Qt::FramelessWindowHint);			//ȥ������߿�,������������ʾͼ��
	this->setAttribute(Qt::WA_TranslucentBackground);			//���ñ���͸��
	this->setWindowIcon(QIcon(ImagesDir + "CZPlayer.png"));		//����logo
	this->resize(1000, 60);

	//���ø��λ��
	double width = QApplication::desktop()->width();
	double height = QApplication::desktop()->height();
	this->move(QPoint(width / 2 - 800 / 2, height - 90));

	//��ʵ����Խ������
	m_linearGradient.setStart(0, 10);//�����������
	m_linearGradient.setFinalStop(0, 40);//�����յ�����

	//���ֵ����Խ������
	m_maskLinearGradient.setStart(0, 10);
	m_maskLinearGradient.setFinalStop(0, 40);

	//���ö�ʱ��
	m_timer = new QTimer;
}

void MusicLrc::createConnect()
{
	connect(m_timer, SIGNAL(timeout()), this, SLOT(handleTimeOut()));

	GlobalConfig *config = GlobalConfig::instance();
	connect(config, SIGNAL(sigFontNameChanged(QString)), this, SLOT(handleFontNameChanged(QString)));
	connect(config, SIGNAL(sigFontSizeChanged(QString)), this, SLOT(handleFontSizeChanged(QString)));
	connect(config, SIGNAL(sigFontTypeChanged(QString)), this, SLOT(handleFontTypeChanged(QString)));
	connect(config, SIGNAL(sigNoPlayShangChanged(QColor)), this, SLOT(handleNoPlayShangChanged(QColor)));
	connect(config, SIGNAL(sigNoPlayZhongChanged(QColor)), this, SLOT(handleNoPlayZhongChanged(QColor)));
	connect(config, SIGNAL(sigNoPlayXiaChanged(QColor)), this, SLOT(handleNoPlayXiaChanged(QColor)));
	connect(config, SIGNAL(sigPlayedShangChanged(QColor)), this, SLOT(handlePlayedShangChanged(QColor)));
	connect(config, SIGNAL(sigPlayedZhongChanged(QColor)), this, SLOT(handlePlayedZhongChanged(QColor)));
	connect(config, SIGNAL(sigPlayedXiaChanged(QColor)), this, SLOT(handlePlayedXiaChanged(QColor)));
	connect(config, SIGNAL(sigShadowChanged(int)), this, SLOT(handleShadowChanged(int)));
}

void MusicLrc::startLrcMask(qint64 intervalTime)
{
    //��������ÿ��30�������һ�����ֵĿ�ȣ���Ϊ�������̫ƽ��
    //������cpuռ���ʣ������ʱ����̫���򶯻�Ч���Ͳ�������
    qreal count = intervalTime / 30;

    //��ȡ����ÿ����Ҫ���ӵĿ�ȣ������800�ǲ����Ĺ̶����
    m_lrcMaskWidthInterval = 1000 / count;
    m_lrcMaskWidth = 0;
    m_timer->start(30);
}

void MusicLrc::stopLrcMask()
{
    m_timer->stop();
    m_lrcMaskWidth = 0;
    this->update();
}

void MusicLrc::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
	painter.setFont(m_font);

    //�Ȼ��Ƶײ����֣���Ϊ��Ӱ��������ʹ��ʾЧ�������������Ҹ����ʸ�
	painter.setPen(QColor(0, 0, 0, m_shadow));
	painter.drawText(1, 1, 1000, 60, Qt::AlignLeft, text());

    //����������ƽ�������
	painter.setPen(QPen(m_linearGradient, 0));
	painter.drawText(0, 0, 1000, 60, Qt::AlignLeft, text());

    //���ø������
	painter.setPen(QPen(m_maskLinearGradient, 0));
	painter.drawText(0, 0, m_lrcMaskWidth, 60, Qt::AlignLeft, text());
    event->accept();
}

void MusicLrc::mousePressEvent(QMouseEvent *event)
{
    if (!m_isLrcLock)//û�п����������
    {
        if (event->button() == Qt::LeftButton)
        {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
		/*Else do nothing, and continue.*/
    }
	/*Else do nothing, and continue.*/
}

void MusicLrc::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_isLrcLock)//û�п����������
    {
        if (event->buttons() == Qt::LeftButton)
        {
            setCursor(Qt::PointingHandCursor);//��ʾ����
            move(event->globalPos() - m_dragPosition);//�ƶ�����
            event->accept();
        }
		/*Else do nothing, and continue.*/
    }
	/*Else do nothing, and continue.*/
}

void MusicLrc::contextMenuEvent(QContextMenuEvent *event)
{
    if (!m_isLrcLock)//û�п����������
    {
        QMenu menu;
        menu.addAction(QIcon(ImagesDir + "lrc.png"), TR("���ظ��"), this, SIGNAL(sigHideLrc()));
        menu.addAction(QIcon(ImagesDir + "lock.png"), TR("�������"), this, SLOT(handleLockLrc()));
        menu.exec(event->globalPos());
    }
	/*Else do nothing, and continue.*/
    event->accept();
}

void MusicLrc::handleLockLrc()
{
    m_isLrcLock = true;
    emit sigLrcLocked();
}

void MusicLrc::unlockLrc()
{
    m_isLrcLock = false;
    emit sigLrcUnlocked();
}

void MusicLrc::handleTimeOut()
{
    //ÿ��һ�ι̶���ʱ�����ֵĳ��Ⱦ�����һ��
    m_lrcMaskWidth += m_lrcMaskWidthInterval;
	//���¸����ʾ�����ǲ��������ػ棬���ǰ���һ��Paint�¼�����������ѭ��ʱ��ϵͳ���ػ�
    this->update();
}

void MusicLrc::handleFontNameChanged(const QString &fontName)
{
	m_font.setFamily(fontName);
	this->update();
}

void MusicLrc::handleFontSizeChanged(const QString &fontSize)
{
	bool ok;
	int size = fontSize.toInt(&ok);
	if (ok)
	{
		m_font.setPointSize(size);
	}
	else
	{
		m_font.setPointSize(30);
	}
	this->update();
}

void MusicLrc::handleFontTypeChanged(const QString &fontType)
{
	if (fontType == TR("����"))
	{
		m_font.setBold(false);
		m_font.setItalic(false);
	}
	else if (fontType == TR("����"))
	{
		m_font.setBold(true);
		m_font.setItalic(false);
	}
	else if (fontType == TR("��б"))
	{
		m_font.setBold(false);
		m_font.setItalic(true);
	}
	else if (fontType == TR("���� ��б"))
	{
		m_font.setBold(true);
		m_font.setItalic(true);
	}
	/*Else do nothing, and conintue.*/
	this->update();
}

void MusicLrc::handleNoPlayShangChanged(const QColor &color)
{
	m_linearGradient.setColorAt(0.1, color);
	this->update();
}

void MusicLrc::handleNoPlayZhongChanged(const QColor &color)
{
	m_linearGradient.setColorAt(0.5, color);
	this->update();
}

void MusicLrc::handleNoPlayXiaChanged(const QColor &color)
{
	m_linearGradient.setColorAt(0.9, color);
	this->update();
}

void MusicLrc::handlePlayedShangChanged(const QColor &color)
{
	m_maskLinearGradient.setColorAt(0.1, color);
	this->update();
}

void MusicLrc::handlePlayedZhongChanged(const QColor &color)
{
	m_maskLinearGradient.setColorAt(0.5, color);
	this->update();
}

void MusicLrc::handlePlayedXiaChanged(const QColor &color)
{
	m_maskLinearGradient.setColorAt(0.9, color);
	this->update();
}

void MusicLrc::handleShadowChanged(const int &shadow)
{
	m_shadow = shadow;
	this->update();
}














