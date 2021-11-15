#include "pch.h"
#include <time.h>

class Timer {
	public:
	Timer() {};
	void start() { if (!block) { init = clock(); cock = init; } };
	float getTime() {
		if (current_time > 0) { 
			cock = clock(); 
			return current_time = (((float)cock) / CLOCKS_PER_SEC) - (((float)init) / CLOCKS_PER_SEC); 
		} 
		return 0; 
	};
	//void stop();
	//void restart();
	bool block = false;
	float current_time = 0;
	private:
	clock_t cock,init;
	
	
};