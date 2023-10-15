#include "job.h"

job::job():
    _jopName(std::string()),
    _arrivalTime(0),
    _runTime(0),
    _priority(0){}

job::job(const std::string& name,
        int arrivaltime,
        int runtime,
        int priority)
    :_jopName(name),
    _arrivalTime(arrivaltime),
    _runTime(runtime),
    _priority(priority){}

std::ostream &operator<<(std::ostream & out, const job & job)
{
    out<< "job name: " << job._jopName
        <<"\t arrival time: " << job._arrivalTime
        <<"\t run time: " << job._runTime
        <<"\t priority: " << job._priority;
    out<<std::endl;
    return out;
}
