// smenu.cpp for jSoundz

/****************************************************************************
   Copyright 2011, drew Roberts. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#include <QtGui>
#include <QGridLayout>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <QToolBar>
#include <QLabel>
#include <QLineEdit>

#include <iostream>
#include "global.h"
#include "smenu.h"



SMenu::SMenu(QWidget *parent)
    : QWidget(parent)
{
  qDebug() << "In SMenu!";
  
  QGridLayout *mgrid = new QGridLayout(this);
  mgrid->setSpacing(2);
  qDebug() << "mgrid made";


  QPushButton *quit = new QPushButton("Quit", this);
  mgrid->addWidget(quit, 0,7);
  connect(quit, SIGNAL(clicked()),
  		this, SLOT(close()));
  		qDebug() << "quit button made";

  QPushButton *update = new QPushButton("Update", this);
  mgrid->addWidget(update, 1,7);
  connect(update, SIGNAL(clicked()),
  		this, SLOT(updateCfg()));
  		qDebug() << "update button made";

  qDebug() << "1. m_soundtm is currently: " << m_soundtm;
  QLabel *title1 = new QLabel("Button Title   ", this);
  m_soundtm = new QString("New Title2");
  mgrid->addWidget(title1, 1, 0, 1, 1);
  edittitle = new QLineEdit(this);
  // edittitle->setText(*m_soundtm);
  mgrid->addWidget(edittitle, 1, 1, 1, 3);
  qDebug() << "F1. m_soundfm is currently: " << m_soundfm;
  QLabel *file1 = new QLabel("Button File", this);
  m_soundfm = new QString("newsong.mp3");
  mgrid->addWidget(file1, 2, 0, 1, 1);
  editfile = new QLineEdit(this);
  mgrid->addWidget(editfile, 2, 1, 1, 3);
  browse = new QPushButton("Browse", this);
  mgrid->addWidget(browse, 2, 7, 1, 1);
  qDebug() << "*title1 qstring made";
  qDebug() << "*file1 qstring made";


  setLayout(mgrid);
  qDebug() << "layout set to mgrid";
  connect( edittitle, SIGNAL(textChanged(QString)), this, SLOT(setSoundTitle(QString)) );
  connect( edittitle, SIGNAL(editingFinished()), this, SLOT(sendSoundTitle()) );
  connect( editfile, SIGNAL(textChanged(QString)), this, SLOT(setSoundFile(QString)) );
  connect( editfile, SIGNAL(editingFinished()), this, SLOT(sendSoundFile()) );
  connect( browse, SIGNAL(clicked()), this, SLOT(getPath()) );


}

void SMenu::setSoundTitle(QString sssound)
{
	qDebug() << "In SMenu::setSoundTitle and passed in: " << sssound;
	qDebug() << "2. Currently, *m_soundtm is: " << *m_soundtm;
	if (sssound != *m_soundtm)
	{
		qDebug() << " sssound is ";
		qDebug() << sssound;
		qDebug() << "3.  *m_soundtm is ";
		qDebug() << *m_soundtm;
		*m_soundtm = sssound;
		qDebug() << "4.  *m_soundtm is now " << *m_soundtm;
		edittitle->setText(*m_soundtm);
		// emit titleChanged(*m_soundtm);
	}
}

void SMenu::sendSoundTitle()
{

	qDebug() << " Now in SMenu::sendSoundTitle ";
	qDebug() << "5.  *m_soundtm is ";
	qDebug() << *m_soundtm;
	qDebug() << "5.1 Sending *m_soundtm which is :" << *m_soundtm;
	edittitle->setText(*m_soundtm);
	// cfgmap[sndt_key] = *msoundtm;
	emit titleChanged(*m_soundtm);

}



// ----------------------

void SMenu::setSoundFile(QString ssfile)
{
	qDebug() << "In SMenu::setSoundFile and passed in: " << ssfile;
	qDebug() << "F2. Currently, *m_soundfm is: " << *m_soundfm;
	if (ssfile != *m_soundfm)
	{
		qDebug() << " ssfile is ";
		qDebug() << ssfile;
		qDebug() << "F3.  *m_soundfm is ";
		qDebug() << *m_soundfm;
		*m_soundfm = ssfile;
		qDebug() << "F4.  *m_soundfm is now " << *m_soundfm;
		editfile->setText(*m_soundfm);
	}
}

void SMenu::sendSoundFile()
{

	qDebug() << " Now in SMenu::sendSoundFile ";
	qDebug() << "F5.  *m_soundfm is ";
	qDebug() << *m_soundfm;
	qDebug() << "F5.1 Sending *m_soundfm which is :" << *m_soundfm;
	editfile->setText(*m_soundfm);
	emit fileChanged(*m_soundfm);

}

void SMenu::getPath()
{

	qDebug() << " Now in SMenu::getPath ";
	QString path;
	
	path = QFileDialog::getOpenFileName(
		this,
		"Choose a file.",
		QString::null,
		QString::null);
		
		if ( ! path.isNull() )
		{
			QFileInfo pathInfo (path );
			*m_soundfm = path;
			*m_soundtm = pathInfo.fileName();
			editfile->setText(*m_soundfm);
			edittitle->setText(*m_soundtm);
		}
		editfile->setFocus();


}

void SMenu::updateCfg()
{

	qDebug() << " Now in SMenu::updateCfg ";
	// is this needed?
/*
	QString path;
	
	path = QFileDialog::getOpenFileName(
		this,
		"Choose a file.",
		QString::null,
		QString::null);
		
		if ( ! path.isNull() )
		{
			QFileInfo pathInfo (path );
			*m_soundfm = path;
			*m_soundtm = pathInfo.fileName();
			editfile->setText(*m_soundfm);
			edittitle->setText(*m_soundtm);
		}
		editfile->setFocus();
*/
}
