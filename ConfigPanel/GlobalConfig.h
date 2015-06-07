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
 * \file   GlobalConfig.h
 * \author chengxuan   787280310@qq.com
 * \date   2015-01-18
 * \brief  ȫ������ͷ�ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2015-01-18    by chengxuan
 *
 * \endverbatim
 *
 */

#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

/*! \def GLOBALCONFIG_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define GLOBALCONFIG_VERSION   0x030000

#include <QObject>
#include <QString>
#include <QColor>

/*���������ϢĬ��ֵ*/
extern const QString FontName;
extern const QString FontSize;
extern const QString FontType;
extern const QColor NoPlayShang;
extern const QColor NoPlayZhong;
extern const QColor NoPlayXia;
extern const QColor PlayedShang;
extern const QColor PlayedZhong;
extern const QColor PlayedXia;
extern const QString DefaultChoiceColor;
extern const int Shadow;

/*�ȼ�������ϢĬ��ֵ*/
extern const QString ConfigOptions;
extern const QString ShowHideMainWidget;
extern const QString MinMainWidget;
extern const QString OpenMusicFile;
extern const QString ShowHideMediaWidget;
extern const QString ShowHideMusicList;
extern const QString ShowHideLrc;
extern const QString PlayPause;
extern const QString PlayPre;
extern const QString PlayNext;

//�����
extern const QColor NoPlayWhiteShang;
extern const QColor NoPlayWhiteZhong;
extern const QColor NoPlayWhiteXia;
extern const QColor PlayedWhiteShang;
extern const QColor PlayedWhiteZhong;
extern const QColor PlayedWhiteXia;

//������
extern const QColor NoPlayBlueShang;
extern const QColor NoPlayBlueZhong;
extern const QColor NoPlayBlueXia;
extern const QColor PlayedBlueShang;
extern const QColor PlayedBlueZhong;
extern const QColor PlayedBlueXia;

//�����
extern const QColor NoPlayRedShang;
extern const QColor NoPlayRedZhong;
extern const QColor NoPlayRedXia;
extern const QColor PlayedRedShang;
extern const QColor PlayedRedZhong;
extern const QColor PlayedRedXia;

//���ź�
extern const QColor NoPlayBlackShang;
extern const QColor NoPlayBlackZhong;
extern const QColor NoPlayBlackXia;
extern const QColor PlayedBlackShang;
extern const QColor PlayedBlackZhong;
extern const QColor PlayedBlackXia;

//��ɫ��
extern const QColor NoPlayYellowShang;
extern const QColor NoPlayYellowZhong;
extern const QColor NoPlayYellowXia;
extern const QColor PlayedYellowShang;
extern const QColor PlayedYellowZhong;
extern const QColor PlayedYellowXia;

//������
extern const QColor NoPlayPurpleShang;
extern const QColor NoPlayPurpleZhong;
extern const QColor NoPlayPurpleXia;
extern const QColor PlayedPurpleShang;
extern const QColor PlayedPurpleZhong;
extern const QColor PlayedPurpleXia;

//��Ȼ��
extern const QColor NoPlayGreenShang;
extern const QColor NoPlayGreenZhong;
extern const QColor NoPlayGreenXia;
extern const QColor PlayedGreenShang;
extern const QColor PlayedGreenZhong;
extern const QColor PlayedGreenXia;

Q_DECLARE_METATYPE(enum PlayModeType)

/*! ȫ������
 */
class GlobalConfig : public QObject
{
	Q_OBJECT

public:
	/*! ��ȡȫ�ֶ���
	\return ���ش�ע��������Ϣ���ö���
	*/
	static GlobalConfig* instance();

	/*! ɾ��ȫ�ֶ���
	\note ��һ���ڳ����˳�ǰ���� delInstance() �����򽫵��³������
	*/
	static void delInstance();

	/*! ���¼���������Ϣ
	 * \return true����ɹ�������ʧ��
	 */
	bool reload();

	/*! ����������Ϣ
	 * \return true����ɹ�������ʧ��
	 */
	bool save();

