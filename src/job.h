#pragma once
#include "utils.h"

class job
{
private:
    std::string _jopName;
    int _arrivalTime;
    int _runTime;
    int _priority;
public:
    job();
    job(const std::string& name, int arrivaltime = 0, int runtime = 0, int priority = 0);
    friend std::ostream& operator<<(std::ostream&, const job&);
    int arrivalTime()  const  { return _arrivalTime;  }
    int runTime() const   { return _runTime;   }
    int priority() const  { return _priority;  }
};

struct compByArrivalFirst
{
    bool operator()(const job& j1, const job& j2) { return j1.arrivalTime() > j2.arrivalTime(); }
};