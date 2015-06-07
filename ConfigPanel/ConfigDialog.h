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
* \file   ConfigDialog.h
* \author chengxuan   787280310@qq.com
* \date   2015-01-24
* \brief  ȫ������ͷ�ļ���
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

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

/*! \def CONFIGDIALOG_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define CONFIGDIALOG_VERSION   0x030000

#include <QDialog>

class GeneralSettingsPage;
class DownloadSettingsPage;
class LrcSettingsPage;
class HotKeysSettingsPage;
class UpdatePage;
class QListWidget;
class QPushButton;
class QStackedWidget;
class QListWidgetItem;
class QCloseEvent;

/*! ���öԻ���
*/
class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
	 */
    ConfigDialog(QWidget *parent = NULL);

	/*! ��������.*/
    ~ConfigDialog();

	/*! ��ʼ�����ý���
	*/
	void init();

protected:
	/*! �麯��������ʵ��closeEvent����
	*  \param event QPaintEvent����
	*/
	virtual void closeEvent(QCloseEvent *event);

signals:
	/*! ���öԻ���ر�
	 */
	void sigConfigDialogClosed();

private slots:
	/*! ҳ��ı�
	 *  \param current ��ǰҳ��
	 *  \param previous ֮ǰҳ��
	 */
    void handleChangePage(QListWidgetItem *current, QListWidgetItem *previous);

	/*! ȷ��
	 */
    void handleOkFunc();								

	/*! Ӧ��
	 */
    void handleAppFunc();	

	/*! ��������ҳ��ı�
	 */
	void handleGeneralSettingsChanged();

	/*! ��������ҳ��ı�
	 */
	void handleDownloadSettingsChanged();

	/*! �������ҳ��ı�
	 */
	void handleLrcSettingsChanged();

	/*! �ȼ�����ҳ��ı�
	 */
	void handleHotKeysSettingsChanged();

private:
	/*! ��������
	*/
	void createUI();

	/*! ����ͼ��
	*/
	void createIcons();

	/*! �ź����
	*/
	void createConnect();

private:
	QListWidget *m_contentsWidget;					/*!< ͼ��widget*/
    QStackedWidget *m_pagesWidget;					/*!< ҳ��widget*/

    QPushButton *m_okButton;						/*!< ȷ����ť*/				
    QPushButton *m_cancelButton;					/*!< ȡ����ť*/
    QPushButton *m_appButton;						/*!< Ӧ�ð�ť*/

    GeneralSettingsPage *m_generalSettingsPage;		/*!< ��������*/
    DownloadSettingsPage *m_downloadSettingsPage;	/*!< ��������*/
    LrcSettingsPage *m_lrcSettingsPage;				/*!< �������*/
    HotKeysSettingsPage *m_hotKeysSettingsPage;		/*!< �ȼ�����*/
	UpdatePage *m_updatePage;						/*!< ����ҳ��*/

	bool m_isGeneralSettingsChanged;				/*!< ���������Ƿ�ı�*/
	bool m_isDownloadSettingsChanged;				/*!< ���������Ƿ�ı�*/
	bool m_isLrcSettingsChanged;					/*!< ��������Ƿ�ı�*/
	bool m_isHotKeysSettingsChanged;				/*!< �ȼ������Ƿ�ı�*/
};

#endif // CONFIGDIALOG_H
