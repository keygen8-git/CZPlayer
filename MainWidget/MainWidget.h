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
 * \file   MainWidget.h
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-21
 * \brief  ������������ͷ�ļ���
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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

/*! \def MAINWIDGET_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define MAINWIDGET_VERSION   0x030000

#include <vector>
using namespace std;
#include <QWidget>
#include <QString>
#include <QMap>
#include <QPoint>
#include <QUrl>
#include <QSystemTrayIcon>
#include "signal_slot.h"
#include "StatusDefine.h"
#include "MusicInfoEntity.h"

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if STATUSDEFINE_VERSION < 0x030000
#error  "StatusDefine version error."
#endif

#if MUSICINFOENTITY_VERSION < 0x030000
#error  "MusicInfoEntity version error."
#endif

class QPushButton;
class QLabel;
class QMenu;
class QAction;
class QSlider;
class QTimer;
class QPaintEvent;
class QMouseEvent;
class QContextMenuEvent;
class QDragEnterEvent;
class QDropEvent;

class CBasicPlayer;
class Spectrograph;
class MinMusicWidget;
class MusicList;
class MusicListWidget;
class MusicLrc;
class MediaWidget;
class ConfigDialog;
class SharedDialog;
class AboutPanel;
class GlobalHotKey;
class LoadMusicThread;
class LoadMusicThreadEvent;
class AutoStartHandle;
class FileRelationHandle;

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/

/*! ������������
*/
class MainWidget : public QWidget
{
	Q_OBJECT

public:
	 /*! ���캯��
     *  \param argvMusicPath �豸ָ��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
     */
    MainWidget(const char *argvMusicPath, QWidget *parent = NULL);

	/*! ��������.*/
    ~MainWidget();

protected:
	/*! �麯��������ʵ��paintEvent����
     *  \param event QPaintEvent����
     */
	virtual void paintEvent(QPaintEvent *event);

	/*! �麯��������ʵ��mousePressEvent����
     *  \param event QMouseEvent����
     */
	virtual void mousePressEvent(QMouseEvent *event);

	/*! �麯��������ʵ��mouseMoveEvent����
     *  \param event QMouseEvent����
     */
	virtual void mouseMoveEvent(QMouseEvent *event);

	/*! �麯��������ʵ��contextMenuEvent����
     *  \param event QContextMenuEvent����
     */
	virtual void contextMenuEvent(QContextMenuEvent *event);

	/*! �麯��������ʵ��dragEnterEvent����
     *  \param event QDragEnterEvent����
     */
	virtual void dragEnterEvent(QDragEnterEvent *event);

	/*! �麯��������ʵ��dropEvent����
     *  \param event QDropEvent����
     */
	virtual void dropEvent(QDropEvent *event);

signals:
	/*! ��ʾ������
     */
	void sigShowMainWidget();	

	/*! Ƶ�׸ı�
	 * \param vecFrequency Ƶ������
     */
	void sigSpectrumChanged(const vector<float> &vecFrequency);

	/*! �������ļ� ���ò���
	*  \param musicList �����б���Ϣ����
	*/
	void sigStartloadMusic(const QStringList &musicList);

	/*! �϶������ļ������ָ�ʽ�ļ� ���ò���
	*  \param urls ����url�б�
	*/
	void sigStartloadMusic(const QList<QUrl> &urls);

	/*! �������ָ�ʽ�ļ����ļ��� ���ò���
	*  \param strFileOrDir ���ָ�ʽ�ļ����ļ���
	*/
	void sigStartloadMusic(const QString &strFileOrDir);

	/*! �����ݿ��ȡ�����ļ� ���ò���
	*/
	void sigStartloadMusic();

private slots:
	/*! ����ʱ��͸��
     */
	void handleUpdateTime();																	

	/*! �����������
     */
	void handleOpenMinWidget();																

	/*! �������ļ�
     */
	void handleOpenFile();																	

