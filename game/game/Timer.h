#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <gl/freeglut.h>
#include <iostream>
#include <thread>
#include <chrono>

class Timer {
	int interval;
	std::thread timerThread;

	static void repeat(Timer*);
public:
	bool running;
	Timer();

	void start();
	
	void setRate(int);

	void stop();

	int getRate();

	~Timer();

	virtual void action() = 0;

};
#endif /*TIMER_H*/