/** 
 * @file track.cpp
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

#include "track.h"

namespace Radio {

    Track::Track()
    {
        this->t_n_upd = 0;
        this->t_isOpening = false;
        this->t_isStep = false;
        this->setTrackIcon();
    }

    Track::Track(QString name, QString path)
    {
        this->t_name = name;
        this->t_path = path;
        this->t_n_upd = 2;
        this->setText(this->t_name+": "+this->t_path);
        this->t_isOpening = false;
        this->t_isStep = false;
        this->setTrackIcon();
    }

    Track::Track(QString name, QString path, bool isOpening)
    {
        this->t_name = name;
        this->t_path = path;
        this->t_n_upd = 2;
        this->setText(this->t_name+": "+this->t_path);
        this->t_isOpening = isOpening;
        this->setTrackIcon();
    }

    Track::~Track()
    {

    }

    void Track::setName(QString val)
    {
        this->t_name = val;
        this->t_n_upd++;
        //if (this->t_name.contains("pening")) this->setIcon(QIcon(":/Resources/media-playback-start.png"));
        if (this->t_n_upd>1) this->setText(this->t_name+": "+this->t_path);
    }

    void Track::setPath(QString val)
    {
        this->t_path = val;
        this->t_n_upd++;
        if (this->t_n_upd>1) this->setText(this->t_name+": "+this->t_path);
    }

    void Track::setBasePath(QString val)
    {
        this->t_path = val+this->t_path;
        this->ms = Phonon::MediaSource(this->t_path);
    }

    Phonon::MediaSource Track::getMediaSource()
    {
        return this->ms;
    }

    QString Track::getName()
    {

        return this->t_name;
    }
    QString Track::getPath()
    {
        return this->t_path;
    }

    QString Track::toString()
    {
        QString a(this->getName()+" - "+this->getPath());
        return a;
    }

    QString Track::text()
    {
        QString a(this->getName()+" - "+this->getPath());
        return a;
    }

    void Track::setIsOpening(bool val)
    {
        this->t_isOpening = val;
        this->setTrackIcon();
    }

    void Track::setIsStep(bool val)
    {
        this->t_isStep = val;
        this->setTrackIcon();
    }

    bool Track::isOpening()
    {
        return this->t_isOpening;
    }

    bool Track::isStep()
    {
        return this->t_isOpening;
    }

    void Track::setTrackIcon()
    {
        if (this->t_isOpening) this->setIcon(QIcon(":/Resources/audio_opening.png"));
        else if (this->t_isStep) this->setIcon(QIcon(":/Resources/audio_step.png"));
        else this->setIcon(QIcon(":/Resources/audio_track.png"));
    }

    void Track::setPlayingState(bool val) {
        if (val) this->setIcon(QIcon(":/Resources/media-playback-start.png"));
        else this->setTrackIcon();
    }

    Track *Track::parseTrack(QDomElement el)
    {
        if (el.isNull()) return NULL;
        Track *tr = new Track();
        // Attrs
        QString tmpstr = el.attribute("name", "noname"); tr->setName(tmpstr);
        tmpstr = el.attribute("isOpening", "false"); tr->setIsOpening(tmpstr=="true");
        if (!tr->isOpening()) {
            tmpstr = el.attribute("isStep", "false"); tr->setIsStep(tmpstr=="true");
        } else tr->setIsStep(false);
        tr->setPath(el.text());
        return tr;
    }

}
