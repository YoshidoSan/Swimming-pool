#include "reserving.h"
#include <iostream>
#include <fstream>


std::vector<Reservation> czytamres(std::string reservs)
{
    std::vector<Reservation> vere;
    std::ifstream file(reservs);
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            size_t pos = 0;
            std::string token;
            std::string delimiter = ",";
            std::vector<std::string> grupa;
            while ((pos = line.find(delimiter)) != std::string::npos)
            {
                token = line.substr(0, pos);
                grupa.push_back(token);
                line.erase(0, pos + delimiter.length());
            }
            Reservation re;
            re.tracknr = stoi(grupa[0]);
            re.starting = {stoi(grupa[1]),00};
            re.duration = stoi(grupa[2]);
            re.instrid = stoi(grupa[3]);
            std::vector<int> clids;
            for(long long unsigned int i=4; i< grupa.size(); i++)
            {
                clids.push_back(stoi(grupa[i]));
            }
            re.clientsid = clids;
            vere.push_back(re);
        }
    }
    return vere;
}