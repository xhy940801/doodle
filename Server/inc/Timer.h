#ifndef _TIMER_H
#define _TIMER_H

#include <chrono>

/**
 * @author xiao.hy
 */
class Timer
{
	std::chrono::time_point<std::chrono::high_resolution_clock> begin;
public:
	Timer();
	~Timer();

	unsigned long elapsed() const;
	unsigned long elapsed_micro() const;
	unsigned long elapsed_nano() const;
	unsigned long elapsed_seconds() const;
	unsigned long elapsed_minutes() const;
	unsigned long elapsed_hours() const;
};

#endif