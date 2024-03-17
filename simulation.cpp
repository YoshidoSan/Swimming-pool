#include "simulation.h"
#include "reading.h"
#include <random>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

Simulation::Simulation(string using_databaze, string reservations)
{
    string databaze = using_databaze;
    Reading* r = da_read(using_databaze); //"Databaze.txt"
    vector<Reservation> res = czytamres(reservations);

    list_of_clients = r->clients;
    list_of_lifeguards = r->staff_available;
    list_of_atractions = r->atractions;

    par = r->rand;
    tick_length = r->tick;
    gowno = r->dapool;
    max_number_of_enters_per_tick = tick_length % 3 + 1;
    this->res = res;

    for (long long unsigned int i = 0; i < res.size(); i++)
    {
        for (long long unsigned int j = 0; j < res[i].clientsid.size(); j++)
        {
            for (long long unsigned int k = 0; k < list_of_clients.size(); k++)
            {
                if (list_of_clients[k].carnet_id == res[i].clientsid[j])
                {
                    list_of_clients[k].did_reserve = true;
                }
            }
        }
        for (long long unsigned int j = 0; j < list_of_lifeguards.size(); j++)
        {
            if (list_of_lifeguards[j]->work_id == res[i].instrid)
            {
                list_of_lifeguards[j]->busy = true;
            }
        }
    }

}

void Simulation::customers_movements(int par)
{
    for (long long unsigned int i = 0; i < gowno.clients.size(); i++)
    {
        int rand_nummber = give_random_number(par) + 1;
        if (rand_nummber == 0 && gowno.clients[i].did_reserve == false)
        {
            int rand2;
            bool overcrowded = true;
            int k = 0;
            for (long long unsigned int i = 0; i < list_of_atractions.size(); i++)
            {
                if (gowno.atractions[i]->name == "Swimming_Pool")
                {
                    Swimming_Pool* t = static_cast<Swimming_Pool*>(gowno.atractions[i]);
                    if (t->free_places() <= 0)
                    {
                        k += 1;
                    }
                }
                else if (gowno.atractions[i]->people_limit <= (int)gowno.atractions[i]->people.size())
                {
                    k += 1;
                }
            }
            if (k < (int)list_of_atractions.size())
            {
                while (overcrowded == true)
                {
                    rand2 = give_random_number(list_of_atractions.size());
                    if (gowno.atractions[rand2]->name == "Swimming_Pool")
                    {
                        Swimming_Pool* t = static_cast<Swimming_Pool*>(gowno.atractions[rand2]);
                        if (t->free_places() > 0)
                        {
                            overcrowded = false;
                        }
                    }
                    else
                    {
                        if (gowno.atractions[rand2]->people_limit > (int)gowno.atractions[rand2]->people.size())
                        {
                            overcrowded = false;
                        }
                    }
                }
                gowno.change_atr(gowno.clients[i], gowno.clients[i].curent_atr_nr, gowno.atractions[rand2]->atraction_nr);
            }
        }
    }
}

void Simulation::lifeguards_enters()
{
    for (long long unsigned int i = 0; i < list_of_atractions.size(); i++)
    {
        int rand;
        bool buzy = true;
        while (buzy == true)
        {
            rand = give_random_number(list_of_lifeguards.size());
            if (list_of_lifeguards[rand]->busy == true)
            {
                continue;
            }
            else
            {
                buzy = false;
            }
        }
        gowno.assign_lifeguard(*list_of_lifeguards[rand], list_of_atractions[i]->atraction_nr);
        list_of_lifeguards[rand]->busy = true;
    }
}

