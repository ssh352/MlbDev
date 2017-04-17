// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	ODBC Wrapper Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the OdbcHandleEnv class.

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

#include <OdbcWrapper/OdbcHandle.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace OdbcWrapper {

// ////////////////////////////////////////////////////////////////////////////
OdbcHandleEnv::OdbcHandleEnv()
	:OdbcHandleBase<SQLHENV>(SQL_HANDLE_ENV, SQL_NULL_HANDLE, "Env",
		GetEnvAttrBasic, SetEnvAttrBasic)
	,child_set_()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
OdbcHandleEnv::~OdbcHandleEnv()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
OdbcHandleDbcSPtr OdbcHandleEnv::CreateConnection()
{
	return(OdbcHandleDbcSPtr(new OdbcHandleDbc(GetNativeHandle())));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
OdbcHandleDbcSPtr OdbcHandleEnv::AddConnection()
{
	CleanChildList();

	OdbcHandleDbcSPtr child_sptr(CreateConnection());

	child_set_.insert(OdbcHandleDbcWPtr(child_sptr));

	return(child_sptr);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void OdbcHandleEnv::RemoveConnection(OdbcHandleDbcSPtr &child_sptr)
{
	CleanChildList();

	OdbcHandleDbcWPtrSetIter iter_f(
		child_set_.find(OdbcHandleDbcWPtr(child_sptr)));

	if (iter_f == child_set_.end())
		MLB::Utility::ThrowInvalidArgument("Unable to locate the ODBC "
			"connection pointer " +
			MLB::Utility::ValueToStringHex(child_sptr.get()) +
			" for removal.");

	child_set_.erase(iter_f);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void OdbcHandleEnv::CleanChildList()
{
	OdbcHandleDbcWPtrSetIter iter_b(child_set_.begin());
	OdbcHandleDbcWPtrSetIter iter_e(child_set_.end());

	for ( ; iter_b != iter_e; ) {
		if (iter_b->lock() == NULL)
			child_set_.erase(iter_b++);
		else
			++iter_b;
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
AttrInfoBasicVector &OdbcHandleEnv::GetAttrInfoBasicList(
	AttrInfoBasicVector &out_list, SQLUSMALLINT Direction) const
{
	return(AttrInfoBasic::GetAttrInfoBasicList(GetNativeHandle(),
		out_list, Direction));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
AttrInfoBasicVector OdbcHandleEnv::GetAttrInfoBasicList(
	SQLUSMALLINT Direction) const
{
	return(AttrInfoBasic::GetAttrInfoBasicList(GetNativeHandle(),
		Direction));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
AttrInfoBasicVector &OdbcHandleEnv::GetDataSourceBasicList(
	AttrInfoBasicVector &out_list, SQLUSMALLINT Direction) const
{
	return(AttrInfoBasic::GetDataSourceBasicList(GetNativeHandle(),
		out_list, Direction));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
AttrInfoBasicVector OdbcHandleEnv::GetDataSourceBasicList(
	SQLUSMALLINT Direction) const
{
	return(AttrInfoBasic::GetDataSourceBasicList(GetNativeHandle(),
		Direction));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace OdbcWrapper

} // namespace MLB

