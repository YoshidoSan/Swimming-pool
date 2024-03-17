#include <iostream>
#include <vector>
#include <sstream>
#include "Instructor.h"

using namespace std;

Instructor::Instructor(
    string na,
    string sur,
    int wid,
    int ex,
    Time s,
    Time f,
    vector <Client> gr
) : Lifeguard(na, sur, wid, ex, s, f)
{
    name = na;
    surname = sur;
    work_id = wid;
    experience = ex;
    start = s;
    finish = f;
    group = gr;
}

void Instructor::add_persongroup(Client& new_person)
{
    group.push_back(new_person);
}

ostream& operator << (ostream& output, Instructor& i)
{
    cout << "Name: " << i.name << endl;
    cout << "Surname: " << i.surname << endl;
    cout << "Worker id: " << i.work_id << endl;
    cout << "Experience level " << i.experience << endl;
    return output;
}

bool Instructor::operator == (Instructor& i1)
{
    if (i1.work_id == work_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Instructor::operator != (Instructor& i1)
{
    if ((i1.name == name) &&
        (i1.surname == surname) &&
        (i1.work_id == work_id))
    {
        return false;
    }
    else
    {
        return true;
    }
}

Instructor Instructor::operator=(Instructor i)
{

    name = i.name;
    surname = i.surname;
    work_id = i.work_id;
    experience = i.experience;
    start = i.start;
    finish = i.finish;
    group = i.group;
    return*this;
}
