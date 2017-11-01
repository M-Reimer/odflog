/*
  odflog - Command line ODF log extraction program
  Copyright (C) 2017  Manuel Reimer <manuel.reimer@gmx.de>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "versionparser.h"
// The class "VersionParser" encapsulates all calls to "tinyxml2"

// Method to request parsing of the supplied XML string.
// Parameters:
//   aXML: The XML string
// Return: none
bool VersionParser::ParseXML(string aXML) {
  XMLError error = doc.Parse(aXML.c_str());
  if (error)
    return false;

  return true;
}

// Method which returns the list of versions
// Parameters: none
// Return: Vector with entries as "LogData" class instances.
vector<LogData> VersionParser::GetVersions() const {
  vector<LogData> list;

  for (const XMLNode* node = doc.FirstChildElement()->FirstChild(); node; node = node->NextSibling()) {
    const XMLElement *childelement = node->ToElement();
    const char* datetime = childelement->Attribute("dc:date-time");
    const char* creator = childelement->Attribute("VL:creator");
    const char* comment = childelement->Attribute("VL:comment");
    if (datetime && creator && comment)
      list.push_back(LogData(datetime, creator, comment));
  }

  return list;
}