	/*! ��Ӳ����б�
     */
	void handleAddMusicList();																

	/*! ��Ӹ����ļ���
     */
	void handleAddMusicDir();																

	/*! �����ֲ����б�
     */
	void handleOpenMusicList();			

	/*! �򿪸��
     */
	void handleOpenMusicLrc();																

    /*! ��ý�����
     */
    void handleOpenMediaWidget();

    /*! ����ý�����
     */
    void handleHideMediaWidget();

	/*! �������ֲ������б�
     */
	void handleHideMusicList();																

	/*! ����������
     */
	void handleHideMainWidget();																

	/*! ��ʾ������
     */
	void handleShowMusicPanel();																

	/*! ����
     */
	void handleConfigCZPlayer();																

	/*! ����CZPlayer
     */
	void handleAboutCZPlayer();		

	/*! ����Qt
     */
	void handleAboutQt();																	

	/*! ����/��ͣ
     */
	void handleSetPlayPaused();																

	/*! ����
     */
	void handleSetPlay();																	

	/*! ��ͣ
     */
	void handleSetPause();																	

	/*! ֹͣ
     */
	void handleSetStop();																	

	/*! ��һ��
     */
	void handleSetPre();																		

	/*! ��һ��
     */
	void handleSetNext();																	

	/*! ˫��ý���ѡ�в��Ÿ�����
	 *  \param row �����б���
	 *  \param column �����б���
     */
	void handleTableDoubleClicked(const int &row, const int &column);									

	/*! ���Դ
     */
	void handleClearSources();																

	/*! ɾ��ѡ��Դ�����ݿ���Ӧ����
	*  \param row �����б���
	*  \param musicName ��������
     */
	void handleDelSelectSource(const int &row, const QString &musicName);									

	/*! ϵͳ���̼����
	 *  \param activationReason QSystemTrayIcon::ActivationReason����
     */
	void handleTrayIconActivated(QSystemTrayIcon::ActivationReason activationReason);		

	/*! ��С��
     */
	void handleShowMinSize();																

	/*! ��С��������
     */
	void handleMinToTray();																	

	/*! ��ʾ����Ѿ�������Ϣ
     */
	void handleShowLrcLocked();																

	/*! ��ʾ����Ѿ�������Ϣ
     */
	void handleShowLrcUnlocked();															

	/*! �������
     */
	void handleUnlockLrc();																	

	/*! �˳�����
     */
	void handleCloseAllProgress();															

	/*! ��ʱ��
     */
	void handleTimeOut();	

	/*! �Զ�����
	*/
	void handleAutoUpdate();

	/*! ѡ������
     */
	void handleConfigOptions();																

	/*! ��ʾ/����������
     */
	void handleShowHideMainWidget();															

	/*! ����ģʽ/��������
     */
	void handleMinMainWidget();																

	/*! ��������
	 *  \param value ������С
     */
	void handleSetVolume(const int &value);															

	/*! ���þ���
     */
	void handleSetMute();																	

	/*! ��ʾģʽ�˵�
     */
	void handleShowModeMenu();																

	/*! ѭ������
     */
	void handleCyclePlay();																	

	/*! �������
     */
	void handleRandomPlay();																	

	/*! ר����������ź�
	 *  \param musicName ��������
	 *  \param albumUrl ר��Url
     */
	void handleAlbumDownloadFinished(const QString &musicName, const QString &albumUrl);				

	/*! ����ø���
	 *  \param musicName ��������
     */
	void handleSharedCurrentMusic(const QString &musicName);										

	/*! �����겥���б�
     */
	void handleLoadMusicListFinished();														

	/*! ���ز����б����
     */
	void handleLoadMusicListError();	

	/*! ����Ŀ¼�ı�
	 * \param path ����·��
	 */
	void handleMusicDirChanged(const QString &path);

	/*! ר��Ŀ¼�ı�
	 * \param path ר��·��
	 */
	void handleAlbumDirChanged(const QString &path);

