// spushbutton.cpp for jSoundz

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


#include <QPushButton>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <QGridLayout>
#include <QMenu>
#include <QMap>
#include <QToolBar>
#include "spushbutton.h"
#include "smenu.h"
#include "global.h"

SPushButton::SPushButton(QWidget *parent)
    : QPushButton(parent)
{
  qDebug() << "Constructor1";	
};

SPushButton::SPushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)// , m_parent(parent)
{
  // qDebug() << "Constructor2";
  QString m_sndf = '\0';
  /*
  qDebug() << "m_sndf initialised to :";
  qDebug() << m_sndf;
  */
  QString m_sndtt = '\0';
  QString m_procid = '\0';
  bool m_playb = false;
  /*
  qDebug() << "m_playb initialised to : ";
  qDebug() << m_playb;
  */
  bool m_sndloop = false;
  /*
  qDebug() << "m_sndloop initialised to : ";
  qDebug() << m_sndloop;
  qDebug() << "m_parent is : ";
  */

  // qDebug() << m_parent;
  

};

SPushButton::SPushButton(const QIcon& icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{
  qDebug() << "Constructor3";	
};

SPushButton::~SPushButton()
{

}

void SPushButton::setSndf(const QString& setsoundfile)
{
	// this will set the sound file to be played
	m_sndf = setsoundfile;
	// qDebug() << "m_sndf set to :";
    // qDebug() << m_sndf;
}

void SPushButton::setSndfKey(const QString& setsoundfilekey)
{
	// this will set the sound file to be played
	m_sndf_key = setsoundfilekey;
	// qDebug() << "m_sndf_key set to :";
    // qDebug() << m_sndf_key;
}
	

void SPushButton::setSndt(const QString& setsoundtitle)
{
	// this will set the sound title of the button
	m_sndtt = setsoundtitle;
	// qDebug() << "m_sndtt set to :";
    // qDebug() << m_sndtt;
}

void SPushButton::setSndtKey(const QString& setsoundtitlekey)
{
	// this will set the sound title of the button
	m_sndtt_key = setsoundtitlekey;
	// qDebug() << "m_sndtt_key set to :";
    // qDebug() << m_sndtt_key;
}

void SPushButton::setProcId(const QString& setprocid)
{
	// this will set the process id the button player
	m_procid = setprocid;
	// qDebug() << "m_procid set to :";
    // qDebug() << m_procid;
}

void SPushButton::setPlayb(const bool& setplayb)
{
	// this will set a flag if the button file is playing or not
	m_playb = setplayb;
	// qDebug() << "m_playb set to :";
    // qDebug() << m_playb;
}


void SPushButton::setSndLoop(const bool& setsndloop)
{
	// this will set a flag if the button file is playing or not
	m_sndloop = setsndloop;
	// qDebug() << "m_sndloop set to :";
    // qDebug() << m_sndloop;
}

QString SPushButton::getSndf()
{
	// this will get the sound file to be played
	// qDebug() << "get m_sndf is :";
    // qDebug() << m_sndf;
    return (m_sndf);
}

QString SPushButton::getSndt()
{
	// this will get the sound title of the button
	// qDebug() << "get m_sndtt is :";
    // qDebug() << m_sndtt;
    return (m_sndtt);
    return (0);
}

QString SPushButton::getProcId()
{
	// this will get the process Id of the button player
	// use to kill the running sound player
	// qDebug() << "get m_procidt is :";
    qDebug() << m_procid;
    return (m_procid);
}



void SPushButton::processButton()
{
	// this should process the button when clicked
	// first, are we in playmode or editmode
	// when in playmode, g_[laymode is true
	// when in editmode, g_playmode is false
	if (g_playmode) {
		//processing for playmode
		// qDebug() << "Processing for playmode. ";
		if (!this->m_playb) {
			/*
			qDebug() << "Trying to play file :";
			qDebug() << "this->m_sndf is now: " << this->m_sndf;
			qDebug() << "this->m_playb is now: " << this->m_playb;
			*/
			// QString doPlayer = "/usr/bin/mpg123";
			QString doPlayer = "/usr/bin/play"; // use sox to play?
			QStringList playMe;
			playMe<<this->m_sndf;
			QProcess *doProcess = new QProcess(this);
			doProcess->start(doPlayer, playMe);
			connect(doProcess, SIGNAL(finished(int)), this, SLOT(updateExit(int)));
			this->setProcId(QString::number(doProcess->pid()));
			/*
			qDebug() << "ProcessID info: ";
			qDebug() << doProcess->pid();
			qDebug() << this->m_procid;
			qDebug() << "Playing now.";
			*/
			this->m_playb = true;
		}
		else {
			/*
			qDebug() << "Trying to stop file :";
			qDebug() << "this->m_sndf is now: " << this->m_sndf;
			qDebug() << "this->m_playb is now: " << this->m_playb;
			*/
			QString doPlayer = "/bin/kill";
			QStringList killMe;
			killMe<<this->getProcId();
			QProcess *doProcess = new QProcess(this);
			doProcess->start(doPlayer, killMe);
			// this->m_playb = false;
		}
	}
	else {
		// processing for editmode
		if (!this->m_playb) {
			// qDebug() << "Processing for editmode. ";
			this->m_playb = true;
			
			
			popmenu = new SMenu();
			popmenu->resize(350, 380);
			// qDebug() << "popmenu had been resized";
			QString mtitle;
			mtitle.append(QString("jSoundz Menu For "));
			mtitle.append(m_sndtt);
  			popmenu->setWindowTitle(mtitle);
  			// qDebug() << "popmenu title set";
  			// qDebug() << "Passing in m_sndtt: " << m_sndtt;
  			popmenu->setSoundTitle(m_sndtt);
  			// qDebug() << "Passing in m_sndf: " << m_sndf;
  			popmenu->setSoundFile(m_sndf);
  			popmenu->show();
  			// qDebug() << "Button text is now: " << m_sndtt << " Button file is now: " << m_sndf;
  			connect( popmenu, SIGNAL(titleChanged(QString)), this, SLOT(setTitleText(QString)) );
  			connect( popmenu, SIGNAL(fileChanged(QString)), this, SLOT(setFileText(QString)) );

		}
		else {
			this->m_playb = false;
		}
	}


}

void SPushButton::newFile()
{
  qDebug() << "running newFile";
}

void SPushButton::newTitle()
{
  qDebug() << "running newTitle";
}


void SPushButton::setTitleText(QString newtitle)
{
/*
qDebug() << "In SPushButton::setTitleText.";
qDebug() << "newtitle passed in is: " << newtitle;
qDebug() << "going in, m_sndtt is: " << m_sndtt;
*/

m_sndtt = newtitle; // is this needed? what is going on?
cfgmap[m_sndtt_key] = newtitle;
// emit titleChanged(newtitle);
setSndt(newtitle);
this->setText(newtitle);
}

// ------------------

void SPushButton::setFileText(QString newfile)
{
/*
qDebug() << "In SPushButton::setFileText.";
qDebug() << "newfile passed in is: " << newfile;
qDebug() << "going in, m_sndf is: " << m_sndf;
*/

m_sndf = newfile; // is this needed? what is going on?
cfgmap[m_sndf_key] = newfile;
emit fileChanged(newfile);
setSndf(newfile);
// this->setText(newfile);
}

// ------------------

void SPushButton::updateExit(int exitCode)
{
qDebug() << "In SPushButton::updateExit.";
qDebug() << "exitCode returned from doProcess is: " << exitCode;
this->m_playb = false;
}