	/*! �Ƿ�����������������������
	 * \return isReleaseResource������������������û����������
	 */
    void setReleaseResource(bool isReleaseResource);

	/*****************************************************************************
	 ��������get/set����
	*****************************************************************************/

	/*! ��������������ʱ�Ƿ��Զ���������
	 * \param isAutoPlayMusic true�����Զ����ţ�����ȡ��
	 */
	void setAutoPlayMusic(bool isAutoPlayMusic);

	/*! ���ÿ����Ƿ��Զ����в�����
	 * \param isAutoRunPlayer true�����Զ����У�����ȡ��
	 */
	void setAutoRunPlayer(bool isAutoRunPlayer);

	/*! ��������������ʱ�Ƿ��Զ����к�
	 * \param isAutoGrettings true�����Զ����к�������ȡ��
	 */
	void setAutoGreetings(bool isAutoGrettings);

	/*! ����ΪĬ�ϲ�����
	 * \param isDefaultPlayer true��������ΪĬ�ϲ�����������ȡ��
	 */
	void setDefaultPlayer(bool isDefaultPlayer);

	/*! �Ƿ�����������ʱ�Զ���������
	* \return true�����Զ����ţ�������
	*/
	bool autoPlayMusic() const;

	/*! �Ƿ񿪻��Ƿ��Զ����в�����
	* \return true�����Զ����У�������
	*/
	bool autoRunPlayer() const;

	/*! �Ƿ�����������ʱ�Ƿ��Զ����к�
	* \return true�����Զ����к���������
	*/
	bool autoGreetings() const;

	/*! �Ƿ�ΪĬ�ϲ�����
	* \return true����Ĭ�ϲ�������������
	*/
	bool defaultPlayer() const;

	/*****************************************************************************
	 ��������get/set����
	*****************************************************************************/

	/*! ��������·��
	 * \param path ����·��
	 */
	void setMusicPath(const QString &path);

	/*! ����ר��·��
	 * \param path ר��·��
	 */
	void setAlbumPath(const QString &path);

	/*! ������·��
	 * \param path ���·��
	 */
	void setLrcPath(const QString &path);

	/*! �õ�����·��
	* \return ����·��
	*/
	QString musicPath() const;

	/*! �õ�ר��·��
	* \return ר��·��
	*/
	QString albumPath() const;

	/*! �õ����·��
	* \return ���·��
	*/
	QString lrcPath() const;

	/*****************************************************************************
	 �ȼ�����get/set����
	*****************************************************************************/

	/*! ����ѡ�������ȼ�
	 * \param hotKey ѡ�������ȼ�
	 */
	void setSettingsHotKey(const QString &hotKey);

	/*! ������ʾ/�����������ȼ�
	 * \param hotKey ��ʾ/�����������ȼ�
	 */
	void setMinToTrayHotKey(const QString &hotKey);

	/*! ��������ģʽ/���������ȼ�
	 * \param hotKey ����ģʽ/���������ȼ�
	 */
	void setOpenMinWidgetHotKey(const QString &hotKey);

	/*! ���ô������ļ��ȼ�
	 * \param hotKey �������ļ��ȼ�
	 */
	void setOpenMusicFileHotKey(const QString &hotKey);

    /*! ������ʾ/����ý������ȼ�
	 * \param hotKey ��ʾ/���������б��ȼ�
	 */
    void setOpenMediaWidgetHotKey(const QString &hotKey);

	/*! ������ʾ/���ظ����б��ȼ�
	 * \param hotKey ��ʾ/���ظ����б��ȼ�
	 */
	void setOpenListWidgetHotKey(const QString &hotKey);

	/*! ������ʾ/�����������ȼ�
	 * \param hotKey ��ʾ/�����������ȼ�
	 */
	void setOpenLrcHotKey(const QString &hotKey);

	/*! ���ò���/��ͣ�ȼ�
	 * \param hotKey ����/��ͣ�ȼ�
	 */
	void setPauseHotKey(const QString &hotKey);

	/*! ������һ���ȼ�
	 * \param hotKey ��һ���ȼ�
	 */
	void setLastHotKey(const QString &hotKey);