	/*! ���Ŀ¼�ı�
	 * \param path ���·��
	 */
	void handleLrcDirChanged(const QString &path);

	/*! ��������
	* \param entity ������Ϣʵ��
	*/
	void handleAddMusic(const MusicInfoEntity &entity);

	/*! ����ר��״̬
     *  \param fileName �����ļ���
	 *  \param albumUrl ר��Url
	 *  \param albumFilePath ר���ļ�·��
	 *  \param status ����״̬
     */
	void handleAlbumDownloadStatus(const QString &fileName, 
								   const QString &albumUrl, 
								   const QString &albumFilePath, 
								   AlbumDownloadStatus status);

	/*! ���ظ��״̬
     *  \param musicName ������
	 *  \param musicArtist ����������
	 *  \param lrcFilePath ����ļ�·��
	 *  \param status ����״̬
     */
	void handleLrcDownloadStatus(const QString &musicName, 
							    const QString &musicArtist, 
								const QString &lrcFilePath, 
								LrcDownloadStatus status);

	/*! ���öԻ���ر�
	 */
	void handleConfigDialogClosed();

	/*! �Ƿ������øı�
	 * \param isMute true�����������򲻾���
	 */
    void handleMuteChanged(bool isMute);

	/*! �����Ƿ�ı�
	 * \param volume ����
	 */
	void handleVolumeChanged(const int &volume);

	/*! �������͸ı�
	 * \param playMode ��������
	 */
	void handlePlayModeChanged(enum PlayModeType playMode);

private c_slots:
	/*! Ƶ�׸ı�
	 * \param vecFrequency Ƶ������
     */
	void handleSpectrumChanged(vector<float> vecFrequency);									

	/*! �������
     */
	void handleFinished();																	

private:
	/*!< ����״̬*/
	enum State
	{
		NoState,			/*!< ��״̬*/
		Play,				/*!< ����*/
		Pause,				/*!< ��ͣ*/
		Stop				/*!< ֹͣ*/
	};

	/*!< ����ģʽ*/
	enum Mode
	{
		CyclePlay,			/*!< ѭ������*/
		RandomPlay			/*!< �������*/
	};

private:
	/*! ��������
     */
	void createUI();		

	/*! �����˵�
     */
	void createMenus();	

	/*! �ź����
     */
	void createConnect();		

	/*! ���������б�����߳�
	*/
	void createMusicloadThread();

	/*! �ͷ���Դ
	*/
	void releaseResource();

	/*! ���沥�ſ���������Ϣ
	*/
	void savePlayControlSettingsInfo();

	/*! ���������̣߳��������������øú���
	*/
	void terminateAllThread();

	/*! �����ʺ���
	*/
	void playGreetings();

	/*! �������
	 * \param lrcFilePath ����ļ�·��
     */
	void resolveLrc(const QString &lrcFilePath);	

	/*! ��ʾר��ͼƬ
     */
	void showAlbumImage();	

	/*! ����map
	 * \param musicName ��������
     */
	void updateMap(const QString &musicName);														

	/*! ����״̬�ı�(���½���)
     */
	void stateChanged();																	

	/*! ѡ�е�ǰ����ý��Դ����
     */
	void rowChanged();																		

	/*! ���ظ����б�
	 * \param filePath �����ļ�·��
     */
	void loadMusicList(const QString &filePath);	

	/*! �жϸø����Ƿ���Ч�������Ч�򲥷�
	 * \param currentMusicName ��ǰ���ŵ���������
	 * \param currentMusicRow ��ǰ���ŵ���������ý�����
	 */
	void findAndPlay(const QString &currentMusicName, const int &currentMusicRow);

