#include "FCFS.h"

FCFS::FCFS(const std::vector<job> &v):_totalTime(0), _totalTime_with_weight(0.0)
{
    for(const auto& job: v)
        _runqueue.push(job);
}

void FCFS::print()
{
    auto q = _runqueue;
    while(!q.empty())
    {
        std::cout<<q.top();
        q.pop();
    }
}

timeRecord FCFS::run()
{
    print();
    int sz = _runqueue.size();
    auto q = _runqueue;
    int preEnd = q.top().arrivalTime();
    while(!q.empty())
    {
        auto j = q.top();
        int wait = ( preEnd <= j.arrivalTime() ? 0 : preEnd - j.arrivalTime() );
        _totalTime += ( wait + j.runTime() );
        _totalTime_with_weight += ( wait + j.runTime()) / (1.0 * j.runTime());
        std::cout<< _totalTime << " " << _totalTime_with_weight<< std::endl;
        preEnd = j.arrivalTime() + wait + j.runTime();
        q.pop();
    }
    //return std::make_pair((double)_totalTime / sz, _totalTime_with_weight / sz)
    return { (double)_totalTime / sz, _totalTime_with_weight / sz };
}




