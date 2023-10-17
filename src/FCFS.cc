#include "FCFS.h"

FCFS::FCFS(const std::vector<job> &v):_totalTime(0), _totalTime_with_weight(0.0)
{
    for(const auto& job: v)
        _runqueue.push(job);
}

void FCFS::schedulingInfo()
{
    std::cout<< "模拟FCFS调度算法, 进程的调度执行顺序如下:" << std::endl;
    auto q = _runqueue;
    while(!q.empty())
    {
        std::cout<<q.top();
        q.pop();
    }
}

// void FCFS::printTime()
// {
//     std::cout<<"平均周转时间:" << " " << (double)_totalTime / _runqueue.size() << std::endl;
//     std::cout<<"平均带权周转时间:" << " " << _totalTime_with_weight / _runqueue.size() << std::endl;
// }

timeRecord FCFS::run()
{
    int sz = _runqueue.size();
    auto q = _runqueue;
    int preEnd = q.top().arrivalTime();
    while(!q.empty())
    {
        auto j = q.top();
        int wait = ( preEnd <= j.arrivalTime() ? 0 : preEnd - j.arrivalTime() );
        _totalTime += ( wait + j.runTime() );
        _totalTime_with_weight += ( wait + j.runTime()) / (1.0 * j.runTime());
        // for debug
        //std::cout<< _totalTime << " " << _totalTime_with_weight<< std::endl;
        preEnd = j.arrivalTime() + wait + j.runTime();
        q.pop();
    }
    schedulingInfo();
    //printTime();
    //return std::make_pair((double)_totalTime / sz, _totalTime_with_weight / sz)
    return { (double)_totalTime / sz, _totalTime_with_weight / sz };
}




