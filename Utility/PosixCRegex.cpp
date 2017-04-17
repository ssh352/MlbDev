//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of a C++ wrapper for the boost::regex 
								Posix C language regex support.

	Revision History	:	2006-10-25 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2006 - 2017.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////
 
//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Required include files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility/PosixCRegex.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
PosixCRegexException::PosixCRegexException(int regex_error_code,
	const boost::regex_tA *the_regex, const char *except_string)
	:ExceptionGeneral(FixupString(regex_error_code, the_regex, except_string))
	,regex_error_code_()
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int PosixCRegexException::whatcode() const
{
	return(regex_error_code_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void PosixCRegexException::Rethrow(const char *except_string) const
{
	PosixCRegexException tmp_except(*this);

	tmp_except.SetWhat(except_string);

	throw tmp_except;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string PosixCRegexException::FixupString(int regex_error_code,
	const boost::regex_tA *the_regex, const char *other_text)
{
	char error_text[255 + 1];

	regerrorA(regex_error_code, the_regex, error_text, sizeof(error_text) - 1);

	std::ostringstream status_string;

	status_string <<
		"Error in boost::regex Posix compatibility function call: " <<
		(((other_text != NULL) && *other_text) ? other_text : "Error ") <<
		": Regex error code " << regex_error_code << ", '" << error_text <<
		"'.";

	return(status_string.str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
PosixCRegexWrapper::PosixCRegexWrapper(const char *regex_string,
	int regex_flags)
	:this_regex_()
	,ready_flag_(false)
{
	if (regex_string != NULL)
		ConstructRegexThis(regex_string, regex_flags);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
PosixCRegexWrapper::PosixCRegexWrapper(const std::string &regex_string,
	int regex_flags)
	:this_regex_()
	,ready_flag_(false)
{
	ConstructRegexThis(regex_string.c_str(), regex_flags);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
PosixCRegexWrapper::~PosixCRegexWrapper()
{
	DestroyRegex();
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool PosixCRegexWrapper::IsReady() const
{
	return(ready_flag_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void PosixCRegexWrapper::CheckReady() const
{
	if (!IsReady())
		MLB::Utility::ThrowInvalidArgument("This 'MLB::Utility::"
			"PosixCRegexWrapper' instance is not constructed.");
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool PosixCRegexWrapper::ClearRegex()
{
	bool ready_flag = ready_flag_;

	DestroyRegex();

	return(ready_flag);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool PosixCRegexWrapper::SetRegex(const char *regex_string, int regex_flags)
{
	boost::regex_tA tmp_regex;

	ConstructRegex(regex_string, tmp_regex, regex_flags);

	bool ready_flag = ClearRegex();

	this_regex_ = tmp_regex;
	ready_flag_ = true;

	return(ready_flag);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool PosixCRegexWrapper::SetRegex(const std::string &regex_string,
	int regex_flags)
{
	return(SetRegex(regex_string.c_str(), regex_flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool PosixCRegexWrapper::RegexSearch(const char *target_string,
	int search_flags) const
{
	CheckReady();

	if (target_string == NULL)
		MLB::Utility::ThrowInvalidArgument("Call to 'MLB::Utility::"
			"PosixCRegexWrapper::RegexSearch()' with a 'NULL' string.");

	int regex_error;

	if ((regex_error = boost::regexecA(&this_regex_, target_string,
		0, NULL, search_flags)) == 0)
		return(true);
	else if (regex_error != static_cast<int>(boost::REG_NOMATCH))
		throw MLB::Utility::PosixCRegexException(regex_error, &this_regex_,
			"Call to 'regexecA()' failed");

	return(false);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool PosixCRegexWrapper::RegexSearch(const std::string &target_string,
	int search_flags) const
{
	return(RegexSearch(target_string.c_str(), search_flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void PosixCRegexWrapper::ConstructRegexThis(const char *regex_string,
	int regex_flags)
{
	ConstructRegex(regex_string, this_regex_, regex_flags);

	ready_flag_ = true;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void PosixCRegexWrapper::DestroyRegex()
{
	if (ready_flag_)
		boost::regfreeA(&this_regex_);

	ready_flag_ = false;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void PosixCRegexWrapper::ConstructRegex(const char *regex_string,
	boost::regex_tA &in_regex, int regex_flags)
{
	if (regex_string == NULL)
		MLB::Utility::ThrowInvalidArgument("Specified regex string is 'NULL'.");

	try {
		int regex_error;
		if ((regex_error = boost::regcompA(&in_regex, regex_string,
			regex_flags)) != 0)
			throw MLB::Utility::PosixCRegexException(regex_error, &in_regex,
				"Call to 'regcompA()' failed");
	}
	catch (const std::exception &except) {
		MLB::Utility::Rethrow(except, "Unable to compile the regular "
			"expression '" + std::string(regex_string) + "': " +
			std::string(except.what()));
	}
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

