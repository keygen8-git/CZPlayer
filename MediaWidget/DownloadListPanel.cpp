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
 * \file   DownloadListPanel.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2015-02-23
 * \brief  �����б����ʵ���ļ���
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

#include "DownloadListPanel.h"
#include "DownloadMusicThread.h"
#include "GlobalConfig.h"
#include "NoFocusDelegate.h"
#include "TR.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QProgressBar>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QMediaPlayer>

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if GLOBALCONFIG_VERSION < 0x030000
#error  "GlobalConfig version error."
#endif

#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

DownloadListPanel::DownloadListPanel(QWidget *parent)
    : QWidget(parent)
{
    this->createUI();
    this->createConnect();
}

DownloadListPanel::~DownloadListPanel()
{
    while (!m_musicInfos.isEmpty())
    {
        DownloadInfo *musicInfo = m_musicInfos.takeFirst();
        if (musicInfo->thread()->isRunning())
        {
            musicInfo->thread()->quit();
            musicInfo->thread()->wait();
        }
        /*Else do nothing, and continue.*/
        musicInfo->thread()->deleteLater();
        musicInfo->setThread(NULL);
        musicInfo->deleteLater();
        musicInfo = NULL;
    }
}

void DownloadListPanel::setMusicPath(const QString &musicPath)
{
    this->handleMusicDirChanged(musicPath);
}

void DownloadListPanel::handleMusicDirChanged(const QString &path)
{
    m_musicPath = path;
    QDir dir;
    dir.mkpath(m_musicPath);
}

void DownloadListPanel::handleDownloadMusic(const QString &musicName, const QString &artist)
{
    DownloadInfo *downloadInfo = new DownloadInfo(m_downloadTable);
    downloadInfo->setTitle(QString("%1 - %2").arg(musicName).arg(artist));

    DownloadMusicThread *thread = new DownloadMusicThread(musicName, artist, m_musicPath);
    qRegisterMetaType<MusicDownloadStatus>("MusicDownloadStatus");
    connect(thread, SIGNAL(sigMusicDownloadStatus(MusicDownloadStatus)), this, SLOT(handleMusicDownloadStatus(MusicDownloadStatus)), Qt::QueuedConnection);
    connect(thread, SIGNAL(sigUpdateDataProgress(qint64,qint64)), this, SLOT(handleUpdateDataProgress(qint64,qint64)), Qt::QueuedConnection);
    connect(thread, SIGNAL(sigMusicSize(double)), this, SLOT(handleMusicSize(double)), Qt::QueuedConnection);
    downloadInfo->setThread(thread);
    downloadInfo->setStatus(TR("��������"));
    m_musicInfos.append(downloadInfo);
    thread->start();
}

void DownloadListPanel::handleMusicDownloadStatus(MusicDownloadStatus status)
{
    QThread *thread = dynamic_cast<QThread *>(sender());
    DownloadInfo *info = NULL;

    foreach (DownloadInfo *downloadInfo, m_musicInfos)
    {
        if (downloadInfo->thread() == thread)
        {
            info = downloadInfo;
            m_musicInfos.removeOne(downloadInfo);
            break;
        }
        /*Else do nothing, and continue.*/
    }

    thread->quit();
    thread->wait();
    thread->deleteLater();
    thread = NULL;

    if (info != NULL)
    {
        if (status == MusicDownloadSuccess)
        {
            info->setStatus(TR("�������"));
            info->setSpeed("0KB/S");
            this->playAudio();
        }
        else if (status == MusicDownloadFailed)
        {
            info->setStatus(TR("����ʧ��"));
            info->setSpeed("0KB/S");
        }
        /*Else do nothing, and continue.*/

        info->deleteLater();
        info = NULL;
    }
    /*Else do nothing, and continue.*/
}

void DownloadListPanel::handleUpdateDataProgress(const qint64 &bytesRead, const qint64 &totalBytes)
{
    QThread *thread = dynamic_cast<QThread *>(sender());

    foreach (DownloadInfo *downloadInfo, m_musicInfos)
    {
        if (downloadInfo->thread() == thread)
        {
            //���½�����
            downloadInfo->setProgressMaximum(totalBytes);
            downloadInfo->setProgress(bytesRead);

            //��������
            int currentTime = downloadInfo->elapsed();
            int speed = bytesRead / currentTime * 1000 / 1024;
            QString speedStr = QString::number(speed, 'f', 1) + "KB/S";
            downloadInfo->setSpeed(speedStr);
            break;
        }
        /*Else do nothing, and continue.*/
    }
}

void DownloadListPanel::handleMusicSize(const double &size)
{
    double result = size / 1048576;
    QString musicSizeStr = QString::number(result, 'f', 2) + "MB";

    QThread *thread = dynamic_cast<QThread *>(sender());

    foreach (DownloadInfo *downloadInfo, m_musicInfos)
    {
        if (downloadInfo->thread() == thread)
        {
            downloadInfo->setSize(musicSizeStr);
            break;
        }
        /*Else do nothing, and continue.*/
    }
}

void DownloadListPanel::createUI()
{
    //�����б�
    m_downloadTable = new QTableWidget(this);
    this->setTableWidgetStyle();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_downloadTable);
    this->setLayout(mainLayout);
}

