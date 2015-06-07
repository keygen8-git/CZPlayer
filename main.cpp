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
 * \file   main.cpp
 * \author chengxuan   787280310@qq.com
 * \date   2014-12-21
 * \brief  ������ڡ�
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

#include "MainWidget.h"
#include "TR.h"
#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QString>
#include <QTranslator>
#include "qtsingleapplication.h"

/*****************************************************************************
  �����������汾�Ķ�Ӧ
 *****************************************************************************/
#if TR_VERSION < 0x030000
#error  "TR version error."
#endif

/*****************************************************************************
  ����ȫ�ֱ���
 *****************************************************************************/
const QString AppName = "CZPlayer";								/*!< Ӧ�ó�����*/
const QString QssFilePath = ":/qss/CZPlayer.qss";           	/*!< qss�ļ�·��*/

/*! \fn   main ������ں���
    \param argc ��������
    \param argv ָ������ַ�����ָ��
    \return �����˳�����0�����򷵻ط�0ֵ
    */
int main(int argc, char *argv[])
{
#if 1
    QtSingleApplication app(argc, argv);
	if (app.isRunning())
	{
		return EXIT_SUCCESS;
	}
	/*Else do nothing, and continue.*/
#else
    QApplication app(argc, argv);
#endif
	app.setApplicationName(AppName);

	//��������qss��ʽ��
	QFile file(QssFilePath);
	file.open(QFile::ReadOnly);
    app.setStyleSheet(TR(file.readAll()));
	file.close();

	//��ʾ������
    MainWidget mainWidget(argv[1]);
    mainWidget.show();
	int result = app.exec();
	return result;
}
