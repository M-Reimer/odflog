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

#include "logdata.h"

// Constructor to create LogData instance based on the strings from "VersionList.xml".
// Parameters:
//    aDateTime: DateTime string in the format YYYY-MM-DDThh:mm:ss
//    aCreator: Name of the creator of this version
//    aComment: Comment for this version
LogData::LogData(string aDateTime, string aCreator, string aComment) {
  comment = aComment;
  creator = aCreator;
  if (aDateTime.length() == 19) {
    tm timedata;
    timedata.tm_year = atoi(aDateTime.c_str()) - 1900;
    timedata.tm_mon = atoi(aDateTime.c_str() + 5) - 1;
    timedata.tm_mday = atoi(aDateTime.c_str() + 8);
    timedata.tm_hour = atoi(aDateTime.c_str() + 11);
    timedata.tm_min = atoi(aDateTime.c_str() + 14);
    timedata.tm_sec = atoi(aDateTime.c_str() + 17);
    timedata.tm_isdst = -1;
    timestamp = mktime(&timedata);
  }
}

// Getters. Returns internal attributes.
time_t LogData::GetTimestamp() {
  return timestamp;
}
string LogData::GetCreator() {
  return creator;
}
string LogData::GetComment() {
  return comment;
}
