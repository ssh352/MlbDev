//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the Utility exception classes.

	Revision History	:	1997-08-30 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1997 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////
 
//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Required include files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility/Utility_Exception.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
ExceptionGeneral::ExceptionGeneral(const char *except_string)
#if defined(_MSC_VER) && !defined(__MINGW32__)
	 :std::exception(GetFixedString(except_string))
#else
	 :std::exception()
#endif // #if defined(_MSC_VER) && !defined(__MINGW32__)
	,except_string_(GetFixedString(except_string))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionGeneral::ExceptionGeneral(const std::string &except_string)
#if defined(_MSC_VER) && !defined(__MINGW32__)
	:std::exception(GetFixedString(except_string.c_str()))
#else
	 :std::exception()
#endif // #if defined(_MSC_VER) && !defined(__MINGW32__)
	,except_string_(GetFixedString(except_string.c_str()))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionGeneral::ExceptionGeneral(const std::ostringstream &except_string)
#if defined(_MSC_VER) && !defined(__MINGW32__)
	:std::exception(GetFixedString(except_string.str().c_str()))
#else
	 :std::exception()
#endif // #if defined(_MSC_VER) && !defined(__MINGW32__)
	,except_string_(GetFixedString(except_string.str().c_str()))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionGeneral::~ExceptionGeneral() MBCOMPAT_EXCEPT_NOTHROW
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
const char *ExceptionGeneral::what() const throw()
{
	return(except_string_.c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ExceptionGeneral::SetWhat(const char *except_string)
{
	except_string_ = GetFixedString(except_string);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ExceptionGeneral::SetWhat(const std::string &except_string)
{
	except_string_ = GetFixedString(except_string.c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ExceptionGeneral::SetWhat(const std::ostringstream &except_string)
{
	except_string_ = GetFixedString(except_string.str().c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ExceptionGeneral::Rethrow(const char *except_string) const
{
	ExceptionGeneral tmp_except(*this);

	tmp_except.SetWhat(except_string);

	throw tmp_except;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ExceptionGeneral::Rethrow(const std::string &except_string) const
{
	Rethrow(except_string.c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ExceptionGeneral::Rethrow(const std::ostringstream &except_string) const
{
	Rethrow(except_string.str().c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
const char *ExceptionGeneral::GetFixedString(const char *except_string)
{
	return(((except_string == NULL) || (!(*except_string))) ?
		 "Unspecified exception." : except_string);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionErrno::ExceptionErrno()
	:ExceptionGeneral(GetErrnoString())
	,error_code_(GetLastErrnoCode())
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionErrno::ExceptionErrno(const char *except_string)
	:ExceptionGeneral(except_string)
	,error_code_(GetLastErrnoCode())
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionErrno::ExceptionErrno(const std::string &except_string)
	:ExceptionGeneral(except_string)
	,error_code_(GetLastErrnoCode())
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionErrno::ExceptionErrno(const std::ostringstream &except_string)
	:ExceptionGeneral(except_string)
	,error_code_(GetLastErrnoCode())
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionErrno::ExceptionErrno(int error_code)
	:ExceptionGeneral(GetErrnoString(error_code))
	,error_code_(error_code)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionErrno::ExceptionErrno(int error_code, const char *except_string)
	:ExceptionGeneral(GetStatusString(error_code, except_string))
	,error_code_(error_code)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionErrno::ExceptionErrno(int error_code,
	const std::string &except_string)
	:ExceptionGeneral(GetStatusString(error_code, except_string.c_str()))
	,error_code_(error_code)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionErrno::ExceptionErrno(int error_code,
	const std::ostringstream &except_string)
	:ExceptionGeneral(GetStatusString(error_code, except_string.str().c_str()))
	,error_code_(error_code)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionErrno::~ExceptionErrno() MBCOMPAT_EXCEPT_NOTHROW
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int ExceptionErrno::whatcode() const
{
	return(error_code_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ExceptionErrno::Rethrow(const char *except_string) const
{
	ExceptionErrno tmp_except(*this);

	tmp_except.SetWhat(except_string);

	throw tmp_except;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string ExceptionErrno::GetStatusString(int error_code,
	const char *other_text)
{
	std::ostringstream status_string;

	status_string <<
		(((other_text != NULL) && *other_text) ? other_text : "Error") <<
		": " << GetErrnoString(error_code);
	return(status_string.str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionSystemError::ExceptionSystemError()
	:ExceptionGeneral(GetSystemErrorString())
	,error_code_(GetLastSystemErrorCode())
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionSystemError::ExceptionSystemError(const char *except_string)
	:ExceptionGeneral(except_string)
	,error_code_(GetLastSystemErrorCode())
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionSystemError::ExceptionSystemError(const std::string &except_string)
	:ExceptionGeneral(except_string)
	,error_code_(GetLastSystemErrorCode())
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionSystemError::ExceptionSystemError(
	const std::ostringstream &except_string)
	:ExceptionGeneral(except_string)
	,error_code_(GetLastSystemErrorCode())
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionSystemError::ExceptionSystemError(SystemErrorCode error_code)
	:ExceptionGeneral(GetSystemErrorString(error_code))
	,error_code_(error_code)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionSystemError::ExceptionSystemError(SystemErrorCode error_code,
	const char *except_string)
	:ExceptionGeneral(GetStatusString(error_code, except_string))
	,error_code_(error_code)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionSystemError::ExceptionSystemError(SystemErrorCode error_code,
	const std::string &except_string)
	:ExceptionGeneral(GetStatusString(error_code, except_string.c_str()))
	,error_code_(error_code)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionSystemError::ExceptionSystemError(SystemErrorCode error_code,
	const std::ostringstream &except_string)
	:ExceptionGeneral(GetStatusString(error_code, except_string.str().c_str()))
	,error_code_(error_code)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionSystemError::ExceptionSystemError(bool, SystemErrorCode error_code,
	const std::string &except_string)
	:ExceptionGeneral(except_string)
	,error_code_(error_code)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionSystemError::~ExceptionSystemError() MBCOMPAT_EXCEPT_NOTHROW
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SystemErrorCode ExceptionSystemError::whatcode() const
{
	return(error_code_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ExceptionSystemError::Rethrow(const char *except_string) const
{
	ExceptionSystemError tmp_except(*this);

	tmp_except.SetWhat(except_string);

	throw tmp_except;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string ExceptionSystemError::GetStatusString(SystemErrorCode error_code,
	const char *other_text)
{
	std::ostringstream status_string;

	status_string <<
		(((other_text != NULL) && *other_text) ? other_text : "Error") <<
		": " << GetSystemErrorString(error_code);

	return(status_string.str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionMMapVMFailure::ExceptionMMapVMFailure()
	:ExceptionGeneral(GetFixedString())
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionMMapVMFailure::ExceptionMMapVMFailure(const char *except_string)
	:ExceptionGeneral(GetFixedString(except_string))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionMMapVMFailure::ExceptionMMapVMFailure(
	const std::string &except_string)
	:ExceptionGeneral(GetFixedString(except_string.c_str()))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionMMapVMFailure::ExceptionMMapVMFailure(
	const std::ostringstream &except_string)
	:ExceptionGeneral(GetFixedString(except_string.str().c_str()))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ExceptionMMapVMFailure::Rethrow(const char *except_string) const
{
	ExceptionMMapVMFailure tmp_except(*this);

	tmp_except.SetWhat(except_string);

	throw tmp_except;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
const char *ExceptionMMapVMFailure::GetFixedString(const char *except_string)
{
	return(((except_string == NULL) || (!(*except_string))) ?
		"Insufficient unused virtual memory for mapping exception." :
		except_string);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionCriticalEvent::ExceptionCriticalEvent()
	:ExceptionGeneral(GetFixedString())
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionCriticalEvent::ExceptionCriticalEvent(const char *except_string)
	:ExceptionGeneral(GetFixedString(except_string))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionCriticalEvent::ExceptionCriticalEvent(
	const std::string &except_string)
	:ExceptionGeneral(GetFixedString(except_string.c_str()))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ExceptionCriticalEvent::ExceptionCriticalEvent(
	const std::ostringstream &except_string)
	:ExceptionGeneral(GetFixedString(except_string.str().c_str()))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void ExceptionCriticalEvent::Rethrow(const char *except_string) const
{
	ExceptionCriticalEvent tmp_except(*this);

	tmp_except.SetWhat(except_string);

	throw tmp_except;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
const char *ExceptionCriticalEvent::GetFixedString(const char *except_string)
{
	return(((except_string == NULL) || (!(*except_string))) ?
		"Critical event encountered exception." : except_string);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

