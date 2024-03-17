#ifndef simualtion_h
#define simualtion_h

#include "da_Pool.h"
#include "reserving.h"
#include <sstream>
#include <random>

class Simulation {
public:
    int max_number_of_enters_per_tick;
    int tick_length;
    int par; // parametr losowy
    int max_par;
    std::vector < Client > list_of_clients;
    std::vector < Atraction* > list_of_atractions;
    std::vector < Lifeguard* > list_of_lifeguards;
    int begginer_tr; // ilosc dla beginerow
    int intermeddiate_tr; // ilosc dla srednich
    int advanced_tr; // ilosc dla zaawansowanych
    int n_of_a; // ilosc atrakcji
    int max_ppl; // maksymalna ilosc ludzi
    int n_of_c; // ilosc klientow
    int n_of_i; // ilosc instruktorow
    int n_of_l; // ilosc ratownikow
    int length; // dlugosc toru
    int tr_limit; // ilosc ludzi na tor
    Da_Pool gowno;
    Time start_time; // godzina otwarcia
    Time closing_time; // godzina zamkniecia
    std::vector<Reservation> res;

    Simulation(std::string using_databaze, std::string reservations);

    void start_reservation(int resi);
    void customers_movements(int par);
    void lifeguards_enters(); //  na starcie && zmiany kadry
    int client_enters();
    int set_max_ppl();
    void exit_client();
    void summary_of_tick(int random_number);
    void summary_of_day(); // podsumowanie dnia
    void main_simulation(); // funkcja ktora zawiera wszytskie inne funkcje
    int number_of_enters();
    int give_random_number(int zakres);
};
#endif
