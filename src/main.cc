#include "utils.h"
#include "job.h"
#include "FCFS.h"
#include "HRRF.h"
#include "RR.h"
#include "MLQF.h"

// hardcode for now, only to test
std::vector<job> load_data()
{
    std::vector<job> jobs{
    {"D", 6, 5, 4},
    {"B", 2, 6, 1},
    {"A", 0, 3, 3},
    {"C", 4, 4, 3},
    {"E", 8, 2, 2}};
    return jobs;
}

void test_fcfs()
{
    auto jobs = load_data();
    FCFS f(jobs);
    printTime(f.run());
}

void test_hrrf()
{
    auto jobs = load_data();
    HRRF f(jobs);
    printTime(f.run());
}

void test_RR()
{
    auto jobs = load_data();
    RR f(jobs);
    printTime(f.run());
}

void test_MLQF()
{
    auto jobs = load_data();
    MLFQ f(jobs);
    printTime(f.run());
}

int main()
{
    // test_fcfs();
    // test_hrrf();
    test_RR();
    // test_MLQF();
    return 0;
}