	/*! ������һ���ȼ�
	 * \param hotKey ��һ���ȼ�
	 */
	void setNextHotKey(const QString &hotKey);

	/*! �õ�ѡ�������ȼ�
	 * \return ѡ�������ȼ�
	 */
	QString settingsHotKey() const;

	/*! �õ���ʾ/�����������ȼ�
	 * \return ��ʾ/�����������ȼ�
	 */
	QString minToTrayHotKey() const;

	/*! �õ�����ģʽ/���������ȼ�
	 * \return ����ģʽ/���������ȼ�
	 */
	QString openMinWidgetHotKey() const;

	/*! �õ��������ļ��ȼ�
	 * \return �������ļ��ȼ�
	 */
	QString openMusicFileHotKey() const;

    /*! �õ���ʾ/����ý������ȼ�
	 * \return ��ʾ/���������б��ȼ�
	 */
    QString openMediaWidgetHotKey() const;

	/*! �õ���ʾ/���ظ����б��ȼ�
	 * \return ��ʾ/���ظ����б��ȼ�
	 */
	QString openListWidgetHotKey() const;

	/*! �õ���ʾ/�����������ȼ�
	 * \return ��ʾ/�����������ȼ�
	 */
	QString openLrcHotKey() const;

	/*! �õ�����/��ͣ�ȼ��ı�
	 * \return ����/��ͣ�ȼ�
	 */
	QString pauseHotKey() const;

	/*! �õ���һ���ȼ��ı�
	 * \return ��һ���ȼ�
	 */
	QString lastHotKey() const;

	/*! �õ���һ���ȼ��ı�
	 * \return ��һ���ȼ�
	 */
	QString nextHotKey() const;

	/*****************************************************************************
	 �������get/set����
	*****************************************************************************/

	/*! ���ø������
	 * \param fontName ��������
	 */
	void setFontName(const QString &fontName);

	/*! ���ø�������С
	 * \param fontSize �����С
	 */
	void setFontSize(const QString &fontSize);

	/*! ���ø������
	 * \param fontType �������
	 */
	void setFontType(const QString &fontType);

	/*! ���ø��û�в����ϱ�Ե��ɫ
	 * \param color ��ɫ
	 */
	void setNoPlayShang(const QColor &color);

	/*! ���ø��û�в����м���ɫ
	 * \param color ��ɫ
	 */
	void setNoPlayZhong(const QColor &color);

	/*! ���ø��û�в����±�Ե��ɫ
	 * \param color ��ɫ
	 */
	void setNoPlayXia(const QColor &color);

	/*! ���ø�ʲ��ź��ϱ�Ե��ɫ
	 * \param color ��ɫ
	 */
	void setPlayedShang(const QColor &color);

	/*! ���ø�ʲ��ź��м���ɫ
	 * \param color ��ɫ
	 */
	void setPlayedZhong(const QColor &color);

	/*! ���ø�ʲ��ź��±�Ե��ɫ
	 * \param color ��ɫ
	 */
	void setPlayedXia(const QColor &color);

	/*! ���ø��Ĭ����ɫ��ɫ
	 * \param color ��ɫ
	 */
	void setDefaultChoiceColor(const QString &color);

	/*! ���ø�ʻҶ�
	 * \param shadow �Ҷ�
	 */
	void setShadow(const int &shadow);

	/*! �õ��������
	 * \return ��������
	 */
	QString fontName() const;

	/*! �õ���������С
	 * \return �����С
	 */
	QString fontSize() const;

	/*! �õ��������
	 * \return �������
	 */
	QString fontType() const;

	/*! �õ����û�в����ϱ�Ե��ɫ
	 * \return ��ɫ
	 */
	QColor noPlayShang() const;

	/*! �õ����û�в����м���ɫ
	 * \return ��ɫ
	 */
	QColor noPlayZhong() const;

	/*! �õ����û�в����±�Ե��ɫ
	 * \return ��ɫ
	 */
	QColor noPlayXia() const;

	/*! �õ���ʲ��ź��ϱ�Ե��ɫ
	 * \return ��ɫ
	 */
	QColor playedShang() const;

