#ifndef UNARCHIVER_H_INCLUDED
#define UNARCHIVER_H_INCLUDED

#include <iostream>
#include <unzip.h>

using namespace std;

class UnArchiver {
  private:
    unzFile zipfile;

  public:
    UnArchiver();
    ~UnArchiver();
    bool Open(string aPath);
    string GetFileContent(string aFileName) const;
};

#endif // UNARCHIVER_H_INCLUDED
