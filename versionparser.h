#ifndef VERSIONPARSER_H_INCLUDED
#define VERSIONPARSER_H_INCLUDED

#include <vector>
#include <string>
#include <tinyxml2.h>
#include "logdata.h"

using namespace std;
using namespace tinyxml2;

class VersionParser {
  private:
    XMLDocument doc;

  public:
    bool ParseXML(string aXML);
    vector<LogData> GetVersions() const;
};


#endif // VERSIONPARSER_H_INCLUDED
