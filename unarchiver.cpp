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

#include "unarchiver.h"
// The class "UnArchiver" encapsulates all calls to "minizip"

// Constructor
UnArchiver::UnArchiver() : zipfile(NULL) {

}

// Destructor
UnArchiver::~UnArchiver() {
  // Get sure we don't leave open files.
  if (zipfile != NULL)
    unzClose(zipfile);
}

bool UnArchiver::Open(string aPath) {
  // If a file is already open, close it first.
  if (zipfile != NULL)
    unzClose(zipfile);

  // Open the supplied file, return "false" on error.
  zipfile = unzOpen(aPath.c_str());
  return (zipfile != NULL);
}

string UnArchiver::GetFileContent(string aFileName) const {
  // No file open --> nothing to extract.
  if (zipfile == NULL)
    return "";

  // Locate the supplied file.
  if (unzLocateFile(zipfile, aFileName.c_str(), false) != UNZ_OK)
    return "";

  // Open the located file.
  if (unzOpenCurrentFile(zipfile) != UNZ_OK)
    return "";

  // Read data blockwise and collect the parts in a "string".
  // Finally return this string buffer.
  string buffer;
  const int read_size = 8192;
  char read_buffer[read_size];
  int error = UNZ_OK;
  do {
    error = unzReadCurrentFile(zipfile, read_buffer, read_size);
    if (error < 0) {
      cerr << "Extraction error: " << error << endl;
      break;
    }

    // Write data to buffer.
    if ( error > 0 )
      buffer.append(read_buffer, error);
  } while ( error > 0 );

  unzCloseCurrentFile(zipfile);
  return buffer;
}
