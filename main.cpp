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

#include <iostream>
#include <string>
#include <ctime>

#include "unarchiver.h"
#include "versionparser.h"

using namespace std;

int main(int argc, char **argv) {
  // Check parameters. First argument is the file path.
  if (argc != 2) {
    cout << "Usage: odflog [PATH]" << endl;
    cout << "  PATH: Path to ODF file" << endl;
    return 0;
  }
  string path = argv[1];

  // Open supplied file
  UnArchiver ua;
  if (!ua.Open(path)) {
    cerr << "Given file is no valid OpenDocument format!" << endl;
    return 1;
  }

  // Extract "VersionList.xml"
  string content = ua.GetFileContent("VersionList.xml");
  if (content == "") {
    cerr << "No versions logged!" << endl;
    return 1;
  }

  // Parse version list
  VersionParser parser;
  if (!parser.ParseXML(content)) {
    cerr << "Failed to parse version list in document" << endl;
    return 1;
  }

  // Write out the version list in a format similar to "git log"
  vector<LogData> versionlist = parser.GetVersions();
  for (int index = versionlist.size() - 1; index >= 0; index--) {
    LogData info = versionlist[index];
    cout << "Author: " << info.GetCreator() << endl;
    time_t timestamp = info.GetTimestamp();
    cout << "Date:   " << asctime(localtime(&timestamp));
    cout << endl;
    cout << "    " << info.GetComment() << endl;
    cout << endl;
  }

  return 0;
}
