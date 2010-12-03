#-------------------------------------------------
# 
#  @file panicoliveradio.pro
#  @author Arturo Casal
#  @date 2010
#  @version v0.1
#
#  @brief Panico Live Radio Podcast music player for "Panico en el Núcleo" Podcast
#
#  @note Copyright (C) Arturo Casal
#
#  @par Licences
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#
#-------------------------------------------------

QT       += core gui xml phonon

TARGET = panicoliveradio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    contentset.cpp \
    section.cpp \
    track.cpp \
    session.cpp \
    sessionstatus.cpp \
    sectionstatus.cpp \
    uilistitem.cpp \
    listableitem.cpp \
    player.cpp \
    playeruiinterface.cpp

HEADERS  += mainwindow.h \
    contentset.h \
    section.h \
    track.h \
    session.h \
    sessionstatus.h \
    sectionstatus.h \
    uilistitem.h \
    listableitem.h \
    player.h \
    playeruiinterface.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    Resources/media-playback-start.png

RESOURCES += \
    resources.qrc
