/** 
 * @file section.h
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

#ifndef SECTION_H
#define SECTION_H

#include <QString>
#include <QVector>
#include <QDomDocument>
#include <QStringList>
#include <QStandardItem>
#include "track.h"
#include "listableitem.h"

#define SECTION_ONETRACK 1
#define SECTION_NORMAL 0

namespace Radio {

class Section : public ListableItem
{
private:
    // Gen attr
    QString t_uuid;
    QString t_name;
    // Fade out
    bool t_hasFadeOutEffect;
    int t_fadeOutTime;
    bool t_hasPreStepFadeOutEffect;
    int t_preStepFadeOutTime;
    // Tracks/Steps
    Track *t_opening_track;
    QVector<Track*> t_tracks;
    QVector<Track*> t_steps;
public:
    Section();
    Section(QString uuid, QString name);
    // Gen attr
    QString getName();
    void setName(QString val);
    QString getUUID();
    void setUUID(QString val);
    void setBasePath(QString val);

    // Fade out
    bool hasFadeOutEffect();
    int getFadeOutTime();
    void setFadeOutTime(int val);

    bool hasPreStepFadeOutEffect();
    int getPreStepFadeOutTime();
    void setPreStepFadeOutTime(int val);

    // Tracks/Steps
    bool setOpeningTrack(Track *val);
    bool addTrack(Track *val);
    bool addStep(Track *val);


    // Player tracks
    Track *getTrackByIndex(int index);
    bool hasTrackByIndex(int index);
    QVector<Track*> getTrackList();
    int getTrackIndex(Track *val);
    // Player steps
    bool containSteps();
    Track *getStepByIndex(int index);
    bool hasStepByIndex(int index);
    QVector<Track*> getStepList();
    int getStepIndex(Track *val);

    void toStringList(QStringList *list);

    // Static
    static Section *parseSection(QDomElement el);

};

}


#endif // SECTION_H
