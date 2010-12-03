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

#include "player.h"

Player::Player()
{
    this->t_isPlaying = false;
    this->t_currentlyPlaying = CP_TRACK;
    this->t_current_track = NULL;
    this->t_current_step = NULL;
    this->t_enqueued_track = NULL;
    this->t_trackMedia = new Phonon::MediaObject();
    this->t_stepMedia = new Phonon::MediaObject();
    this->t_trackFader = new Phonon::VolumeFaderEffect();
    this->t_trackFader->setFadeCurve(Phonon::VolumeFaderEffect::Fade9Decibel);
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::AudioOutput *audioOutput2 = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::Path path = Phonon::createPath(this->t_trackMedia, audioOutput);
    path.insertEffect(this->t_trackFader);
    Phonon::createPath(this->t_stepMedia, audioOutput2);
    MainWindow::player = this;
    //MainWindow::mainwindow->getUI().slMusicProgress->setMediaObject(this->t_trackMedia);
    //MainWindow::mainwindow->getTrackSlider()->setMediaObject(this->t_trackMedia);
    //MainWindow::mainwindow->getStepSlider()->setMediaObject(this->t_stepMedia);
    //MainWindow::mainwindow->setTrackSeekSliderMediaObject(this->t_trackMedia);
    if (MainWindow::mainwindow!=NULL) MainWindow::mainwindow->setTrackSeekSliderMediaObject(this->t_trackMedia);
    if (MainWindow::mainwindow!=NULL) MainWindow::mainwindow->setStepSeekSliderMediaObject(this->t_stepMedia);
    connect(this->t_trackMedia, SIGNAL(aboutToFinish()), this, SLOT(currentFinished()));
    connect(this->t_stepMedia, SIGNAL(finished()), this, SLOT(stepFinished()));
    connect(this->t_trackMedia, SIGNAL(currentSourceChanged(Phonon::MediaSource)), this, SLOT(trackSourceChanged(Phonon::MediaSource)));
}

void Player::play(Track *track, int fadeout, bool force)
{
    this->t_enqueued_track = track;
    if (force && fadeout<=0) { // Force and no fadeout
        this->t_trackMedia->clearQueue();
        this->t_trackMedia->setCurrentSource(track->getMediaSource());
        this->t_trackMedia->play();
    } else if (force && fadeout>0) { // Force and fadeout
        this->t_trackMedia->clearQueue();
        this->t_trackMedia->enqueue(track->getMediaSource());
        this->t_trackFader->fadeOut(fadeout);
        QTimer::singleShot(fadeout*2, this, SLOT(fadeOutFinish()));
    } else if (!force && fadeout<=0) { // No force no fadeout
        this->t_trackMedia->clearQueue();
        this->t_trackMedia->enqueue(track->getMediaSource());
        this->t_trackMedia->play();
    } else { // No force  and fadeout
        this->t_trackMedia->clearQueue();
        this->t_trackMedia->enqueue(track->getMediaSource());
        this->t_trackMedia->play();
        //this->t_trackFader->fadeOut(fadeout);
    }
}

void Player::playStep(Track *track, int fadeout)
{
    if (fadeout<=0) {
        this->t_trackMedia->pause();
        this->t_stepMedia->setCurrentSource(track->getMediaSource());
        this->t_stepMedia->play();
        this->t_current_step = track;
        track->setPlayingState(true); this->t_isPlaying = true;
        this->t_currentlyPlaying = CP_STEP;
    } else {
        //this->t_trackMedia->pause();
        this->t_stepMedia->stop();
        this->t_stepMedia->setCurrentSource(track->getMediaSource());
        this->t_stepMedia->stop();
        this->t_current_step = track;
        track->setPlayingState(false); this->t_isPlaying = false;
        this->t_trackFader->fadeOut(fadeout);
        this->t_stepFaderTime = fadeout;
        QTimer::singleShot(fadeout*2, this, SLOT(stepTrackFadeOutFinish()));
    }
}

void Player::setBasePath(QString val)
{
    this->t_basePath = val;
}

void Player::currentFinished() {
    if (this->t_trackMedia->queue().size()<=0) // If nothing enqueued
    emit trackFinished();
}

void Player::stop() {
    if (this->t_current_track!=NULL) this->t_current_track->setPlayingState(false);
    if (this->t_current_step!=NULL) this->t_current_step->setPlayingState(false);
    this->t_trackMedia->stop();
    this->t_stepMedia->stop();
    this->t_isPlaying = false;
}

void Player::trackSourceChanged(Phonon::MediaSource ms) {

    //this->t_trackFader->setVolume(0.0f);
    //this->t_trackFader->fadeIn(2000);
    this->t_trackFader->setVolume(1.0f);
    if (this->t_current_track!=NULL) { this->t_current_track->setPlayingState(false); this->t_isPlaying = false;}
    this->t_current_track = this->t_enqueued_track;
    this->t_current_track->setPlayingState(true); this->t_isPlaying = true;
}

void Player::stepFinished()
{
    this->t_trackMedia->pause();
    this->t_stepMedia->pause();
    this->t_current_step->setPlayingState(false); this->t_isPlaying = false;
    this->t_stepMedia->stop();

    if (this->t_stepFaderTime>0) {
        this->t_trackMedia->pause();
        this->t_trackFader->setVolume(0.0f);
        this->t_trackMedia->pause();
        this->t_trackFader->fadeIn(this->t_stepFaderTime);
    }
    this->t_trackMedia->play();
    this->t_stepFaderTime = 0;
    this->t_currentlyPlaying = CP_TRACK;
    this->t_isPlaying = true;
}

// Called when the track finishes to play the next enqueued track.
void Player::fadeOutFinish()
{
    if (this->t_trackMedia->queue().size()<=0) return; // If nothing enqueued => do nothing
    this->t_current_track->setPlayingState(false); this->t_isPlaying = false;
    this->t_current_track = this->t_enqueued_track;
    this->t_trackFader->setVolume(1.0);
    this->t_trackMedia->setCurrentSource(this->t_trackMedia->queue().first());
    this->t_trackMedia->play();
    this->t_trackMedia->clearQueue();
    this->t_currentlyPlaying = CP_TRACK;
}

// Called when the track fadeout finishes to play a step.
void Player::stepTrackFadeOutFinish()
{
    this->t_trackMedia->pause();
    this->t_trackFader->setVolume(0.0f);
    this->t_stepMedia->play();
    this->t_current_step->setPlayingState(true); this->t_isPlaying = true;
    this->t_currentlyPlaying = CP_STEP;
}

void Player::playPause()
{
    switch(this->t_currentlyPlaying) {
    case CP_STEP:
        if (this->t_isPlaying) {
            this->t_stepMedia->pause();
            this->t_isPlaying = false;
        } else {
            this->t_stepMedia->play();
            this->t_isPlaying = true;
        }
        break;
    case CP_TRACK:
        if (this->t_isPlaying) {
            this->t_trackMedia->pause();
            this->t_isPlaying = false;
        } else {
            this->t_trackMedia->play();
            this->t_isPlaying = true;
        }
        break;
    }
}

