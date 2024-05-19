#ifndef Computer_Club_H
#define Computer_Club_H

#include <iostream>
#include <fstream>
#include <string>
#include "Event.h"
#include <queue>
#include <map>
#include <set>
#include <list>
#include <cctype>
#include <vector>

using namespace std;

struct Table {
	Time work_time;
	Time current_client_sat_down;
	Time current_client_left;
	string name_client;
	int proceeds = 0;
	void table_is_free(const int cost);
};

class Computer_Club {
private:
	int number_of_tables;
	int number_of_free_tables;
	int cost_per_hour;
	Time start_time;
	Time end_time;
	queue<Event> event_queue;
	list<string> queue_visitors;
	set<string> current_visitors; 
	vector<Table> tables;

public:
	int get_number_of_tables()const;
	Time get_start_time()const;
	Time get_end_time()const;
	int get_cost_per_hour()const;
	queue<Event> get_queue_event()const;

	void take_configuration(const string configuration);
	void computer_club_work();

	void event_processing_client_arrived(const Event event);
	void event_processing_client_sat_down(const Event event);
	void event_processing_client_is_waiting(const Event event);
	void event_processing_client_left(const Event event);
	 
	void outgoing_event_processing_client_left(const Event event);
	void outgoing_event_processing_client_sat_down(const Event event);
};

#endif
