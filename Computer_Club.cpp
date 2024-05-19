#include "Computer_Club.h"

int Computer_Club::get_number_of_tables()const {
	return number_of_tables;
}

Time Computer_Club::get_start_time()const {
	return start_time;
}

Time Computer_Club::get_end_time()const {
	return end_time;
}

int Computer_Club::get_cost_per_hour()const {
	return cost_per_hour;
}

queue<Event> Computer_Club::get_queue_event()const {
	return event_queue;
}

void Computer_Club::take_configuration(const string configuration) {
	ifstream in(configuration);
	string line;
	if (!in.is_open()) {
		cout << "Please enter a valid file name !" << endl;
		exit(-1);
	}
	try {
		getline(in, line);
		number_of_tables = stoi(line);
		number_of_free_tables = number_of_tables;

		for (char c : line) {
			if (!isdigit(c)) {
				throw invalid_argument(line);
			}
		}
		for (int i = 1; i < (number_of_tables + 1); i++) {
			Table table;
			table.work_time.hours = 0;
			if (table.work_time.hours < 10) { table.work_time.insignificant_zero_hours = true; }
			table.work_time.minutes = 0;
			if (table.work_time.minutes < 10) { table.work_time.insignificant_zero_minutes = true; }
			tables.push_back(table);
		}

		getline(in, line);
		start_time.hours = stoi(line.substr(0, 2));
		for (char c : line.substr(0, 2)) {
			if (!isdigit(c)) {
				throw invalid_argument(line);
			}
		}
		start_time.minutes = stoi(line.substr(3, 2));
		for (char c : line.substr(3, 2)) {
			if (!isdigit(c)) {
				throw invalid_argument(line);
			}
		}
		end_time.hours = stoi(line.substr(6, 2));
		end_time.minutes = stoi(line.substr(9, 2));
		if (line[2] != ':' || line[5] != ' ' || line[8] != ':' || line.size() != 11) { throw invalid_argument(line); }
		if (start_time.hours < 10) { start_time.insignificant_zero_hours = true; }
		if (start_time.minutes < 10) { start_time.insignificant_zero_minutes = true; }
		if (end_time.hours < 10) { end_time.insignificant_zero_hours = true; }
		if (end_time.minutes < 10) { end_time.insignificant_zero_minutes = true; }
		if (start_time >= end_time) { throw invalid_argument(line); }

		getline(in, line);
		cost_per_hour = stoi(line);
		for (char c : line) {
			if (!isdigit(c)) {
				throw invalid_argument(line);
			}
		}

		Time time_of_previous_event;
		time_of_previous_event.insignificant_zero_hours = true;
		time_of_previous_event.insignificant_zero_minutes = true;
		while (getline(in, line)) {
			Time t;
			t.hours = stoi(line.substr(0, 2));
			for (char c : line.substr(0, 2)) {
				if (!isdigit(c)) {
					throw invalid_argument(line);
				}
			}
			t.minutes = stoi(line.substr(3, 2));
			for (char c : line.substr(3, 2)) {
				if (!isdigit(c)) {
					throw invalid_argument(line);
				}
			}
			if (t.hours < 10) { t.insignificant_zero_hours = true; }
			if (t.minutes < 10) { t.insignificant_zero_minutes = true; }

			if (time_of_previous_event > t || line[6] - '0' < 1 || line[6] - '0' > 4 || line[2] != ':' || line[5] != ' ' || line[7] != ' ') {
				throw invalid_argument(line);
			}
			string name_client = line.substr(8, line.size() - 10);
			for (char c : name_client) {
				if (!(islower(c) || isdigit(c) || c == '_' || c == '-')) {
					throw invalid_argument(line);
				}
			}
			if (line[6] - '0' == 2) {
				if (line.substr(8 + name_client.size())[0] != ' ') {
					throw invalid_argument(line);
				}
				string table_for_client = line.substr(9 + name_client.size());
				int table_for_client_int = stoi(table_for_client);
				for (char c : table_for_client) {
					if (!isdigit(c)) {
						throw invalid_argument(line);
					}
				}
				if (table_for_client_int > number_of_tables || table_for_client_int == 0) {
					throw invalid_argument(line);
				}
			}

			time_of_previous_event = t;

			Event event(line);
			event_queue.push(line);
		}
	}
	catch (const invalid_argument& e) {
		cerr << line << endl;
		exit(-1);
	}

	in.close();
}

void Computer_Club::computer_club_work() {
	cout << start_time << endl;
	while (!event_queue.empty() && !(event_queue.front().get_time_event() >= end_time)) {
		Event current_event = event_queue.front();
		try {
			switch (current_event.get_event_ID()) {
			case 1:
				event_processing_client_arrived(current_event);
				break;
			case 2:
				event_processing_client_sat_down(current_event);
				break;
			case 3:
				event_processing_client_is_waiting(current_event);
				break;
			case 4:
				event_processing_client_left(current_event);
				break;
			}
		}
		catch (Event event) {
			switch (event.get_event_ID()) {
			case 13:
				cout << event << endl;
				break;
			case 11:
				outgoing_event_processing_client_left(event);
				break;
			case 12:
				outgoing_event_processing_client_sat_down(event);
				break;
			}
		}
		event_queue.pop();
	}

	while (current_visitors.size() != 0) {
		Event event(end_time, 11, *(current_visitors.begin()));
		outgoing_event_processing_client_left(event);
	}
	
	cout << end_time << endl;

	int num_table = 1;
	for (auto i : tables) {
		cout << num_table << " " << i.proceeds << " " << i.work_time << endl;
		num_table++;
	}
}

