#ifndef client_h
#define client_h

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "da_time.h"

class Client
{
    friend class Atraction;
    friend class Da_Pool;
public:
    std::string name;
    std::string surname;
    int carnet_id;
    bool discount;
    int remaining_time;
    bool did_reserve;
    int curent_atr_nr;
    int time_spent;
    std::vector<Time> time_spent_hours;

    Client();

    Client(
        std::string name,
        std::string surname,
        int carnet_id,
        bool discount,
        int remaining_time
    );

    Client(const Client& client)
    {
        name = client.name;
        surname = client.surname;
        carnet_id = client.carnet_id;
        discount = client.discount;
        remaining_time = client.remaining_time;
        curent_atr_nr = client.curent_atr_nr;
        time_spent = client.time_spent;
        time_spent_hours = client.time_spent_hours;
        did_reserve = client.did_reserve;
    }

    friend std::ostream& operator << (std::ostream& output, const Client& c);

    bool operator == (const Client& c1);

    bool operator != (const Client& c1);

    Client& operator=(const Client& s);

    std::string get_name() const;

    std::string get_surname() const;

    int get_carnet_id() const;

    void set_time(int time);
};
#endif
