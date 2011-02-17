// swall.cpp for jSoundz

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
#include <QMap>
#include <QDebug>
#include <qtoolbar.h>
#include <iostream>
#include "swall.h"
#include "spushbutton.h"
#include "global.h"


Swall::Swall(QWidget *parent)
    : QWidget(parent)
{
//sndt_key = new QString("");
//sndf_key = new QString("");

  // think I don't need playplay due to g_playmode
  // m_playplay = true; // this does not seem to have the right or any effect. why?
/*
  QMap<QString, QString>::const_iterator ii = cfgmap.constBegin();
  while (ii != cfgmap.constEnd()) {
      qDebug() << ii.key() << ": " << ii.value();
      ++ii;
  }
*/

  QGridLayout *grid = new QGridLayout(this);
  grid->setSpacing(2);

  QPushButton *quit = new QPushButton("Quit", this);
  grid->addWidget(quit, 11,0);
  connect(quit, SIGNAL(clicked()),
  		qApp, SLOT(quit()));

  QPushButton *savecfg = new QPushButton("Save Config", this);
  grid->addWidget(savecfg, 11,2);
  connect(savecfg, SIGNAL(clicked()),
  		this, SLOT(saveconfig()));

  QPushButton *loadcfg = new QPushButton("Load Config", this);
  grid->addWidget(loadcfg, 11,3);
  connect(loadcfg, SIGNAL(clicked()),
  		this, SLOT(loadconfig()));


  QPushButton *playmode = new QPushButton("Play Mode", this);
  playmode->setCheckable(1);
  playmode->setChecked(1);
  grid->addWidget(playmode, 11,5);
  connect(playmode, SIGNAL(clicked()),
  		this, SLOT(processplaymode()));

	
  QPushButton *editmode = new QPushButton("Edit Mode", this);
  editmode->setCheckable(1);
  grid->addWidget(editmode, 11,6);
  connect(editmode, SIGNAL(clicked()),
  		this, SLOT(processeditmode()));


  QButtonGroup* buttonGroup = new QButtonGroup(this) ;
  buttonGroup->addButton(playmode);
  buttonGroup->addButton(editmode);


  QPushButton *help = new QPushButton("Help", this);
  grid->addWidget(help, 11,7);
  connect(help, SIGNAL(clicked()),
  		this, SLOT(help()));
		
  QPushButton *about = new QPushButton("About", this);
  grid->addWidget(about, 11,8);
  connect(about, SIGNAL(clicked()),
  		this, SLOT(about()));


  QPushButton *notes = new QPushButton("Notes", this);
  grid->addWidget(notes, 11,9);
  connect(notes, SIGNAL(clicked()),
  		this, SLOT(notes()));

  QPalette pal;
  pal.setColor( QPalette::Active, QPalette::Button, "Blue" );
  pal.setColor( QPalette::Active, QPalette::ButtonText, "Yellow" );
  pal.setColor( QPalette::Inactive, QPalette::Button, "Cyan" );
  pal.setColor( QPalette::Inactive, QPalette::ButtonText, "Green" );



  // QButtonGroup* gridGroup = new QButtonGroup(this) ;
  // gridGroup->setExclusive(0);
  for (int row=0; row<10; row++) {
    for (int col=0; col<10; col++) {
      SPushButton *btn = new SPushButton("", this);
      // qDebug() << "Making SPushButtons for the grid.";
      btn->setFixedSize(115, 80);
      btn->setCheckable(1);
      // btn->setAutoDefault(false);
      btn->setPalette( pal );
      QString sndt_key;
      QString some_sndt;
      // sndt_key = new QString("");
      some_sndt.append(QString("Cut::R"));
      some_sndt.append(QString("%1").arg(row));
      some_sndt.append(QString(":C"));
      some_sndt.append(QString("%1").arg(col));
      sndt_key.append(QString("sndt"));
      sndt_key.append(QString("%1").arg(row));
      sndt_key.append(QString("%1").arg(col));
      some_sndt = cfgmap[sndt_key];
      QString sndf_key;
      QString some_sndf;
      // sndf_key = new QString("");
      some_sndf.append(QString("cut_r"));
      some_sndf.append(QString("%1").arg(row));
      some_sndf.append(QString("_c"));
      some_sndf.append(QString("%1").arg(col));
      some_sndf.append(QString(".mp3"));
      sndf_key.append(QString("sndf"));
      sndf_key.append(QString("%1").arg(row));
      sndf_key.append(QString("%1").arg(col));
      some_sndf = cfgmap[sndf_key];
      btn->setSndf(some_sndf);
      btn->setSndfKey(sndf_key);
      btn->setSndt(some_sndt);
      btn->setSndtKey(sndt_key);
      btn->setProcId("00");
      btn->setText(btn->getSndt());
      btn->setPlayb(false);
      btn->setSndLoop(false);
      connect(btn, SIGNAL(clicked()),
  		btn, SLOT(processButton()));
      grid->addWidget(btn, row, col);

    }
  }



  setLayout(grid);

}


