#ifndef Instructor_h
#define Instructor_h

#include <iostream>
#include <vector>
#include <sstream>
#include "client.h"
#include "Lifeguard.h"
#include "da_time.h"

class Instructor :public Lifeguard
{
private:
    std::vector <Client> group;

public:
    Instructor(
        std::string na = "",
        std::string sur = "",
        int wid = 0,
        int ex = 1,
        Time start = { -1,-1 },
        Time finish = { -1,-1 },
        std::vector <Client> gr = {}
    );

    Instructor(const Instructor& I) : Lifeguard(I)
    {
        group = I.group;
    }

    void add_persongroup(Client& new_person);

    friend std::ostream& operator << (std::ostream& output, Instructor& i);

    bool operator == (Instructor& i1);

    bool operator != (Instructor& i1);

    Instructor operator=(Instructor i);

};
#endif
