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
* \file   Spectrograph.cpp
* \author chengxuan   787280310@qq.com
* \date   2015-02-03
* \brief  Ƶ�׻���ʵ���ļ���
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

#include "spectrograph.h"
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QBitmap>

Spectrograph::Spectrograph(QWidget *parent) 
	: QLabel(parent),
	  m_lowFreq(0.0),
	  m_highFreq(0.0)
{
	this->resize(190, 78);
	m_vecFrequency.clear();
}

Spectrograph::~Spectrograph()
{
	/*Do nothing.*/
}

void Spectrograph::setParams(const double &lowFreq, const double &highFreq)
{
    Q_ASSERT(highFreq > lowFreq);
    m_lowFreq = lowFreq;		
    m_highFreq = highFreq;		
}

void Spectrograph::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

#if 0
	QPixmap backgroundImage;
	backgroundImage.load(":/app/images/screen.png");
	//��ͨ��pix�ķ������ͼƬ�Ĺ��˵�͸���Ĳ��ֵõ���ͼƬ����ΪloginPanel�Ĳ�����߿�
	this->setMask(backgroundImage.mask());
	painter.drawPixmap(0, 0, 190, 78, backgroundImage);
#endif

	const int numBars = m_vecFrequency.size();

	QColor barColor(5, 184, 204);		//Ƶ��bar��ɫ

    barColor = barColor.lighter();
    barColor.setAlphaF(0.75);		//����alphaͨ��

    //����Ƶ��
    if (numBars)
	{
        //�����ȵ����Ϳհ�
		const int widgetWidth = this->width();										//Ƶ��widget���
        const int barPlusGapWidth = widgetWidth / numBars;							//ÿһ��Ƶ�׼ӿհ׼�϶�Ŀ��
        const int barWidth = 0.8 * barPlusGapWidth;									//ÿһ��Ƶ��bar�Ŀ��
        const int gapWidth = barPlusGapWidth - barWidth;								//ÿһ���հ׼�϶���
        const int paddingWidth = widgetWidth - numBars * (barWidth + gapWidth);		//��Ե���
        const int leftPaddingWidth = (paddingWidth + gapWidth) / 2;					//���Ե���
        const int barHeight = this->height() - 2 * gapWidth;							//ÿһ��Ƶ��bar�ĸ߶�

		//����ÿһ��Ƶ��bar
        for (int i = 0; i < numBars; ++i)
		{
            const double value = m_vecFrequency[i];		//vlaue��ֵ��0��1֮��
            Q_ASSERT(value >= 0.0 && value <= 1.0);

            QRect bar = rect();
			//����Ƶ��bar��λ�úʹ�С
            bar.setLeft(rect().left() + leftPaddingWidth + (i * (gapWidth + barWidth)));
            bar.setWidth(barWidth);
            bar.setTop(rect().top() + gapWidth + (1.0 - value) * barHeight);
            bar.setBottom(rect().bottom() - gapWidth);
#if 0
			//������ɫ����
			QLinearGradient linearGradient(bar.topLeft(), bar.bottomRight());
			linearGradient.setColorAt(0.1, QColor(247, 104, 9));
			linearGradient.setColorAt(1.0, QColor(238, 17, 128));
			painter.fillRect(bar, QBrush(linearGradient));
#else
			painter.fillRect(bar, barColor);
#endif
        }
    }
	event->accept();
}

void Spectrograph::handleSpectrumChanged( const vector<float> &vecFrequency )
{
	m_vecFrequency = vecFrequency;
	this->update();						
}

void Spectrograph::reset()
{
	m_vecFrequency.clear();
	this->update();
}

