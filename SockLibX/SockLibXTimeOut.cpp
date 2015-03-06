//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	SockLibX Portable Socket Library Source Module
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the SockLibXTimeOut class.

	Revision History	:	2002-01-26 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2002 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Include necessary header files . . .
//	////////////////////////////////////////////////////////////////////////////

#include <SockLibX.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace SockLibX {

//	////////////////////////////////////////////////////////////////////////////
SockLibXTimeOut::SockLibXTimeOut()
	:SockLibXException("Socket select() timed-out.")
	,time_out_(0, 0)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SockLibXTimeOut::SockLibXTimeOut(const char *except_string)
	:SockLibXException(except_string)
	,time_out_(0, 0)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SockLibXTimeOut::SockLibXTimeOut(const std::string &except_string)
	:SockLibXException(except_string)
	,time_out_(0, 0)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SockLibXTimeOut::SockLibXTimeOut(const std::ostringstream &except_string)
	:SockLibXException(except_string)
	,time_out_(0, 0)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SockLibXTimeOut::SockLibXTimeOut(const MLB::Utility::TimeVal &time_out)
	:SockLibXException(GetTimeOutString(time_out))
	,time_out_(time_out)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SockLibXTimeOut::SockLibXTimeOut(const MLB::Utility::TimeVal &time_out,
	const char *except_string)
	:SockLibXException(GetTimeOutString(time_out, except_string))
	,time_out_(time_out)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SockLibXTimeOut::SockLibXTimeOut(const MLB::Utility::TimeVal &time_out,
	const std::string &except_string)
	:SockLibXException(GetTimeOutString(time_out, except_string.c_str()))
	,time_out_(time_out)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SockLibXTimeOut::SockLibXTimeOut(const MLB::Utility::TimeVal &time_out,
	const std::ostringstream &except_string)
	:SockLibXException(GetTimeOutString(time_out, except_string.str().c_str()))
	,time_out_(time_out)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SockLibXTimeOut::~SockLibXTimeOut() MBCOMPAT_EXCEPT_NOTHROW
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
MLB::Utility::TimeVal SockLibXTimeOut::GetTimeOut() const
{
	return(time_out_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SockLibXTimeOut::Rethrow(const char *except_string) const
{
	SockLibXTimeOut tmp_except(*this);

	tmp_except.SetWhat(except_string);

	throw tmp_except;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string SockLibXTimeOut::GetTimeOutString(
	const MLB::Utility::TimeVal &time_out, const char *other_text)
{
	std::ostringstream time_out_string;

	time_out_string << "Socket library exception resulted from a wait " <<
		"which exceeded the specified time-out period (" <<
		time_out.ToStringInterval() << ")."<<
		((other_text != NULL) ? ": " : "") <<
		((other_text != NULL) ? other_text : "");

	return(time_out_string.str());
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace SockLibX

} // namespace MLB

