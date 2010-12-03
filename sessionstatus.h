/** 
 * @file sessionstatus.h
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

#ifndef SESSIONSTATUS_H
#define SESSIONSTATUS_H

#include <QObject>
#include "contentset.h"
#include "session.h"
#include "sectionstatus.h"
#include "player.h"

using namespace Radio;

class Player;

namespace RadioPlayer {

class SessionStatus : public QObject
{
    Q_OBJECT
private:
    Radio::Session *t_session;
    Radio::Section *t_currentSection;
    Radio::Track *t_currentTrack;
    RadioPlayer::SectionStatus t_section_status;
    Player *t_player;
    int t_section_index;
    bool t_isPaused;
    bool t_canPlay;
    bool t_started;

    void playCurrentTrack();
    void enqueueCurrentTrack();
    void setCurrentTrack(Track *tr);
public:
    explicit SessionStatus();
    ~SessionStatus();
    bool setSession(Session *s);
    bool isPaused();

public slots:
    void nextTrack();
    void start();
    void nextStep();
    void nextSection();
    void nextSectionByUser();
    void playPause();
    void setIsPaused(bool v);
    void stop();
};

}

#endif // SESSIONSTATUS_H
