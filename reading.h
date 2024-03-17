#ifndef Reading_H
#define Reading_H

#include <fstream>
#include "da_time.h"
#include "Lifeguard.h"
#include "Instructor.h"
#include "client.h"
#include "atractions.h"
#include "da_Pool.h"


struct Reading
{
    std::vector<Atraction*> atractions;
    std::vector<Lifeguard*> staff_available;
    std::vector<Client> clients;
    Da_Pool dapool;
    int tick;
    int rand;
};

Reading m;
std::vector<Atraction> atr;
std::vector<Swimming_Pool> swm;
std::vector<Lifeguard> lif;
std::vector<Instructor> ins;

Reading* da_read(std::string databaze)
{
    std::ifstream file(databaze);
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            size_t pos = 0;
            std::string token;
            std::string delimiter = ",";
            std::vector<std::string> obiekt;
            while ((pos = line.find(delimiter)) != std::string::npos)
            {
                token = line.substr(0, pos);
                obiekt.push_back(token);
                line.erase(0, pos + delimiter.length());
            }
            if (obiekt[0] == "klient")
            {
                std::string name = obiekt[1];
                std::string surname = obiekt[2];
                int id = stoi(obiekt[3]);
                int z = stoi(obiekt[4]);
                if (z == 0)
                {
                    Client klient(name, surname, id, false, 0);
                    m.clients.push_back(klient);
                }
                if (z == 1)
                {
                    Client klient(name, surname, id, true, 0);
                    m.clients.push_back(klient);
                }
            }
            if (obiekt[0] == "Lifeguard")
            {
                std::string name = obiekt[1];
                std::string surname = obiekt[2];
                int id = stoi(obiekt[3]);
                int exp = stoi(obiekt[4]);
                int starth = stoi(obiekt[5]);
                Time sh = { starth,00 };
                int finish = stoi(obiekt[6]);
                Time fh = { finish,00 };

                Lifeguard ratownik(name, surname, id, exp, sh, fh);
                lif.push_back(ratownik);
            }
            if (obiekt[0] == "Instructor")
            {
                std::string name = obiekt[1];
                std::string surname = obiekt[2];
                int id = stoi(obiekt[3]);
                int exp = stoi(obiekt[4]);
                int starth = stoi(obiekt[5]);
                Time sh = { starth,00 };
                int finish = stoi(obiekt[6]);
                Time fh = { finish,00 };

                Instructor instr(name, surname, id, exp, sh, fh);
                ins.push_back(instr);
            }
            if (obiekt[0] == "pool")
            {
                int atraction_nr = stoi(obiekt[1]);
                int length = stoi(obiekt[2]);
                int tr_limit = stoi(obiekt[3]);
                int begginer_tr = stoi(obiekt[4]);
                int intermeddiate_tr = stoi(obiekt[5]);
                int advanced_tr = stoi(obiekt[6]);

                Swimming_Pool swipool(atraction_nr, length, tr_limit, begginer_tr, intermeddiate_tr, advanced_tr);
                swm.push_back(swipool);
            }
            if (obiekt[0] == "attraction")
            {
                std::string name = obiekt[1];
                int attraction_num = stoi(obiekt[2]);
                int people_limit = stoi(obiekt[3]);

                Atraction atraction(name, attraction_num, people_limit);
                atr.push_back(atraction);
            }
            if (obiekt[0] == "da_pool")
            {
                std::string name = obiekt[1];
                int start = stoi(obiekt[2]);
                Time starth = { start,00 };
                int finish = stoi(obiekt[3]);
                Time finishh = { finish,00 };

                Da_Pool dapool(name, m.atractions, starth, finishh);
                m.dapool = dapool;
            }
            if (obiekt[0] == "rand")
            {
                m.rand = stoi(obiekt[1]);
            }
            if (obiekt[0] == "tick")
            {
                m.tick = stoi(obiekt[1]);
            }
        }
    }
    for (long long unsigned int i = 0; i < atr.size(); i++)
    {
        m.atractions.push_back(&atr[i]);
    }
    for (long long unsigned int i = 0; i < swm.size(); i++)
    {
        m.atractions.push_back(&swm[i]);
    }
    m.dapool.set_atractions(m.atractions);
    for (long long unsigned int i = 0; i < lif.size(); i++)
    {
        m.staff_available.push_back(&lif[i]);
    }
    for (long long unsigned int i = 0; i < ins.size(); i++)
    {
        m.staff_available.push_back(&ins[i]);
    }

    return &m;
}
#endif
