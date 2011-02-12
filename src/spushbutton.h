// spushbutton.h for jSoundz

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

#ifndef SPUSHBUTTON_H
#define SPUSHBUTTON_H

#include <QPushButton>
#include <QAction>
#include <QActionGroup>
#include <QMenu>
#include <QLabel>
#include <QToolBar>

#include "swall.h"
#include "smenu.h"

class SMenu;

class SPushButton : public QPushButton
{
    Q_OBJECT

public:
    // Constructor
    SPushButton(QWidget *parent = 0);
    SPushButton(const QString &text, QWidget *parent=0);
    SPushButton(const QIcon& icon, const QString &text, QWidget *parent=0);
    
    // Destructor
    ~SPushButton();

    QString m_sndf;
    QString m_sndf_key;
    QString m_sndtt;
    QString m_sndtt_key;
    QString m_procid; // used to stop a file playing.
    bool m_playb;
    bool m_sndloop;
    QWidget m_parent;
    QString *m_sndt;
    QLabel *soundtitle;
    SMenu *popmenu;
    
    void setSndf(const QString&);
    void setSndfKey(const QString&);
    void setSndt(const QString&);
    void setSndtKey(const QString&);
    void setProcId(const QString&);
    void setPlayb(const bool&);
    void setSndLoop(const bool&);
    QString getSndf();
    QString getSndt();
    QString getProcId();
    
private:


protected:
    QAction *chooseFile;
    QAction *setTitle;

public slots:
   void processButton();
   void setTitleText(QString title);
   void setFileText(QString title);
   void updateExit(int exitCode);


private slots:
   void newTitle();
   void newFile();

signals:
	void titleChanged(QString newTitle);
	void fileChanged(QString newFile);

};

#endif