	/*! �õ���ʲ��ź��м���ɫ
	 * \return ��ɫ
	 */
	QColor playedZhong() const;

	/*! �õ���ʲ��ź��±�Ե��ɫ
	 * \return ��ɫ
	 */
	QColor playedXia() const;

	/*! �õ����Ĭ����ɫ
	 * \return ��ɫ
	 */
	QString defaultChoiceColor() const;

	/*! �õ���ʻҶ�
	 * \return �Ҷ�
	 */
	int shadow() const;

	/*****************************************************************************
	 ���ſ�������get/set����
	*****************************************************************************/

	/*! �����Ƿ���
	 * \param isMute true�����������򲻾���
	 */
    void setMute(bool isMute);

	/*! ��������
	 * \param volume ����
	 */
	void setVolume(const int &volume);

	/*! ����ģʽ
	 * \param playMode ����ģʽ
	 */
	void setPlayMode(enum PlayModeType playMode);

	/*! �Ƿ���
	 * \return true�����������򲻾���
	 */
	bool mute() const;

	/*! �õ�����
	 * \return ����
	 */
	int volume() const;

	/*! �õ���������
	 * \return ��������
	 */
	enum PlayModeType playMode() const;

signals:
	/*****************************************************************************
	 ��������������Ϣ�ı䷢�͵��ź�
	*****************************************************************************/

	/*! �Զ������������øı�
	 * \param isAutoPlayMusic true�����Զ����ţ�����ȡ��
	 */
	void sigAutoPlayMusicChanged(bool isAutoPlayMusic);

	/*! �����Ƿ��Զ����в��������øı�
	 * \param isAutoRunPlayer true�����Զ����У�����ȡ��
	 */
	void sigAutoRunPlayerChanged(bool isAutoRunPlayer);

	/*! ����������ʱ�Ƿ��Զ����к����øı�
	 * \param isAutoGrettings true�����Զ����к�������ȡ��
	 */
	void sigAutoGreetingsChanged(bool isAutoGrettings);

	/*! Ĭ�ϲ��������øı�
	 * \param isDefaultPlayer true��������ΪĬ�ϲ�����������ȡ��
	 */
	void sigDefaultPlayerChanged(bool isDefaultPlayer);

	/*****************************************************************************
	 ��������������Ϣ�ı䷢�͵��ź�
	*****************************************************************************/

	/*! ����·���ı�
	 * \param path ����·��
	 */
	void sigMusicPathChanged(const QString &path);

	/*! ר��·���ı�
	 * \param path ר��·��
	 */
	void sigAlbumPathChanged(const QString &path);

	/*! ���·���ı�
	 * \param path ���·��
	 */
	void sigLrcPathChanged(const QString &path);

	/*****************************************************************************
	 �ȼ�����������Ϣ�ı䷢�͵��ź�
	*****************************************************************************/
	/*! ѡ�������ȼ��ı�
	 * \param hotKey ѡ�������ȼ�
	 */
	void sigSettingsHotKeyChanged(const QString &hotKey);

	/*! ��ʾ/�����������ȼ��ı�
	 * \param hotKey ��ʾ/�����������ȼ�
	 */
	void sigMinToTrayHotKeyChanged(const QString &hotKey);

	/*! ����ģʽ/���������ȼ��ı�
	 * \param hotKey ����ģʽ/���������ȼ�
	 */
	void sigOpenMinWidgetHotKeyChanged(const QString &hotKey);

	/*! �������ļ��ȼ��ı�
	 * \param hotKey �������ļ��ȼ�
	 */
	void sigOpenMusicFileHotKeyChanged(const QString &hotKey);

    /*! ��ʾ/����ý������ȼ��ı�
	 * \param hotKey ��ʾ/���������б��ȼ�
	 */
    void sigOpenMediaWidgetHotKeyChanged(const QString &hotKey);

	/*! ��ʾ/���ظ����б��ȼ��ı�
	 * \param hotKey ��ʾ/���ظ����б��ȼ�
	 */
	void sigOpenListWidgetHotKeyChanged(const QString &hotKey);

