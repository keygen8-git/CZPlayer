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
 * \file   SharedDialog.h
 * \author chengxuan   787280310@qq.com
 * \date   2015-01-06
 * \brief  ��������Ի���ͷ�ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2015-01-06    by chengxuan
 *
 * \endverbatim
 *
 */

#ifndef SHAREDDIALOG_H
#define SHAREDDIALOG_H

/*! \def SHAREDDIALOG_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define SHAREDDIALOG_VERSION   0x030000

#include <QDialog>
#include <QString>

class QLabel;
class QTextEdit;
class QCheckBox;
class QPushButton;

/*! ��������Ի���
*/
class SharedDialog : public QDialog
{
	Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
     */
	SharedDialog(QWidget *parent = NULL);

	/*! ��������.*/
	~SharedDialog(void);

public:
	/*! ��ʼ������Ի���
	 *  \param albumImagePath ר��ͼƬ·��
	 *  \param musicName ������
	 *  \param albumUrlPath ר��url
     */
	void init(const QString &albumImagePath, 
				const QString &musicName, 
				const QString &albumUrlPath);		

private slots:
	/*! ��ѡ��״̬�ı�
	 *  \param state ״̬
     */
	void handleCheckBoxStateChanged(int state);									

	/*! �������
     */
	void handleSharedMusic();													

private:
	QString m_albumUrlPath;					/*!< ר��ͼƬ·��*/
	QString m_musicName;					/*!< ������*/

	QLabel *m_albumLabel;					/*!< ר��*/
	QTextEdit *m_textEdit;					/*!< �ı�*/
	QLabel *m_sharedLabel;					/*!< ������ʾ*/

	QCheckBox *m_xinlangweiboCheckBox;		/*!< ����΢��*/
	QLabel *m_xinlangweiboLabel;			/*!< ����΢��*/

	QCheckBox *m_tengxunweiboCheckBox;		/*!< ��Ѷ΢��*/
	QLabel *m_tengxunweiboLabel;			/*!< ��Ѷ΢��*/

	QCheckBox *m_qqkongjianCheckBox;		/*!< QQ�ռ�*/
	QLabel *m_qqkongjianLabel;				/*!< QQ�ռ�*/

	QCheckBox *m_renrenCheckBox;			/*!< ������*/
	QLabel *m_renrenLabel;					/*!< ������*/

	QCheckBox *m_kaixinCheckBox;			/*!< ������*/
	QLabel *m_kaixinLabel;					/*!< ������*/

	QCheckBox *m_doubanCheckBox;			/*!< ������*/
	QLabel *m_doubanLabel;					/*!< ������*/

	QCheckBox *m_souhuweiboCheckBox;		/*!< �Ѻ�΢��*/
	QLabel *m_souhuweiboLabel;				/*!< �Ѻ�΢��*/

	QCheckBox *m_qqhaoyouCheckBox;			/*!< QQ����*/
	QLabel *m_qqhaoyouLabel;				/*!< QQ����*/

	QPushButton *m_shareButton;				/*!< ����ť*/
	QPushButton *m_cancelButton;			/*!< ȡ����ť*/

private:
	/*! �������
	 *  \param url url����
     */
	void openBrowser(const QString &url);						

	/*! ��������
     */
	void createUI();				

	/*! �ź����
     */
	void createConnect();	
};

#endif //SHAREDDIALOG_H

