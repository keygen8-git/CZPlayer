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
* \file   HotKeysSettingsPage.h
* \author chengxuan   787280310@qq.com
* \date   2015-01-24
* \brief  �ȼ�����ҳ��ͷ�ļ���
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

#ifndef HOTKEYSSETTINGSPAGE_H
#define HOTKEYSSETTINGSPAGE_H

/*! \def HOTKEYSSETTINGSPAGE_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define HOTKEYSSETTINGSPAGE_VERSION   0x030000

#include <QWidget>
#include <QString>

class QTableWidget;
class QPushButton;
class QTableWidgetItem;
class EditHotkeyDialog;

/*! �ȼ�����ҳ��
*/
class HotKeysSettingsPage : public QWidget
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
	 */
    HotKeysSettingsPage(QWidget *parent = NULL);

	/*! ��������.*/
    ~HotKeysSettingsPage();

	/*! ��ʼҳ��
	*/
	void init();

	/*! Ӧ�øı�
	*/
	void apply();

signals:
	/*! ���ȼ�����������Ϣ�����ı�ʱ���͸��ź�
	 */
	void sigHotKeysSettingsChanged();

private slots:
	/*! �ָ�Ĭ�Ϸ���
	 */
	void handleRecoverDefaultSetting();

	/*! �༭�ȼ�
	*/
	void handleEditHotKeys();

	/*! ��ȡѡ����
	 *  \param row �к�
	 */
	void handleTableClicked(const int &index);

	/*! �ȼ��༭���
	 * \param hotKeyName �ȼ���
	 * \param hotKey �ȼ�
	 */
	void handleEditHotkeyFinished(const QString &hotKeyName, const QString &hotKey);

	/*! ˫���ȼ��б�༭�ȼ�
	 *  \param row �ȼ��б���
	 *  \param column �ȼ��б���
	 */
	void handleTableDoubleClicked(const int &row, const int &column);

private:
	/*! ��������
	*/
	void createUI();

	/*! �ź����
	*/
	void createConnect();

    /*! ���ñ����
     */
    void setTableWidgetStyle();

private:
    QTableWidget *m_hotKeysTableWidget;             	/*!< �ȼ���*/
	EditHotkeyDialog *m_editHotkeyDialog;				/*!< �ȼ��༭�Ի���*/
    QPushButton *m_editButton;							/*!< �༭�ȼ�*/
    QPushButton *m_recoverDefaultSettingButton;			/*!< �ָ�Ĭ��*/

    QTableWidgetItem *m_settingsHotKey;					/*!< ѡ������*/
    QTableWidgetItem *m_minToTrayHotKey;				/*!< ��ʾ/����������*/
    QTableWidgetItem *m_openMinWidgetHotKey;			/*!< ����ģʽ/��������*/
    QTableWidgetItem *m_openMusicFileHotKey;			/*!< �������ļ�*/
    QTableWidgetItem *m_openMediaWidgetHotKey;          /*!< ��ʾ/����ý�����*/
    QTableWidgetItem *m_openListWidgetHotKey;			/*!< ��ʾ/���ظ����б�*/
    QTableWidgetItem *m_openLrcHotKey;					/*!< ��ʾ/����������*/
    QTableWidgetItem *m_pauseHotKey;					/*!< ����/��ͣ*/
    QTableWidgetItem *m_lastHotKey;						/*!< ��һ��*/
    QTableWidgetItem *m_nextHotKey;						/*!< ��һ��*/

	int m_row;											/*!< ѡ����*/
};

#endif // HOTKEYSSETTINGSPAGE_H
