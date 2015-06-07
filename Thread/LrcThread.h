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
 * \file   LrcThread.h
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-28
 * \brief  ��������߳�ͷ�ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2014-12-28    by chengxuan
 *
 * \endverbatim
 *
 */

#ifndef LRCTHREAD_H
#define LRCTHREAD_H

/*! \def LRCTHREAD_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define LRCTHREAD_VERSION   0x030000

#include <QThread>
#include <QFile>
#include <QUrl>
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
class QLabel;

/*! ��������߳�
*/
class LrcThread : public QThread
{
	Q_OBJECT

public:
	/*! ���캯��
	 *  \param musicName ��������
	 *  \param musicArtist ����������
	 *  \param lrcFilePath ���·��
     *  \param parent QObject���ͣ�Ĭ��ΪNULL
     */
	LrcThread(const QString &musicName, 
		const QString &musicArtist, 
		const QString &lrcFilePath, 
		QObject *parent = NULL);

	/*! ��������.*/
	~LrcThread();

protected:
    /*! �麯�����̳���QThread
     */
	virtual void run();

signals:
	/*! ���ظ��״̬
     *  \param musicName ������
	 *  \param musicArtist ����������
	 *  \param lrcFilePath ����ļ�·��
	 *  \param status ����״̬
     */
	void sigLrcDownloadStatus(const QString &musicName, 
							    const QString &musicArtist, 
								const QString &lrcFilePath, 
								LrcDownloadStatus status);

private slots:
	/*! �õ�MusicXML
	 *  \param replay �����Ӧ����
     */
	void handleGetMusicXML(QNetworkReply *replay);

	/*! ������
	 *  \param replay �����Ӧ����
     */
	void handleSaveLrc(QNetworkReply *replay);

private:
	/*! ���ø��Url
     *  \param url ���Url
     */
	void setLrcFromURL(const QUrl &url);

private:
	QFile m_lrcFile;							/*!< ����ļ�����*/
	QString m_musicName;						/*!< ��������*/
	QString m_musicArtist;						/*!< ����������*/
	QString m_lrcFilePath;						/*!< ����ĸ���ļ�·��*/

	QNetworkAccessManager *m_lrcManager;		/*!< ����������*/
	QNetworkAccessManager *m_lrcManager2;		/*!< ����������*/
};

#endif // LRCTHREAD_H
