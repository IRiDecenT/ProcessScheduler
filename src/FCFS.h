#include "utils.h"
#include "job.h"
class FCFS
{
private:
    std::priority_queue<job, std::vector<job>, compByArrivalFirst> _runqueue;
    int _totalTime; //总周转时间
    double _totalTime_with_weight; //总带权周转时间

public:
    FCFS(const std::vector<job>& v);
    void print();
    timeRecord run();
};