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
 * \file   MusicList.h
 * \author chengxuan   787280310@qq.com
 * \date   2015-01-07
 * \brief  �����б�ͷ�ļ���
 * \version 3.0.0
 *
 * \verbatim
 * ��ʷ
 *          3.0.0   ����,
 *          2015-01-07    by chengxuan
 *
 * \endverbatim
 *
 */

#ifndef MUSICLIST_H
#define MUSICLIST_H

/*! \def MUSICLIST_VERSION
 *  �汾���ƺ꣬��Ӧv3.0.0�汾.
 */
#define MUSICLIST_VERSION   0x030000

#include <QTableWidget>
#include <QString>
#include <QPoint>
#include <QColor>

class QContextMenuEvent;
class QMenu;

/*! �����б�
*/
class MusicList : public QTableWidget
{
    Q_OBJECT

public:
	/*! ���캯��
	 *  \param parent ������ָ�룬Ĭ��ΪNULL
     */
    MusicList(QWidget *parent = NULL);

	/*! ��������.*/
    ~MusicList();

public:
	/*! ���õ�ǰ�������ŵ��к�
	 *  \param row �к�
     */
	void setCurrentMusicRow(const int &row);	

protected:
	/*! �麯��������ʵ��contextMenuEvent����
     *  \param event QContextMenuEvent����
     */
    virtual void contextMenuEvent(QContextMenuEvent *event);

signals:
	/*! ��ղ����б����
     */
    void sigPlayListCleanFinshed();

	/*! ���õ�ǰ�������ŵ��к�
	 *  \param row �к�
	 *  \param title ����
     */
    void sigRowSelected(const int &row, const QString &title);

	/*! ����ǰ����
	 *  \param musicName ������
     */
	void sigSharedCurrentMusic(const QString &musicName);

private slots:
	/*! ��ո���
     */
    void handleClearAllMusicList();		

	/*! ɾ����ǰ����
     */
    void handleDelCurrentMusic();	

	/*! ��ȡѡ����
	 *  \param row �к�
     */
    void handleTableClicked(const int &index);	

	/*! ��껬����ÿһ��
	 *  \param row �к�
	 *  \param col �к�
     */
	void handleTableRowEnter(const int &row, const int &col);	

	/*! ��λ����ǰ����
     */
    void handleLocateCurrentMusic();		

	/*! ���浱ǰ�б�
     */
	void handleSaveList();	

	/*! ����ǰ����
     */
	void handleShareCurrentMusic();				

private:
	/*! ���²����б����
     */
    void updateMusicList();				

	/*! ��������ɫ
	 *  \param row �к�
	 *  \param color ��ɫ
     */
	void setRowColor(const int &row, const QColor &color);	

	/*! ��������
     */
	void createUI();				

	/*! �ź����
     */
	void createConnect();	

private:
    QWidget *m_parent;				/*!< ������*/
    int m_row;						/*!< �к�*/
	int m_currentMusicRow;			/*!< ��ǰ�����к�*/
	int m_perviousColorRow;			/*!< ֮ǰ���������ɫ���к�*/
	QMenu *m_rightHandMenu;			/*!< �����б��Ҽ��˵�*/
};

#endif // MUSICLIST_H
