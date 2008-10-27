/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
 *   echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil"                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "queryget.h"
#include "parser.h"
#include <QtXml>

QueryGet::QueryGet(Parser* parser, QXmlStreamWriter* streamWriter, const QString& id):
QObject(parser), mp_streamWriter(streamWriter), m_id(id)
{

}

QueryGet::~QueryGet()
{
}

void QueryGet::getServerInfo()
{
    writeStartQuery();
    mp_streamWriter->writeEmptyElement("serverinfo");
    writeEndQuery();
}

void QueryGet::writeStartQuery()
{
    mp_streamWriter->writeStartElement("query");
    mp_streamWriter->writeAttribute("type", "get");
    mp_streamWriter->writeAttribute("id", m_id);
}

void QueryGet::writeEndQuery()
{
    mp_streamWriter->writeEndElement();
}

void QueryGet::parseResult(const QXmlStreamReader*)
{

}