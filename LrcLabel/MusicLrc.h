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
 * \file   MusicLrc.h
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-21
 * \brief  ��ʽ���ͷ�ļ���
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

#ifndef MUSICLRC_H
#define MUSICLRC_H

/*! \def MUSICLRC_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define MUSICLRC_VERSION   0x030000

#include <QString>
#include <QPoint>
#include <QPainter>
#include <QLinearGradient>
#include <QFont>
#include <QLabel>

class QTimer;
class QPaintEvent;
class QMouseEvent;
class QContextMenuEvent;

/*! ���Label
*/
class MusicLrc : public QLabel
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
     */
    MusicLrc(QWidget *parent = NULL);

	/*! ��������.*/
    ~MusicLrc();

public:
	/*! ����������֣���Ҫָ����ǰ��ʿ�ʼ�����֮���ʱ����
     *  \param intervalTime ʱ����
     */
    void startLrcMask(qint64 intervalTime);

	/*! ֹͣ�������
     */
    void stopLrcMask();

	/*! �������
     */
    void unlockLrc();


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
	/*! ����Ѿ�����
     */
    void sigLrcLocked();
	
	/*! ����Ѿ�����
     */
    void sigLrcUnlocked();

    /*! ����������
     */
    void sigHideLrc();

private slots:
	/*! �ƶ�����Ѿ�����mask
     */
    void handleTimeOut();

	/*! �������
     */
    void handleLockLrc();

	/*! �������ı�
	 * \param fontName ��������
	 */
	void handleFontNameChanged(const QString &fontName);

	/*! ��������С�ı�
	 * \param fontSize �����С
	 */
	void handleFontSizeChanged(const QString &fontSize);

	/*! ������͸ı�
	 * \param fontType �������
	 */
	void handleFontTypeChanged(const QString &fontType);

	/*! ���û�в����ϱ�Ե��ɫ�ı�
	 * \param color ��ɫ
	 */
	void handleNoPlayShangChanged(const QColor &color);

	/*! ���û�в����м���ɫ�ı�
	 * \param color ��ɫ
	 */
	void handleNoPlayZhongChanged(const QColor &color);

	/*! ���û�в����±�Ե��ɫ�ı�
	 * \param color ��ɫ
	 */
	void handleNoPlayXiaChanged(const QColor &color);

	/*! ��ʲ��ź��ϱ�Ե��ɫ�ı�
	 * \param color ��ɫ
	 */
	void handlePlayedShangChanged(const QColor &color);

	/*! ��ʲ��ź��м���ɫ�ı�
	 * \param color ��ɫ
	 */
	void handlePlayedZhongChanged(const QColor &color);

	/*! ��ʲ��ź��±�Ե��ɫ�ı�
	 * \param color ��ɫ
	 */
	void handlePlayedXiaChanged(const QColor &color);

	/*! ��ʻҶȸı�
	 * \param shadow �Ҷ�
	 */
	void handleShadowChanged(const int &shadow);

private:
	/*! ��������
	 */
	void createUI();

	/*! �ź����
	 */
	void createConnect();

private:
    QTimer *m_timer;								/*!< ��ʱ��*/
    qreal m_lrcMaskWidth;							/*!< ���볤��*/
    qreal m_lrcMaskWidthInterval;					/*!< ���ֿ�ȼ��*/
    QPoint m_dragPosition;							/*!< ����*/
    bool m_isLrcLock;								/*!< �����������*/

	QLinearGradient m_linearGradient;		/*!< ��ʵ����Խ���*/
	QLinearGradient m_maskLinearGradient;	/*!< ��ʵ��������Խ���*/
	QFont m_font;							/*!< ����*/
    int m_shadow;							/*!< �Ҷ�ֵ*/
};

#endif // MUSICLRC_H


