int Simulation::client_enters()
{
    int rand = number_of_enters();
    int rand1;
    int rand3 = give_random_number(3) + 1;
    int free_seats = 0;
    for (long long unsigned int i = 0; i < list_of_atractions.size(); i++)
    {
        if (list_of_atractions[i]->name == "Swimming_Pool")
        {
            Swimming_Pool* t = static_cast<Swimming_Pool*>(list_of_atractions[i]);
            free_seats += t->free_places();
        }
        else
        {
            free_seats += (list_of_atractions[i]->people_limit - list_of_atractions[i]->people.size());
        }
    }
    if (free_seats < rand)
    {
        rand = free_seats - 5;
    }
    bool correct_time = false;
    while (correct_time == false)
    {
        Time E1 = gowno.current_time;
        E1 = E1 + 91;
        Time E2 = gowno.current_time;
        E2 = E2 + 151;
        if (gowno.closing_time < E1)
        {
            rand3 = 1;
            correct_time = true;
        }
        else if (gowno.closing_time < E2)
        {
            rand3 = give_random_number(2) + 1;
            correct_time = true;
        }
        else
        {
            rand3 = give_random_number(3) + 1;
            correct_time = true;
        }
    }
    if (free_seats > 5)
    {
        for (int i = 0; i < rand; i++)
        {
            bool buzy = true;
            while (buzy == true)
            {
                rand1 = give_random_number(list_of_clients.size());
                if (list_of_clients[rand1].curent_atr_nr != -1 || list_of_clients[rand1].did_reserve == true)
                {
                    continue;
                }
                else
                {
                    buzy = false;
                }
            }
            Time L = gowno.current_time;
            list_of_clients[rand1].time_spent += rand3;
            list_of_clients[rand1].time_spent_hours.push_back(L);
            list_of_clients[rand1].time_spent_hours.push_back(L + rand3 * 60);
            int rand2;
            bool overcrowded = true;
            while (overcrowded == true)
            {
                rand2 = give_random_number(list_of_atractions.size());
                if (gowno.atractions[rand2]->name == "Swimming_Pool")
                {
                    Swimming_Pool* t = static_cast<Swimming_Pool*>(gowno.atractions[rand2]);
                    if (t->free_places() > 0)
                    {
                        overcrowded = false;
                    }
                }
                else
                {
                    if (gowno.atractions[rand2]->people_limit > (int)gowno.atractions[rand2]->people.size())
                    {
                        overcrowded = false;
                    }
                }
            }
            if (gowno.atractions[rand2]->name == "Swimming_Pool")
            {
                Swimming_Pool* t = static_cast<Swimming_Pool*>(gowno.atractions[rand2]);
                gowno.add_client(list_of_clients[rand1], gowno.atractions[rand2]->atraction_nr, t->min_tr(), rand3 * 60);
            }
            else
            {
                gowno.add_client(list_of_clients[rand1], gowno.atractions[rand2]->atraction_nr, rand3 * 60);
            }
            list_of_clients[rand1].curent_atr_nr = gowno.atractions[rand2]->atraction_nr;
        }
    }
    return rand;
}

void Simulation::start_reservation(int resi)
{
    int index;
    vector<Client> grupka;
    for (long long unsigned i = 0; i < list_of_lifeguards.size(); i++)
    {
        if (list_of_lifeguards[i]->work_id == res[resi].instrid)
        {
            index = i;
            break;
        }
    }
    for (long long unsigned i = 0; i < res[resi].clientsid.size(); i++)
    {
        for (long long unsigned j = 0; j < list_of_clients.size(); j++)
        {
            if (list_of_clients[j].carnet_id == res[resi].clientsid[i])
            {
                grupka.push_back(list_of_clients[j]);
            }
        }
    }
    Instructor* maniek = static_cast<Instructor*>(list_of_lifeguards[index]);
    vector<Client> exiles;
    exiles = gowno.reservation(res[resi].tracknr, res[resi].duration, *maniek, grupka);
    for (long long unsigned int i = 0; i < exiles.size(); i++)
    {
        int rand2;
        bool overcrowded = true;
        int k = 0;
        for (long long unsigned int i = 0; i < list_of_atractions.size(); i++)
        {
            if (gowno.atractions[i]->name == "Swimming_Pool")
            {
                Swimming_Pool* t = static_cast<Swimming_Pool*>(gowno.atractions[i]);
                if (t->free_places() <= 0)
                {
                    k += 1;
                }
            }
            else if (gowno.atractions[i]->people_limit <= (int)gowno.atractions[i]->people.size())
            {
                k += 1;
            }
        }
        if (k < (int)list_of_atractions.size())
        {
            while (overcrowded == true)
            {
                rand2 = give_random_number(list_of_atractions.size());
                if (gowno.atractions[rand2]->name == "Swimming_Pool")
                {
                    continue;
                }
                else
                {
                    if (gowno.atractions[rand2]->people_limit > (int)gowno.atractions[rand2]->people.size())
                    {
                        overcrowded = false;
                    }
                }
            }
            gowno.add_client(exiles[i], gowno.atractions[rand2]->atraction_nr, exiles[i].remaining_time);
        }
    }
}

