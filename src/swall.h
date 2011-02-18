// swall.h for jSoundz

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

#ifndef SWALL_H
#define SWALL_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QMap>
#include <QVector>

#include "spushbutton.h"


class Swall : public QWidget
{
  Q_OBJECT

  public:
    Swall(QWidget *parent = 0);
    QPushButton playmode;
    QPushButton editmode;
    //QString sndt_key;
    //QString sndf_key;


  public slots:
    void processplaymode();
    void processeditmode();
    void saveconfig();
    void loadconfig();
    void help();
    void about();
    void notes();
  
  signals:
    void sbutconfig(QString butid, QString sndt, QString sndf);

};

#endif
