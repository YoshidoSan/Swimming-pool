#include <iostream>
#include <vector>
#include <sstream>
#include "da_time.h"
#include "Lifeguard.h"
using namespace std;

Lifeguard::Lifeguard()
{
    name = "";
    surname = "";
    work_id = 0;
    experience = 1;
    busy = false;
    start = { -1,-1 };
    finish = { -1,-1 };
}

Lifeguard::Lifeguard(string na, string sur, int wid, int ex, Time s, Time f)
{
    name = na;
    surname = sur;
    work_id = wid;
    experience = ex;
    start = s;
    finish = f;
}

string Lifeguard::get_name()
{
    return name;
}

string Lifeguard::get_surname()
{
    return surname;
}

int Lifeguard::get_work_id()
{
    return work_id;
}

Time Lifeguard::get_starting_time()
{
    return start;
}

Time Lifeguard::get_finish_time()
{
    return finish;
}

ostream& operator << (ostream& output, Lifeguard& l)
{
    cout << "Name: " << l.name << endl;
    cout << "Surname: " << l.surname << endl;
    cout << "Worker id: " << l.work_id << endl;
    cout << "Experience level " << l.experience << endl;
    return output;
}

bool Lifeguard::operator == (Lifeguard& l1)
{
    if (l1.work_id == work_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Lifeguard::operator!= (Lifeguard& l1)
{
    if ((l1.name == name) &&
        (l1.surname == surname) &&
        (l1.work_id == work_id))
    {
        return false;
    }
    else
    {
        return true;
    }
}

Lifeguard Lifeguard::operator=(Lifeguard l)
{

    name = l.name;
    surname = l.surname;
    work_id = l.work_id;
    experience = l.experience;
    start = l.start;
    finish = l.finish;
    busy = l.busy;
    return*this;
}