void Simulation::exit_client()
{
    for (long long unsigned int i = 0; i < gowno.exiting.size(); i++)
    {

        for (long long unsigned int j = 0; j < list_of_clients.size(); j++)
        {
            if (list_of_clients[j].carnet_id == gowno.exiting[i])
            {
                list_of_clients[j].curent_atr_nr = -1;
                list_of_clients[j].did_reserve = false;
            }
        }
    }
}

int Simulation::set_max_ppl()
{
    int max_ppl = 0;
    for (long long unsigned int i = 0; i < list_of_atractions.size(); i++)
    {
        if (list_of_atractions[i]->name == "Swimming_Pool")
        {
            Swimming_Pool* t = static_cast<Swimming_Pool*>(list_of_atractions[i]);
            for (long long unsigned int j = 0; j < t->tracks.size(); j++)
            {
                max_ppl += t->tracks[j].people_limit;
            }
        }
        else
        {
            max_ppl += list_of_atractions[i]->people_limit;
        }
    }
    return max_ppl;
}

void Simulation::summary_of_tick(int random_number)
{
    int y = (int)list_of_atractions.size();
    Time m = gowno.current_time;
    Time k = m + tick_length;
    cout << "Time: " << gowno.current_time << " to " << k << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Number of enters: " << random_number << endl;
    cout << "Curent number of people: " << gowno.clients.size() << endl;
    for (int i = 0; i < y; i++)
    {
        if (list_of_atractions[i]->name == "Swimming_Pool")
        {
            Swimming_Pool* t = static_cast<Swimming_Pool*>(list_of_atractions[i]);
            cout << "Atraction name: " << t->name << "; Atraction number: " << t->atraction_nr << endl;
            cout << "\tLifeguards: " << t->lifeguard.name << "  " << t->lifeguard.surname << endl;
            for (int j = 0; j < t->tr_nr; j++)
            {
                int m = j + 1;
                cout << "\tTrack" << m << ": " << t->tracks[j].people.size() << "  reserved:" << t->tracks[j].reserved;
                if (!t->tracks[j].reserved)
                {
                    cout << "  Instructor:" << " none" << endl;
                }
                else
                {
                    cout << "  Instructor:" << t->tracks[j].instructor.name << " " << t->tracks[j].instructor.surname << endl;
                }
            }
        }
        else
        {
            cout << "Atraction name: " << list_of_atractions[i]->name <<
                "; Artaction number: " << list_of_atractions[i]->atraction_nr << endl;
            cout << "\tLifeguards: " << gowno.atractions[i]->lifeguard.name <<
                "  " << gowno.atractions[i]->lifeguard.surname << endl;
            cout << "\tNumber of clients: " << gowno.atractions[i]->people.size() << endl;
        }
    }
    cout << "-----------------------------------------------" << endl;

    ofstream out("Logi.txt", ios_base::app);
    streambuf* coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    cout << "Time: " << gowno.current_time << " to " << k << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Number of enters: " << random_number << endl;
    cout << "Curent number of people: " << gowno.clients.size() << endl;
    for (int i = 0; i < y; i++)
    {
        if (list_of_atractions[i]->name == "Swimming_Pool")
        {
            Swimming_Pool* t = static_cast<Swimming_Pool*>(list_of_atractions[i]);
            cout << "Atraction name: " << t->name << "; Atraction number: " << t->atraction_nr << endl;
            cout << "\tLifeguards: " << t->lifeguard.name <<
                "  " << t->lifeguard.surname << endl;
            for (int j = 0; j < t->tr_nr; j++)
            {
                int m = j + 1;
                cout << "\tTrack" << m << ": " << t->tracks[j].people.size() << "  reserved:" << t->tracks[j].reserved;
                if (!t->tracks[j].reserved)
                {
                    cout << " Instructor:" << " none" << endl;
                }
                else
                {
                    cout << "  Instructor:" << t->tracks[j].instructor.name << " " << t->tracks[j].instructor.surname << endl;
                }
            }
        }
        else
        {
            cout << "Atraction name: " << list_of_atractions[i]->name <<
                "; Artaction number: " << list_of_atractions[i]->atraction_nr << endl;
            cout << "\tLifeguards: " << gowno.atractions[i]->lifeguard.name <<
                "  " << gowno.atractions[i]->lifeguard.surname << endl;
            cout << "\tNumber of clients: " << gowno.atractions[i]->people.size() << endl;
        }
    }
    cout << "-----------------------------------------------" << endl;
    cout.rdbuf(coutbuf); //reset to standard output again
}

