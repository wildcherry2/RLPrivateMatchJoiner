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
		size_t pushNewInstance(double& shared_var,int time_to_run);
		Timer_Instance* getInstance(int id);
		void clearVector();
		void begin();
		void destroy();

	private:
		thread time_th;
		vector<Timer_Instance> timers;
		bool timer_running = true;
};

struct Timer_Instance {
	Timer_Instance(int id,double& shared_var, int time_to_run);
	void start();
	void tock();

	double* shared_var;
	double start_time;
	int time_to_run = -1;
	int tick = 1;
	string err = "";
	bool done = false, has_started = false;
	int id = -1;
};

