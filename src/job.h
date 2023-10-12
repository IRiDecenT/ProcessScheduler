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
};