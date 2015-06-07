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
 * \file   MusicList.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2015-01-07
 * \brief  �����б�ʵ���ļ���
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

#include "MusicList.h"
#include "NoFocusDelegate.h"
#include "DBModule.h"
#include "MusicListSaveFormatEntity.h"
#include "Global.h"
#include "TR.h"
#include <QHeaderView>
#include <QContextMenuEvent>
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include <QTextStream>
#ifdef CZ_DEBUG
#include <QDebug>
#endif

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if DBMODULE_VERSION < 0x030000
#error  "DBModule version error."
#endif

#if MUSICLISTSAVEFORMATENTITY_VERSION < 0x030000
#error  "MusicListSaveFormatEntity version error."
#endif

#if GLOBAL_VERSION < 0x030000
#error  "Global version error."
#endif

#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

MusicList::MusicList(QWidget *parent) 
	: QTableWidget(parent), 
	  m_parent(parent),  
	  m_perviousColorRow(0),
	  m_currentMusicRow(-1),
	  m_row(-1)
{
	this->createUI();
	this->createConnect();
}

MusicList::~MusicList()
{
	/*Do nothing.*/
}

void MusicList::handleClearAllMusicList()
{
	if (this->rowCount())
	{
		if (QMessageBox::Yes == QMessageBox::information(this, TR("��Ϣ"),
			TR("�Ƿ�Ҫ��ղ����б�"), QMessageBox::Yes | QMessageBox::No))
		{
			while (this->rowCount())
			{
				removeRow(0);
			}
			emit sigPlayListCleanFinshed();
		}
		/*Else do nothing, and continue.*/
	}
	else
	{
		QMessageBox::information(this, TR("��Ϣ"), TR("��ǰ�����б�Ϊ�գ�"), QMessageBox::Yes);
	}
}

void MusicList::handleDelCurrentMusic()
{
	if (m_row < 0)
	{
		return;
	}
	/*Else do nothing, and continue.*/

	if (this->rowCount())
    {
        QString musicName = this->item(m_row, 1)->text();
		if (QMessageBox::Yes == QMessageBox::information(this, TR("��Ϣ"),
			TR("�Ƿ�ɾ����%1����").arg(musicName), QMessageBox::Yes | QMessageBox::No))
        {
            if (m_row < this->rowCount())
            {
                this->removeRow(m_row);
				emit sigRowSelected(m_row, musicName);//���ݿ���ɾ��
				//���²����б����
                this->updateMusicList();
            }
			/*Else do nothing, and continue.*/
        }
		/*Else do nothing, and continue.*/
    }
	else
	{
		QMessageBox::information(this, TR("��Ϣ"), TR("��ǰ�����б�Ϊ�գ�"), QMessageBox::Yes);
	}
}

void MusicList::updateMusicList()
{
    for (int index = m_row; index < this->rowCount(); ++index)
    {
        QTableWidgetItem *rowItem = this->item(index, 0);
        rowItem->setText(QString::number(index + 1));
    }
}

void MusicList::handleTableClicked(const int &index)
{
    m_row = index;
}

void MusicList::handleTableRowEnter( const int &row, const int &col )
{
	(void)col;
	QTableWidgetItem *item = NULL;

	//��ԭ��һ�е���ɫ
	item = this->item(m_perviousColorRow, 0);
	
	if (item != NULL)
	{
		for (int i = 0; i < this->columnCount(); ++i)
		{
			QTableWidgetItem *item = this->item(m_perviousColorRow, i);
			item->setFont(QFont(TR("΢���ź�"), 10, QFont::Normal));
			item->setBackgroundColor(QColor(0, 0, 0, 0));
		}
	}
	/*Else do nothing, and continue.*/

	//���õ�ǰ����ɫ
	this->setRowColor(row, QColor(5, 184, 204));

	m_perviousColorRow = row;
}

void MusicList::setRowColor( const int &row, const QColor &color )
{
	for (int i = 0; i < this->columnCount(); ++i)
	{
		QTableWidgetItem *item = this->item(row, i);
		item->setFont(QFont(TR("΢���ź�"), 10, QFont::Bold));
		item->setBackgroundColor(color);
	}
}

void MusicList::contextMenuEvent(QContextMenuEvent *event)
{
    m_rightHandMenu->exec(event->globalPos());
    event->accept();
}

void MusicList::handleLocateCurrentMusic()
{
	if (m_currentMusicRow < 0)
	{
		return;
	}
	/*Else do nothing, and continue.*/

	if (m_currentMusicRow == 0)
	{
		this->selectRow(m_currentMusicRow + 1);
	}
	else
	{
		this->selectRow(m_currentMusicRow - 1);
	}
	this->selectRow(m_currentMusicRow);
}

