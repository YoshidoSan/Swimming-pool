#ifndef Time_H
#define Time_H

#include <iostream>

struct Time
{
    int hour;
    int minutes;
    Time operator+(int min)
    {
        int temp =minutes + min%60;
        minutes = (temp)%60;
        hour = hour + min/60 + temp/60;
        return* this;
    }
    Time operator-(int min)
    {
        int temp = minutes - min%60;
        if(temp<0)
        {
            minutes = 60 + temp;
            hour = hour - minutes/60 - 1;
        }
        else
        {
            minutes = temp;
            hour  = hour - minutes/60;
        }
        return*this;
    }
    bool operator== (Time& tim)
    {
        if(hour == tim.hour && minutes == tim.minutes)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    friend std::ostream& operator << (std::ostream& output, Time& t)
    {
        if(t.minutes>9)
        {
            output<<t.hour<<":"<<t.minutes;
        }
        else
        {
            output<<t.hour<<":0"<<t.minutes;
        }
        return output;
    }
    bool operator<(Time& t)
    {
        if (hour>t.hour)
        {
            return false;
        }
        else if (hour<t.hour)
        {
            return true;
        }
        else if (minutes>=t.minutes)
        {
            return false;
        }
        else{return true;}
    }
};

#endif