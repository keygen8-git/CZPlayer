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
 * \file   SearchThread.h
 * \author chengxuan   787280310@qq.com
 * \date   2015-03-03
 * \brief  ���������߳�ͷ�ļ���
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

#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

/*! \def SEARCHTHREAD_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define SEARCHTHREAD_VERSION   0x030000

#include <QThread>
#include <QString>
#include "StatusDefine.h"

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if STATUSDEFINE_VERSION < 0x030000
#error  "StatusDefine version error."
#endif

class QNetworkAccessManager;
class QNetworkReply;

/*! ���������߳�
*/
class SearchThread : public QThread
{
    Q_OBJECT

public:
    /*! ���캯��
     *  \param parent QObject���ͣ�Ĭ��ΪNULL
     */
    SearchThread(QObject *parent = NULL);

    /*! ��������.*/
    ~SearchThread();

protected:
    /*! �麯�����̳���QThread
     */
    virtual void run();
};

/*! ���������߳��¼�������
*/
class SearchThreadEvent : public QObject
{
    Q_OBJECT

public:
    /*! ���캯��
     *  \param parent QObject���ͣ�Ĭ��ΪNULL
     */
    SearchThreadEvent(QObject *parent = NULL);

    /*! ��������.*/
    ~SearchThreadEvent();

signals:
    /*! ����������Ϣ
    *  \param musicName ������
    *  \param artist ������
    *  \param album ר��
    */
    void sigAddMusicInfo(const QString &musicName, const QString &artist, const QString &album);

    /*! ��������״̬
    *  \param status ״̬
    */
    void sigMusicSearchStatus(MusicSearchStatus status);

private slots:
    /*! ��������
    *  \param text �ؼ����ı�
    */
    void handleSearchMusic(const QString &text);

    /*! �������
     *  \param replay �����Ӧ����
     */
    void handleSearchFinished(QNetworkReply *replay);

private:
    QNetworkAccessManager *m_searchManager; /*!< ����������*/
};

#endif // SEARCHTHREAD_H
