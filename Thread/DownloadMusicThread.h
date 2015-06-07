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
 * \file   DownloadMusicThread.h
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

#ifndef DOWNLOADMUSICTHREAD_H
#define DOWNLOADMUSICTHREAD_H

/*! \def DOWNLOADMUSICTHREAD_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define DOWNLOADMUSICTHREAD_VERSION   0x030000

#include <QThread>
#include <QFile>
#include <QString>
#include <QNetworkReply>
#include "StatusDefine.h"

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if STATUSDEFINE_VERSION < 0x030000
#error  "StatusDefine version error."
#endif

class QNetworkAccessManager;

/*! ���������߳�
*/
class DownloadMusicThread : public QThread
{
    Q_OBJECT

public:
    /*! ���캯��
     *  \param musicName ��������
     *  \param musicArtist ����������
     *  \param musicPath ������ֵ�·��
     *  \param parent QObject���ͣ�Ĭ��ΪNULL
     */
    DownloadMusicThread(const QString &musicName, const QString artist, const QString &musicPath, QObject *parent = NULL);

    /*! ��������.*/
    ~DownloadMusicThread();

protected:
    /*! �麯�����̳���QThread
     */
    virtual void run();

signals:
    /*! ���ظ���״̬
     *  \param status ����״̬
     */
    void sigMusicDownloadStatus(MusicDownloadStatus status);

    /*! ���½�����
     *  \param bytesRead �Ѿ����صĴ�С
     *  \param totalBytes �ܴ�С
     */
    void sigUpdateDataProgress(const qint64 &bytesRead, const qint64 &totalBytes);

    /*! �����ļ���С
     *  \param size �����ļ���С����λ���ֽ�
     */
    void sigMusicSize(const double &size);

private slots:
    /*! �õ�����XML��ʽ
    *  \param replay �����Ӧ����
    */
    void handleGetMusicXML(QNetworkReply *replay);

    /*! �������
     */
    void handleSaveMusic();

    /*! �������
    */
    void handleReplayFinished();

    /*! �������
     */
    void handleReplyError(QNetworkReply::NetworkError networkError);

private:
    /*! ��������url
    *  \param url ����url
    */
    void setMusicURL(const QUrl &url);

    /*! ����������ת�����ַ���
     *  \param networkError ����������
     */
    QString errorCodeToString(QNetworkReply::NetworkError networkError);

private:
    QString m_musicName;                        /*!< ������*/
    QString m_artist;                           /*!< ������*/
    QString m_filePath;                         /*!< �ļ�·��*/
    QFile m_musicFile;							/*!< �����ļ�����*/

    QNetworkAccessManager *m_musicManager;		/*!< ����������*/
    QNetworkAccessManager *m_musicManager2;		/*!< ����������*/
    QNetworkReply *m_musicReply;				/*!< �����Ӧ����*/

    int m_times;                                /*!< ���ؼ���*/
};

#endif // DOWNLOADMUSICTHREAD_H
