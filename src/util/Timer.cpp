#include "Timer.hpp"

Timer::Timer() {}

float Timer::getDeltaTimeNS() {
	return m_current_time - m_last_time;
}

float Timer::getDeltaTimeMS() {
	return (m_current_time - m_last_time) / 1000000.0;
}

float Timer::getFrameDeltaTimeNS() {
	return m_current_time - m_last_frame_time;
}

float Timer::getFrameDeltaTimeMS() {
	return (m_current_time - m_last_frame_time) / 1000000.0;
}

float Timer::getTickDeltaTimeNS() {
	return m_current_time - m_last_tick_time;
}

float Timer::getTickDeltaTimeMS() {
	return (m_current_time - m_last_tick_time) / 1000000.0;
}

void Timer::swapTimes() {
	swapTime();
	swapFrameTime();
	swapTickTime();
}

void Timer::swapTime() {
	m_last_time = m_current_time;
}

void Timer::swapFrameTime() {
	m_last_frame_time = m_current_time;
}

void Timer::swapTickTime() {
	m_last_tick_time = m_current_time;
}

void Timer::setLastTimes() {
	setLastTime();
	setLastFrameTime();
	setLastTickTime();
}

void Timer::setLastTime() {
	m_last_time = SDL_GetTicksNS();
}

void Timer::setLastFrameTime() {
	m_last_frame_time = SDL_GetTicksNS();
}

void Timer::setLastTickTime() {
	m_last_tick_time = SDL_GetTicksNS();
}

void Timer::setCurrentTime() {
	m_current_time = SDL_GetTicksNS();
}