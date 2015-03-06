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
								function 'SQLSetEnvAttr()'.

	Revision History	:	2001-10-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2015.
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
SQLRETURN SetEnvAttrBasic(SQLHENV EnvironmentHandle, SQLINTEGER Attribute,
	SQLPOINTER ValuePtr, SQLINTEGER StringLength,
	OdbcThrowFlags::Flags throw_flags)
{
	return(OdbcWrapper_THROW_STATUS_IF_LEVEL_1(throw_flags,
		SQL_HANDLE_ENV, EnvironmentHandle, ::SQLSetEnvAttr,
		(EnvironmentHandle, Attribute, ValuePtr, StringLength)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN SetEnvAttr(SQLHENV EnvironmentHandle, SQLINTEGER Attribute,
	SQLPOINTER ValuePtr, SQLINTEGER StringLength,
	OdbcThrowFlags::Flags throw_flags)
{
	return(SetAttrForHandle(EnvironmentHandle, Attribute, ValuePtr,
		StringLength, SetEnvAttrBasic, throw_flags));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN SetEnvAttr(SQLHENV EnvironmentHandle, SQLINTEGER Attribute,
	SQLINTEGER ValuePtr, OdbcThrowFlags::Flags throw_flags)
{
	return(SetAttrForHandle(EnvironmentHandle, Attribute, ValuePtr,
		SetEnvAttrBasic, throw_flags));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN SetEnvAttr(SQLHENV EnvironmentHandle, SQLINTEGER Attribute,
	SQLUINTEGER ValuePtr, OdbcThrowFlags::Flags throw_flags)
{
	return(SetAttrForHandle(EnvironmentHandle, Attribute, ValuePtr,
		SetEnvAttrBasic, throw_flags));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN SetEnvAttr(SQLHENV EnvironmentHandle, SQLINTEGER Attribute,
	SQLSMALLINT ValuePtr, OdbcThrowFlags::Flags throw_flags)
{
	return(SetAttrForHandle(EnvironmentHandle, Attribute, ValuePtr,
		SetEnvAttrBasic, throw_flags));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN SetEnvAttr(SQLHENV EnvironmentHandle, SQLINTEGER Attribute,
	SQLUSMALLINT ValuePtr, OdbcThrowFlags::Flags throw_flags)
{
	return(SetAttrForHandle(EnvironmentHandle, Attribute, ValuePtr,
		SetEnvAttrBasic, throw_flags));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN SetEnvAttr(SQLHENV EnvironmentHandle, SQLINTEGER Attribute,
	OdbcAttrFlags32 ValuePtr, OdbcThrowFlags::Flags throw_flags)
{
	return(SetAttrForHandle(EnvironmentHandle, Attribute, ValuePtr,
		SetEnvAttrBasic, throw_flags));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN SetEnvAttr(SQLHENV EnvironmentHandle, SQLINTEGER Attribute,
	OdbcAttrWindowHandle ValuePtr, OdbcThrowFlags::Flags throw_flags)
{
	return(SetAttrForHandle(EnvironmentHandle, Attribute, ValuePtr,
		SetEnvAttrBasic, throw_flags));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN SetEnvAttr(SQLHENV EnvironmentHandle, SQLINTEGER Attribute,
	const char *ValuePtr, SQLINTEGER StringLength,
	OdbcThrowFlags::Flags throw_flags)
{
	return(SetAttrForHandle(EnvironmentHandle, Attribute, ValuePtr,
		StringLength, SetEnvAttrBasic, throw_flags));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SQLRETURN SetEnvAttr(SQLHENV EnvironmentHandle, SQLINTEGER Attribute,
	const std::string &ValuePtr, OdbcThrowFlags::Flags throw_flags)
{
	return(SetAttrForHandle(EnvironmentHandle, Attribute, ValuePtr,
		"::SQLSetEnvAttr", SetEnvAttrBasic, throw_flags));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace OdbcWrapper

} // namespace MLB

