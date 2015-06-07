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
 * \file   DBModule.h
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-21
 * \brief  ���ݿ�ģ��ͷ�ļ���
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

#ifndef DBMODULE_H
#define DBMODULE_H

/*! \def DBMODULE_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define DBMODULE_VERSION   0x030000

#include "MusicListSaveFormatEntity.h"
#include "MusicInfoEntity.h"
#include <QStringList>
#include <QString>
#include <QList>

/*! ���ݿ�ģ��
 */
class DBModule
{
public:
	/*! ��ʼ�����ݿ�
	 */
	static void initDB();																			

	/*! �������ݿ�
	 * \return true����ɹ�������ʧ��
	 */
	static bool createConnection();																	

	/*! ������
	 */
	static void createTable();																		

	/*! �����ݿ��ж���������ʾ���������б���
	 * \param list �ļ�·��
	 * \return true����ɹ�������ʧ��
	 */
	static bool readFilePath(QStringList &list);													

	/*! �����ݿ��ж���������ʾ��m3u�ļ���
	 * \param list �����б��ʽ����
	 * \return true����ɹ�������ʧ��
	 */
	static bool readMusicListSaveFormatEntity(QList<MusicListSaveFormatEntity> &list);				

	/*! �����ݿ��ȡ������Ϣ
	 * \param list ������Ϣ����
	 * \return true����ɹ�������ʧ��
	 */
	static bool readMusicInfoEntity(QList<MusicInfoEntity> &list);									

	/*! ������ݿ�
	 * \return true����ɹ�������ʧ��
	 */
	static bool clearDB();																			

	/*! ɾ��һ����¼
	 * \param fileName �ļ���
	 * \return true����ɹ�������ʧ��
	 */
	static bool delLine(const QString &fileName);													

	/*! ����һ�м�¼
	 * \param fileName �ļ���
	 * \param time ����ʱ��
	 * \param filePath �ļ�·��
	 * \return true����ɹ�������ʧ��
	 */
	static bool insertLine(const QString &fileName, const QString &time, const QString &filePath);	

	/*! ����ר��url
	 * \param fileName �ļ���
	 * \param albumUrlPath ר��url
	 * \return true����ɹ�������ʧ��
	 */
	static bool updateAlbumUrlPath(const QString &fileName, const QString &albumUrlPath);			

	/*! �����ݿ��ж�����������Ӧ��ר��url
	 * \param fileName �ļ���
	 * \param albumUrlPath ר��url
	 * \return true����ɹ�������ʧ��
	 */
	static bool readAlbumUrlPathFromDB(const QString &fileName, QString &albumUrlPath);					

private:
	/*! ���캯��.*/
	DBModule();

	/*! ��������.*/
	~DBModule();
};

#endif //DBMODULE_H
