// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	ODBC Wrapper Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of wrapper logic around the ODBC
								function 'SQLRowCount()'.

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

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN RowCount(SQLHSTMT StatementHandle, SQLINTEGER *RowCountPtr,
	OdbcThrowFlags::Flags throw_flags)
{
	return(OdbcWrapper_THROW_STATUS_IF_LEVEL_1(throw_flags,
		SQL_HANDLE_STMT, StatementHandle, ::SQLRowCount,
		(StatementHandle, RowCountPtr)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN RowCount(SQLHSTMT StatementHandle, SQLINTEGER &RowCountPtr,
	OdbcThrowFlags::Flags throw_flags)
{
	return(RowCount(StatementHandle, &RowCountPtr, throw_flags));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace OdbcWrapper

} // namespace MLB
