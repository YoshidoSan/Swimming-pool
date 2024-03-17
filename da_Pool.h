#ifndef Da_Pool_H
#define Da_Pool_H

#include <iostream>
#include <list>
#include<vector>
#include "client.h"
#include "Lifeguard.h"
#include "Instructor.h"
#include "da_time.h"
#include "atractions.h"

class Da_Pool
{
    friend class Simulation;
    std::string name;
    int max_ppl;
    int attr_nr; // ilosc atrkcji
    std::vector<Atraction*> atractions;
    std::vector<Lifeguard> staff_available;
    std::vector<Client> clients;
    std::vector<int> exiting;
    Time start_time;
    Time closing_time;
    Time current_time;
public:
    Da_Pool();
    Da_Pool(
        std::string name,
        std::vector<Atraction*>& atr,
        Time start_time,
        Time closing_timev
    );
    Da_Pool(const Da_Pool& da)
    {
        name = da.name;
        max_ppl = da.max_ppl;
        attr_nr = da.attr_nr;
        atractions = da.atractions;
        staff_available = da.staff_available;
        clients = da.clients;
        exiting = da.exiting;
        start_time = da.start_time;
        closing_time = da.closing_time;
        current_time = da.current_time;
    }
    void set_atractions(std::vector<Atraction*>& atr)
    {
        atractions = atr;
    }
    void add_client(Client& client, int atraction_nr, int time);
    void add_client(Client& client, int atraction_nr, int tr_number, int time);
    void change_atr(Client& client, int atraction_nr1, int atraction_nr2); //przejscie z jednego basenu do 2
    int exit_da_pool(Client& client);
    void staff_exit(Lifeguard& staff);
    void assign_lifeguard(Lifeguard& lif, int atraction_nr);
    std::vector<Client> reservation(int tr_nr, int duration, Instructor& inst, std::vector<Client>& group); // duration w 60 min -> czas biletu
    bool the_time_is_passing(int tick);
};
#endif
