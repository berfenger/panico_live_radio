/** 
 * @file sessionstatus.cpp
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

#include "sessionstatus.h"

namespace RadioPlayer {

SessionStatus::SessionStatus()
{
    this->t_currentSection = NULL;
    this->t_session = NULL;
    this->t_section_index = 0;
    this->t_isPaused = true;
    this->t_canPlay = false;
    this->t_started = false;
    this->t_player = new Player();
}

SessionStatus::~SessionStatus(){}

bool SessionStatus::setSession(Session *s) {
    if (s==NULL) return false;
    if (s->getSections().size()<=0) return false;
    this->t_section_index = 0;
    this->t_isPaused = true;
    this->t_canPlay = false;
    this->t_started = false;
    this->t_section_status.reset();
    this->t_player->stop();
    this->t_session = s;
    // Reset Section index counters
    this->t_section_status.reset();
    // Set current section/track
    this->t_currentSection = this->t_session->getSections().at(this->t_section_index);
    this->setCurrentTrack(this->t_currentSection->getTrackByIndex(this->t_section_status.getTrackIndex()));
    this->t_canPlay = (this->t_currentSection!= NULL && this->t_currentTrack!=NULL);
    this->t_player->setBasePath(s->getBasePath());
    disconnect(this->t_player, SIGNAL(trackFinished()), this, SLOT(nextTrack()));
    connect(this->t_player, SIGNAL(trackFinished()), this, SLOT(nextTrack()));
    return true;
}

bool SessionStatus::isPaused()
{
    return this->t_isPaused;
}

void SessionStatus::playCurrentTrack()
{
    // Player play with current section fadeout
    this->t_player->play(this->t_currentTrack, this->t_session->getSections().at(this->t_section_index-1)->getFadeOutTime(), true);
}

void SessionStatus::enqueueCurrentTrack()
{
    // Player play with current section fadeout
    this->t_player->play(this->t_currentTrack, 0, false);
}

void SessionStatus::setCurrentTrack(Track *tr)
{
    this->t_currentTrack = tr;
}

void SessionStatus::nextTrack()
{
    this->t_section_status.incrementTrackIndex();
    if (this->t_currentSection->hasTrackByIndex(this->t_section_status.getTrackIndex())) {
        Track *ttmp = this->t_currentSection->getTrackByIndex(this->t_section_status.getTrackIndex());
        this->setCurrentTrack(ttmp);
        this->enqueueCurrentTrack();
    } else {
        this->nextSection();
    }
}

void SessionStatus::start()
{
    if (this->t_isPaused) {
        this->enqueueCurrentTrack();
        this->t_isPaused = false;
    } else {
        this->t_player->playPause();
    }
}

void SessionStatus::nextStep()
{
    if (this->t_currentSection->hasStepByIndex(this->t_section_status.getStepIndex())) {
        Track *ttmp = this->t_currentSection->getStepByIndex(this->t_section_status.getStepIndex());
        this->t_player->playStep(ttmp, this->t_currentSection->getPreStepFadeOutTime());
        this->t_section_status.incrementStepIndex();
    }
}

void SessionStatus::nextSection()
{
    this->t_section_index++;
    if (this->t_section_index>=this->t_session->getSections().size()) return;
    this->t_currentSection = this->t_session->getSections().at(this->t_section_index);
    this->t_section_status.reset();
    this->setCurrentTrack(this->t_currentSection->getTrackByIndex(this->t_section_status.getTrackIndex()));
    this->enqueueCurrentTrack();
}

void SessionStatus::nextSectionByUser()
{
    this->t_section_index++;
    if (this->t_section_index>=this->t_session->getSections().size()) return;
    this->t_currentSection = this->t_session->getSections().at(this->t_section_index);
    this->t_section_status.reset();
    this->setCurrentTrack(this->t_currentSection->getTrackByIndex(this->t_section_status.getTrackIndex()));
    this->playCurrentTrack();
}

void SessionStatus::playPause()
{
    // Player playPause con callback a this->setIsPaused(true/false)
}

void SessionStatus::setIsPaused(bool v)
{
    this->t_isPaused = v;
}

void SessionStatus::stop()
{
    this->t_player->stop();
}


}
