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
* \file   GlobalHotKey.h
* \author chengxuan   787280310@qq.com
* \date   2015-01-31
* \brief  ȫ���ȼ�ͷ�ļ���
* \version 3.0.0
*
* \verbatim
* ��ʷ
*          3.0.0   ����,
*          2015-01-31    by chengxuan
*
* \endverbatim
*
*/

#ifndef GLOBALHOTKEY_H
#define GLOBALHOTKEY_H

/*! \def GLOBALHOTKEY_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define GLOBALHOTKEY_VERSION   0x030000

#include <QObject>
#include <QString>

class QxtGlobalShortcut;

/*! ȫ���ȼ�
*/
class GlobalHotKey : public QObject
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
	 */
	GlobalHotKey(QObject *parent = NULL);

	/*! ��������.*/
    ~GlobalHotKey();

public:
	/*! �Ƿ�����ѡ�������ȼ�
	 *  \param isWork true�������ã�����ر�
	 */
    void setConfigOptionsHotkeyWork(bool isWork);

	/*! �Ƿ�������ʾ/�����������ȼ�
	 *  \param isWork true�������ã�����ر�
	 */
    void setShowHideMainWidgetHotkeyWork(bool isWork);

	/*! �Ƿ���������ģʽ/���������ȼ�
	 *  \param isWork true�������ã�����ر�
	 */
    void setMinMainWidgetHotkeyWork(bool isWork);

	/*! �Ƿ����ô������ļ��ȼ�
	 *  \param isWork true�������ã�����ر�
	 */
    void setOpenMusicfileHotkeyWork(bool isWork);

	/*! �Ƿ�������ʾ/���������б��ȼ�
	 *  \param isWork true�������ã�����ر�
	 */
    void setShowDownloadHotkeyWork(bool isWork);

	/*! �Ƿ�������ʾ/���ظ����б��ȼ�
	 *  \param isWork true�������ã�����ر�
	 */
    void setShowMusicListHotkeyWork(bool isWork);

	/*! �Ƿ�������ʾ/�����������ȼ�
	 *  \param isWork true�������ã�����ر�
	 */
    void setShowLrcHotkeyWork(bool isWork);

	/*! �Ƿ����ò���/��ͣ�ȼ�
	 *  \param isWork true�������ã�����ر�
	 */
    void setPlayPauseHotkeyWork(bool isWork);

	/*! �Ƿ�������һ���ȼ�
	 *  \param isWork true�������ã�����ر�
	 */
    void setLastHotkeyWork(bool isWork);

	/*! �Ƿ�������һ���ȼ�
	 *  \param isWork true�������ã�����ر�
	 */
    void setNextHotkeyWork(bool isWork);

private slots:
	/*! ѡ�������ȼ��ı�
	* \param hotKey ѡ�������ȼ�
	*/
	void handleSettingsHotKeyChanged(const QString &hotKey);

	/*! ��ʾ/�����������ȼ��ı�
	* \param hotKey ��ʾ/�����������ȼ�
	*/
	void handleMinToTrayHotKeyChanged(const QString &hotKey);

	/*! ����ģʽ/���������ȼ��ı�
	* \param hotKey ����ģʽ/���������ȼ�
	*/
	void handleOpenMinWidgetHotKeyChanged(const QString &hotKey);

	/*! �������ļ��ȼ��ı�
	* \param hotKey �������ļ��ȼ�
	*/
	void handleOpenMusicFileHotKeyChanged(const QString &hotKey);

    /*! ��ʾ/����ý������ȼ��ı�
    * \param hotKey ��ʾ/����ý������ȼ�
	*/
    void handleOpenMediaWidgetHotKeyChanged(const QString &hotKey);

	/*! ��ʾ/���ظ����б��ȼ��ı�
	* \param hotKey ��ʾ/���ظ����б��ȼ�
	*/
	void handleOpenListWidgetHotKeyChanged(const QString &hotKey);

	/*! ��ʾ/�����������ȼ��ı�
	* \param hotKey ��ʾ/�����������ȼ�
	*/
	void handleOpenLrcHotKeyChanged(const QString &hotKey);

	/*! ����/��ͣ�ȼ��ı�
	* \param hotKey ����/��ͣ�ȼ�
	*/
	void handlePauseHotKeyChanged(const QString &hotKey);

	/*! ��һ���ȼ��ı�
	* \param hotKey ��һ���ȼ�
	*/
	void handleLastHotKeyChanged(const QString &hotKey);

	/*! ��һ���ȼ��ı�
	* \param hotKey ��һ���ȼ�
	*/
	void handleNextHotKeyChanged(const QString &hotKey);

private:
	QxtGlobalShortcut *m_configOptions;				/*!< ѡ�������ȼ�*/
    QxtGlobalShortcut *m_showHideMainWidget;		/*!< ��ʾ/�����������ȼ�*/
    QxtGlobalShortcut *m_minMainWidget;				/*!< ����ģʽ/���������ȼ�*/
    QxtGlobalShortcut *m_openMusicfile;				/*!< �������ļ��ȼ�*/
    QxtGlobalShortcut *m_showDownload;				/*!< ��ʾ/���������б��ȼ�*/
    QxtGlobalShortcut *m_showMusicList;				/*!< ��ʾ/���ظ����б��ȼ�*/
    QxtGlobalShortcut *m_showLrc;					/*!< ��ʾ/�����������ȼ�*/
    QxtGlobalShortcut *m_playPause;					/*!< ����/��ͣ�ȼ�*/
    QxtGlobalShortcut *m_last;						/*!< ��һ���ȼ�*/
    QxtGlobalShortcut *m_nextSc;					/*!< ��һ���ȼ�*/
};

#endif // GLOBALHOTKEY_H