void Swall::saveconfig()
{
  // seems to work
  qDebug() << "Save Config Button was clicked.";
  QFile file(cfgfile);
  qDebug() << "QFile set to: " << cfgfile;
  if (file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
  	qDebug() << "if file open bit";
  	QTextStream gout(&file);
  QMap<QString, QString>::const_iterator ii = cfgmap.constBegin();
  while (ii != cfgmap.constEnd()) {
      qDebug() << ii.key() << " " << ii.value();
     gout << ii.key() << " " << ii.value() << "\n";
      ++ii;
  }
  	file.close();
  }
  else
  {
  	// we have a problem, config file was not opened
  	qDebug() << "Could not open config file!. Try again.";
  	return;
  }
}

void Swall::loadconfig()
{
  // we shall see
  qDebug() << "Load Config Button was clicked.";
  QMessageBox::about(this,"Load Config",
    "* This is going to take some refiguring. For now just load a config via the "
    "command line switch: '-c' ...\n");

/*
  QString path;
	
  path = QFileDialog::getOpenFileName(
  	this,
	"Choose a Config file to load.",
	QString::null,
	QString::null);
		
	if ( ! path.isNull() )
	{
		QFileInfo pathInfo (path );
		cfgfile = path;

  		QString parmm;
		QStringList words;
  	

  		QFile file(cfgfile);
  		qDebug() << "QFile set to: " << cfgfile;
  		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  		{
  			qDebug() << "if file open bit";
  			QTextStream gin(&file);
  			while (!gin.atEnd())
  			{
  			  QString line = gin.readLine();
  			  // process_line(line);
  			  QStringList words = line.split(" ");
  			  cfgmap.insert(words[0], words[1]);

  			}
  			file.close();
  		}
  		else
  		{
  			// we have a problem, config file was not opened
  			qDebug() << "Could not open config file!. Try again.";
  			return;
  		}

		QMap<QString, QString>::const_iterator ii = cfgmap.constBegin();
		while (ii != cfgmap.constEnd()) {
		    qDebug() << ii.key() << ": " << ii.value();
		    ++ii;
		}

	}
*/
}


void Swall::processplaymode()
{
  // done
  qDebug() << "Play Mode Button was clicked.";
  g_playmode = true;
  qDebug() << "g_playmode set to true in processplaymode." << g_playmode ;
}

void Swall::processeditmode()
{
  // done
  qDebug() << "Edit Mode Button was clicked.";
  g_playmode = false;
  qDebug() << "g_playmode set to false in processeditmode." << g_playmode ;
}

void Swall::help()
{
  // a little bit of help

  QMessageBox::about(this,"Help Me",
    "This button is meant to help you.\n"
    "Later on mabeezo.\n");

}

void Swall::about()
{
  // a little bit of help
  QMessageBox::about(this,"About jSoundz",
    "This is your Qt and jack SoundWall.\n"
    "jSoundz version 0.01, Copyright 2011 drew Roberts.\n"
    "jSoundz comes with ABSOLUTELY NO WARRANTY.\n"
    "This is Free Software and you are welcome to redistribute it \n"
    "under certain conditions. See the LICENSE file. GPL v2 or later.\n");
}

void Swall::notes()
{
  // a little bit of help
  QMessageBox::about(this,"Notes for jSoundz",
    "* I think I should be able to get rid of this play and edit button thing and replace "
    "it by a right click popup menu but I can't seem to figure out how.\n"
    "\n"
    "* I think I will want to use QSettings to store and load the applications "
    "settings and preferences.\n");
}


