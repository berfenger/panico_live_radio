/** 
 * @file contentset.h
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

#ifndef CONTENTSET_H
#define CONTENTSET_H

#include <QVector>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDomDocument>
#include "section.h"
#include <iostream>

namespace Radio {

class ContentSet
{
private:
    QString t_name;
    QString t_uuid;
    QVector<Section*> t_sections;
    QString t_basePath;
public:
    ContentSet();
    // Gen attr
    QString getName();
    void setName(QString val);
    QString getUUID();
    void setUUID(QString val);
    QString getBasePath();
    void setBasePath(QString val);
    QVector<Section*> getSections();


    bool addSection(Section *section);

    // Static
    static ContentSet *parseContentSet(QString path);
};

}

#endif // CONTENTSET_H
