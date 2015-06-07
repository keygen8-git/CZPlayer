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
 * \file   AlbumThread.h
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-24
 * \brief  ר�������߳�ͷ�ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2014-12-24    by chengxuan
 *
 * \endverbatim
 *
 */

#ifndef ALBUMTHREAD_H
#define ALBUMTHREAD_H

/*! \def ALBUMTHREAD_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define ALBUMTHREAD_VERSION   0x030000

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
class QLabel;

/*! ר�������߳�
*/
class AlbumThread : public QThread
{
	Q_OBJECT

public:
	/*! ���캯��
	 *  \param fileName �����ļ���
	 *  \param musicName ��������
	 *  \param musicArtist ����������
	 *  \param albumFilePath ר���ļ�·��
     *  \param parent QObject���ͣ�Ĭ��ΪNULL
     */
	AlbumThread(const QString &fileName, 
				const QString &musicName, 
				const QString &musicArtist, 
				const QString &albumFilePath,
				QObject *parent = NULL);

	/*! ��������.*/
	~AlbumThread();

protected:
	/*! �麯�����̳���QThread
     */
	virtual void run();

signals:
	/*! ����ר��״̬
     *  \param fileName �����ļ���
	 *  \param albumUrl ר��Url
	 *  \param albumFilePath ר���ļ�·��
	 *  \param status ����״̬
     */
	void sigAlbumDownloadStatus(const QString &fileName, 
								const QString &albumUrl, 
								const QString &albumFilePath, 
								AlbumDownloadStatus status);

private slots:
	/*! �õ�ר��Json��ʽ����
     *  \param replay �����Ӧ����
     */
	void handleGetMusicAlbumJson(QNetworkReply *replay);

	/*! �õ�ר��Json��ʽ����
     *  \param replay �����Ӧ����
     */
	void handleGetMusicAlbumJson2(QNetworkReply *replay);

	/*! ����ר��
     */
	void handleSaveAlbum();

	/*! ר��ר���������
     */
	void handleReplayFinished();

	/*! �������
     */
	void handleReplyError(QNetworkReply::NetworkError networkError);

private:
	/*! ����ר��Url
     *  \param url ר��Url
     */
	void setAlbumFromURL(const QUrl &url);

	/*! ����������ת�����ַ���
     *  \param networkError ����������
     */
	QString errorCodeToString(QNetworkReply::NetworkError networkError);

private:
	QFile m_albumFile;							/*!< ר���ļ�����*/
	QString m_fileName;							/*!< �����ļ���*/
	QString m_musicName;						/*!< ��������*/
	QString m_musicArtist;						/*!< ����������*/
	QString m_albumFilePath;					/*!< �����ר���ļ�·��*/
	QString m_albumUrl;							/*!< ����ר��URL*/

	QNetworkAccessManager *m_albumManager;		/*!< ����������*/
	QNetworkAccessManager *m_albumManager2;		/*!< ����������*/
	QNetworkAccessManager *m_albumManager3;		/*!< ����������*/
	QNetworkReply *m_albumReply;				/*!< �����Ӧ����*/
};

#endif // ALBUMTHREAD_H
