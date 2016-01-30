// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	ODBC Wrapper Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the OdbcExceptionDiag class.

	Revision History	:	2001-10-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <OdbcWrapper/OdbcWrapper.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace OdbcWrapper {

//	////////////////////////////////////////////////////////////////////////////
OdbcExceptionDiag::OdbcExceptionDiag()
	:OdbcExceptionStatus()
	,diagnostic_state_()
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OdbcExceptionDiag::OdbcExceptionDiag(SQLSMALLINT handle_type,
	SQLHANDLE handle_value)
	:OdbcExceptionStatus()
	,diagnostic_state_(handle_type, handle_value, OdbcThrowFlags::None)
{
	FixupWhat();
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OdbcExceptionDiag::OdbcExceptionDiag(SQLRETURN odbc_status,
	SQLSMALLINT handle_type, SQLHANDLE handle_value)
	:OdbcExceptionStatus(odbc_status)
	,diagnostic_state_(handle_type, handle_value, OdbcThrowFlags::None)
{
	FixupWhat();
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OdbcExceptionDiag::OdbcExceptionDiag(SQLRETURN odbc_status,
	SQLSMALLINT handle_type, SQLHANDLE handle_value, const char *except_string,
	const char *function_args)
	:OdbcExceptionStatus(odbc_status, except_string, function_args)
	,diagnostic_state_(handle_type, handle_value, OdbcThrowFlags::None)
{
	FixupWhat();
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OdbcExceptionDiag::OdbcExceptionDiag(SQLRETURN odbc_status,
	SQLSMALLINT handle_type, SQLHANDLE handle_value,
	const std::string &except_string, const char *function_args)
	:OdbcExceptionStatus(odbc_status, except_string, function_args)
	,diagnostic_state_(handle_type, handle_value, OdbcThrowFlags::None)
{
	FixupWhat();
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OdbcExceptionDiag::OdbcExceptionDiag(SQLRETURN odbc_status,
	SQLSMALLINT handle_type, SQLHANDLE handle_value,
	const std::ostringstream &except_string, const char *function_args)
	:OdbcExceptionStatus(odbc_status, except_string, function_args)
	,diagnostic_state_(handle_type, handle_value, OdbcThrowFlags::None)
{
	FixupWhat();
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OdbcExceptionDiag::~OdbcExceptionDiag()
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OdbcDiagState OdbcExceptionDiag::GetDiagState() const
{
	return(GetDiagStateRef());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
const OdbcDiagState &OdbcExceptionDiag::GetDiagStateRef() const
{
	return(diagnostic_state_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void OdbcExceptionDiag::Rethrow(const char *except_string) const
{
	OdbcExceptionDiag tmp_except(*this);

	tmp_except.SetWhat(except_string);

	throw tmp_except;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void OdbcExceptionDiag::FixupWhat()
{
	if ((!diagnostic_state_.diag_record_list_.empty()) &&
		(!diagnostic_state_.diag_record_list_[0].message_text_ex_.empty()))
		except_string_ +=
			": " + diagnostic_state_.diag_record_list_[0].message_text_ex_;
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace OdbcWrapper

} // namespace MLB

