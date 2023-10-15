#include "utils.h"
#include "job.h"
#include "FCFS.h"
#include "HRRF.h"

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

int main()
{
    test_fcfs();
    test_hrrf();
    return 0;
}