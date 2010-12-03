/** 
 * @file track.h
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

#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QDomDocument>
#include <QStandardItem>
#include <MediaSource>
#include "listableitem.h"

namespace Radio {

    class Track : public ListableItem
{
    //Q_OBJECT
private:
    QString t_name;
    QString t_path;
    bool t_isOpening;
    bool t_isStep;
    int t_n_upd;
    void setTrackIcon();
    Phonon::MediaSource ms;
public:
    Track();
    Track(QString name, QString path);
    Track(QString name, QString path, bool isOpening);
     ~Track();

    void setName(QString val);
    void setPath(QString val);
    void setBasePath(QString val);
    void setIsOpening(bool val);
    void setIsStep(bool val);
    Phonon::MediaSource getMediaSource();

    QString getName();
    QString getPath();
    bool isOpening();
    bool isStep();

    QString toString();
    QString text();

    // Static
    static Track *parseTrack(QDomElement el);

//public slots:
    void setPlayingState(bool val);
};

}

#endif // TRACK_H
