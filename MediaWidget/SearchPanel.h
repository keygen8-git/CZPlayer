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
 * \file   SearchPanel.h
 * \author chengxuan   787280310@qq.com
 * \date   2015-02-23
 * \brief  �������ͷ�ļ���
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

#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

/*! \def SEARCHPANEL_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define SEARCHPANEL_VERSION   0x030000

#include <QWidget>
#include <QMap>
#include <QString>
#include "StatusDefine.h"

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if STATUSDEFINE_VERSION < 0x030000
#error  "StatusDefine version error."
#endif

class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;
class QTableWidget;
class QTableWidgetItem;
class QEvent;

class SearchThread;
class SearchThreadEvent;

/*! �������
*/
class SearchPanel : public QWidget
{
    Q_OBJECT

public:
    /*! ���캯��
    *  \param parent ������ָ�룬Ĭ��ΪNULL
    */
    SearchPanel(QWidget *parent = NULL);

    /*! ��������.*/
    ~SearchPanel();

protected:
    /*! �麯��������ʵ��eventFilter����
     *  \param target QObject����
     *  \param event QEvent����
     *  \reurn ����true�������˸��¼�
     */
    virtual bool eventFilter(QObject *target, QEvent *event);

signals:
    /*! ��������
    *  \param text �ؼ����ı�
    */
    void sigSearchMusic(const QString &text);

    /*! ��������
    *  \param musicName ������
    *  \param artist ������
    */
    void sigDownloadMusic(const QString &musicName, const QString &artist);

    /*! �ղظ���
    *  \param musicName ������
    *  \param artist ������
    */
    void sigCollectMusic(const QString &musicName, const QString &artist);

private slots:
    /*! ��������
     */
    void handleSearchMusic();

    /*! ����������Ϣ
    *  \param musicName ������
    *  \param artist ������
    *  \param album ר��
    */
    void handleAddMusicInfo(const QString &musicName, const QString &artist, const QString &album);

    /*! ���ظ���
     */
    void handleDownloadMusic();

    /*! �ղظ���
     */
    void handleCollectMusic();

    /*! ȫ��ѡ��
     *  \param isChecked �Ƿ�ѡ��
     */
    void handleSelectAllMusic(bool isChecked);

    /*! ѡ��һ��
     *  \param isChecked �Ƿ�ѡ��
     */
    void handleSelectOneMusic(bool isChecked);

    /*! ��������״̬
    *  \param status ״̬
    */
    void handleMusicSearchStatus(MusicSearchStatus status);

private:
    /*! ��������
     */
    void createUI();

    /*! �ź����
     */
    void createConnect();

    /*! �������������߳�
    */
    void createMusicSearchThread();

    /*! ���ñ����
     */
    void setTableWidgetStyle();

private:
    QLineEdit *m_searchEdit;            /*!< ���������*/
    QPushButton *m_searchButton;        /*!< ������ť*/
    QLabel *m_searchInfoLabel;          /*!< ������ʾ*/
    QCheckBox *m_allChecked;            /*!< ѡ��ȫ������*/
    QPushButton *m_downloadButton;      /*!< ���ظ���*/
    QPushButton *m_collectButton;       /*!< �ղظ���*/
    QTableWidget *m_searchTable;        /*!< �����б�*/

    SearchThread *m_searchThread;             /*!< �����߳�*/
    SearchThreadEvent *m_searchThreadEvent;   /*!< �����߳��¼�������*/

    QMap<QCheckBox*, QString> m_searchMap;  /*!< key��QCheckBox���ͣ�value������������*/
    bool m_isSearching;                     /*!< �Ƿ�������������*/
};

#endif // SEARCHPANEL_H
