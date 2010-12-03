/** 
 * @file session.h
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

#ifndef SESSION_H
#define SESSION_H

#include <QDomElement>
#include <QVector>
#include <QString>
#include <QStandardItem>
#include "contentset.h"
#include "section.h"
#include "track.h"

namespace Radio {

class Session : public QStandardItem
{
private:
    QString t_name;
    QString t_contentset_name;
    QString t_basePath;
    QVector<Section *> t_sections;
public:
    Session();
    ~Session();

    void setName(QString val);
    void setContentSetName(QString val);
    void setBasePath(QString val);
    QString getName();
    QString getContentSetName();
    QString getBasePath();

    void addSection(Section *val);
    QVector<Section *> getSections();

    // Static
    static Session *parseSession(QDomElement el, ContentSet *cs);
    static Session *parseSessionFromPath(QString path, ContentSet *cs);

};

}

#endif // SESSION_H