void Computer_Club::event_processing_client_arrived(const Event event){
	cout << event << endl;
	if (current_visitors.find(event.get_configuration()) == current_visitors.end()) {
		if (event.get_time_event() < start_time) {
			throw Event(event.get_time_event(), 13, "NotOpenYet");
		}
		else {
			current_visitors.emplace(event.get_configuration());
		}
	}
	else {
		throw Event(event.get_time_event(), 13, "YouShellNotPass");
	}
}

void Computer_Club::event_processing_client_sat_down(const Event event) {
	cout << event << endl;

	int num_table = event.get_configuration().back() - '0';
	string name_client = event.get_configuration().substr(0, event.get_configuration().size() - 2);

	if (current_visitors.find(name_client) == current_visitors.end()) {
		throw Event(event.get_time_event(), 13, "ClientUnknown");
	}
	if (tables[num_table - 1].name_client.empty()) {
		for (auto i = tables.begin(); i != tables.end();i++) {
			if (i->name_client == name_client) {
				i->current_client_left = event.get_time_event();
				i->table_is_free(cost_per_hour);
				number_of_free_tables++;
				break;
			}
		}
		for (auto i = queue_visitors.begin(); i != queue_visitors.end(); i++) {
			if (*i == name_client) {
				queue_visitors.erase(i);
				break;
			}
		}
		tables[num_table - 1].name_client = name_client;
		tables[num_table - 1].current_client_sat_down = event.get_time_event();
		number_of_free_tables--;
	}
	else {
		throw Event(event.get_time_event(), 13, "PlaceIsBusy");
	}
}

void Computer_Club::event_processing_client_is_waiting(const Event event) {
	cout << event << endl;
	string name_client = event.get_configuration();
	queue_visitors.push_back(name_client);
	
	if (queue_visitors.size() >= number_of_tables) {
		throw Event(event.get_time_event(), 11, name_client);
	}
	if (number_of_free_tables != 0) {
		throw Event(event.get_time_event(), 13, "ICanWaitNoLonger!");
	}
}

void Computer_Club::event_processing_client_left(const Event event) {
	cout << event << endl;
	string name_client = event.get_configuration();
	if (current_visitors.find(name_client) == current_visitors.end()) {
		throw Event(event.get_time_event(), 13, "ClientUnknown");
	}
	current_visitors.erase(name_client);

	int num_table = 1;
	for (auto i = tables.begin(); i != tables.end(); i++) {
		if (i->name_client == name_client) {
			i->current_client_left = event.get_time_event();
			i->table_is_free(cost_per_hour);
			number_of_free_tables++;
			break;
		}
		num_table++;
	}
	for (auto i = queue_visitors.begin(); i != queue_visitors.end(); i++) {
		if (*i == name_client) {
			queue_visitors.erase(i);
			break;
		}
	}

	if (!queue_visitors.empty() && number_of_free_tables != 0) {
		throw Event(event.get_time_event(), 12, queue_visitors.front() + " " + to_string(num_table));
	}
}

void Computer_Club::outgoing_event_processing_client_left(const Event event) {
	cout << event << endl;
	string name_client = event.get_configuration();
	queue_visitors.remove(name_client);
	current_visitors.erase(name_client);

	for (auto i = tables.begin(); i != tables.end(); i++) {
		if (i->name_client == name_client) {
			i->current_client_left = event.get_time_event();
			i->table_is_free(cost_per_hour);
			number_of_free_tables++;
			break;
		}
	}
}

void Computer_Club::outgoing_event_processing_client_sat_down(const Event event) {
	cout << event << endl;
	int num_table = event.get_configuration().back() - '0';
	string name_client = event.get_configuration().substr(0, event.get_configuration().size() - 2);

	tables[num_table - 1].current_client_sat_down = event.get_time_event();
	tables[num_table - 1].name_client = name_client;
	number_of_free_tables--;

	queue_visitors.pop_front();
}

void Table::table_is_free(const int cost) {
	Time temp = current_client_left - current_client_sat_down;
	proceeds += temp.hours * cost;
	if (temp.minutes > 0) {
		proceeds += cost;
	}

	current_client_left.hours = current_client_left.minutes = current_client_sat_down.hours = current_client_sat_down.minutes = 0;

	current_client_left.insignificant_zero_hours = current_client_left.insignificant_zero_minutes = 
		current_client_sat_down.insignificant_zero_hours = current_client_sat_down.insignificant_zero_minutes = false;

	name_client.clear();

	work_time = work_time + temp;
}
