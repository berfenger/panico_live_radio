/** 
 * @file listableitem.cpp
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

#include "listableitem.h"

ListableItem::ListableItem()
{

}

QString ListableItem::getText()
{
    return this->t_list_name;
}

QIcon ListableItem::getIcon()
{
    return this->t_list_icon;
}

void ListableItem::addUIListItem(UIListItem *i)
{
    this->t_uilistitems.append(i);
}

void ListableItem::clear()
{
    this->t_uilistitems.clear();
}

void ListableItem::setText(QString name)
{
    this->t_list_name = name;
    int i;
    for(i=0;i<this->t_uilistitems.size();i++) {
        this->t_uilistitems.at(i)->setText(name);
    }
}

void ListableItem::setIcon(QIcon icon)
{
    this->t_list_icon = icon;
    int i;
    for(i=0;i<this->t_uilistitems.size();i++) {
        this->t_uilistitems.at(i)->setIcon(icon);
    }
}


