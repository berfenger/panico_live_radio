/** 
 * @file player.h
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

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QErrorMessage>
#include <QTimer>
#include <MediaSource>
#include <MediaObject>
#include <AudioOutput>
#include <Path>
#include <VolumeFaderEffect>
#include "track.h"
#include "mainwindow.h"

#define CP_STEP 1
#define CP_TRACK 2

using namespace Radio;

class Player : public QObject
{
    Q_OBJECT
private:
    QString t_basePath;
    Phonon::MediaObject *t_trackMedia;
    Phonon::MediaObject *t_stepMedia;
    Phonon::VolumeFaderEffect *t_trackFader;
    Track *t_current_track;
    Track *t_enqueued_track;
    Track *t_current_step;
    int t_stepFaderTime;
    int t_currentlyPlaying;
    bool t_isPlaying;
public:
    Player();

    void play(Track *track, int fadeout, bool force);
    void playStep(Track *track, int fadeout);

    void setBasePath(QString val);
    void playPause();
signals:
    void trackFinished();
public slots:
    void currentFinished();
    void stop();
    void trackSourceChanged(Phonon::MediaSource ms);
    void stepFinished();
    void fadeOutFinish();
    void stepTrackFadeOutFinish();
};

#endif // PLAYER_H
