#include "pch.h"
#include <time.h>

class Timer {
	public:
	Timer() {};
	void start() { init = clock(); cock = init; current = time_to_count; };
	float getTime() {
		if (current > 0) { 
			cock = clock(); 
			current = time_to_count - (((float)cock - (float)init)/CLOCKS_PER_SEC);
			return current; 
		} 
		return 0; 
	};
	float time_to_count = 0;
	float current = 0;
	private:
	clock_t cock,init;
	
	
};