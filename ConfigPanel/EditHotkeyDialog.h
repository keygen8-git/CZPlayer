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
* \file   EditHotkeyDialog.h
* \author chengxuan   787280310@qq.com
* \date   2015-01-24
* \brief  �ȼ��༭�Ի���ͷ�ļ���
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

#ifndef EDITHOTKEYDIALOG_H
#define EDITHOTKEYDIALOG_H

/*! \def EDITHOTKEYDIALOG_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define EDITHOTKEYDIALOG_VERSION   0x030000

#include <QDialog>

class QEvent;
class QLineEdit;
class QLabel;
class QPushButton;

/*! �ȼ��༭�Ի���
*/
class EditHotkeyDialog : public QDialog
{
	Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
	 */
	EditHotkeyDialog(QWidget *parent = NULL);

	/*! ��������.*/
	~EditHotkeyDialog();

	/*! ��ʼ������
	 *  \param currentHotKeyName ��ǰ�ȼ�����
	 *  \param currentHotKey ��ǰ�ȼ�
	 */
	void init(const QString &currentHotKeyName, const QString &currentHotKey);

protected:
	/*! �麯��������ʵ��eventFilter����
	 *  \param target QObject����
	 *  \param event QEvent����
	 *  \reurn ����true�������˸��¼�
	 */
	virtual bool eventFilter(QObject *target, QEvent *event);

signals:
	/*! �ȼ��༭���
   	 * \param hotKeyName �ȼ���
	 * \param hotKey �ȼ�
	 */
	void sigEditHotkeyFinished(const QString &hotKeyName, const QString &hotKey);

private slots:
	/*! �ȼ��༭���
	 */
	void handleEditHotkeyFinished();

private:
	/*! ��������
	*/
	void createUI();

	/*! �ź����
	*/
	void createConnect();

	/*! �����ȼ����óɹ���ر���
	 */
	void hotKeySuccessReset();

	/*! �����ȼ��ͷ���ر���
	 */
	void keyReleaseReset();

private:
	QLabel *m_label;			/*!< �ȼ�����*/
	QLineEdit *m_edit;		    /*!< �༭�ȼ�*/
	QPushButton *m_okButton;	/*!< ȷ����ť*/
	QPushButton *m_cancelButton;/*!< ȡ����ť*/

	bool m_isHeadKeyPress;		/*!< �ȼ�ͷ�Ƿ���*/
	bool m_isTailkeyPress;		/*!< �ȼ�β�Ƿ���*/
	bool m_isHotkeySuccess;		/*!< �ȼ��Ƿ���*/

	bool m_isCtrlKeyPress;		/*!< Ctrl���Ƿ���*/
	bool m_isAltKeyPress;		/*!< Alt���Ƿ���*/
	bool m_isShiftKeyPress;		/*!< Shift���Ƿ���*/

	QString m_currentHotKeyName;/*!< �ȼ�����*/
	QString m_currentHotKey;	/*!< �ȼ�*/
};

#endif //EDITHOTKEYDIALOG_H

