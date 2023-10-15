#include "utils.h"
#include "job.h"
#include "FCFS.h"
void test1()
{
    job j{"A", 0, 3, 3};
    std::vector<job> jobs{
        {"A", 0, 3, 3},
        {"B", 2, 6, 1},
        {"C", 4, 4, 3},
        {"D", 6, 5, 4},
        {"E", 8, 2, 2}};
    for (const auto& e : jobs)
        std::cout << e;
    std::cout << j << std::endl;
}

int main()
{
    //std::priority_queue<>
    std::vector<job> jobs{
        {"A", 0, 3, 3},
        {"B", 2, 6, 1},
        {"C", 4, 4, 3},
        {"D", 6, 5, 4},
        {"E", 8, 2, 2}};
    FCFS f(jobs);
    auto ans = f.run();
    std::cout<<ans.first<<" "<<ans.second<<std::endl;
    return 0;
}