	/*! ����
	 * \param currentFilePath ��ǰ���ŵ������ļ�·��
	 * \param currentMusicName ��ǰ���ŵ���������
	 * \param currentMusicRow ��ǰ���ŵ���������ý�����
	 * \param currentMusicTime ��ǰ���ֲ��ŵ�ʱ��
     */
	void play(const QString &currentFilePath, 
			  const QString &currentMusicName, 
			  const int &currentMusicRow, 
			  const QString &currentMusicTime);					

	/*! ���ò���״̬
	 * \param state ����״̬
     */
	void setState(State state);																

	/*! ���ò���ģʽ
	 * \param mode ����ģʽ
     */
	void setMode(Mode mode);																

	/*! ����
     */
	void reset();																			

	/*! ����
     */
	void play();																			

	/*! ����
	 * \param currentFilePath ��ǰ���ŵ������ļ�·��
     */
	void play(const QString &currentFilePath);											

	/*! ��ͣ
     */
	void pause();																			

	/*! �ı乤��Ŀ¼
     */
	void changeWorkDir();		

	/*! ����ר��ͼƬ
	 * \param albumFilePath ר��·��
     */
	void changeAlbumImage(const QString &albumFilePath);

	/*! ����ר��
	 *  \param fileName �����ļ���
	 *  \param musicName ��������
	 *  \param musicArtist ����������
	 *  \param albumFilePath ר���ļ�·��
     */
	void downloadAlbum(const QString &fileName, 
				const QString &musicName, 
				const QString &musicArtist, 
				const QString &albumFilePath);

	/*! ���ظ��
	 *  \param musicName ��������
	 *  \param musicArtist ����������
	 *  \param lrcFilePath ���·��
     */
	void downloadLrc(const QString &musicName, const QString &musicArtist, const QString &lrcFilePath);

private:
	bool m_musicListShowFlag;						/*!< �Ƿ���ʾ�����б�����*/
	bool m_musicDownloadShowFlag;					/*!< �Ƿ���ʾ�����б�����*/

	QPoint m_dragPosition;							/*!< �����*/
	QTimer *m_timer;								/*!< ��ʱ��*/
	QTimer *m_upDateTimer;							/*!< ����ʱ�䶨ʱ��*/

	QList<QThread *> m_albumThreads;				/*!< ר���̼߳���*/
	QList<QThread *> m_lrcThreads;					/*!< ����̼߳���*/

	MinMusicWidget *m_minMusicWidget;				/*!< ���㲥�Ž���*/
	MusicList *m_playList;							/*!< �����б�*/
	MusicListWidget *m_musicListWidget;				/*!< �����б�*/
	MusicLrc *m_lrc;								/*!< ���*/
    MediaWidget *m_mediaWidget;                     /*!< ý�����*/
	ConfigDialog *m_configDialog;					/*!< ���ý���*/
	SharedDialog *m_sharedDialog;					/*!< �������*/
	AboutPanel *m_aboutPanel;						/*!< ����CZPlayer*/
	GlobalHotKey *m_globalHotKey;					/*!< ȫ���ȼ�*/
	LoadMusicThread *m_loadMusicThread;				/*!< �����б�����߳�*/
	LoadMusicThreadEvent *m_loadMusicThreadEvent;	/*!< �����б�����߳��¼�������*/
    AutoStartHandle *m_autoStartHandle;             /*!< ������������*/
    FileRelationHandle *m_fileRelationHandle;       /*!< �ļ�����������*/

	QMap<qint64, QString> m_lrcMap;
	QMap<QString, int> m_mapMusicRows;				/*!< key����������value���к�*/
	QMap<QString, QString> m_mapMusicFilePath;		/*!< key����������value������·��*/

	State m_state;									/*!< ����״̬*/
	Mode m_mode;									/*!< ����ģʽ*/

	CBasicPlayer *m_basicPlayer;					/*!< ��������*/
	Spectrograph *m_spectrograph;					/*!< Ƶ�׻�������*/

	QSlider *m_seekSlider;							/*!< ���ſ�����*/
	QSlider *m_volumeSlider;						/*!< ����������*/
	bool m_isMute;									/*!< �Ƿ���*/

