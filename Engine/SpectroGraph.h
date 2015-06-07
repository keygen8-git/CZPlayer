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
* \file   Spectrograph.h
* \author chengxuan   787280310@qq.com
* \date   2015-02-03
* \brief  Ƶ�׻���ͷ�ļ���
* \version 3.0.0
*
* \verbatim
* ��ʷ
*          3.0.0   ����,
*          2015-02-03    by chengxuan
*
* \endverbatim
*
*/

#ifndef SPECTROGRAPH_H
#define SPECTROGRAPH_H

/*! \def SPECTROGRAPH_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define SPECTROGRAPH_VERSION   0x030000

#include <QLabel>
#include <QString>
#include <vector>
using namespace std;

class QPaintEvent;

QT_FORWARD_DECLARE_CLASS(QMouseEvent)

/*! Ƶ�׻���
*/
class Spectrograph : public QLabel
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
	 */
    Spectrograph(QWidget *parent = NULL);

	/*! ��������.*/
    ~Spectrograph();

public:
	/*! ���ò���
	 *  \param lowFreq Ƶ���½�
	 *  \param highFreq Ƶ���Ͻ�
	 */
    void setParams(const double &lowFreq, const double &highFreq);

	/*! ����Ƶ��
	 */
	void reset();													
	
protected:
	/*! �麯��������ʵ��paintEvent����
	 *  \param event QPaintEvent����
	 */
    virtual void paintEvent(QPaintEvent *event);

public slots:
	/*! Ƶ�����ݸı�
	 *  \param vecFrequency Ƶ������
	 */
	void handleSpectrumChanged(const vector<float> &vecFrequency);

private:
    double m_lowFreq;								/*!< Ƶ���½�*/
    double m_highFreq;								/*!< Ƶ���Ͻ�*/
	vector<float> m_vecFrequency;					/*!< ͨ�����ٸ���Ҷ�任�������Ĳ���*/
};

#endif // SPECTROGRAPH_H
