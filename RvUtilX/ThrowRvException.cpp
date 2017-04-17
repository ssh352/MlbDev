// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	TibCo/Rendezvous Support Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Provides an interface for throwing RvUtilX exceptions.

	Revision History	:	2001-10-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2017.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <RvUtilX.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace RvUtilX {

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvStatus(TibrvStatus error_code, const char *error_text)
{
	throw RvExceptionStatus(error_code, error_text);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvStatus(TibrvStatus error_code, const std::string &error_text)
{
	throw RvExceptionStatus(error_code, error_text);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvStatus(TibrvStatus error_code,
	const std::ostringstream &error_text)
{
	throw RvExceptionStatus(error_code, error_text);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOut(double time_out, const char *error_text)
{
	throw RvExceptionTimeOut(time_out,
		((error_text != NULL) && *error_text) ? error_text :
		"TibCo/Rendezvous function timed-out.");
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOut(double time_out, const std::string &error_text)
{
	ThrowTibrvTimeOut(time_out, error_text.c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOut(double time_out, const std::ostringstream &error_text)
{
	ThrowTibrvTimeOut(time_out, error_text.str().c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOutIf(TibrvStatus rv_status, double time_out,
	const char *error_text)
{
	if (rv_status == TIBRV_TIMEOUT)
		ThrowTibrvTimeOut(time_out, error_text);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOutIf(TibrvStatus rv_status, double time_out,
	const std::string &error_text)
{
	ThrowTibrvTimeOutIf(rv_status, time_out, error_text.c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOutIf(TibrvStatus rv_status, double time_out,
	const std::ostringstream &error_text)
{
	ThrowTibrvTimeOutIf(rv_status, time_out, error_text.str().c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOut(const char *function_name, double time_out)
{
	std::ostringstream error_text;

	error_text << "Invocation of '" <<
		(((function_name != NULL) && *function_name) ? function_name :
			"*UNSPECIFIED TIBCO/RV FUNCTION*") <<
		(((function_name != NULL) && *function_name) ? "()" : "") <<
		"' resulted in a wait which exceeded the specified time-out period (" <<
		time_out << " seconds).";

	ThrowTibrvTimeOut(time_out, error_text);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOut(const std::string &function_name, double time_out)
{
	ThrowTibrvTimeOut(function_name.c_str(), time_out);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOut(const std::ostringstream &function_name, double time_out)
{
	ThrowTibrvTimeOut(function_name.str().c_str(), time_out);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOutIf(TibrvStatus rv_status, const char *function_name,
	double time_out)
{
	if (rv_status == TIBRV_TIMEOUT)
		ThrowTibrvTimeOut(function_name, time_out);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOutIf(TibrvStatus rv_status,
	const std::string &function_name, double time_out)
{
	ThrowTibrvTimeOutIf(rv_status, function_name.c_str(), time_out);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ThrowTibrvTimeOutIf(TibrvStatus rv_status,
	const std::ostringstream &function_name, double time_out)
{
	ThrowTibrvTimeOutIf(rv_status, function_name.str().c_str(), time_out);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace RvUtilX

} // namespace MLB

