#include "pch.h"
#include "Timer.h"

size_t Timer::pushNewInstance(bool is_count_up, chrono::seconds tick, int& shared_var) {
	size_t size = timers.size();
	size_t id;
	if (size != 0) id = size;
	else id = 0;
	//auto temp = std::make_shared
	timers.push_back(std::make_shared<Timer_Instance>(is_count_up, tick, id, shared_var));

	return id;
}

size_t Timer::pushNewInstance(bool is_count_up, chrono::seconds tick, int& shared_var, size_t time_to_run) {
	size_t size = timers.size();
	size_t id;
	if (size != 0) id = size;
	else id = 0;
	timers.push_back(std::make_shared<Timer_Instance>(is_count_up, tick, id, shared_var, time_to_run));

	return id;
}

std::shared_ptr<Timer_Instance> Timer::getInstance(int id) {
	return timers[id];
}

void Timer::clearVector() {
	for (auto it = timers.begin(); it != timers.end(); it++) {
		it->get()->active = false;
	}
	timers.clear();
}

Timer_Instance::Timer_Instance(bool is_count_up, chrono::seconds tick, int id, int& shared_var) {
	try {
		if (id < 0) throw "[Timer] Could not create timer instance!";
		this->is_count_up = is_count_up;
		this->time_to_run = shared_var;
		this->tick = tick;
		this->id = id;
		this->shared_var = &shared_var;
	}
	catch (exception e) {
		err = e.what();
		return;
	}

}

Timer_Instance::Timer_Instance(bool is_count_up, chrono::seconds tick, int id, int& shared_var, size_t time_to_run) {
	try {
		if (id < 0) throw "[Timer] Could not create timer instance!";
		this->is_count_up = is_count_up;
		this->time_to_run = time_to_run;
		this->tick = tick;
		this->id = id;
		this->shared_var = &shared_var;
	}
	catch (exception e) {
		err = e.what();
		return;
	}

}

void Timer_Instance::start() {
	if(!is_count_up){
		pthread = std::make_shared<thread>(thread([this]() { //on countdown
			while (*shared_var > 0 && active) {
				*shared_var = *shared_var - 1;
				this_thread::sleep_for(tick);
			}
			return;
			}));
	}
	else {
		pthread = std::make_shared<thread>(thread([this]() { //on countup
			while (*shared_var < time_to_run && active) {
				*shared_var = *shared_var + 1;
				this_thread::sleep_for(tick);
			}
			return;
			}));
	}

	pthread->detach();
}