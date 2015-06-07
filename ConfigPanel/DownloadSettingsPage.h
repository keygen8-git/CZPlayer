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
* \file   DownloadSettingsPage.h
* \author chengxuan   787280310@qq.com
* \date   2015-01-24
* \brief  ��������ҳ��ͷ�ļ���
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

#ifndef DOWNLOADSETTINGSPAGE_H
#define DOWNLOADSETTINGSPAGE_H

/*! \def DOWNLOADSETTINGSPAGE_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define DOWNLOADSETTINGSPAGE_VERSION   0x030000

#include <QWidget>
#include <QString>

class QLabel;
class QLineEdit;
class QPushButton;

/*! ��������ҳ��
*/
class DownloadSettingsPage : public QWidget
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
	 */
    DownloadSettingsPage(QWidget *parent = NULL);

	/*! ��������.*/
    ~DownloadSettingsPage();

	/*! ��ʼҳ��
	 */
	void init();

	/*! Ӧ�øı�
	 */
	void apply();

signals:
	/*! �����ؽ���������Ϣ�����ı�ʱ���͸��ź�
	 */
	void sigDownloadSettingsChanged();

private slots:
	/*! ����Ŀ¼�ı�
	 */
    void handleMusicDirChanged();

	/*! ר��Ŀ¼�ı�
	 */
	void handleAlbumDirChanged();

	/*! ���Ŀ¼�ı�
	 */
	void handleLrcDirChanged();

private:
	/*! ��������
	*/
	void createUI();

	/*! �ź����
	*/
	void createConnect();

private:
	QLabel *m_musicDirLabel;		 /*!< ����Ŀ¼*/
    QLineEdit *m_musicEdit;			 /*!< ����Ŀ¼*/
    QPushButton *m_musicButton;	     /*!< ����Ŀ¼*/

    QLabel *m_albumDirLabel;		 /*!< ר��Ŀ¼*/
    QLineEdit *m_albumEdit;			 /*!< ר��Ŀ¼*/
    QPushButton *m_albumButton;		 /*!< ר��Ŀ¼*/

    QLabel *m_lrcFileLabel;			 /*!< ���Ŀ¼*/
    QLineEdit *m_lrcFileEdit;		 /*!< ���Ŀ¼*/
    QPushButton *m_lrcFileButton;	 /*!< ���Ŀ¼*/
};

#endif // DOWNLOADSETTINGSPAGE_H
