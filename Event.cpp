#include "Event.h"

Event::Event(const string event_configuration) {
	time_event.hours = stoi(event_configuration.substr(0, 2));
	if (time_event.hours < 10){
		time_event.insignificant_zero_hours = true;
	}
	time_event.minutes = stoi(event_configuration.substr(3, 2));
	if (time_event.minutes < 10) {
		time_event.insignificant_zero_minutes = true;
	}
	event_ID = event_configuration[6] - '0';
	configuration = event_configuration.substr(8);
}

Event::Event(const Time time, int ID, string configuration) {
	time_event = time;
	event_ID = ID;
	this->configuration = configuration;
}

int Event::get_event_ID()const{
	return event_ID;
}

Time Event::get_time_event()const {
	return time_event;
}

string Event::get_configuration()const {
	return configuration;
}

ostream& operator <<(std::ostream &os, const Time &time) {
	if (time.insignificant_zero_hours) {os << '0';}
	os << time.hours << ":";
	if (time.insignificant_zero_minutes) {os << '0';}
	os << time.minutes;
	return os;
}

ostream& operator<<(ostream &os, const Event &event) {
	return os << event.get_time_event() << " " << event.get_event_ID() << " " << event.get_configuration();
}

bool Time::operator>(const Time time)const {
	if (hours > time.hours) {return true;}
	else if (hours == time.hours) {
		if (minutes > time.minutes) {return true;}
	}
	return false;
}

bool Time::operator<(const Time time)const {
	if (*this > time || (this->hours == time.hours && this->minutes == time.minutes)) {return false;}
	return true;
}

bool Time::operator==(const Time time)const {
	if (*this > time || *this < time) {
		return false;
	}
	return true;
}

bool Time::operator>=(const Time time)const {
	if (*this > time || *this == time) {
		return true;
	}
	return false;
}

Time Time::operator-(const Time time)const {
	Time temp;
	int time_to_minutes = (this->hours * 60 + this->minutes) - (time.hours * 60 + time.minutes);
	temp.hours = time_to_minutes / 60;
	temp.minutes = time_to_minutes % 60;
	if (temp.hours < 10) {
		temp.insignificant_zero_hours = true;
	}
	if (temp.minutes < 10) {
		temp.insignificant_zero_minutes = true;
	}
	return temp;
}

Time Time::operator+(const Time time)const {
	Time temp;
	int time_to_minutes = (this->hours * 60 + this->minutes) + (time.hours * 60 + time.minutes);
	temp.hours = time_to_minutes / 60;
	temp.minutes = time_to_minutes % 60;
	if (temp.hours < 10) {
		temp.insignificant_zero_hours = true;
	}
	if (temp.minutes < 10) {
		temp.insignificant_zero_minutes = true;
	}
	return temp;
}
