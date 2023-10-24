#include "utils.h"
#include "job.h"
#include "FCFS.h"
#include "HRRF.h"
#include "RR.h"
#include "MLQF.h"
#include "SRTF.h"
#include "SJF.h"

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

// void test_fcfs()
// {
//     auto jobs = load_data();
//     FCFS f(jobs);
//     printTime(f.run());
// }

// void test_hrrf()
// {
//     auto jobs = load_data();
//     HRRF f(jobs);
//     printTime(f.run());
// }

// void test_RR()
// {
//     auto jobs = load_data();
//     RR f(jobs);
//     printTime(f.run());
// }

// void test_MLQF()
// {
//     auto jobs = load_data();
//     MLQF f(jobs);
//     printTime(f.run());
// }


// void test_SJF()
// {
//     auto jobs = load_data();
//     SJF f(jobs);
//     printTime(f.run());
// }

void test_SRTF()
{
    auto jobs = load_data();
    SRTF f(jobs);
    f.run(true);
    f.outputSchedulingInfo();
}


template<typename T>
void test(bool flag)
{
    auto jobs = load_data();
    T f(jobs);
    f.run(flag);
    if(!flag)
        f.outputSchedulingInfo();
}

// ./main [for normal usage, print all information in terminal]
// ./main -v | visualize.py [to visualize the information]

void usage()
{
    std::cerr << "usage error! Correct usage:" << std::endl;
    std::cerr << "\t\t./main (for normal usage, print all information in terminal)" << std::endl;
    std::cerr << "\t\t./main -v | python3 [visualize python code] (to visualize the information)" << std::endl;
}


int main(int argc, char* argv[])
{

    bool vis;

    if(argc == 1)
    {
        vis = false;
        test<FCFS>(vis);
        test<SJF>(vis);
        test<HRRF>(vis);
        test<RR>(vis);
        test<MLQF>(vis);
        //test_SRTF();

    }
    else if(argc == 2 && (strcmp("-v", argv[1]) == 0))
    {
        vis = true;
        test<FCFS>(vis);
        test<SJF>(vis);
        test<HRRF>(vis);
        test<RR>(vis);
        test<MLQF>(vis);
    }
    else
    {
        usage();
        exit(-1);
    }
    return 0;
}