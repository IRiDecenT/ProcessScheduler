// 多级反馈队列调度 非抢占式版本
#pragma once
#include "job.h"
#include "util.h"

const int NO_INQUEUE = -1; // 表示还未进入队列，尚未处理的任务
const int PRI0 = 0;
const int PRI1 = 1;
const int PRI2 = 2;
const int FINISHED = 3; // 已经完成的任务

const int PRI0_PERIOD = 1;
const int PRI1_PERIOD = 2;
const int PRI2_PERIOD = 4;

static int pri2period(int);

struct job_mlfq : public job
{
    int _leftRuntime;
    int _queueIndex;
    std::vector<timePeriod> _runPeriod;
    job_mlfq(const job&);
};

class MLFQ
{
private:
    std::vector<job_mlfq> _jobs;
    std::vector<std::queue<job_mlfq*>> _queues;
    int _totalTime; //总周转时间
    double _totalTime_with_weight; //总带权周转时间
    std::vector<job_mlfq*> _schedulingList; //按照调度顺序存放指向任务的指针

private:
    bool queuesAllEmpty();
    void queuePRI0_scheduling(int&);
    void queuePRI1_scheduling(int&);
    void queuePRI2_scheduling(int&x);
    void schedulingInfo();
    timeRecord solveTimeRecord();



public:
    MLFQ(std::vector<job>&, int queue_size = 3);
    timeRecord run();
    // 不允许拷贝和赋值
    MLFQ(const MLFQ&) = delete;
    MLFQ& operator=(const MLFQ&) = delete;
};