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
 * \file   SearchThread.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2015-03-03
 * \brief  ���������߳�ʵ���ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2015-03-03    by chengxuan
 *
 * \endverbatim
 *
 */

#include "SearchThread.h"
#include "TR.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#ifdef CZ_DEBUG
#include <QDebug>
#endif

SearchThread::SearchThread(QObject *parent)
    : QThread(parent)
{
    /*Do nothing.*/
}

SearchThread::~SearchThread()
{
    /*Do nothing.*/
}

void SearchThread::run()
{
    this->exec();
}


SearchThreadEvent::SearchThreadEvent(QObject *parent)
    : QObject(parent),
      m_searchManager(NULL)
{
    /*Do nothing.*/
}

SearchThreadEvent::~SearchThreadEvent()
{
    if (m_searchManager != NULL)
    {
        m_searchManager->deleteLater();
        m_searchManager = NULL;
    }
    /*Else do nothing, and continue.*/
}

void SearchThreadEvent::handleSearchMusic(const QString &text)
{
    QString url = QString("http://songs.sinaapp.com/search/key/%1/page/1").arg(text);

    m_searchManager = new QNetworkAccessManager;
    m_searchManager->get(QNetworkRequest(QUrl(url)));
    connect(m_searchManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleSearchFinished(QNetworkReply*)));
}

void SearchThreadEvent::handleSearchFinished(QNetworkReply *replay)
{
    QString resultStr = replay->readAll();

    if (replay != NULL)
    {
        replay->deleteLater();
        replay = NULL;
    }
    /*Else do nothing, and continue.*/
    if (m_searchManager != NULL)
    {
        m_searchManager->deleteLater();
        m_searchManager = NULL;
    }
    /*Else do nothing, and continue.*/

    //û�����ӵ�����
    if (resultStr.isEmpty())
    {
#ifdef CZ_DEBUG
        qDebug() << "Search music error.";
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
#endif
        emit sigMusicSearchStatus(MusicSearchFailed);
        return;
    }
    /*Else do nothing, and continue.*/

    //����Json
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(resultStr.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError)
    {
#ifdef CZ_DEBUG
        qDebug() << "Search music error.";
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
#endif
        emit sigMusicSearchStatus(MusicSearchFailed);
        return;
    }
    /*Else do nothing, and continue.*/

    if (!jsonDocument.isObject())
    {
#ifdef CZ_DEBUG
        qDebug() << "Search music error.";
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
#endif
        emit sigMusicSearchStatus(MusicSearchFailed);
        return;
    }
    /*Else do nothing, and continue.*/

    QVariantMap result = jsonDocument.toVariant().toMap();
    //�ж�json�����Ƿ����url
    if (result["total"].toString() == "0")
    {
#ifdef CZ_DEBUG
        qDebug() << "Not found music";
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
#endif
        emit sigMusicSearchStatus(MusicSearchFailed);
        return;
    }
    /*Else do nothing, and continue.*/

    //�õ�ר��aid
    QVariantList resultList = result["results"].toList();
    foreach(QVariant var, resultList)
    {
        QVariantMap resultMap = var.toMap();
        emit sigAddMusicInfo(resultMap["song_name"].toString(),
                resultMap["artist_name"].toString(),
                resultMap["song_album"].toString());
    }
    emit sigMusicSearchStatus(MusicSearchSuccess);
}
