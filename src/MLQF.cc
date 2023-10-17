#include "MLQF.h"


int pri2period(int priority)
{
    switch (priority)
    {
    case PRI0:
        return PRI0_PERIOD;
    case PRI1:
        return PRI1_PERIOD;
    case PRI2:
        return PRI2_PERIOD;
    default:
        std::cerr << "unknow priority" << std::endl;
        exit(-1);
    }
}

job_mlfq::job_mlfq(const job &j)
    :job(j),
    _leftRuntime(j.runTime()),
    _queueIndex(NO_INQUEUE)
{}

bool MLFQ::queuesAllEmpty()
{
    return _queues[PRI0].empty() && _queues[PRI1].empty() && _queues.empty();
}

void MLFQ::queuePRI0_scheduling(int& curTime)
{
    while(!_queues[PRI0].empty())
    {
        job_mlfq* curJob_ptr = _queues[PRI0].front();
        _queues[PRI0].pop();
        _schedulingList.push_back(curJob_ptr);
        int runtime = pri2period(PRI0);
        if(curJob_ptr->_leftRuntime <= runtime)
        {
            runtime = curJob_ptr->_leftRuntime;
            curJob_ptr->_leftRuntime = 0;
        }
        else
            curJob_ptr->_leftRuntime -= runtime;

        // 记录运行时间片
        (curJob_ptr->_runPeriod).push_back({curTime, curTime + runtime});
        // 更新当前时间
        curTime += runtime;
        // 如果当前进程未在时间段内完成，则进入PRI1队列
        if(curJob_ptr->_leftRuntime > 0)
            _queues[PRI1].push(curJob_ptr);
        // 将当前时间之前到达的任务放入PRI0队列
        for(auto& j : _jobs)
        {
            if(j._queueIndex == NO_INQUEUE && j.arrivalTime() <= curTime)
                _queues[PRI0].push(&j);
        }
    }
}
void MLFQ::queuePRI1_scheduling(int& curTime)
{
    // 此时PRI0队列一定为空
    while(!_queues[PRI1].empty())
    {
        job_mlfq* curJob_ptr = _queues[PRI1].front();
        _queues[PRI1].pop();
        _schedulingList.push_back(curJob_ptr);
        int runtime = pri2period(PRI1);
        if(curJob_ptr->_leftRuntime <= runtime)
        {
            runtime = curJob_ptr->_leftRuntime;
            curJob_ptr->_leftRuntime = 0;
        }
        else
            curJob_ptr->_leftRuntime -= runtime;

        // 记录运行时间片
        (curJob_ptr->_runPeriod).push_back({curTime, curTime + runtime});
        // 更新当前时间
        curTime += runtime;
        // 如果当前进程未在时间段内完成，则进入PRI2队列
        if(curJob_ptr->_leftRuntime > 0)
            _queues[PRI2].push(curJob_ptr);
        // 此处检查是否有新任务来
        // 对于新任务，需要放进PRI0队列，然后调用queuePRI0_scheduling先处理新任务
        for(auto& j : _jobs)
        {
            if(j._queueIndex == NO_INQUEUE && j.arrivalTime() < curTime)
                _queues[PRI0].push(&j);
        }
        // 处理优先级更高的新任务（如果有）
        queuePRI0_scheduling(curTime);
    }
}

void MLFQ::queuePRI2_scheduling(int& curTime)
{
    // 此处PRI0和PRI1队列一定为空
    while(!_queues[PRI2].empty())
    {
        job_mlfq* curJob_ptr = _queues[PRI2].front();
        _queues[PRI2].pop();
        _schedulingList.push_back(curJob_ptr);
        int runtime = pri2period(PRI2);
        if(curJob_ptr->_leftRuntime <= runtime)
        {
            runtime = curJob_ptr->_leftRuntime;
            curJob_ptr->_leftRuntime = 0;
        }
        else
            curJob_ptr->_leftRuntime -= runtime;
        // 记录运行时间片
        (curJob_ptr->_runPeriod).push_back({curTime, curTime + runtime});
        // 更新当前时间
        curTime += runtime;
        // 如果当前进程未在时间段内完成，则重新进入PRI2队列等待被再次调度
        if(curJob_ptr->_leftRuntime > 0)
            _queues[PRI2].push(curJob_ptr);
        // 此处检查是否有新任务来
        // 对于新任务，需要放进PRI0队列，然后调用queuePRI0_scheduling先处理新任务
        for(auto& j : _jobs)
        {
            if(j._queueIndex == NO_INQUEUE && j.arrivalTime() < curTime)
                _queues[PRI0].push(&j);
        }
        // 处理优先级更高的新任务（如果有）
        queuePRI0_scheduling(curTime);
        queuePRI1_scheduling(curTime);
    }
}

MLFQ::MLFQ(std::vector<job> &jobs, int queue_size)
    : _totalTime(0),
      _totalTime_with_weight(0.0)
{
    _jobs.reserve(jobs.size());
    for(const auto& j : jobs)
        _jobs.push_back(job_mlfq(j));

    std::sort(_jobs.begin(), _jobs.end(), JobComp);

    _queues.reserve(queue_size);

    // for debug
    // for(auto& j : _jobs)
    //     std::cout << j;
}

timeRecord MLFQ::run()
{
    int curTime = _jobs[0].arrivalTime();
    _jobs[0]._queueIndex = PRI0;
    _queues[PRI0].push(&_jobs[0]);

    while(!queuesAllEmpty())
    {
        queuePRI0_scheduling(curTime);
        queuePRI1_scheduling(curTime);
        queuePRI2_scheduling(curTime);
    }

    // for debug
    for(auto& ptr : _schedulingList)
    {
        std::cout<<ptr->name()<<std::endl;
        for(auto& pair : ptr->_runPeriod)
        {
            std::cout<< pair.first << " " << pair.second << std::endl;
        }
    }
    return timeRecord();
}
