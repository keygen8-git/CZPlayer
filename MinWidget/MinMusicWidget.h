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
 * \file   MinMusicWidget.h
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-21
 * \brief  �������ͷ�ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2014-12-21    by chengxuan
 *
 * \endverbatim
 *
 */

#ifndef MINMUSICWIDGET_H
#define MINMUSICWIDGET_H

/*! \def MINMUSICWIDGET_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define MINMUSICWIDGET_VERSION   0x030000

#include <QWidget>
#include <QPoint>

class QPaintEvent;
class QMouseEvent;
class QContextMenuEvent;
class QPushButton;
class QLabel;
class QMenu;

/*! �������������
*/
class MinMusicWidget : public QWidget
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param mainWidget ������
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
     */
    MinMusicWidget(QWidget *mainWidget, QWidget *parent = NULL);

	/*! ��������.*/
    ~MinMusicWidget();

	/*! ����������水ť�Ƿ����
	 *  \param isWork true������ã����򲻿���
     */
	void setWork(bool isWork);

	/*! ���ø��Action�ı�
	 *  \param text �ı�����
     */
	void setMinMusicLrcActionText(const QString &text);

	/*! ����������ר��ͼƬ
	 * \param albumFilePath ר��·��
     */
	void changeAlbumImage(const QString &albumFilePath);

protected:
	/*! �麯��������ʵ��paintEvent����
     *  \param event QPaintEvent����
     */
	virtual void paintEvent(QPaintEvent *event);

	/*! �麯��������ʵ��mousePressEvent����
     *  \param event QMouseEvent����
     */
	virtual void mousePressEvent(QMouseEvent *event);

	/*! �麯��������ʵ��mouseMoveEvent����
     *  \param event QMouseEvent����
     */
	virtual void mouseMoveEvent(QMouseEvent *event);

	/*! �麯��������ʵ��contextMenuEvent����
     *  \param event QContextMenuEvent����
     */
	virtual void contextMenuEvent(QContextMenuEvent *event);

signals:
	/*! ��������
     */
    void sigShowMusicPanel();		

private slots:
	/*! ��������
     */
    void handleOpenMainWidget();	

private:
	/*! ��������
     */
	void createUI();				

	/*! �ź����
     */
	void createConnect();	

private:
    QWidget *m_mainWidget;						/*!< ������*/
    QPoint m_dragPosition;						/*!< �����*/

	QLabel *m_albumImage;						/*!< ר��ͼƬ*/

	QPushButton *m_minPlayButton;				/*!< ����*/
	QPushButton *m_minPauseButton;				/*!< ��ͣ*/
	QPushButton *m_minStopButton;				/*!< ֹͣ*/
	QPushButton *m_minNextButton;				/*!< ��һ��*/
	QPushButton *m_minLastButton;				/*!< ��һ��*/
	QPushButton *m_minOpenFileButton;			/*!< ���ļ�*/
	QAction *m_minMusicLrcAction;				/*!< ��ʾ���*/
	QMenu *m_rightHandMenu;						/*!< �Ҽ��˵�*/
};

#endif // MINMUSICWIDGET_H
