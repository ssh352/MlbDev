//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Provides portable high-resolution timing.

	Revision History	:	1993-10-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////
 
//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Required include files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility/HRTimer.hpp>
#include <Utility/Utility_Exception.hpp>

#ifdef __GNUC__
	// IMPLEMENTATION NOTE: Needed for gettimeofday()
# include <sys/time.h>
#endif // #ifdef __GNUC__

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
HRTimer::HRTimer()
	:ticks_per_second_(GetTicksPerSecondFromSystem())
	,start_tick_(0)
	,end_tick_(0)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void HRTimer::Start()
{
	GetTicksCurrentFromSystem(start_tick_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void HRTimer::End()
{
	GetTicksCurrentFromSystem(end_tick_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimerTick HRTimer::GetTicksPerSecond() const
{
	return(ticks_per_second_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimerTick HRTimer::GetStartTick() const
{
	return(start_tick_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimerTick HRTimer::GetEndTick() const
{
	return(end_tick_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimerTick HRTimer::GetTickDiff() const
{
	return(end_tick_ - start_tick_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
double HRTimer::GetTickDiffInSeconds() const
{
	return(static_cast<double>(GetTickDiff()) /
		static_cast<double>(ticks_per_second_));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimer & HRTimer::operator += (const HRTimer &rhs)
{
	end_tick_ += rhs.GetTickDiff();

	return(*this);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimer & HRTimer::operator -= (const HRTimer &rhs)
{
	end_tick_ -= rhs.GetTickDiff();

	return(*this);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void HRTimer::swap(HRTimer &other)
{
	std::swap(ticks_per_second_, other.ticks_per_second_);
	std::swap(start_tick_, other.start_tick_);
	std::swap(end_tick_, other.end_tick_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimerTick HRTimer::GetTicksCurrentFromSystem()
{
	HRTimerTick curr_tick;

	return(GetTicksCurrentFromSystem(curr_tick));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimerTick &HRTimer::GetTicksCurrentFromSystem(HRTimerTick &curr_tick)
{
#ifdef __MSDOS__
	struct timeb tmp_ftime;

	ftime(&tmp_ftime);
	curr_tick = (tmp_ftime.time * 1000) + tmp_ftime.millitm;
#elif _Windows
	if (::QueryPerformanceCounter(
		reinterpret_cast<LARGE_INTEGER *>(&curr_tick)) == 0)
		ThrowStdException("Invocation of 'QueryPerformanceCounter()' failed");
#elif sun
	curr_tick = static_cast<HRTimerTick>(gethrtime());
#else
	struct timeval tmp_timeval;

	::gettimeofday(&tmp_timeval, NULL);

	curr_tick = (static_cast<HRTimerTick>(tmp_timeval.tv_sec) *
		static_cast<HRTimerTick>(1000000)) +
		static_cast<HRTimerTick>(tmp_timeval.tv_usec);
#endif // #ifdef __MSDOS__

	return(curr_tick);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimerTick HRTimer::GetTicksPerSecondFromSystem()
{
	HRTimerTick per_sec_ticks;

	return(GetTicksPerSecondFromSystem(per_sec_ticks));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimerTick &HRTimer::GetTicksPerSecondFromSystem(HRTimerTick &per_sec_ticks)
{
#ifdef __MSDOS__
	per_sec_ticks = 1000;				//	Milliseconds for ftime()
#elif _Windows
	if (::QueryPerformanceFrequency(
		reinterpret_cast<LARGE_INTEGER *>(&per_sec_ticks)) == 0)
		ThrowStdException("Invocation of 'QueryPerformanceFrequency()' failed");
#elif sun
	per_sec_ticks = 1000000000;		//	Nanoseconds for gethrtime()
#else
	per_sec_ticks = static_cast<HRTimerTick>(1000000);
#endif // #ifdef __MSDOS__

	return(per_sec_ticks);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimerTick GetSystemTicksPerSecond()
{
	return(HRTimer::GetTicksPerSecondFromSystem());
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB


#ifdef TEST_MAIN

#include <cstdlib>
#include <iomanip>

#include <Utility/Sleep.hpp>

using namespace MLB::Utility;

//	////////////////////////////////////////////////////////////////////////////
static const unsigned int TEST_SleepTimes[] = { 0, 1, 10, 100, 1000 };
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	std::cout << "Test routine for class 'HRTimer'" << std::endl;
	std::cout << "---- ------- --- ----- ---------" << std::endl;

	try {
		HRTimer      hr_timer_total;
		HRTimer      hr_timer;
		unsigned int count_1;
		for (count_1 = 0;
			count_1 < (sizeof(TEST_SleepTimes) / sizeof(TEST_SleepTimes[0]));
			++count_1) {
			std::cout << "Sleep " << std::setw(4) << TEST_SleepTimes[count_1] <<
				": " << std::flush;
			hr_timer.Start();
			SleepSecs(TEST_SleepTimes[count_1]);
			hr_timer.End();
			std::cout << " --- elapsed time: " << std::setw(32) <<
				std::setprecision(12) << hr_timer.GetTickDiffInSeconds() <<
				std::endl;
			hr_timer_total += hr_timer;
		}
		std::cout << "Total time: " << std::setw(32) <<
				std::setprecision(12) << hr_timer_total.GetTickDiffInSeconds() <<
				std::endl;
	}
	catch (const std::exception &except) {
		std::cout << std::endl << std::endl;
		std::cout << "ERROR: " << except.what() << std::endl;
	}

	return(return_code);
}
//	////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

