/** 
 * @file main.cpp
 * @author Arturo Casal
 * @date 2010
 * @version v0.1
 *
 * @brief Panico Live Radio Podcast music player for "Panico en el Núcleo" Podcast
 *
 * @note Copyright (C) Arturo Casal
 *
 * @par Licences
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "contentset.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("Panico Live Radio");
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    MainWindow::mainwindow = w;

    w->show();
//return a.exec();

    /*Radio::ContentSet *cs = Radio::ContentSet::parseContentSet("contents.xml");
    int i = 0;
    if (cs!=NULL) i++;
    std::cout << "bu"+i;*/
    //return false;
    return a.exec();

}
