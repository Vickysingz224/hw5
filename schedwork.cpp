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
bool scheduleHelp(const AvailabilityMatrix& avail,
 const size_t dailyNeed, 
 const size_t maxShifts,
 DailySchedule& sched,
 std::vector<size_t>& workTime,
 size_t day,
 size_t position);

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

    // Declaration of two variables to store the days and workers
    size_t days = avail.size();
    size_t workers = avail[0].size();

    sched.resize(days, std::vector<Worker_T>(dailyNeed, INVALID_ID));
    
    // Variable to store the amount of shifts each worker is given
    std::vector<size_t> workTime(workers,0);

    return scheduleHelp(avail, dailyNeed, maxShifts, sched, workTime, 0, 0);




}

bool scheduleHelp(const AvailabilityMatrix& avail,
 const size_t dailyNeed, 
 const size_t maxShifts,
 DailySchedule& sched,
 std::vector<size_t>& workTime,
 size_t day,
 size_t position)
 {
    // // Declaration of two variables to store the days and workers
    size_t days2 = avail.size();
    size_t workers2 = avail[0].size();

    //Check if the the day variable is full and the days are all scheduled
    if(day == days2)
    {
        return true;
    }

    // Check if the position for workers are fileld for the day, move to next day
    if(position == dailyNeed)
    {
         return scheduleHelp(avail, dailyNeed, maxShifts, sched, workTime, day+1, 0);
    }

    // Iterate through the group of workers and check to see if the worker can fill the position on the current day
    for(Worker_T m =0; m < workers2; m++)
    {
        // Check if the worker is not available on day
        if(!avail[day][m])
        {
            continue;
        }
         
         // Check if worker has reached limit of shifts
        if(workTime[m] >= maxShifts)
        {
            continue;
        }
        
        // Loops through the schedule to see if the worker is scheduled 
        bool checkSched = false;
        for(size_t n=0; n < position; n++)
        {
            if(sched[day][n] == m)
            {
                checkSched = true;
                break;
            }
        }
         
         // Check if worker is scheduled for day
        if(checkSched)
        {
            continue;
        }
        
        // Sets worker to position and increment their shifts
        sched[day][position] = m;
        workTime[m]++;

        // recursivley schedule remaining positions
        if(scheduleHelp(avail, dailyNeed, maxShifts, sched, workTime, day, position+1))
        {
            return true;
        }
      
        // Backtracking 
        sched[day][position] = INVALID_ID;
        workTime[m]--;
    }
    return false;

 }