void Simulation::summary_of_day()
{
    cout << "SUMMARY OF DAY" << endl;
    for (long long unsigned int i = 0; i < list_of_clients.size(); i++)
    {
        if (list_of_clients[i].time_spent > 0)
        {
            cout << "-----------------------------------------------" << endl;
            cout << "\tClient: " << list_of_clients[i].name << " " << list_of_clients[i].surname << endl;
            cout << "\tTime spent: " << list_of_clients[i].time_spent << endl;
            if (list_of_clients[i].discount == true)
            {
                cout << "\tPayment: " << list_of_clients[i].time_spent * 20 / 2 << endl; // cena za godzine do modyfikacji
            }
            else
            {
                cout << "\tPayment: " << list_of_clients[i].time_spent * 20 << endl; // to co wyzej
            }
            for (long long unsigned int j = 0; j < list_of_clients[i].time_spent_hours.size(); j = j + 2)
            {
                cout << "\tEnter time: " << list_of_clients[i].time_spent_hours[j] << endl;
                cout << "\tExit time: " << list_of_clients[i].time_spent_hours[j + 1] << endl;
            }
            cout << "-----------------------------------------------" << endl;
        }
    }

    ofstream out("Podsumowania.txt", ios_base::app);
    streambuf* coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    cout << "SUMMARY OF DAY" << endl;
    for (long long unsigned int i = 0; i < list_of_clients.size(); i++)
    {
        if (list_of_clients[i].time_spent > 0)
        {
            cout << "-----------------------------------------------" << endl;
            cout << "\tClient: " << list_of_clients[i].name << " " << list_of_clients[i].surname << endl;
            cout << "\tTime spent: " << list_of_clients[i].time_spent << endl;
            if (list_of_clients[i].discount == true)
            {
                cout << "\tPayment: " << list_of_clients[i].time_spent * 20 / 2 << endl; // cena za godzine do modyfikacji
            }
            else
            {
                cout << "\tPayment: " << list_of_clients[i].time_spent * 20 << endl; // to co wyzej
            }
            for (long long unsigned int j = 0; j < list_of_clients[i].time_spent_hours.size(); j = j + 2)
            {
                cout << "\tEnter time: " << list_of_clients[i].time_spent_hours[j] << endl;
                cout << "\tExit time: " << list_of_clients[i].time_spent_hours[j + 1] << endl;
            }
            cout << "-----------------------------------------------" << endl;
        }
    }
    cout.rdbuf(coutbuf); //reset to standard output again
}

void Simulation::main_simulation()
{
    // clear plikow tekstowych
    max_par = tick_length / 10;
    gowno.max_ppl = set_max_ppl();
    Time b = gowno.start_time;
    Time l = b + 360;
    while (gowno.current_time < gowno.closing_time)
    {
        if (gowno.current_time == gowno.start_time || gowno.current_time == l)
        {
            lifeguards_enters();
        }

        for (long long unsigned int i = 0; i < res.size(); i++)
        {
            if (res[i].starting == gowno.current_time)
            {
                start_reservation(i);
            }
        }

        if (gowno.clients.size() != 0)
        {
            customers_movements(par);
        }
        int a;
        Time e = gowno.current_time;
        if (e + 59 < gowno.closing_time)
        {
            a = client_enters();
        }
        else
        {
            a = 0;
        }
        if (a < 0)
        {
            a = 0;
        }
        summary_of_tick(a);
        gowno.the_time_is_passing(tick_length);
        exit_client();
    }
    summary_of_day();
}

int Simulation::number_of_enters()
{
    srand(time(NULL));
    int random_number = rand() % (max_par + 1) + 1;
    return random_number;
}

int Simulation::give_random_number(int zakres)
{
    srand(time(NULL));
    int random_number = rand() % zakres;
    return random_number;
}
