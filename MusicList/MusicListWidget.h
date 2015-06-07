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
 * \file   MusicListWidget.h
 * \author chengxuan   787280310@qq.com
 * \date   2015-01-08
 * \brief  �����б����ͷ�ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2015-01-08    by chengxuan
 *
 * \endverbatim
 *
 */

#ifndef MUSICLISTWIDGET_H
#define MUSICLISTWIDGET_H

/*! \def MUSICLISTWIDGET_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define MUSICLISTWIDGET_VERSION   0x030000

#include <QWidget>
#include <QMap>

class MusicList;
class QPaintEvent;
class QTimer;
class QLineEdit;
class QPushButton;
class QMenu;

//�����б����
class MusicListWidget : public QWidget
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param playList �����б�
	 *  \param mapMusicRows �������-��map
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
     */
    MusicListWidget(MusicList *playList,
					QMap<QString, int> *mapMusicRows,
                    QWidget *parent = NULL);

	/*! ��������.*/
    ~MusicListWidget();

protected:
	/*! �麯��������ʵ��paintEvent����
     *  \param event QPaintEvent����
     */
    virtual void paintEvent(QPaintEvent *event);

	/*! �麯��������ʵ��eventFilter����
     *  \param target QObject����
	 *  \param event QEvent����
	 *  \return ����true�����ж��¼��Ĵ���
     */
    virtual bool eventFilter(QObject *target, QEvent *event);

private slots:
	/*! ��������
     */
    void handleOnClickedAddMusic();

	/*! ��������
     */
    void handleSearchMusic();

	/*! ��齹���Ƿ�۽������������
     */
    void handleLineEditFocus();

	/*! ���ص������б�
     */
    void handleBackMusicList();

private:
	/*! ��������
     */
	void createUI();				

	/*! �ź����
     */
	void createConnect();	

private:
    QWidget *m_parent;						/*!< ������*/
    MusicList *m_playList;					/*!< �����б�*/
    QTimer *m_editFocusTimer;				/*!< ��齹�㶨ʱ��*/
	QMap<QString, int> *m_mapMusicRows;		/*!< key:�������ƣ�value:��*/

    QLineEdit *m_searchLineEdit;			/*!< ���������*/
    QPushButton *m_searchButton;			/*!< ������ť*/
    QPushButton *m_addMusicButton;			/*!< ������ְ�ť*/
    QPushButton *m_localeButton;			/*!< ��λ����*/
    QPushButton *m_delMusicButton;			/*!< ɾ����ǰ����*/
    QPushButton *m_findButton;				/*!< ��������*/
    QPushButton *m_backButton;				/*!< ���������б�ť*/
	QMenu *m_addMusicMenu;					/*!< ������ֲ˵�*/
};

#endif // MUSICLISTWIDGET_H
