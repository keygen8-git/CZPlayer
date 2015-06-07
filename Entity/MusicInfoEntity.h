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
 * \file   MusicInfoEntity.h
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-21
 * \brief  ������Ϣʵ��ͷ�ļ���
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

#ifndef MUSICINFOENTITY_H
#define MUSICINFOENTITY_H

/*! \def MUSICINFOENTITY_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define MUSICINFOENTITY_VERSION   0x030000

#include <QString>

/*! ������Ϣʵ��
*/
class MusicInfoEntity
{
public:
	/*! ���캯��.*/
	MusicInfoEntity();

	/*! ���캯��
	 * \param fileName �����ļ���
	 * \param time ����ʱ��
	 * \param filePath �ļ�·��
	 */
	MusicInfoEntity(const QString &fileName, const QString &time, const QString &filePath);

	/*! ��������.*/
	~MusicInfoEntity();

	/*! �õ��ļ���
	 * \return �ļ���
	 */
	QString fileName() const;

	/*! �����ļ���
	 * \param fileName �����ļ���
	 */
	void setFileName(const QString &fileName);

	/*! �õ����ֲ��ŵ�ʱ��
	 * \return ʱ��
	 */
	QString time() const;

	/*! ����ʱ��
	 * \param time ʱ��
	 */
	void setTime(const QString &time);

	/*! �õ��ļ�·��
	 * \return �ļ�·��
	 */
	QString filePath() const;

	/*! �����ļ�·��
	 * \param filePath �ļ�·��
	 */
	void setFilePath(const QString &filePath);

private:
	QString m_fileName;		/*!< �����ļ���*/
	QString m_time;			/*!< ����ʱ��*/
	QString m_filePath;		/*!< �ļ�·��*/
};

#endif // MUSICINFOENTITY_H