	/*! ��ʾ/�����������ȼ��ı�
	 * \param hotKey ��ʾ/�����������ȼ�
	 */
	void sigOpenLrcHotKeyChanged(const QString &hotKey);

	/*! ����/��ͣ�ȼ��ı�
	 * \param hotKey ����/��ͣ�ȼ�
	 */
	void sigPauseHotKeyChanged(const QString &hotKey);

	/*! ��һ���ȼ��ı�
	 * \param hotKey ��һ���ȼ�
	 */
	void sigLastHotKeyChanged(const QString &hotKey);

	/*! ��һ���ȼ��ı�
	 * \param hotKey ��һ���ȼ�
	 */
	void sigNextHotKeyChanged(const QString &hotKey);

	/*****************************************************************************
	 �������������Ϣ�ı䷢�͵��ź�
	*****************************************************************************/
	/*! �������ı�
	 * \param fontName ��������
	 */
	void sigFontNameChanged(const QString &fontName);

	/*! ��������С�ı�
	 * \param fontSize �����С
	 */
	void sigFontSizeChanged(const QString &fontSize);

	/*! ������͸ı�
	 * \param fontType �������
	 */
	void sigFontTypeChanged(const QString &fontType);

	/*! ���û�в����ϱ�Ե��ɫ�ı�
	 * \param color ��ɫ
	 */
	void sigNoPlayShangChanged(const QColor &color);

	/*! ���û�в����м���ɫ�ı�
	 * \param color ��ɫ
	 */
	void sigNoPlayZhongChanged(const QColor &color);

	/*! ���û�в����±�Ե��ɫ�ı�
	 * \param color ��ɫ
	 */
	void sigNoPlayXiaChanged(const QColor &color);

	/*! ��ʲ��ź��ϱ�Ե��ɫ�ı�
	 * \param color ��ɫ
	 */
	void sigPlayedShangChanged(const QColor &color);

	/*! ��ʲ��ź��м���ɫ�ı�
	 * \param color ��ɫ
	 */
	void sigPlayedZhongChanged(const QColor &color);

	/*! ��ʲ��ź��±�Ե��ɫ�ı�
	 * \param color ��ɫ
	 */
	void sigPlayedXiaChanged(const QColor &color);

	/*! ���Ĭ����ɫ�ı�
	 * \param color ��ɫ
	 */
	void sigDefaultChoiceColorChanged(const QString &color);

	/*! ��ʻҶȸı�
	 * \param shadow �Ҷ�
	 */
	void sigShadowChanged(const int &shadow);

	/*****************************************************************************
	���ſ���������Ϣ�ı䷢�͵��ź�
	*****************************************************************************/

	/*! �Ƿ������øı�
	 * \param isMute true�����������򲻾���
	 */
    void sigMuteChanged(bool isMute);

	/*! �����Ƿ�ı�
	 * \param volume ����
	 */
	void sigVolumeChanged(const int &volume);

	/*! �������͸ı�
	 * \param playMode ��������
	 */
	void sigPlayModeChanged(enum PlayModeType playMode);

private:
	/*! ���캯��.*/
	GlobalConfig();

	/*! ��������.*/
	~GlobalConfig();

	/*! ����ϵͳ����ע���
	 * \return true����ɹ�������ʧ��
	 */
	bool createRegedit();

	/*! ���泣��������Ϣ
	 * \return true����ɹ�������ʧ��
	 */
	bool saveGeneralSettingsInfo();

	/*! ��������������Ϣ
	 * \return true����ɹ�������ʧ��
	 */
	bool saveDownloadSettingsInfo();

	/*! �����ȼ�������Ϣ
	 * \return true����ɹ�������ʧ��
	 */
	bool saveHotkeysSettingsInfo();

	/*! ������������Ϣ
	 * \return true����ɹ�������ʧ��
	 */
	bool saveLrcSettingsInfo();

	/*! ���沥�ſ���������Ϣ
	 * \return true����ɹ�������ʧ��
	 */
	bool savePlayControlSettingsInfo();