void DownloadListPanel::createConnect()
{
    GlobalConfig *config = GlobalConfig::instance();
    connect(config, SIGNAL(sigMusicPathChanged(QString)), this, SLOT(handleMusicDirChanged(QString)));
}

void DownloadListPanel::playAudio()
{
    QString filePath = "./download-complete.wav";
    if (QFile::exists(filePath))
    {
        QMediaPlayer *mediaPlayer = new QMediaPlayer;
        mediaPlayer->setMedia(QUrl::fromLocalFile(filePath));
        mediaPlayer->setVolume(100);
        mediaPlayer->play();
    }
    /*Else do nothing, and continue.*/
}

void DownloadListPanel::setTableWidgetStyle()
{
    m_downloadTable->setRowCount(0);
    m_downloadTable->setColumnCount(5);

    QStringList headList;
    headList << TR("��������") << TR("״̬") << TR("��С") << TR("�ٶ�") << TR("����");
    m_downloadTable->setHorizontalHeaderLabels(headList);

    m_downloadTable->setSelectionMode(QAbstractItemView::SingleSelection);              //����ֻ��ѡ�е���
    m_downloadTable->setSelectionBehavior(QAbstractItemView::SelectRows);               //����ѡ��ϰ��Ϊѡ����
    m_downloadTable->setEditTriggers(QAbstractItemView::NoEditTriggers);                //�������ݲ��ɱ༭
    m_downloadTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //���������Զ�����������������
    m_downloadTable->setFrameStyle(QFrame::NoFrame);                                    //ȥ���߿�
    m_downloadTable->setShowGrid(false);                                                //���ò���ʾ����
    m_downloadTable->setItemDelegate(new NoFocusDelegate());                            //ȥ��ѡ�е�Ԫ�������
    m_downloadTable->horizontalHeader()->setHighlightSections(false);                   //�����ʱ���Ա�ͷ�й�������ȡ���㣩
    m_downloadTable->verticalHeader()->setVisible(false);                               //���ô�ֱͷ���ɼ�
    m_downloadTable->horizontalHeader()->setSectionsClickable(false);                   //����Ӧ��굥��
}

DownloadInfo::DownloadInfo(QTableWidget *downloadTable, QObject *parent)
    : QObject(parent)
{
    //������
    m_progressBar = new QProgressBar;
    m_progressBar->setObjectName(tr("progressBar"));

    //��������
    m_musicTitleItem = new QTableWidgetItem;
    m_musicTitleItem->setTextAlignment(Qt::AlignCenter);

    //����״̬
    m_musicStatusItem = new QTableWidgetItem;
    m_musicStatusItem->setTextAlignment(Qt::AlignCenter);
    m_musicStatusItem->setText(TR("�ȴ�����"));

    //��С
    m_musicSizeItem = new QTableWidgetItem;
    m_musicSizeItem->setTextAlignment(Qt::AlignCenter);
    m_musicSizeItem->setText("--");

    //����
    m_speedItem = new QTableWidgetItem;
    m_speedItem->setTextAlignment(Qt::AlignCenter);
    m_speedItem->setText("0KB/S");

    int currentRows = downloadTable->rowCount();
    downloadTable->insertRow(currentRows);
    downloadTable->setItem(currentRows, 0, m_musicTitleItem);
    downloadTable->setItem(currentRows, 1, m_musicStatusItem);
    downloadTable->setItem(currentRows, 2, m_musicSizeItem);
    downloadTable->setItem(currentRows, 3, m_speedItem);
    downloadTable->setCellWidget(currentRows, 4, m_progressBar);

    m_time = new QTime;
    m_time->start();
}

DownloadInfo::~DownloadInfo()
{
    /*Do nothing.*/
}

QString DownloadInfo::title() const
{
    return m_musicTitleItem->text();
}

void DownloadInfo::setTitle(const QString &text)
{
    m_musicTitleItem->setText(text);
    m_musicTitleItem->setToolTip(text);
}

QString DownloadInfo::status() const
{
    return m_musicStatusItem->text();
}

void DownloadInfo::setStatus(const QString &text)
{
    m_musicStatusItem->setText(text);
}

QString DownloadInfo::size() const
{
    return m_musicSizeItem->text();
}

void DownloadInfo::setSize(const QString &text)
{
    m_musicSizeItem->setText(text);
}

QString DownloadInfo::speed() const
{
    return m_speedItem->text();
}

void DownloadInfo::setSpeed(const QString &text)
{
    m_speedItem->setText(text);
}

qint64 DownloadInfo::progress() const
{
    return m_progressBar->value();
}

void DownloadInfo::setProgress(const qint64 &value)
{
    m_progressBar->setValue(value);
}

void DownloadInfo::setProgressMaximum(const qint64 &value)
{
    m_progressBar->setMaximum(value);
}

QThread *DownloadInfo::thread() const
{
    return m_thread;
}

void DownloadInfo::setThread(QThread *thread)
{
    m_thread = thread;
}

int DownloadInfo::elapsed() const
{
    return m_time->elapsed();
}
