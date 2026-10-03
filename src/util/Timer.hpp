#pragma once

#include <iostream>
#include <SDL3/SDL.h>

class Timer {
	public:
		Timer();

		float getDeltaTimeNS();
		float getDeltaTimeMS();

		float getFrameDeltaTimeNS();
		float getFrameDeltaTimeMS();

		float getTickDeltaTimeNS();
		float getTickDeltaTimeMS();

		void swapTimes();
		void swapTime();
		void swapFrameTime();
		void swapTickTime();

		void setLastTimes();
		void setLastTime();
		void setLastFrameTime();
		void setLastTickTime();

		void setCurrentTime();
		float getCurrentTime() { return m_current_time; }

		float getLastTime() { return m_last_time; }
		float getLastFrameTime() { return m_last_frame_time; }
		float getLastTickTime() { return m_last_tick_time; }

		void printDeltaTimeNS() { std::cout << "ΔNT: " << getFrameDeltaTimeNS() << std::endl; }
		void printFrameDeltaTimeNS() { std::cout << "ΔFT: " << getFrameDeltaTimeNS() << std::endl; }
		void printTickDeltaTimeNS() { std::cout << "ΔTT: " << getTickDeltaTimeNS() << std::endl; }

		void printDeltaTimeMS() { std::cout << "ΔNT: " << getFrameDeltaTimeMS() << std::endl; }
		void printFrameDeltaTimeMS() { std::cout << "ΔFT: " << getFrameDeltaTimeMS() << std::endl; }
		void printTickDeltaTimeMS() { std::cout << "ΔTT: " << getTickDeltaTimeMS() << std::endl; }
		
	private:
	long m_current_time = SDL_GetTicksNS();
	long m_last_time;
	long m_last_frame_time;
	long m_last_tick_time;
};