	/*! ���¼��س���������Ϣ
	 * \return true����ɹ�������ʧ��
	 */
	bool reloadGeneralSettingsInfo();

	/*! ���¼�������������Ϣ
	 * \return true����ɹ�������ʧ��
	 */
	bool reloadDownloadSettingsInfo();

	/*! ���¼��ظ��������Ϣ
	 * \return true����ɹ�������ʧ��
	 */
	bool reloadLrcSettingsInfo();

	/*! ���¼����ȼ�������Ϣ
	* \return true����ɹ�������ʧ��
	*/
	bool reloadHotkeySettingsInfo();

	/*! ���¼��ز��ſ���������Ϣ
	* \return true����ɹ�������ʧ��
	*/
	bool reloadPlayControlSettingsInfo();

private:
	static GlobalConfig* m_instance;				  /*!< ȫ�ֶ���*/
	bool m_isReleaseResource;						  /*!< �Ƿ���������Դ*/

	bool m_isGeneralSettingsNeedSave;			   	  /*!< ���ڼ���Ƿ���Ҫ��������*/
	bool m_isDownloadSettingsNeedSave;			   	  /*!< ���ڼ���Ƿ���Ҫ��������*/
	bool m_isLrcSettingsNeedSave;			   		  /*!< ���ڼ���Ƿ���Ҫ��������*/
	bool m_isHotkeySettingsNeedSave;			   	  /*!< ���ڼ���Ƿ���Ҫ��������*/
	bool m_isPlayControlSettingsNeedSave;			  /*!< ���ڼ���Ƿ���Ҫ��������*/

	bool m_isAutoPlayMusic;							  /*!< ����������ʱ�Ƿ��Զ���������*/
	bool m_isAutoRunPlayer;							  /*!< �����Ƿ��Զ����в�����*/
	bool m_isAutoGrettings;							  /*!< ����������ʱ�Ƿ��Զ����к�*/
	bool m_isDefaultPlayer;							  /*!< �Ƿ���Ĭ�ϲ�����*/

	QString m_musicPath;							 /*!< ����·��*/
	QString m_albumPath;							 /*!< ר��·��*/
	QString m_lrcPath;								 /*!< ���·��*/

	QString m_settingsHotKey;						 /*!< ѡ������*/
	QString m_minToTrayHotKey;						 /*!< ��ʾ/����������*/
	QString m_openMinWidgetHotKey;					 /*!< ����ģʽ/��������*/
	QString m_openMusicFileHotKey;					 /*!< �������ļ�*/
    QString m_openMediaWidgetHotKey;				 /*!< ��ʾ/����ý�����*/
	QString m_openListWidgetHotKey;					 /*!< ��ʾ/���ظ����б�*/
	QString m_openLrcHotKey;						 /*!< ��ʾ/����������*/
	QString m_pauseHotKey;							 /*!< ����/��ͣ*/
	QString m_lastHotKey;							 /*!< ��һ��*/
	QString m_nextHotKey;							 /*!< ��һ��*/

	QString m_fontName;								/*!< ��������*/
	QString m_fontSize;								/*!< �����С*/
	QString m_fontType;								/*!< ��������*/
	QColor m_noPlayShang;							/*!< û�в����ϱ�Ե��ɫ*/
	QColor m_noPlayZhong;							/*!< û�в����м���ɫ*/
	QColor m_noPlayXia;								/*!< û�в����±�Ե��ɫ*/
	QColor m_playedShang;							/*!< ���Ź�����ϱ�Ե��ɫ*/
	QColor m_playedZhong;							/*!< ���Ź�����м���ɫ*/
	QColor m_playedXia;								/*!< ���Ź�����±�Ե��ɫ*/
	QString m_defaultChoiceColor;					/*!< Ĭ����ɫ*/
	int m_shadow;									/*!< �Ҷ�*/

	bool m_isMute;									/*!< �Ƿ���*/
	int m_volume;									/*!< ������С*/
	enum PlayModeType m_playMode;					/*!< ����ģʽ*/
};

#endif // GLOBALCONFIG_H
