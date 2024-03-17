#ifndef lifeguard_h
#define lifeguard_h

#include <iostream>
#include <vector>
#include <sstream>
#include "da_time.h"

class Lifeguard
{
    friend class Da_Pool;
protected:
    std::string name, surname;
    int work_id, experience;
    bool busy;
    Time start, finish;

public:

    friend class Atraction;
    friend class Simulation;

    Lifeguard();

    Lifeguard(
        std::string na,
        std::string sur,
        int wid,
        int ex,
        Time start,
        Time finish);
    Lifeguard(const Lifeguard& L)
    {
        name = L.name;
        surname = L.surname;
        work_id = L.work_id;
        experience = L.experience;
        start = L.start;
        finish = L.finish;
        busy = L.busy;
    }
    std::string get_name();
    std::string get_surname();
    int get_work_id();
    Time get_starting_time();
    Time get_finish_time();

    friend std::ostream& operator << (std::ostream& output, Lifeguard& l);

    bool operator == (Lifeguard& l1);

    bool operator != (Lifeguard& l1);

    Lifeguard operator=(Lifeguard l);
};
#endif
