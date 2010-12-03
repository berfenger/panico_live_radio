/** 
 * @file contentset.cpp
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

#include "contentset.h"

namespace Radio {

ContentSet::ContentSet()
{
}

bool ContentSet::addSection(Section *section) {
    this->t_sections.append(section);
    return true;
}

QString ContentSet::getName()
{
    return this->t_name;
}

void ContentSet::setName(QString val)
{
    this->t_name = val;
}

QString ContentSet::getBasePath()
{
    return this->t_basePath;
}

void ContentSet::setBasePath(QString val)
{
    this->t_basePath = val;
    int i;
    for(i=0;i<this->t_sections.size();i++) this->t_sections.at(i)->setBasePath(val);
}

QString ContentSet::getUUID()
{
    return this->t_uuid;
}

void ContentSet::setUUID(QString val)
{
    this->t_uuid = val;
}

QVector<Section*> ContentSet::getSections()
{
    return this->t_sections;
}

// Static
ContentSet *ContentSet::parseContentSet(QString path) {
    QFile xmlfile(path);
    QDomDocument doc("mydocument");

    QFileInfo finfo(path);

    if (!xmlfile.open(QIODevice::ReadOnly))
        return NULL;
    if (!doc.setContent(&xmlfile)) {
        xmlfile.close();
        return NULL;
    }
    xmlfile.close();

    // Parse XML
    QDomElement el = doc.documentElement();
    if (el.isNull()) return NULL;
    if (el.tagName()!="contentset") return NULL;
    ContentSet *cs = new ContentSet;
    // Attrs
    QString tmpstr = el.attribute("name", "noname"); cs->setName(tmpstr);
    tmpstr = el.attribute("uuid", "nouuid"); cs->setUUID(tmpstr);
    // Sections
    QDomNode n = el.firstChild();
    while(!n.isNull()) {
         QDomElement e = n.toElement();
         if(!e.isNull()) {
             // Cada hijo (section)
             Section *stmp = Section::parseSection(e);
             if (stmp!=NULL) cs->addSection(stmp);
         }
         n = n.nextSibling();
     }
    cs->setBasePath(finfo.dir().absolutePath()+"/");


    return cs;
}

}
