#include "pch.h"
#include "Timer.h"

size_t Timer::pushNewInstance(double& shared_var,int time_to_run) {
	size_t size = timers.size();
	size_t id;
	if (size != 0) id = size;
	else id = 0;
	timers.push_back(Timer_Instance(id, shared_var,time_to_run));
	return id;
}

Timer_Instance* Timer::getInstance(int id) {
	return &timers[id];
}

void Timer::clearVector() {
	timers.clear();
}

void Timer::deleteInstance(int id) {
	if(id < timers.size())
	{
		timers.erase(timers.begin() + id);
	}
}

void Timer::destroy() {
	timer_running = false;
	clearVector();
}

void Timer::begin() {
	time_th = thread([this]() {
		while (timer_running) {	
			if (timers.size() == 0) {
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			if(timers.size() != 0)
			{
				for (auto it = timers.begin(); it != timers.end(); it++) {
					if (it->has_started && !it->done) it->tock();
					/*else if (!it->has_started && !it->done) {
						it->start();
					}*/
					else if(it->has_started && it->done) {
						timers.erase(it);
					}
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}

		return;
		});

	time_th.detach();
}

Timer_Instance::Timer_Instance(int id,double& shared_var,int time_to_run) {
	try {
		if (id < 0) throw "[Timer] Could not create timer instance!";
		this->time_to_run = time_to_run;
		this->tick = tick;
		this->id = id;
		this->shared_var = &shared_var;
		this->start_time = 0;
	}
	catch (exception e) {
		err = e.what();
		return;
	}
}

void Timer_Instance::tock() {
	if (*shared_var >= time_to_run) { done = true; }
	else *shared_var = ImGui::GetTime() - start_time;
}

void Timer_Instance::start() {
	start_time = ImGui::GetTime();
	*shared_var = 0;
	has_started = true;
}