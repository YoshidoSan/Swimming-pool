#include "client.h"

using namespace std;

Client::Client()
{
    name = "";
    surname = "";
    carnet_id = 0;
    discount = false;
    remaining_time = 0;
    curent_atr_nr = -1;
    time_spent = 0;
    time_spent_hours = {};
    did_reserve = false;
}
Client::Client(string name,
    string surname,
    int carnet_id,
    bool discount,
    int remaining_time)
{
    this->name = name;
    this->surname = surname;
    this->carnet_id = carnet_id;
    this->discount = discount;
    this->remaining_time = remaining_time;
    curent_atr_nr = -1;
    time_spent = 0;
    time_spent_hours = {};
    did_reserve = false;
}

string Client::get_name() const
{
    return name;
}

string Client::get_surname() const
{
    return surname;
}

int Client::get_carnet_id() const
{
    return carnet_id;
}

void Client::set_time(int time)
{
    remaining_time = time;
}

ostream& operator << (ostream& output, const Client& c)
{
    cout << "Name: " << c.name << endl;
    cout << "Surname: " << c.surname << endl;
    cout << "carnet_id: " << c.carnet_id << endl;
    return output;
}

bool Client::operator == (const Client& c1)
{
    if (c1.carnet_id == carnet_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Client::operator != (const Client& c1)
{
    if ((c1.name == name) &&
        (c1.surname == surname) &&
        (c1.carnet_id == carnet_id))
    {
        return false;
    }
    else
    {
        return true;
    }
}

Client& Client::operator=(const Client& c)
{
    if (this != &c)
    {
        name = c.name;
        surname = c.surname;
        carnet_id = c.carnet_id;
        discount = c.discount;
        remaining_time = c.remaining_time;
    }
    return*this;
}
