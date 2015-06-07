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
 * \file   LoadMusicThread.h
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-28
 * \brief  ���ּ����߳�ͷ�ļ���
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

#ifndef LOADMUSICTHREAD_H
#define LOADMUSICTHREAD_H

/*! \def LOADMUSICTHREAD_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define LOADMUSICTHREAD_VERSION   0x030000

#include <QThread>
#include <QString>
#include <QList>
#include <QStringList>
#include <QLabel>
#include <QUrl>
#include "MusicInfoEntity.h"

/*! ���ظ����߳�
*/
class LoadMusicThread : public QThread
{
	Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent QObject���ͣ�Ĭ��ΪNULL
	 */
	LoadMusicThread(QObject *parent = NULL);

	/*! ��������.*/
    ~LoadMusicThread();

protected:
	/*! �麯�����̳���QThread
	 */
	virtual void run();
};

/*! ���ظ����߳��¼�������
*/
class LoadMusicThreadEvent : public QObject
{
	Q_OBJECT

public:
	/*! ���캯��
     *  \param parent QObject���ͣ�Ĭ��ΪNULL
     */
	LoadMusicThreadEvent(QObject *parent = NULL);

	/*! ��������.*/
    ~LoadMusicThreadEvent();

signals:
	/*! ���ز����б����
	*/
	void sigLoadMusicListError();

	/*! �����겥���б�
	 */
	void sigLoadMusicListFinished();

	/*! ��������
	 * \param entity ������Ϣʵ��
	 */
	void sigAddMusic(const MusicInfoEntity &entity);

private slots:
	/*! �������ļ� ���ò���
     *  \param musicList �����б���Ϣ����
     */
	void handleStartloadMusic(const QStringList &musicList);

	/*! �϶������ļ������ָ�ʽ�ļ� ���ò���
     *  \param urls ����url�б�
     */
	void handleStartloadMusic(const QList<QUrl> &urls);

	/*! �������ָ�ʽ�ļ����ļ��� ���ò���
     *  \param strFileOrDir ���ָ�ʽ�ļ����ļ���
     */
	void handleStartloadMusic(const QString &strFileOrDir);

	/*! �����ݿ��ȡ�����ļ� ���ò���
     */
	void handleStartloadMusic();							

private:
	/*! ��ʼ����
     */
	void startLoad();

	/*! �������ļ�����ģʽ
     */
	void openMusicModeLoad();								

	/*! �϶������ļ������ָ�ʽ�ļ�����ģʽ
     */
	void dragEnterMusicModeLoad();							

	/*! �����ָ�ʽ�ļ�����ģʽ
     */
	void openMusicFormatFileLoad();							

	/*! ���ݿ��ȡ�����ļ�����ģʽ
     */
	void readFromDBModeLoad();								

	/*! �����ļ��м���ģʽ
     */
	void openMusicDirectoryMode();		

	/*! ͨ�������ļ�·����������
	 * \param filePath �ļ�·��
	 */
	void analyzeMusic(const QString &filePath);

private:
	QStringList m_musicList;								/*!< �����б�*/
	QList<QUrl> m_urls;										/*!< ����url*/
	QString m_musicFormatFile;								/*!< ���ָ�ʽ�ļ�*/
	QString m_musicDirectory;								/*!< �����ļ���*/

	/*! ���������б�ģʽ*/
	enum LoadMusicMode
	{
		OpenMusic				= 1,		/*!< �������ļ�����ģʽ*/	
		DragEnterMusic			= 2,		/*!< �϶������ļ������ָ�ʽ�ļ�����ģʽ*/	
		OpenMusicFormatFile		= 3,		/*!< ���ָ�ʽ�ļ�����ģʽ*/	
		ReadFromDB				= 4,		/*!< ���ݿ��ȡ�����ļ�����ģʽ*/	
		OpenDirectory			= 5			/*!< �����ļ��м���ģʽ*/	
	};

	LoadMusicMode m_loadMusicMode;			/*!< ���������б�ģʽ*/
};

#endif //LOADMUSICTHREAD_H

