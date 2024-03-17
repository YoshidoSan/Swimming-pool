#include <stdexcept>
#include "da_Pool.h"
#include "client.h"
#include "Lifeguard.h"
#include "Instructor.h"
#include "da_time.h"
#include "atractions.h"

using namespace std;


Da_Pool::Da_Pool()
{
    name = "";
    max_ppl = 0;
    atractions = {};
    staff_available = {};
    clients = {};
    exiting = {};
    start_time = { 0, 0 };
    closing_time = { 0,0 };
}

Da_Pool::Da_Pool(
    string name,
    std::vector<Atraction*>& atr,
    Time sta_time,
    Time clo_time
)
{
    name = name;
    atractions = atr;
    start_time = sta_time;
    closing_time = clo_time;
    current_time = sta_time;
    attr_nr = (int)atractions.size();
    max_ppl = 0;
}

void Da_Pool::add_client(Client& client, int atraction_nr, int time)
{
    int index;
    client.curent_atr_nr = atraction_nr;
    client.set_time(time);
    for (long long unsigned int i = 0; i < atractions.size(); i++)
    {
        if (atractions[i]->atraction_nr == atraction_nr)
        {
            index = i;
            break;
        }
    }
    atractions[index]->add_person(client);
    clients.push_back(client);
}

void Da_Pool::assign_lifeguard(Lifeguard& lif, int atraction_nr)
{
    int index;
    for (long long unsigned int i = 0; i < atractions.size(); i++)
    {
        if (atractions[i]->atraction_nr == atraction_nr)
        {
            index = i;
            break;
        }
    }
    atractions[index]->set_lifeguard(lif);
    staff_available.push_back(lif);
}

void Da_Pool::add_client(Client& client, int atraction_nr, int tr_number, int time)
{
    int index;
    client.set_time(time);
    client.curent_atr_nr = atraction_nr;
    clients.push_back(client);
    for (long long unsigned int i = 0; i < atractions.size(); i++)
    {
        if (atractions[i]->atraction_nr == atraction_nr)
        {
            index = i;
            break;
        }
    }
    if (atractions[index]->name == "Swimming_Pool")
    {
        Swimming_Pool* t = static_cast<Swimming_Pool*>(atractions[index]);
        t->add_person(tr_number, client);
    }
    else
    {
        atractions[index]->add_person(client);
    }
}

void Da_Pool::change_atr(Client& client, int atraction_nr1, int atraction_nr2)
{
    int index1;
    int index2;
    for (long long unsigned int i = 0; i < atractions.size(); i++)
    {
        if (atractions[i]->atraction_nr == atraction_nr1)
        {
            index1 = i;
            break;
        }
    }
    for (long long unsigned int i = 0; i < atractions.size(); i++)
    {
        if (atractions[i]->atraction_nr == atraction_nr2)
        {
            index2 = i;
            break;
        }
    }
    if (atractions[index1]->name == "Swimming_Pool")
    {
        Swimming_Pool* t = static_cast<Swimming_Pool*>(atractions[index1]);
        t->remove_person(client.carnet_id);
    }
    else
    {
        atractions[index1]->remove_person(client.carnet_id);
    }
    if (atractions[index2]->name == "Swimming_Pool")
    {
        Swimming_Pool* t = static_cast<Swimming_Pool*>(atractions[index2]);
        t->add_person(t->min_tr(), client);
    }
    else
    {
        atractions[index2]->add_person(client);
    }
}

int Da_Pool::exit_da_pool(Client& client)
{
    int id = client.carnet_id;
    for (long long unsigned int i = 0; i < atractions.size(); i++)
    {
        for (long long unsigned int j = 0; j < atractions[i]->people.size(); j++)
        {
            if (atractions[i]->people[j].carnet_id == id)
            {
                if (atractions[i]->name == "Swimming_Pool")
                {
                    Swimming_Pool* t = static_cast<Swimming_Pool*>(atractions[i]);
                    t->remove_person(id);
                }
                else
                {
                    atractions[i]->remove_person(id);
                }
            }
        }
    }
    int index;
    for (long long unsigned int i = 0; i < clients.size(); i++)
    {
        if (clients[i].carnet_id == id)
        {
            index = i;
            break;
        }
    }
    clients.erase(clients.begin() + index);
    return id;
}

void Da_Pool::staff_exit(Lifeguard& staff)
{
    int index;
    for (long long unsigned int i = 0; i < staff_available.size(); i++)
    {
        if (staff_available[i] == staff)
        {
            index = i;
            break;
        }
    }
    staff.busy = false;
    staff_available.erase(staff_available.begin() + index);
}

std::vector<Client> Da_Pool::reservation(int tr_nr, int duration, Instructor& inst, vector<Client>& group)
{
    int index;
    for (long long unsigned int i = 0; i < atractions.size(); i++)
    {
        if (atractions[i]->name == "Swimming_Pool")
        {
            index = i;
            break;
        }
    }
    Swimming_Pool* t = static_cast<Swimming_Pool*>(atractions[index]);
    std::vector<Client> exile;
    exile = t->reserve_track(tr_nr, inst, group, duration);
    for (long long unsigned int i = 0; i < group.size(); i++)
    {
        group[i].remaining_time = duration;
        clients.push_back(group[i]);
    }
    return exile;
}

bool Da_Pool::the_time_is_passing(int tick)
{
    exiting.clear();
    current_time = current_time + tick;
    if (current_time == closing_time)
    {
        for (long long unsigned int i = 0; i < clients.size(); i++)
        {
            clients[i].set_time(clients[i].remaining_time - tick);
            if (clients[i].remaining_time <= 0)
            {
                exiting.push_back(exit_da_pool(clients[i]));
                i = i - 1;
            }
        }
        for (long long unsigned int i = 0; i < staff_available.size(); i++)
        {
            if (staff_available[i].finish == current_time)
            {
                staff_exit(staff_available[i]);
                i = i - 1;
            }
        }
        return false;
    }
    else
    {
        for (long long unsigned int i = 0; i < atractions.size(); i++)
        {
            if (atractions[i]->name == "Swimming_Pool")
            {
                Swimming_Pool* t = static_cast<Swimming_Pool*>(atractions[i]);
                for (long long unsigned int j = 0; j < t->tracks.size(); j++)
                {
                    t->tracks[j].reservation_time = t->tracks[j].reservation_time - tick;
                    if (t->tracks[j].reservation_time == 0)
                    {
                        t->tracks[j].reserved = false;
                        Instructor f;
                        t->tracks[j].instructor = f;
                        for (long long unsigned int k = 0; k < t->tracks[j].people.size(); k++)
                        {
                            t->tracks[j].people[k].did_reserve = false;
                            int id = t->tracks[j].people[k].carnet_id;
                            t->remove_person(id);
                            exiting.push_back(id);
                        }
                    }
                }
            }
        }
        for (long long unsigned int i = 0; i < clients.size(); i++)
        {
            clients[i].set_time(clients[i].remaining_time - tick);
            if (clients[i].remaining_time <= 0)
            {
                exiting.push_back(exit_da_pool(clients[i]));
                i = i - 1;
            }
        }
        for (long long unsigned int i = 0; i < staff_available.size(); i++)
        {
            if (staff_available[i].finish == current_time)
            {
                staff_exit(staff_available[i]);
                i = i - 1;
            }
        }
    }
    return true;
}