	QLabel *m_albumImage;							/*!< ר��ͼƬ*/
	QLabel *m_timeLabel;							/*!< ��ʾ����ʱ��*/
	QLabel *m_infoLabel;							/*!< ��ʾһЩ��Ϣ*/
	QLabel *m_currentMusicLabel;					/*!< ��ʾ��ǰ���Ÿ���*/

	QAction *m_closeAction;							/*!< �ر�*/
	QAction *m_pauseAction;							/*!< ��ͣ*/
	QAction *m_stopAction;							/*!< ֹͣ*/
	QAction *m_lastAction;							/*!< ��һ��*/
	QAction *m_nextAction;							/*!< ��һ��*/
	QAction *m_minAction;							/*!< ��С��*/
	QAction *m_quitAction;							/*!< �˳�*/
	QAction *m_unlockLrcAction;						/*!< �������*/
	QAction *m_openFileAction;						/*!< ���ļ�*/
	QAction *m_openMusicListAction;					/*!< �򿪲����б�*/
    QAction *m_openMediaWidgetAction;               /*!< ��ý�����*/
	QAction *m_openLrcAction;						/*!< �򿪸��*/
	QAction *m_autoUpdateAction;					/*!< �Զ�����*/
	QAction *m_configAction;						/*!< �����ý���*/
	QAction *m_aboutAction;							/*!< ����*/
	QAction *m_aboutQtAction;						/*!< ����Qt*/
	QAction *m_cycleAction;							/*!< ѭ������*/
	QAction *m_randomAction;						/*!< �������*/

	QMenu *m_trayMenu;								/*!< ϵͳ���̲˵�*/
	QSystemTrayIcon *m_trayIcon;					/*!< ϵͳ����ͼ��*/
	QMenu *m_rightHandMenu;							/*!< �Ҽ��˵�*/
	QMenu *m_playModeMenu;							/*!< ����ģʽ�˵�*/

	QPushButton *m_playButton;						/*!< ����*/	
	QPushButton *m_endButton;						/*!< ֹͣ*/	
	QPushButton *m_preButton;						/*!< ��һ��*/	
	QPushButton *m_nextButton;						/*!< ��һ��*/	
	QPushButton *m_openFileButton;					/*!< ���ļ�*/	
	QPushButton *m_musicListButton;					/*!< ��ʾ�����б�*/	
	QPushButton *m_lrcButton;						/*!< ��ʾ���*/	
	QPushButton *m_showButton;						/*!< ��ʾ���ؽ���*/	
	QPushButton *m_volumeButton;					/*!< ��������*/	
	QPushButton *m_modeButton;						/*!< ����ģʽ*/	

	QString m_musicName;							/*!< ��������*/	
	QString m_musicArtist;							/*!< ������*/	
	QString m_title;								/*!< ����*/	
	QString m_artist;								/*!< ������*/	
	int m_pos;										/*!< �����λ��*/	

	QString m_currentFilePath;						/*!< ��ǰ���Ÿ�����·��*/	
	QString m_currentMusicName;						/*!< ��ǰ���Ÿ���������*/	
	QString m_currentMusicTime;						/*!< ��ǰ���Ÿ�����ʱ��(mm:ss)*/	
	int m_currentMusicRow;							/*!< ��ǰ���Ÿ������к�*/	
	int m_time;										/*!< ��ǰ���Ÿ�����ʱ��(��)*/	

	bool m_isStarupLoadMusic;						/*!< �Ƿ�������ʱ���ز����б�*/	
	QString m_argvMusicPath;						/*!< �����������Ĳ���*/	

	QString m_musicPath;							 /*!< ����·��*/
	QString m_albumPath;							 /*!< ר��·��*/
	QString m_lrcPath;								 /*!< ���·��*/
};

#endif // MAINWIDGET_H
