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
* \file   LrcSettingsPage.h
* \author chengxuan   787280310@qq.com
* \date   2015-01-24
* \brief  �������ҳ��ͷ�ļ���
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

#ifndef LRCSETTINGSPAGE_H
#define LRCSETTINGSPAGE_H

/*! \def LRCSETTINGSPAGE_VERSION
*  �汾���ƺ꣬��Ӧv3.0.0�汾.
*/
#define LRCSETTINGSPAGE_VERSION   0x030000

#include <QWidget>
#include <QString>
#include <QColor>
#include <QMenu>

class LrcDemo;
class QLabel;
class QSpinBox;
class QLineEdit;
class QSlider;
class QPushButton;
class QAction;
class QComboBox;

/*! �������ҳ��
*/
class LrcSettingsPage : public QWidget
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
	 */
    LrcSettingsPage(QWidget *parent = NULL);

	/*! ��������.*/
    ~LrcSettingsPage();

	/*! ��ʼҳ��
	 */
	void init();

	/*! Ӧ�øı�
	 */
	void apply();

signals:
	/*! ����ʽ���������Ϣ�����ı�ʱ���͸��ź�
	 */
	void sigLrcSettingsChanged();

private slots:
	/*! �ı���ɫ
	 */
	void handleChangeColor();

	/*! �������ı�
	 * \param fontName ��������
	 */
	void handleFontNameChanged(const QString &fontName);

	/*! ��������С�ı�
	 * \param fontSize �����С
	 */
	void handleFontSizeChanged(const QString &fontSize);

	/*! ������͸ı�
	 * \param fontType �������
	 */
	void handleFontTypeChanged(const QString &fontType);

	/*! ���û�в����ϱ�Ե��ɫ�ı�
	 */
	void handleNoPlayShangColorChanged();

	/*! ���û�в����м���ɫ�ı�
	 */
	void handleNoPlayZhongColorChanged();

	/*! ���û�в����±�Ե��ɫ�ı�
	 */
	void handleNoPlayXiaColorChanged();

	/*! ��ʲ��ź��ϱ�Ե��ɫ�ı�
	 */
	void handlePlayedShangColorChanged();

	/*! ��ʲ��ź��м���ɫ�ı�
	 */
	void handlePlayedZhongColorChanged();

	/*! ��ʲ��ź��±�Ե��ɫ�ı�
	 */
	void handlePlayedXiaColorChanged();

	/*! ѡ����Ԥ����ɫ
	 */
	void handlePresetColor();

	/*! �ָ�Ĭ������
	 */
	void handleRecoverDefaultSetting();

	/*! Ԥ������ɫ�ı�
	 */
	void handlePresetColorChanged();

	/*! ��ʻҶȸı�
	 */
	void handleShadowChanged(const int &shadow);

private:
	/*! ��������
	 */
	void createUI();

	/*! �ź����
   	 */
	void createConnect();

	/*! �ı�QLineEdit��ɫ
	 *  \param lineEdit QLineEditָ��
	 *  \param color ��ɫ
	 */
	void setLineEditColor(QLineEdit *lineEdit, const QColor &color);

	/*! ����Ԥ����ɫ
	 *  \param color ��ɫ
	 */
	void setDefaultChoiceColor(const QString &color);

private:
    LrcDemo *m_lrcDemo;								/*!< ���Demo*/

    QLabel *m_fontLabel;							/*!< ��������*/
	QComboBox *m_fontNameCombo;							/*!< ��������*/

    QLabel *m_fontSizeLabel;						/*!< �����С*/
	QComboBox *m_fontSizeCombo;						/*!< �����С*/

    QLabel *m_fontTypeLabel;						/*!< ��������*/
	QComboBox *m_fontTypeCombo;						/*!< ��������*/

    QLabel *m_shadowLabel;							/*!< �Ҷ�*/
	QSlider *m_shadowSlider;						/*!< �Ҷ�*/
	QSpinBox *m_shadowSpinBox;						/*!< �Ҷ�*/

    QLineEdit *m_noPlayEdit;						/*!< û�в����ϱ�Ե��ɫ*/
	QPushButton *m_changeNoPlayButton;				/*!< û�в����ϱ�Ե��ɫ*/
	QColor m_noPlayShang;							/*!< û�в����ϱ�Ե��ɫ*/

    QLineEdit *m_noPlayEdit2;						/*!< û�в����м���ɫ*/
	QPushButton *m_changeNoPlayButton2;				/*!< û�в����м���ɫ*/
	QColor m_noPlayZhong;							/*!< û�в����м���ɫ*/

    QLineEdit *m_noPlayEdit3;						/*!< û�в����±�Ե��ɫ*/
	QPushButton *m_changeNoPlayButton3;				/*!< û�в����±�Ե��ɫ*/
	QColor m_noPlayXia;								/*!< û�в����±�Ե��ɫ*/

    QLineEdit *m_playedEdit;						/*!< ���Ź�����ϱ�Ե��ɫ*/
	QPushButton *m_changePlayedButton;				/*!< ���Ź�����ϱ�Ե��ɫ*/
	QColor m_playedShang;							/*!< ���Ź�����ϱ�Ե��ɫ*/

    QLineEdit *m_playedEdit2;						/*!< ���Ź�����м���ɫ*/
	QPushButton *m_changePlayedButton2;				/*!< ���Ź�����м���ɫ*/
	QColor m_playedZhong;							/*!< ���Ź�����м���ɫ*/

    QLineEdit *m_playedEdit3;						/*!< ���Ź�����±�Ե��ɫ*/
	QPushButton *m_changePlayedButton3;				/*!< ���Ź�����±�Ե��ɫ*/
	QColor m_playedXia;								/*!< ���Ź�����±�Ե��ɫ*/
    
	QPushButton *m_yuSheButton;						/*!< Ԥ����ɫ*/
	QPushButton *m_recoverDefaultColorButton;		/*!< �ָ�Ĭ����ɫ*/

	QMenu m_presetMenu;								/*!< Ԥ����ɫ*/
	QString m_defaultChoiceColor;					/*!< Ԥ��Ĭ����ɫ*/

    QAction *m_jingDianWhite;						/*!< �����*/
    QAction *m_haiYangBlue;							/*!< ������*/
    QAction *m_huoYanRed;							/*!< �����*/
    QAction *m_kuXuanBlack;							/*!< ���ź�*/
    QAction *m_qiuSeYellow;							/*!< ��ɫ��*/
    QAction *m_langManPurple;						/*!< ������*/
    QAction *m_ziRanGreen;							/*!< ��Ȼ��*/
};

#endif // LRCSETTINGSPAGE_H
