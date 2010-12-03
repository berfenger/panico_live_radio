/** 
 * @file section.cpp
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

#include "section.h"


namespace Radio {

    Section::Section(){
        this->t_fadeOutTime = 0;
        this->t_preStepFadeOutTime = 0;
        this->t_opening_track = NULL;
    }

    Section::Section(QString uuid, QString name)
    {
        this->t_uuid = uuid;
        this->t_name = name;
        this->t_fadeOutTime = 0;
        this->t_preStepFadeOutTime = 0;
        this->t_opening_track = NULL;
    }

    // Gen attr
    QString Section::getName()
    {
        return this->t_name;
    }

    void Section::setName(QString val)
    {
        this->t_name = val;
        this->setText("-- "+this->t_name+" --");
    }

    QString Section::getUUID()
    {
        return this->t_uuid;
    }

    void Section::setUUID(QString val)
    {
        this->t_uuid = val;
    }

    void Section::setBasePath(QString val)
    {
        int i;
        if (this->t_opening_track!=NULL) this->t_opening_track->setBasePath(val);
        for(i=0;i<this->t_tracks.size();i++) this->t_tracks.at(i)->setBasePath(val);
        for(i=0;i<this->t_steps.size();i++) this->t_steps.at(i)->setBasePath(val);
    }


    // Fade out
    bool Section::hasFadeOutEffect()
    {
        if (this->t_fadeOutTime>0) return true; else return false;
    }

    int Section::getFadeOutTime()
    {
        return this->t_fadeOutTime;
    }

    void Section::setFadeOutTime(int val)
    {
        this->t_fadeOutTime = val;
    }

    bool Section::hasPreStepFadeOutEffect()
    {
        if (this->t_preStepFadeOutTime>0) return true; else return false;
    }

    int Section::getPreStepFadeOutTime()
    {
        return this->t_preStepFadeOutTime;
    }

    void Section::setPreStepFadeOutTime(int val)
    {
        this->t_preStepFadeOutTime = val;
    }

    // Tracks/Steps
    bool Section::setOpeningTrack(Track *val)
    {
        this->t_opening_track = val;
        return true;
    }

    bool Section::addTrack(Track *val)
    {
        this->t_tracks.append(val);
        return true;
    }

    bool Section::addStep(Track *val)
    {
        this->t_steps.append(val);
        return true;
    }


    // Player tracks
    Track *Section::getTrackByIndex(int index)
    {
        if (this->t_opening_track != NULL && index == 1) {
            return this->t_opening_track;
        } else if (this->t_opening_track != NULL && index > 1 && this->t_tracks.size()>0) {
            return this->t_tracks.at((index-2)%this->t_tracks.size());
        } else if (this->t_opening_track == NULL && index > 0 && this->t_tracks.size()>0) {
            return this->t_tracks.at((index-1)%this->t_tracks.size());
        }
        return NULL;
    }

    bool Section::hasTrackByIndex(int index)
    {
        if (this->t_opening_track != NULL && index == 1) {
            return true;
        } else if (this->t_opening_track != NULL && index > 1 && this->t_tracks.size()>0) {
            return true;
        } else if (this->t_opening_track == NULL && index > 0 && this->t_tracks.size()>0) {
            return true;
        }
        return false;
    }

    QVector<Track*> Section::getTrackList()
    {
        QVector<Track*> tracks;
        int i;

        if (this->t_opening_track!=NULL) tracks.append(this->t_opening_track);
        for(i=0;i<this->t_tracks.size();i++) tracks.append(this->t_tracks.at(i));
        return tracks;
    }

    int Section::getTrackIndex(Track *val)
    {
        int i;
        if (this->t_opening_track!=NULL && this->t_opening_track == val) return 1;
        for(i=0;this->t_tracks.size();i++) {
            if (this->t_tracks.at(i)==val) {
                if (this->t_opening_track!=NULL) return i+2;
                else return i+1;
            }
        }
        return -1;
    }

    // Player steps
    bool Section::containSteps()
    {
        if (this->t_steps.size()>0) return true; else return false;
    }

    Track *Section::getStepByIndex(int index)
    {
        if (index>0 && this->t_steps.size()>=index) return this->t_steps.at(index-1); else return NULL;
    }

    bool Section::hasStepByIndex(int index)
    {
        if (index>0 && this->t_steps.size()>=index) return true; else return false;
    }

    QVector<Track*> Section::getStepList()
    {
        QVector<Track*> steps;
        int i;

        for(i=0;i<this->t_steps.size();i++) steps.append(this->t_steps.at(i));
        return steps;
    }

    int Section::getStepIndex(Track *val)
    {
        int i;
        for(i=0;this->t_steps.size();i++) {
            if (this->t_steps.at(i)==val) {
                return i+1;
            }
        }
        return -1;
    }

    // Others

    void Section::toStringList(QStringList *list)
    {
        int i;
        if (this->t_opening_track!=NULL) list->append(this->t_name+" :o: "+this->t_opening_track->toString());
        for(i=0;i<this->t_tracks.size();i++) {
            list->append(this->t_name+" :t: "+this->t_tracks.at(i)->toString());
        }
        for(i=0;i<this->t_steps.size();i++) {
            list->append(this->t_name+" :s: "+this->t_steps.at(i)->toString());
        }
    }

    // Static

    Section *Section::parseSection(QDomElement el) {
        if (el.isNull()) return NULL;
        Section *sc = new Section();
        // Attrs
        QString tmpstr = el.attribute("uuid", "nouuid"); sc->setUUID(tmpstr);
        tmpstr = el.attribute("name", "noname"); sc->setName(tmpstr);
        tmpstr = el.attribute("fadeOut", "0"); sc->setFadeOutTime(tmpstr.toInt());
        tmpstr = el.attribute("preStepFadeOut", "0"); sc->setPreStepFadeOutTime(tmpstr.toInt());
        // Tracks
        int nchilds = el.childNodes().size();
        QDomNode n = el.firstChild();
        while(!n.isNull()) {
            QDomElement e = n.toElement();
            if(!e.isNull()) {
                // Cada hijo (track)
                Track *stmp = Track::parseTrack(e);
                /*if (stmp!=NULL && e.attribute("isStep", "false")=="true") sc->addStep(stmp);
                else if (stmp!=NULL && e.attribute("isOpening", "false")=="false" && nchilds>1) sc->addTrack(stmp);
                else if (stmp!=NULL && (e.attribute("isOpening", "false")=="true" || nchilds==1)) sc->setOpeningTrack(stmp);*/
                if (stmp!=NULL && e.attribute("isStep", "false")=="true") sc->addStep(stmp);
                else if (stmp!=NULL && !stmp->isOpening() && nchilds>1) sc->addTrack(stmp);
                else if (stmp!=NULL && (stmp->isOpening() || nchilds==1)) sc->setOpeningTrack(stmp);
            }
            n = n.nextSibling();
        }
        return sc;
    }

}
