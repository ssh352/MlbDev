// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the sleep functions.

	Revision History	:	1998-04-08 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////


#ifndef HH__MLB__Utility__Sleep_hpp__HH

#define HH__MLB__Utility__Sleep_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file Sleep.hpp

	\brief	The sleep functions header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/TimeSupport.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY void     SleepSecs(unsigned long seconds);
API_UTILITY void     SleepMilliSecs(unsigned long milliseconds);
API_UTILITY void     SleepMicroSecs(unsigned long microseconds);
API_UTILITY void     SleepNanoSecs(unsigned long nanoseconds);
API_UTILITY void     SleepNanoSecs(unsigned long long nanoseconds);
API_UTILITY TimeSpec NanoSleep(const TimeSpec &request);
API_UTILITY void     YieldThreadQuantum();
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__Sleep_hpp__HH

