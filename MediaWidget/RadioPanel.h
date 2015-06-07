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
 * \file   RadioPanel.h
 * \author chengxuan   787280310@qq.com
 * \date   2015-02-23
 * \brief  ��̨���ͷ�ļ���
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

#ifndef RADIOPANEL_H
#define RADIOPANEL_H

/*! \def RADIOPANEL_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define RADIOPANEL_VERSION   0x030000

#include <QWidget>
#include <QList>
#include <QMap>
#include <QMediaPlayer>
#include "RadioInfoEntity.h"

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if RADIOINFOENTITY_VERSION < 0x030000
#error  "RadioInfoEntity version error."
#endif

class QLabel;
class QTableWidget;
class QPushButton;

/*! ��̨���
*/
class RadioPanel : public QWidget
{
    Q_OBJECT

public:
    /*! ���캯��
    *  \param parent ������ָ�룬Ĭ��ΪNULL
    */
    RadioPanel(QWidget *parent = NULL);

    /*! ��������.*/
    ~RadioPanel();

private slots:
    /*! ˫����̨��Ӧ����
    *  \param row ��
    */
    void handlePlayRadio(const int &row);

    /*! ���ŵ�̨
    */
    void handlePlayRadio();

    /*! ��һ��̨
    */
    void handlePreRadio();

    /*! ��һ��̨
    */
    void handleNextRadio();

    /*! ���Ŵ���
    *  \param error ��������
    */
    void handleError(QMediaPlayer::Error error);

private:
    /*! ��������
     */
    void createUI();

    /*! �ź����
     */
    void createConnect();

    /*! ���ص�̨��Ϣ
    *  \param entity ��̨��Ϣʵ��
    */
    void addRadioInfo(const RadioInfoEntity &entity);

    /*! ���ñ����
     */
    void setTableWidgetStyle();

    /*! ��ȡradio�����ļ�
    *  \param filePath �ļ�·��
    *  \return radio��Ϣ����
    */
    QList<RadioInfoEntity> readXML(const QString &filePath);

    /*! �������ת�����ַ���
     *  \param networkError ����������
     */
    QString errorCodeToString(QMediaPlayer::Error error);

private:
    QTableWidget *m_radioTable;                 /*!< radio���*/
    QMap<int, RadioInfoEntity> m_radioInfoMap;  /*!< key�����������value����̨��Ϣʵ��*/

    QMediaPlayer *m_radioPlayer;                 /*!< ��̨������*/

    QPushButton *m_playButton;                  /*!< ����/��ͣ��ť*/
    QPushButton *m_preButton;                   /*!< ��һ��*/
    QPushButton *m_nextButton;                  /*!< ��һ��*/

    QLabel *m_currentRadioLabel;                /*!< ��ǰ��̨*/
    RadioInfoEntity m_radioInfo;                /*!< ��ǰ��̨��Ϣ*/
    int m_currentRow;                           /*!< ��ǰ������*/

    /*! ����ģʽ*/
    enum PlayStatus
    {
        Playing = 1,     /*!< ����*/
        Stoped = 2         /*!< ֹͣ*/
    };
    enum PlayStatus m_playStatus;   /*!< ����ģʽ*/
};

#endif // RADIOPANEL_H
