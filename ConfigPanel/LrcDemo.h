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
* \file   LrcDemo.h
* \author chengxuan   787280310@qq.com
* \date   2015-01-24
* \brief  ���ģ��ͷ�ļ���
* \version 3.0.0
*
* \verbatim
* ��ʷ
*          3.0.0   ����,
*          2015-01-24    by chengxuan
*
* \endverbatim
*
*/

#ifndef LRCDEMO_H
#define LRCDEMO_H

/*! \def LRCDEMO_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define LRCDEMO_VERSION   0x030000

#include <QLabel>
#include <QString>
#include <QLinearGradient>
#include <QFont>
#include <QColor>

class QPaintEvent;

/*! ���ģ��
*/
class LrcDemo : public QLabel
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
	 */
	LrcDemo(QWidget *parent = NULL);

	/*! ��������.*/
    ~LrcDemo();

public:
	/*! ���ø������
	 * \param fontName ��������
	 */
	void setFontName(const QString &fontName);

	/*! ���ø�������С
	 * \param fontSize �����С
	 */
	void setFontSize(const QString &fontSize);

	/*! ���ø������
	 * \param fontType �������
	 */
	void setFontType(const QString &fontType);

	/*! ���ø��û�в����ϱ�Ե��ɫ
	 * \param color ��ɫ
	 */
	void setLinearGradient(const QColor &color);

	/*! ���ø��û�в����м���ɫ
	 * \param color ��ɫ
	 */
	void setLinearGradient2(const QColor &color);

	/*! ���ø��û�в����±�Ե��ɫ
	 * \param color ��ɫ
	 */
	void setLinearGradient3(const QColor &color);

	/*! ���ø�ʲ��ź��ϱ�Ե��ɫ
	 * \param color ��ɫ
	 */
	void setMaskLinearGradient(const QColor &color);

	/*! ���ø�ʲ��ź��м���ɫ
	 * \param color ��ɫ
	 */
	void setMaskLinearGradient2(const QColor &color);

	/*! ���ø�ʲ��ź��±�Ե��ɫ
	 * \param color ��ɫ
	 */
	void setMaskLinearGradient3(const QColor &color);

	/*! ���ø�ʻҶ�
	 * \param shadow �Ҷ�
	 */
	void setLrcDemoShadow(const int &shadow);

protected:
	/*! �麯��������ʵ��paintEvent����
	 *  \param event QPaintEvent����
	 */
    virtual void paintEvent(QPaintEvent *event);

private:
	/*! ����mask����
	 * \param maskWidth mask����
	 */
	void setLrcMaskWidth(const double &maskWidth);

private:
    QLinearGradient m_linearGradient;			/*!< ��ʵ����Խ���*/
    QLinearGradient m_maskLinearGradient;		/*!< ��ʵ��������Խ���*/
    QFont m_font;								/*!< ����*/
	double m_lrcMaskWidth;						/*!< mask����*/
    int m_shadow;								/*!< �Ҷ�*/
};

#endif // LRCDEMO_H


































