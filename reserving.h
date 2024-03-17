#ifndef reserving_h
#define reserving_h

#include <vector>
#include <string>
#include "da_time.h"


struct Reservation
{
    int tracknr;
    Time starting;
    int duration;
    int instrid;
    std::vector<int> clientsid;
};

std::vector<Reservation> czytamres(std::string reservs);

#endif
