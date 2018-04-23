// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the HRTimer class.

	Revision History	:	1993-10-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////


#ifndef HH__MLB__Utility__HRTimer_hpp__HH

#define HH__MLB__Utility__HRTimer_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file HRTimer.hpp

	\brief	The MLB HRTimer header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
#ifdef __MSDOS__
typedef long     HRTimerTick;
#elif _Windows
typedef __int64  HRTimerTick;
#elif sun
typedef hrtime_t HRTimerTick;				//	Solaris
#else
typedef unsigned long long HRTimerTick;
#endif // #ifdef __MSDOS__
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
/**
	\brief A portable high-resolution timer class.
*/
struct API_UTILITY HRTimer {
	HRTimer();

	void Start();
	void End();

	HRTimerTick GetTicksPerSecond() const;
	HRTimerTick GetStartTick() const;
	HRTimerTick GetEndTick() const;
	HRTimerTick GetTickDiff() const;
	double      GetTickDiffInSeconds() const;

	HRTimer & operator += (const HRTimer &rhs);
	HRTimer & operator -= (const HRTimer &rhs);

	void swap(HRTimer &other);

	static HRTimerTick  GetTicksCurrentFromSystem();
	static HRTimerTick &GetTicksCurrentFromSystem(HRTimerTick &curr_tick);
	static HRTimerTick  GetTicksPerSecondFromSystem();
	static HRTimerTick &GetTicksPerSecondFromSystem(HRTimerTick &per_sec_ticks);

	HRTimerTick ticks_per_second_;
	HRTimerTick start_tick_;
	HRTimerTick end_tick_;
};
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
API_UTILITY HRTimerTick GetSystemTicksPerSecond();
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__HRTimer_hpp__HH

