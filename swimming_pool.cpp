#include <stdexcept>
#include "atractions.h"
#include "client.h"
#include "Lifeguard.h"
#include "Instructor.h"


using namespace std;


Swimming_Pool::Swimming_Pool()
{
    name = "Swimming_Pool";
    atraction_nr = -1;
    people_limit = 0;
    people = {};
    lifeguard = Lifeguard();
    tr_nr = 0;
    length = 0;
    tracks = {};
}
Swimming_Pool::Swimming_Pool
(
    int atraction_nr,
    int length,
    int tr_limit,
    int begginer_tr,
    int intermeddiate_tr,
    int advanced_tr
) : Atraction("Swimming_Pool", atraction_nr, (tr_limit* (begginer_tr + intermeddiate_tr + advanced_tr)))
{
    tr_nr = begginer_tr + intermeddiate_tr + advanced_tr;
    atraction_nr = atraction_nr;
    length = length;
    int current_tr = 0;
    for (int i = 0; i < begginer_tr; i++)
    {
        Track tr(100, length, current_tr, tr_limit, atraction_nr);
        tracks.push_back(tr);
        current_tr = current_tr + 1;
    }
    for (int i = 0; i < intermeddiate_tr; i++)
    {
        Track tr(200, length, current_tr, tr_limit, atraction_nr);
        tracks.push_back(tr);
        current_tr = current_tr + 1;
    }
    for (int i = 0; i < advanced_tr; i++)
    {
        Track tr(300, length, current_tr, tr_limit, atraction_nr);
        tracks.push_back(tr);
        current_tr = current_tr + 1;
    }
}
std::vector<Client> Swimming_Pool::reserve_track(int track_nr, Instructor& inst, std::vector<Client> group, int res_time)
{
    std::vector<Client> exile;
    int index;
    for (int i = 0; i < tr_nr; i++)
    {
        if (tracks[i].track_nr == track_nr)
        {
            index = i;
            break;
        }
    }
    if (tracks[index].is_reserved() == false)
    {
        for (long long unsigned int i = 0; i < tracks[index].people.size(); i++)
        {
            try
            {
                change_track(tracks[index].people[i], track_nr, min_tr(track_nr));
                i=i-1;
            }
            catch (...)
            {
                exile.push_back(tracks[index].people[i]);
                remove_person(tracks[index].people[i].carnet_id);
                i=i-1;
            }
        }
        tracks[index].reserve_track(inst, group, res_time);
        for (long long unsigned int i = 0; i < group.size(); i++)
        {
            group[i].remaining_time = res_time;
            people.push_back(group[i]);
        }
    }
    return exile;
}
void Swimming_Pool::change_track(Client& cl, int tr1_nr, int tr2_nr)
{
    int index1;
    int index2;
    for (int i = 0; i < tr_nr; i++)
    {
        if (tracks[i].track_nr == tr1_nr)
        {
            index1 = i;
            break;
        }
    }
    for (int i = 0; i < tr_nr; i++)
    {
        if (tracks[i].track_nr == tr2_nr)
        {
            index2 = i;
            break;
        }
    }
    try
    {
        tracks[index1].remove_person(cl.carnet_id);
        tracks[index2].add_person(cl);
    }
    catch (...)
    {
        throw std::out_of_range("SP");
    }
}

void Swimming_Pool::add_person(int tr1_nr, Client& clnt)
{
    int index;
    if ((int)people.size() < people_limit)
    {
        for (int i = 0; i < tr_nr; i++)
        {
            if (tracks[i].track_nr == tr1_nr)
            {
                index = i;
                break;
            }
        }
    }
    clnt.curent_atr_nr = atraction_nr;
    tracks[index].add_person(clnt);
    people.push_back(clnt);
}

void Swimming_Pool::remove_person(int car_id)
{
    int index1;
    for (long long unsigned int i = 0; i < people.size(); i++)
    {
        if (people[i].carnet_id == car_id)
        {
            index1 = i;
            break;
        }
    }
    for (int i = 0; i < tr_nr; i++)
    {
        for (long long unsigned int j = 0; j < tracks[i].people.size(); j++)
        {
            if (tracks[i].people[j].carnet_id == car_id)
            {
                tracks[i].remove_person(car_id);
            }
        }
    }
    people.erase(people.begin() + index1);
}

int Swimming_Pool::min_tr()
{
    int min = 500;
    Track t(100, 0, -1, tracks[0].people_limit + 4, -1);
    for (int i = 0; i <= tracks[0].people_limit + 2; i++)
    {
        Client m("a", "a", -5, false, 0);
        t.add_person(m);
    }
    for (int i = 0; i < tr_nr; i++)
    {
        if (tracks[i].people.size() < t.people.size() && tracks[i].reserved == false)
        {
            min = tracks[i].track_nr;
            t = tracks[i];
        }
    }
    return min;
}

int Swimming_Pool::min_tr(int tr_num)
{
    int min = 500;
    Track t(100, 0, -1, tracks[0].people_limit + 4, -1);
    for (int i = 0; i <= tracks[0].people_limit + 2; i++)
    {
        Client m("a", "a", -5, false, 0);
        t.add_person(m);
    }
    for (long long unsigned int i = 0; i < tracks.size(); i++)
    {
        if (tracks[i].people.size() < t.people.size() && tracks[i].reserved == false && tracks[i].track_nr != tr_num)
        {
            min = tracks[i].track_nr;
            t = tracks[i];
        }
    }
    return min;
}


int Swimming_Pool::free_places()
{
    int siz = 0;
    for (long long unsigned int i = 0; i < tracks.size(); i++)
    {
        if (tracks[i].reserved==false)
        {
            siz = siz + tracks[i].people.size();
        }
        else
        {
            siz = siz +tracks[0].people_limit;
        }
    }
    return people_limit - siz;
}
