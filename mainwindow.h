/** 
 * @file mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QErrorMessage>
#include <QStringListModel>
#include <QDir>
#include <QFileInfoList>
#include <SeekSlider>
#include "contentset.h"
#include "section.h"
#include "sessionstatus.h"
#include "player.h"
#include "uilistitem.h"

namespace Ui {
    class MainWindow;
}

class Player;
namespace RadioPlayer {
    class SessionStatus;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //friend class Player;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent * event);
    static MainWindow *mainwindow;
    static Player *player;
    void setTrackSeekSliderMediaObject(Phonon::MediaObject *mo);
    void setStepSeekSliderMediaObject(Phonon::MediaObject *mo);
private:
    Ui::MainWindow *ui;
    RadioPlayer::SessionStatus *t_sess_status;

public slots:
    void closeApp();
    void selectFile();
    void listaSelect(QModelIndex index);
    void sessionListSelect(QModelIndex index);
};

#endif // MAINWINDOW_H
