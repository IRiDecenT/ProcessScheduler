#include "RR.h"

// void RR::updateWait(int curTime)
// {
//     for(auto& j : _jobs)
//         if(!j._isProcessed & j._lastInterruptTime < curTime)
// }

timeRecord RR::solveTimeRecord()
{
    int size = _jobs.size();
    for(const auto& j : _jobs)
    {
        int n = j._runPeriod.size();
        int period = j._runPeriod[n - 1].second - j.arrivalTime();
        _totalTime += period;
        _totalTime_with_weight += (double)period / j.runTime();
    }
    return {(double)_totalTime / size, _totalTime_with_weight / size};
}

void RR::schedulingInfo()
{
    std::cout << "模拟RR调度, 时间片长度为:" << RR_PER <<", 进程的调度执行顺序如下: " << std::endl;
    for(const auto & ptr : _schedulingList)
        std::cout << ptr->name() << " " ;
    std::cout << std::endl;

    std::cout << "每一个进程运行时间片如下:" << std::endl;
    for(const auto& j : _jobs)
    {
        std::cout << j.name() << ": ";
        for(const auto& period : j._runPeriod)
        {
            std::cout << "(" << period.first << ", "
                    << period.second << ")" << " ";
        }
        std::cout << std::endl;
    }
}

RR::RR(const std::vector<job> &jobs)
    : _totalTime(0), _totalTime_with_weight(0.0)
{
    _jobs.reserve(jobs.size());
    for(const auto& j : jobs)
        _jobs.push_back(job_rr(j));

    _schedulingList.reserve(_jobs.size());

    std::sort(_jobs.begin(), _jobs.end(), [](const job& j1, const job& j2){
        return j1.arrivalTime() < j2.arrivalTime();
    });

    // for debug
    // for(auto& e : _jobs)
    //     std::cout<< e;

    // bug 在此处就将所有的任务按照到达时间顺序加入_runqueue的做法并不正确
    // 有可能前面某个进程在执行完一个时间片后加入队列等待比后面某个进程到来的时间要早
    // for(auto& j : _jobs)
    //     _runqueue.push(&j);
}



timeRecord RR::run()
{
    _runqueue.push(&_jobs[0]);
    _jobs[0]._inRunqueue = true;
    int curTime = _runqueue.front()->arrivalTime();
    while(!_runqueue.empty())
    {
        job_rr* curJob_ptr = _runqueue.front();
        _runqueue.pop();
        _schedulingList.push_back(curJob_ptr);
        int runtime = RR_PER;
        if(curJob_ptr->_leftRuntime <= RR_PER)
        {
            runtime = curJob_ptr->_leftRuntime;
            curJob_ptr->_leftRuntime = 0;
        }
        else
            curJob_ptr->_leftRuntime -= runtime;

        (curJob_ptr->_runPeriod).push_back({curTime, curTime + runtime});
        curTime += runtime;

        //在当前进程运行时间片结束要被切换时，将在当前时间之到来的进程加入到runqueue中等待
        //由于_jobs以及按照到达时间排好序按顺序迭代判断即可
        for(auto& j : _jobs)
        {
            if(!j._inRunqueue && j.arrivalTime() < curTime)
            {
                _runqueue.push(&j);
                j._inRunqueue = true;
            }
            else
                continue;
        }
        if(curJob_ptr->_leftRuntime != 0)
            _runqueue.push(curJob_ptr);
    }

    // for debug
    // for(auto& ptr : _schedulingList)
    // {
    //     std::cout<<ptr->name()<<std::endl;
    //     for(auto& pair : ptr->_runPeriod)
    //     {
    //         std::cout<< pair.first << " " << pair.second << std::endl;
    //     }
    // }
    schedulingInfo();
    return solveTimeRecord();
}

job_rr::job_rr(const job & j)
    :job(j), _wait(0)
    ,_leftRuntime(this->runTime())
    ,_inRunqueue(false)
    //_isProcessed(false)
{}
