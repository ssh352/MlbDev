//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the ExecProcessInfo class.

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

#include <Utility/ExecProcess.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
ExecProcessInfo::ExecProcessInfo(int process_id,
	ExecProcessHandle process_handle, ExecThreadHandle thread_handle)
	:process_id_(process_id)
	,process_handle_(process_handle)
	,thread_handle_(thread_handle)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool ExecProcessInfo::operator < (const ExecProcessInfo &other) const
{
	return(process_id_ < other.process_id_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool ExecProcessInfo::operator == (const ExecProcessInfo &other) const
{
	return(process_id_ == other.process_id_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str, const ExecProcessInfo &datum)
{
	o_str
		<< datum.process_id_     << ":"
		<< datum.process_handle_ << ":"
		<< datum.thread_handle_;

	return(o_str);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

