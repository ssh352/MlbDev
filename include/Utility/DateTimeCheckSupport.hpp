//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for date/time checking support.

	Revision History	:	2005-09-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2005 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////
 
#ifndef HH__MLB__Utility__DateTimeCheckSupport_hpp__HH

#define HH__MLB__Utility__DateTimeCheckSupport_hpp__HH	1

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Required include files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility.hpp>

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
const unsigned int DateSupport_YearMinimum = 1753;
const unsigned int DateSupport_YearMaximum = 9999;
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
API_UTILITY bool MonthOk(unsigned int in_month);
API_UTILITY bool YearOk(unsigned int in_year);
API_UTILITY bool YearMonthOk(unsigned int in_year, unsigned int in_month);
API_UTILITY bool IsLeapYear(unsigned int in_year);
API_UTILITY bool YearMonthDayOk(unsigned int in_year, unsigned int in_month,
	unsigned int in_day);

API_UTILITY unsigned int MonthDayMax(unsigned int in_year,
	unsigned int in_month);
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
inline bool MonthOk(unsigned int in_month)
{
	return((in_month >= 1) && (in_month <= 12));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
inline bool YearOk(unsigned int in_year)
{
	return((in_year >= DateSupport_YearMinimum) &&
		(in_year <= DateSupport_YearMaximum));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
inline bool YearMonthOk(unsigned int in_year, unsigned int in_month)
{
	return(YearOk(in_year) && MonthOk(in_month));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
inline bool YearMonthDayOk(unsigned int in_year, unsigned int in_month,
	unsigned int in_day)
{
	unsigned int month_day_max = MonthDayMax(in_year, in_month);

	return((month_day_max > 0) && (in_day <= month_day_max));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
inline bool IsLeapYear(unsigned int in_year)
{
	return((YearOk(in_year) &&
		(((!(in_year % 4)) && (in_year % 100)) ||
		 ((!(in_year % 4)) && (!(in_year % 400))))) ? true : false);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
inline unsigned int MonthDayMax(unsigned int in_year, unsigned int in_month)
{
	return((!YearMonthOk(in_year, in_month)) ? 0 :
		(((in_month == 1) || (in_month == 3) ||
		(in_month == 5) || (in_month == 7) || (in_month == 8) ||
		(in_month == 10) || (in_month == 12)) ? 31 : ((in_month == 4) ||
		(in_month == 6) || (in_month == 9) || (in_month == 11)) ? 30 :
		(28 + ((IsLeapYear(in_year)) ? 1 : 0))));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__DateTimeCheckSupport_hpp__HH

