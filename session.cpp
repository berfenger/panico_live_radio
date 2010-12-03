/** 
 * @file session.cpp
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

#include "session.h"

namespace Radio {


Session::Session()
{
}

Session::~Session()
{

}

void Session::setName(QString val)
{
    this->t_name = val;
    this->setText(this->t_name);
}

void Session::setContentSetName(QString val)
{
    this->t_contentset_name = val;
}

QString Session::getName()
{
    return this->t_name;
}

QString Session::getContentSetName()
{
    return this->t_contentset_name;
}

QString Session::getBasePath()
{
    return this->t_basePath;
}

void Session::setBasePath(QString val)
{
    this->t_basePath = val;
}

QVector<Section *> Session::getSections()
{
    return this->t_sections;
}

void Session::addSection(Section *val)
{
    this->t_sections.append(val);
}

// Static
Session *Session::parseSessionFromPath(QString path, ContentSet *cs)
{
    QFile xmlfile(path);
    QDomDocument doc("mydocument");

    if (!xmlfile.open(QIODevice::ReadOnly))
        return NULL;
    if (!doc.setContent(&xmlfile)) {
        xmlfile.close();
        return NULL;
    }
    xmlfile.close();

    // Parse XML
    QDomElement el = doc.documentElement();
    return Session::parseSession(el, cs);
}

Session *Session::parseSession(QDomElement el, ContentSet *cs)
{
    if (el.isNull()) return NULL;
    Session *ss = new Session();

    // Attrs
    QString tmpstr = el.attribute("name", "noname"); ss->setName(tmpstr);

    // Session refs
    int i;
    QDomNode n = el.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            if (e.tagName()=="sectionref" && e.attribute("uuid", "nouuid")!="nouuid") {
                for(i=0;i<cs->getSections().size();i++) {
                    if (cs->getSections().at(i)->getUUID()==e.attribute("uuid")) {
                        ss->addSection(cs->getSections().at(i));
                    }
                }
            } else if (e.tagName()=="track") {
                Track *stmp = Track::parseTrack(e);
                if (stmp!=NULL) {
                    Section *sectmp = new Section();
                    sectmp->setName("standalone");
                    sectmp->setOpeningTrack(stmp);
                    sectmp->setBasePath(cs->getBasePath());
                    ss->addSection(sectmp);
                }
            }
        }
        n = n.nextSibling();
    }
    ss->setContentSetName(cs->getName());
    ss->setBasePath(cs->getBasePath());
    return ss;

}

}