void MusicList::handleSaveList()
{
	QString fileName = QFileDialog::getSaveFileName(this, TR("���沥���б�"),
		TR("�����б�.m3u"), "*.m3u;;*.pls");
	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			file.close();
			return;
		}
		/*Else do nothing, and continue.*/
		QTextStream out(&file);

		QString suffixName = fileName.right(3);//�õ���׺��
		if (suffixName == "m3u" || suffixName == "M3U")
		{
			out << "#EXTM3U\n";			//��ʾһ��M3U�ļ�
		}
		else if (suffixName == "pls" || suffixName == "PLS")
		{
			out << "[playlist]\n";		//��ʾһ��pls�ļ�
		}
		/*Else do nothing, and continue.*/

		QList<MusicListSaveFormatEntity> list;
		if (DBModule::readMusicListSaveFormatEntity(list))
		{
			int i = 0;
			foreach (MusicListSaveFormatEntity entity, list)
			{
				++i;
				QTime time = QTime::fromString(entity.time(), "mm:ss");
				int second = time.minute() * 60 + time.second();

				if (suffixName == "m3u" || suffixName == "M3U")
				{
					QString fileName = entity.fileName();
					QString musicName = "";
					if (fileName.contains('-'))
					{
						musicName = fileName.split('-').at(1).trimmed();
					}
					/*Else do nothing, and continue.*/
					out << "#EXTINF:" << second << "," << musicName
						<< '\n' << entity.filePath() << '\n';
				}
				else if (suffixName == "pls" || suffixName == "PLS")
				{
					QString fileName = entity.fileName();
					QString musicName = "";
					if (fileName.contains('-'))
					{
						musicName = fileName.split('-').at(1).trimmed();
					}
					/*Else do nothing, and continue.*/
					out << "File" << i << "=" << entity.filePath() << '\n'
						<< "Title" << i << "=" << musicName << '\n'
						<< "Length" << i << "=" << second << '\n';
				}
				/*Else do nothing, and continue.*/
			}
			if (suffixName == "pls" || suffixName == "PLS")
			{
				out << "NumberOfEntries=" << i << '\n';
			}
			/*Else do nothing, and continue.*/
		}
		/*Else do nothing, and continue.*/
		file.close();
	}
	/*Else do nothing, and continue.*/
}

void MusicList::setCurrentMusicRow( const int &row )
{
	m_currentMusicRow = row;
}

void MusicList::handleShareCurrentMusic()
{
	if (this->rowCount())
	{
		if (m_row < this->rowCount())
		{
			emit sigSharedCurrentMusic(this->item(m_row, 1)->text());
		}
		/*Else do nothing, and continue.*/
	}
	else
	{
		QMessageBox::information(this, TR("��Ϣ"), TR("��ǰ�����б�Ϊ�գ�"), QMessageBox::Yes);
	}
}

void MusicList::createUI()
{
	//���ô��ڻ�������
	this->resize(380, 360);

	this->setWindowIcon(QIcon(ImagesDir + "CZPlayer.png"));
	this->setWindowTitle(TR("���ֲ����б�"));

	this->setRowCount(0);		//��ʼ��������Ϊ0
	this->setColumnCount(3);		//��ʼ��������Ϊ3

	QStringList headList;
	headList << TR("���") << TR("����") << TR("ʱ��");
	this->setHorizontalHeaderLabels(headList);//����ͷ��Ϣ

	this->horizontalHeader()->setVisible(false);
	this->verticalHeader()->setVisible(false);
	//this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//���������Զ�����������������
	this->horizontalHeader()->resizeSection(0, 30);
	this->horizontalHeader()->resizeSection(1, 270);
	this->horizontalHeader()->resizeSection(2, 65);
	this->horizontalHeader()->setHighlightSections(false);			//�����ʱ���Ա�ͷ�й�������ȡ���㣩
	this->horizontalHeader()->setSectionsClickable(false);			//����Ӧ��굥��
	this->setSelectionMode(QAbstractItemView::SingleSelection);		//����ֻ��ѡ�е���
	this->setSelectionBehavior(QAbstractItemView::SelectRows);		//����ѡ��ϰ��Ϊѡ����
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);		//�������ݲ��ɱ༭
	this->setShowGrid(false);										//���ò���ʾ����
	this->setItemDelegate(new NoFocusDelegate());					//ȥ��ѡ�е�Ԫ�������
	this->setMouseTracking(true);									//����������깦��

	//�Ҽ��˵�
	m_rightHandMenu = new QMenu(this);
	m_rightHandMenu->addAction(QIcon(ImagesDir + "shareMusic.png"), TR("����"), this, SLOT(handleShareCurrentMusic()));
	m_rightHandMenu->addAction(QIcon(ImagesDir + "locateButton.png"), TR("��λ����ǰ���Ÿ���"), this, SLOT(handleLocateCurrentMusic()));
	m_rightHandMenu->addSeparator();
	m_rightHandMenu->addAction(QIcon(ImagesDir + "delCurrentMusic.png"), TR("ɾ����ǰ����"), this, SLOT(handleDelCurrentMusic()));
	m_rightHandMenu->addAction(QIcon(ImagesDir + "clearMusicList.png"), TR("����б�"), this, SLOT(handleClearAllMusicList()));
	m_rightHandMenu->addAction(QIcon(ImagesDir + "saveList.png"), TR("�����б�"), this, SLOT(handleSaveList()));
	m_rightHandMenu->addSeparator();
	m_rightHandMenu->addAction(QIcon(ImagesDir + "quitAction.png"), TR("�ر������б�"), m_parent, SLOT(handleOpenMusicList()));
}

void MusicList::createConnect()
{
	connect(this, SIGNAL(cellPressed(int, int)), this, SLOT(handleTableClicked(int)));
	connect(this, SIGNAL(cellEntered(int, int)), this, SLOT(handleTableRowEnter(int, int)));
}
