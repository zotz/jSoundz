// smenu.h for jSoundz

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

#ifndef SMENU_H
#define SMENU_H

#include <QWidget>
#include <QPushButton>
// #include <QGridLayout>
#include <QString>
#include <QVector>
#include <QDialog>
#include <QLineEdit>

#include "spushbutton.h"

// QString passme = "passme";

class SMenu : public QWidget
{
  Q_OBJECT

  public:
    //Constructor
    SMenu(QWidget *parent = 0);

   // Destructor
   // ~SMenu();
   
   QLabel *soundtitle;
   QLineEdit *editfile;  
   QLineEdit *edittitle; 
   QPushButton *browse;
   QPushButton *update;
    
    
  public slots:
    void setSoundTitle(QString sssound);
    void sendSoundTitle();
    void setSoundFile(QString ssfile);
    void sendSoundFile();
    void getPath();
    void updateCfg();

signals:
	void titleChanged(QString newSound);
	void fileChanged(QString newTitle);

private:
	QString *m_soundtm;
	QLabel m_soundtlm;
	QString *m_soundfm;
	QLabel m_soundflm;

};

#endif
