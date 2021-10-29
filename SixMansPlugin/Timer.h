#pragma once
#include "pch.h"
#include <chrono>
#include <thread>
#include <string>
#include <vector>

using namespace std;

struct Timer_Instance;

class Timer {
	public:
	size_t pushNewInstance(bool is_count_up, chrono::seconds tick, int& shared_var); //return id
	size_t pushNewInstance(bool is_count_up, chrono::seconds tick, int& shared_var, size_t time_to_run);

	std::shared_ptr<Timer_Instance> getInstance(int id);
	void clearVector();

	private:
	vector<std::shared_ptr<Timer_Instance>> timers;
};

struct Timer_Instance {
	
	Timer_Instance(bool is_count_up,chrono::seconds tick, int id, int& shared_var);
	Timer_Instance(bool is_count_up, chrono::seconds tick, int id, int& shared_var, size_t time_to_run);
	void start();

	int* shared_var;
	int current = 0;

	shared_ptr<thread> pthread;
	size_t time_to_run;
	chrono::seconds tick;
	string err = "";
	bool is_count_up, active = true;
	int id = -1;
};

