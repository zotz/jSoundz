// main.cpp for jSoundz

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



#include <QDesktopWidget>
#include <QApplication>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QIODevice>


#include "swall.h"
#include "spushbutton.h"
#include "global.h"

/*
hmm, well, you're creating the Widget on the stack, not on the heap
<remon> not sure if that messes things up too
<mabeezo> how would i do the alternative?
<remon> Swall* window = new Swall();
<remon> window->setWindowtitle(blah)
<remon> window->show();
<remon> declare the center function as
<remon> void center(QWidget* widget);
<mabeezo> you talking main.cpp now?
<remon> yes
<mabeezo> the center function does not matter to me
<remon> so everytime you want to call a function of window it's not with the dot operator but with the arrow operator
<remon> *widget
*/
QMap<QString, QString> cfgmap;
QString cfgfile;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv); 

  qDebug() << "argc is: " << argc;
  qDebug() << "argv is: " << argv;
  qDebug() << "g_playmode is: " << g_playmode;
  for (int nArg=0; nArg < argc; nArg++)
  	qDebug() << nArg << " " << argv[nArg];
  	
  // QMap<QString, QString> cfgmap;
  QString parmm;
  // QString cfgfile;
  QStringList words;
  	
  	if (argc == 3)
  	{
  		parmm = argv[1];
  		qDebug() << "parmm is now: " << parmm;
  		if (parmm == "-c")
  		{
  			cfgfile = argv[2];
  		}
  		else
  		{
  			// nothing
  			qDebug() <<"We have a problem. Wrong parameter passed in?";
  			return 1;
 		}
	}
  	else
  	{
  		cfgfile = "jsoundz.cfg";
  	}
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
  	  int word_count = 0;
  	  //QString word1 = QString(NULL);
	  QString word1 = QString("");
  	  foreach(QString word, words)
  	  {
  	  	if (word_count > 0)
  	  	{
  	  		word1 = word1.append(word);
  	  		word1 = word1.append(" ");
  	  		qDebug() << "word is "<<word << "word1 is " << word1;
 	  	}
 	  	word_count++;
 	  }
 	  word1 = word1.trimmed();
 	  qDebug() << "Inserting to cfgmap: words[0] : " << words[0] << " and word1 : " << word1;
  	  cfgmap.insert(words[0], word1);
/*
  	  qDebug() << "line is: "<< line;
  	  qDebug() << "words(0) is: "<< words[0];
  	  qDebug() << "words(1) is: "<< words[1];
*/
  	}
  	file.close();
  }
  else
  {
  	// we have a problem, config file was not opened
  	qDebug() << "Could not open config file!. Try again.";
  	return 1;
  }


  Swall* window = new Swall();

  window->setWindowTitle("jSoundz a (jack?) SoundWall");
  window->show();

  return app.exec();
}
