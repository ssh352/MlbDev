//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Provides portable high-resolution time stamp.

	Revision History	:	1993-10-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////
 
//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Required include files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility/HRTimeStamp.hpp>
#include <Utility/StringSupport.hpp>

#ifdef __GNUC__
# include <string.h>
#endif // #ifdef __GNUC__

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
HRTimeStamp::HRTimeStamp(bool init_flag)
	:time_utc_((init_flag) ? TimeSpec() : TimeSpec(0, 0))
	,time_tick_((init_flag) ? HRTimer::GetTicksCurrentFromSystem() : 0)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimeStamp::HRTimeStamp(const timespec &in_time, HRTimerTick in_ticks)
	:time_utc_(in_time)
	,time_tick_(in_ticks)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool HRTimeStamp::operator <  (const HRTimeStamp &other) const
{
	return(Compare(this, &other) <  0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool HRTimeStamp::operator >  (const HRTimeStamp &other) const
{
	return(Compare(this, &other) >  0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool HRTimeStamp::operator == (const HRTimeStamp &other) const
{
	return(Compare(this, &other) == 0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool HRTimeStamp::operator != (const HRTimeStamp &other) const
{
	return(Compare(this, &other) != 0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool HRTimeStamp::operator <= (const HRTimeStamp &other) const
{
	return(Compare(this, &other) <= 0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool HRTimeStamp::operator >= (const HRTimeStamp &other) const
{
	return(Compare(this, &other) >= 0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimeStamp &HRTimeStamp::SetToNow()
{
	HRTimeStamp(true).swap(*this);

	return(*this);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimeStamp &HRTimeStamp::SetToMinimumValue()
{
	time_utc_.SetToMinimumValue();

	time_tick_ = 0;

	return(*this);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimeStamp &HRTimeStamp::SetToMaximumValue()
{
	time_utc_.SetToMaximumValue();

	time_tick_ = std::numeric_limits<HRTimerTick>::max();

	return(*this);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
char *HRTimeStamp::ToString(char *buffer, unsigned int max_length) const
{
	if (max_length < HRTimeStampLength) {
		char tmp_buffer[HRTimeStampLength + 1];
		return(nstrcpy(buffer, ToString(tmp_buffer), max_length));
	}

	time_utc_.ToString(buffer, HRTimeStampLength);

	buffer[Length_TimeSpec] = '.';

	::strcpy(buffer + Length_TimeSpec + 1,
		ZeroFill(static_cast<unsigned long long>(time_tick_), 20).c_str());

	return(buffer);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string HRTimeStamp::ToString(unsigned int max_length) const
{
	char buffer[HRTimeStampLength + 1];

	return(ToString(buffer, max_length));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string &HRTimeStamp::ToString(std::string &out_string,
	unsigned int max_length) const
{
	char buffer[HRTimeStampLength + 1];

	return(out_string.assign(ToString(buffer, max_length)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void HRTimeStamp::swap(HRTimeStamp &other)
{
	time_utc_.swap(other.time_utc_);
	std::swap(time_tick_, other.time_tick_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int HRTimeStamp::Compare(const HRTimeStamp *lhs, const HRTimeStamp *rhs)
{
	int cmp;

	if ((cmp = TimeSpec::Compare(&lhs->time_utc_, &rhs->time_utc_)) == 0)
		cmp = BasicCompare(static_cast<unsigned long long>(lhs->time_tick_),
			static_cast<unsigned long long>(rhs->time_tick_));

	return(cmp);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimeStamp HRTimeStamp::GetMinimumValue()
{
	HRTimeStamp tmp_datum(false);

	return(tmp_datum.SetToMinimumValue());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
HRTimeStamp HRTimeStamp::GetMaximumValue()
{
	HRTimeStamp tmp_datum(false);

	return(tmp_datum.SetToMaximumValue());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str, const HRTimeStamp &datum)
{
	char out_string[HRTimeStampLength + 1];

	o_str <<
		datum.ToString(out_string);

	return(o_str);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB


#ifdef TEST_MAIN

#include <iomanip>

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
			::Sleep(TEST_SleepTimes[count_1]);
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

