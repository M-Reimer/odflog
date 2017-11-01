#ifndef LOGDATA_H_INCLUDED
#define LOGDATA_H_INCLUDED

#include <ctime>
#include <string>

using namespace std;

class LogData {
  private:
    time_t timestamp;
    string creator;
    string comment;

  public:
    LogData(string aDateTime, string aCreator, string aComment);
    time_t GetTimestamp();
    string GetCreator();
    string GetComment();
};

#endif // LOGDATA_H_INCLUDED
