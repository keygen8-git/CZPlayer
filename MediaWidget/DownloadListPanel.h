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
 * \file   DownloadListPanel.h
 * \author chengxuan   787280310@qq.com
 * \date   2015-02-23
 * \brief  �����б����ͷ�ļ���
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

#ifndef DOWNLOADLISTPANEL_H
#define DOWNLOADLISTPANEL_H

/*! \def DOWNLOADLISTPANEL_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define DOWNLOADLISTPANEL_VERSION   0x030000

#include <QWidget>
#include <QList>
#include "StatusDefine.h"

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if STATUSDEFINE_VERSION < 0x030000
#error  "StatusDefine version error."
#endif

class QLabel;
class QTableWidget;
class QThread;
class QTableWidgetItem;
class QProgressBar;
class QTime;

class DownloadMusicThread;
class DownloadInfo;

/*! �������
*/
class DownloadListPanel : public QWidget
{
    Q_OBJECT

public:
    /*! ���캯��
    *  \param parent ������ָ�룬Ĭ��ΪNULL
    */
    DownloadListPanel(QWidget *parent = NULL);

    /*! ��������.*/
    ~DownloadListPanel();

    /*! ��������Ŀ¼
    *  \param musicPath ����Ŀ¼
    */
    void setMusicPath(const QString &musicPath);

private slots:
    /*! ����Ŀ¼�ı�
     * \param path ����·��
     */
    void handleMusicDirChanged(const QString &path);

    /*! ���ظ���
    *  \param musicName ������
    *  \param artist ������
    */
    void handleDownloadMusic(const QString &musicName, const QString &artist);

    /*! ���ظ���״̬
     *  \param status ����״̬
     */
    void handleMusicDownloadStatus(MusicDownloadStatus status);

    /*! ���½�����
     *  \param bytesRead �Ѿ����صĴ�С
     *  \param totalBytes �ܴ�С
     */
    void handleUpdateDataProgress(const qint64 &bytesRead, const qint64 &totalBytes);

    /*! �����ļ���С
     *  \param size �����ļ���С����λ���ֽ�
     */
    void handleMusicSize(const double &size);

private:
    /*! ��������
     */
    void createUI();

    /*! �ź����
     */
    void createConnect();

    /*! ���������������
     */
    void playAudio();

    /*! ���ñ����
     */
    void setTableWidgetStyle();

private:
    QTableWidget *m_downloadTable;         /*!< �����б�*/
    QList<DownloadInfo *> m_musicInfos;    /*!< ������Ϣ����*/
    QString m_musicPath;                   /*!< ����Ŀ¼*/
};

/*! ������Ϣ��
*/
class DownloadInfo : public QObject
{
    Q_OBJECT

public:
    /*! ���캯��
     *  \param downloadTable �����б�ָ��
    *  \param parent QObject���ͣ�Ĭ��ΪNULL
    */
    DownloadInfo(QTableWidget *downloadTable, QObject *parent = NULL);

    /*! ��������.*/
    ~DownloadInfo();

    /*! �õ����ֱ���
     *  \return ���ֱ���
     */
    QString title() const;

    /*! �������ֱ���
     *  \param text ���ֱ���
     */
    void setTitle(const QString &text);

    /*! �õ�����״̬
     *  \return ����״̬
     */
    QString status() const;

    /*! ��������״̬
     *  \param text ����״̬
     */
    void setStatus(const QString &text);

    /*! �õ������ļ���С
     *  \return �����ļ���С
     */
    QString size() const;

    /*! ���������ļ���С
     *  \param text �����ļ���С
     */
    void setSize(const QString &text);

    /*! �õ������ٶ�
     *  \return �����ٶ�
     */
    QString speed() const;

    /*! ���������ٶ�
     *  \param text �����ٶ�
     */
    void setSpeed(const QString &text);

    /*! �õ����ؽ���
     *  \return ���ؽ���
     */
    qint64 progress() const;

    /*! �������ؽ���
     *  \param value ���ؽ���
     */
    void setProgress(const qint64 &value);

    /*! �������ؽ������ֵ
     *  \param value ���ؽ������ֵ
     */
    void setProgressMaximum(const qint64 &value);

    /*! �õ������߳�ָ��
     *  \return �����߳�ָ��
     */
    QThread *thread() const;

    /*! ���������߳�ָ��
     *  \param value �����߳�ָ��
     */
    void setThread(QThread *thread);

    /*! �õ�ʱ����
     *  \return ʱ����
     */
    int elapsed() const;

private:
    QTableWidgetItem *m_musicTitleItem;     /*!< ���ֱ���*/
    QTableWidgetItem *m_musicStatusItem;    /*!< ��������״̬*/
    QTableWidgetItem *m_musicSizeItem;      /*!< �����ļ���С*/
    QTableWidgetItem *m_speedItem;          /*!< �����ٶ�*/
    QProgressBar *m_progressBar;            /*!< ������*/
    QThread *m_thread;                      /*!< �����߳�*/
    QTime *m_time;                          /*!< ʱ��*/
};

#endif // DOWNLOADLISTPANEL_H
