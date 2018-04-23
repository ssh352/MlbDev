//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Provides an interface for exception throwing.

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

#include <Utility/Utility_Exception.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

namespace {
// ////////////////////////////////////////////////////////////////////////////
template <typename ExceptionClassBase>
	class ExceptionClassProxy : public ExceptionClassBase {
public:
	ExceptionClassProxy(const char *except)
		:ExceptionClassBase()
		,what_string_(except)
	{
	}
	virtual ~ExceptionClassProxy()  MBCOMPAT_EXCEPT_NOTHROW
	{
	}
	virtual const char *what() const MBCOMPAT_EXCEPT_NOTHROW
	{
		return(what_string_.c_str());
	}

private:
	std::string what_string_;
};
// ////////////////////////////////////////////////////////////////////////////
} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
void ThrowExceptionGeneral(const char *error_text)
{
	throw ExceptionGeneral(error_text);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowExceptionGeneral(const std::string &error_text)
{
	ThrowExceptionGeneral(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowExceptionGeneral(const std::ostringstream &error_text)
{
	ThrowExceptionGeneral(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowException(const char *error_text)
{
	ThrowExceptionGeneral(error_text);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowException(const std::string &error_text)
{
	ThrowExceptionGeneral(error_text);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowException(const std::ostringstream &error_text)
{
	ThrowExceptionGeneral(error_text);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowErrorCode(long error_code, const char *error_text)
{
	std::ostringstream tmp_error_text;

	tmp_error_text <<
		(((error_text != NULL) && *error_text) ? error_text : "") <<
		": error code = " << error_code;

	ThrowStdException(tmp_error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowErrorCode(long error_code, const std::string &error_text)
{
	ThrowErrorCode(error_code, error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowErrorCode(long error_code, const std::ostringstream &error_text)
{
	ThrowErrorCode(error_code, error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowErrorCode(unsigned long error_code, const char *error_text)
{
	std::ostringstream tmp_error_text;

	tmp_error_text <<
		(((error_text != NULL) && *error_text) ? error_text : "") <<
		": error code = " << error_code;

	ThrowStdException(tmp_error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowErrorCode(unsigned long error_code, const std::string &error_text)
{
	ThrowErrorCode(error_code, error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowErrorCode(unsigned long error_code,
	const std::ostringstream &error_text)
{
	ThrowErrorCode(error_code, error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowStdException(const char *error_text)
{
	throw ExceptionClassProxy<std::exception>
		(((error_text != NULL) && *error_text) ? error_text :
		"Unspecified standard exception.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowStdException(const std::string &error_text)
{
	ThrowStdException(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowStdException(const std::ostringstream &error_text)
{
	ThrowStdException(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowDomainError(const char *error_text)
{
	if ((error_text != NULL) && *error_text)
		throw std::domain_error(error_text);

	throw std::domain_error("Unspecified domain error.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowDomainError(const std::string &error_text)
{
	ThrowDomainError(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowDomainError(const std::ostringstream &error_text)
{
	ThrowDomainError(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowInvalidArgument(const char *error_text)
{
	if ((error_text != NULL) && *error_text)
		throw std::invalid_argument(error_text);

	throw std::invalid_argument("Unspecified invalid argument error.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowInvalidArgument(const std::string &error_text)
{
	ThrowInvalidArgument(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowInvalidArgument(const std::ostringstream &error_text)
{
	ThrowInvalidArgument(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowLengthError(const char *error_text)
{
	if ((error_text != NULL) && *error_text)
		throw std::length_error(error_text);

	throw std::length_error("Unspecified length error.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowLengthError(const std::string &error_text)
{
	ThrowLengthError(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowLengthError(const std::ostringstream &error_text)
{
	ThrowLengthError(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowLogicError(const char *error_text)
{
	if ((error_text != NULL) && *error_text)
		throw std::logic_error(error_text);

	throw std::logic_error("Unspecified logic error.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowLogicError(const std::string &error_text)
{
	ThrowLogicError(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowLogicError(const std::ostringstream &error_text)
{
	ThrowLogicError(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowOutOfRange(const char *error_text)
{
	if ((error_text != NULL) && *error_text)
		throw std::out_of_range(error_text);

	throw std::out_of_range("Unspecified out of range.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowOutOfRange(const std::string &error_text)
{
	ThrowOutOfRange(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowOutOfRange(const std::ostringstream &error_text)
{
	ThrowOutOfRange(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowOverflowError(const char *error_text)
{
	if ((error_text != NULL) && *error_text)
		throw std::overflow_error(error_text);

	throw std::overflow_error("Unspecified overflow error.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowOverflowError(const std::string &error_text)
{
	ThrowOverflowError(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowOverflowError(const std::ostringstream &error_text)
{
	ThrowOverflowError(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowRangeError(const char *error_text)
{
	if ((error_text != NULL) && *error_text)
		throw std::range_error(error_text);

	throw std::range_error("Unspecified range error.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowRangeError(const std::string &error_text)
{
	ThrowRangeError(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowRangeError(const std::ostringstream &error_text)
{
	ThrowRangeError(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowRuntimeError(const char *error_text)
{
	if ((error_text != NULL) && *error_text)
		throw std::runtime_error(error_text);

	throw std::runtime_error("Unspecified runtime error.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowRuntimeError(const std::string &error_text)
{
	ThrowRuntimeError(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowRuntimeError(const std::ostringstream &error_text)
{
	ThrowRuntimeError(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowUnderflowError(const char *error_text)
{
	if ((error_text != NULL) && *error_text)
		throw std::underflow_error(error_text);

	throw std::underflow_error("Unspecified underflow error.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowUnderflowError(const std::string &error_text)
{
	ThrowUnderflowError(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowUnderflowError(const std::ostringstream &error_text)
{
	ThrowUnderflowError(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowBadAlloc(const char *error_text)
{
	throw ExceptionClassProxy<std::bad_alloc>
		(((error_text != NULL) && *error_text) ? error_text :
		"Unspecified bad allocation error.");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowBadAlloc(const std::string &error_text)
{
	ThrowBadAlloc(error_text.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void ThrowBadAlloc(const std::ostringstream &error_text)
{
	ThrowBadAlloc(error_text.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

