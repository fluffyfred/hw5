#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool schedule_helper(unsigned int day, unsigned int slot, const size_t dailyNeed, const size_t maxShifts, const AvailabilityMatrix& avail, DailySchedule& sched, vector<unsigned int>& shifts);

// Add your implementation of schedule() and other helper functions here
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    int nworkers = avail[0].size(); // number of workers
    // initializations
    vector<unsigned int> shifts(nworkers);
    for(unsigned int i = 0; i < shifts.size(); i++) {
        shifts[i] = 0; // how many shifts a worker has already worked
    }

    // sched = DailySchedule(avail.size(), vector<Worker_T>(dailyNeed));

    std::vector<Worker_T> vect(dailyNeed, -1);
    for(unsigned int i = 0; i < avail.size(); i++) {
        sched.push_back(vect);
    //   for(unsigned int j = 0; j < dailyNeed; j++) {
    //     sched[i][j] = -1;
    //   }
    }

    // call the helper function
    bool ans =  schedule_helper(0, 0, dailyNeed, maxShifts, avail, sched, shifts);
    return ans;   
}

// backtracking helper function
bool schedule_helper(unsigned int day, unsigned int slot, const size_t dailyNeed, const size_t maxShifts, const AvailabilityMatrix& avail, DailySchedule& sched, vector<unsigned int>& shifts)
{
    // finishes assigning
    if(day >= sched.size()) {
        return true;
    }
      //std::cout << "new iteration" << std::endl;
    // assign workers
    for(unsigned int i = 0; i < avail[day].size(); i++) {
        // check for availability

        if(avail[day][i] == 1 && shifts[i] < maxShifts) {
            sched[day][slot] = i;
            shifts[i]++;
        
        // check if we need to remove this worker from available workers
        
        // change the day if necessary
        bool answer = false;
        if(slot == dailyNeed - 1) {
          answer = schedule_helper(day + 1, 0, dailyNeed, maxShifts, avail, sched, shifts);
        }
        // recursively call the function for the next day
        else{
          answer = schedule_helper(day, slot + 1, dailyNeed, maxShifts, avail, sched, shifts);
        }
        if(answer == true)
          return true;
        // backtracking
        shifts[i]--;
        sched[day][i] = -1;
        //std::cout << "val at sched[][] " << day << " " << i << " " << sched[day][i] << std::endl;
      }
    }
    // cannot assign any workers, return false
    return false;
}









