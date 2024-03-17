#include <iostream>
#include<vector>
#include"atractions.h"

using namespace std;

Atraction::Atraction()
{
    name = "";
    atraction_nr = 0;
    people_limit = 0;
    people = {};
    Lifeguard t;
    lifeguard = t;
}

Atraction::Atraction
(
    string nam,
    int atr_nr,
    int ppl_limit
)
{
    name = nam;
    atraction_nr = atr_nr;
    people_limit = ppl_limit;
}

void Atraction::set_atraction_nr(int new_atraction_nr)
{
    if (new_atraction_nr >= 0)
    {
        atraction_nr = new_atraction_nr;
    }
}

void Atraction::set_people_limit(int new_people_limit)
{
    if (new_people_limit >= 0)
    {
        people_limit = new_people_limit;
    }
}

void Atraction::set_lifeguard(Lifeguard& new_lifeguard)
{
    lifeguard = new_lifeguard;
}

void Atraction::set_people(std::vector<Client> new_people)
{
    people = new_people;
}

Atraction Atraction::operator=(Atraction atraction2)
{
    atraction_nr = atraction2.atraction_nr;
    people_limit = atraction2.people_limit;
    people = atraction2.people;
    lifeguard = atraction2.lifeguard;
    return *this;
}

int Atraction::search_list(int card_id)
{
    int index;
    for (long long unsigned int i = 0; i < people.size(); ++i)
    {
        if (people[i].get_carnet_id() == card_id)
        {
            index = i;
            return index;
        }
    }
    index = -1;
    return index;
}

void Atraction::remove_person(int card_id)
{
    int index = search_list(card_id);
    if (index == -1)
    {
        return;
    }
    people.erase(people.begin() + index);
}

void Atraction::add_person(Client& person)
{
    if ((int)people.size() < people_limit)
    {
        people.push_back(person);
        person.curent_atr_nr = atraction_nr;
        person.did_reserve = true;
        return;
    }
    else
    {
        throw;
    }
}
