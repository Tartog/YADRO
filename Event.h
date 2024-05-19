#ifndef Event_H
#define Event_H

#include <iostream>
#include <string>

using namespace std;

struct Time {
	int hours = 0;
	int minutes = 0;
	bool insignificant_zero_hours = false;
	bool insignificant_zero_minutes = false;
	bool operator >(const Time time)const;
	bool operator <(const Time time)const;
	bool operator ==(const Time time)const;
	bool operator >=(const Time time)const;
	Time operator -(const Time time)const;
	Time operator +(const Time time)const;
};

ostream& operator<<(ostream &os, const Time &time);

class Event {
private:
	int event_ID;
	Time time_event;
	string configuration;
public:
	Event(const string event_configuration);
	Event(const Time time, int ID, string configuration);
	int get_event_ID()const;
	Time get_time_event()const;
	string get_configuration()const;
};
ostream& operator<<(ostream &os, const Event &event);

#endif
