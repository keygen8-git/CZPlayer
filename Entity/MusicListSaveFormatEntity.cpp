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
 * \file   MusicListSaveFormatEntity.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-21
 * \brief  �����б����ʽʵ��ʵ���ļ���
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

#include "MusicListSaveFormatEntity.h"

MusicListSaveFormatEntity::MusicListSaveFormatEntity()
{
	m_fileName = "";		/*!< �����ļ���*/
	m_time = "";			/*!< ����ʱ��*/
	m_filePath = "";		/*!< �ļ�·��*/
}

MusicListSaveFormatEntity::MusicListSaveFormatEntity(const QString &fileName, const QString &time, const QString &filePath)
	: m_fileName(fileName),
	  m_time(time), 
	  m_filePath(filePath)
{
	/*Do nothing.*/
}

MusicListSaveFormatEntity::~MusicListSaveFormatEntity()
{
	m_fileName = "";		/*!< �����ļ���*/
	m_time = "";			/*!< ����ʱ��*/
	m_filePath = "";		/*!< �ļ�·��*/
}

QString MusicListSaveFormatEntity::fileName() const
{
	return m_fileName;
}

void MusicListSaveFormatEntity::setFileName( const QString &fileName )
{
	m_fileName = fileName;
}

QString MusicListSaveFormatEntity::time() const
{
	return m_time;
}

void MusicListSaveFormatEntity::setTime( const QString &time )
{
	m_time = time;
}

QString MusicListSaveFormatEntity::filePath() const
{
	return m_filePath;
}

void MusicListSaveFormatEntity::setFilePath( const QString &filePath )
{
	m_filePath = filePath;
}
