#include "Timer.h"

Timer::Timer()
{
	begin = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{

}

unsigned long Timer::elapsed() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin).count();
}
unsigned long Timer::elapsed_micro() const
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - begin).count();
}
unsigned long Timer::elapsed_nano() const
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count();
}
unsigned long Timer::elapsed_seconds() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - begin).count();
}
unsigned long Timer::elapsed_minutes() const
{
	return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - begin).count();
}
unsigned long Timer::elapsed_hours() const
{
	return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - begin).count();
}