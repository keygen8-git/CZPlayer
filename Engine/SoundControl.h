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
* \file   SoundControl.h
* \author chengxuan   787280310@qq.com
* \date   2015-02-06
* \brief  ����������ͷ�ļ���
* \version 3.0.0
*
* \verbatim
* ��ʷ
*          3.0.0   ����,
*          2015-02-06    by chengxuan
*
* \endverbatim
*
*/

#ifndef SOUNDCONTROL_H 
#define SOUNDCONTROL_H   

/*! \def SOUNDCONTROL_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define SOUNDCONTROL_VERSION   0x030000

/*! ����������
*/
class SoundControl
{
public:
	/*! �����豸������
	 *  \param volume ��ʾ�����Ĵ�С, �����뷵��������ֵ�õ��ǰٷֱȣ���������0 -100���������豸�ľ���ֵ   
	 *  \param device �豸���� 0,1,2 �ֱ��ʾ������, ����,MIDI,LINE,IN,Ĭ��Ϊ0
	 * \return true ��ʾ���������Ĵ�С�Ĳ����ɹ�������ʧ��
	 */
	static bool setVolume(long volume, long device = 0);

	/*! �õ��豸������
	 *  \param device �豸���� 0,1,2 �ֱ��ʾ������, ����,MIDI,LINE,IN,Ĭ��Ϊ0
	 *  \return ����
	 */
	static unsigned getVolume(int dev);			

private:
	/*! ���캯��.*/
	SoundControl();

	/*! ��������.*/
	~SoundControl();

	/*! �õ���������
	 *  \param hmixer HMIXER�����
	 *  \param componentType �������
	 *  \param ctrlType ��������
	 *  \param mxc MIXERCONTROL����
	 * \return true����ɹ�������ʧ��
	 */
	static bool getVolumeControl(HMIXER hmixer , long componentType, long ctrlType, MIXERCONTROL *mxc); 

	/*! �õ�����
	 *  \param hmixer HMIXER�����
	 *  \param mxc MIXERCONTROL����
	 * \return ����
	 */
	static unsigned getVolumeValue(HMIXER hmixer, MIXERCONTROL *mxc);   

	/*! �õ�����
	 *  \param hmixer HMIXER�����
	 *  \param mxc MIXERCONTROL����
	 *  \param volume ����
	 *  \return true����ɹ�������ʧ��
	 */
	static bool setVolumeValue(HMIXER hmixer, MIXERCONTROL *mxc, long volume);   
};
 
#endif
