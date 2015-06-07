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
 * \file   MediaWidget.h
 * \author chengxuan   787280310@qq.com
 * \date   2015-02-23
 * \brief  ý�����ͷ�ļ���
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

#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H

/*! \def MEDIAWIDGET_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define MEDIAWIDGET_VERSION   0x030000

#include <QWidget>

class SearchPanel;
class RadioPanel;
class RankingPanel;
class DownloadListPanel;
class CollectionPanel;
class LrcPortraitPanel;
class QStackedWidget;
class QPushButton;
class QLabel;
class QPaintEvent;

/*! ý�����
*/
class MediaWidget : public QWidget
{
    Q_OBJECT

public:
    /*! ���캯��
    *  \param parent ������ָ�룬Ĭ��ΪNULL
    */
    MediaWidget(QWidget *parent = NULL);

    /*! ��������.*/
    ~MediaWidget();

    /*! ��������Ŀ¼
    *  \param musicPath ����Ŀ¼
    */
    void setMusicPath(const QString &musicPath);

protected:
    /*! �麯��������ʵ��paintEvent����
     *  \param event QPaintEvent����
     */
    virtual void paintEvent(QPaintEvent *event);

private slots:
    /*! ����������ť���
     */
    void handleSearchButton();

    /*! ����������ť���
     */
    void handleRadioButton();

    /*! ����񵥰�ť���
     */
    void handleRankingButton();

    /*! �������ذ�ť���
     */
    void handleDownloadListButton();

    /*! �����ղذ�ť���
     */
    void handleCollectionButton();

    /*! ������д�水ť���
     */
    void handleLrcPortraitButton();

private:
    /*! ��������
     */
    void createUI();

    /*! �ź����
     */
    void createConnect();

    /*! �ָ�֮ǰ��ť���
     */
    void recoverButtonStyle();

private:
    QStackedWidget *m_pagesWidget;					/*!< ҳ��widget*/

    SearchPanel *m_searchPanel;                     /*!< ����*/
    RadioPanel *m_radioPanel;                       /*!< ��̨*/
    RankingPanel *m_rankingPanel;                   /*!< ��*/
    DownloadListPanel *m_downloadListPanel;         /*!< �����б�*/
    CollectionPanel *m_collectionPanel;             /*!< �ղ��б�*/
    LrcPortraitPanel *m_lrcPortraitPanel;           /*!< ���д��*/

    QLabel *m_navigationBarLabel;           /*!< ������*/
    QPushButton *m_searchButton;			/*!< ����*/
    QPushButton *m_radioButton;             /*!< ��̨*/
    QPushButton *m_rankingButton;			/*!< ��*/
    QPushButton *m_downLoadListButton;		/*!< �����б�*/
    QPushButton *m_collectionButton;		/*!< �ղ��б�*/
    QPushButton *m_lrcPortraitButton;		/*!< ���д��*/

    bool m_isSearchButtonClicked;           /*!< ������ť��������*/
    bool m_isRadioButtonClicked;            /*!< ��̨��ť��������*/
    bool m_isRankingButtonClicked;          /*!< �񵥰�ť��������*/
    bool m_isDownloadListButtonClicked;     /*!< �����б�ť��������*/
    bool m_isCollectionButtonClicked;       /*!< �ղ��б�ť��������*/
    bool m_isLrcPortraitButtonClicked;      /*!< ��ʰ�ť��������*/
};

#endif // MEDIAWIDGET_H
