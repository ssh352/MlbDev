// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	TibCo/Rendezvous Support Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts I/O types to strings.

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

#include <RvUtilX.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace RvUtilX {

//	////////////////////////////////////////////////////////////////////////////
std::string IOTypeToString(tibrvIOType io_type)
{
	std::string out_string;

	switch (io_type) {
		case TIBRV_IO_READ		:
			out_string = "TIBRV_IO_READ";
			break;
		case TIBRV_IO_WRITE		:
			out_string = "TIBRV_IO_WRITE";
			break;
		case TIBRV_IO_EXCEPTION	:
			out_string = "TIBRV_IO_EXCEPTION";
			break;
		default						:
			std::ostringstream tmp_string;
			tmp_string << "*Invalid/unassigned TibRv I/O type=" <<
				static_cast<int>(io_type) << "*";
			out_string = tmp_string.str();
			break;
	}

	return(out_string);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string IOTypeToDescription(tibrvIOType io_type)
{
	std::ostringstream out_string;

	out_string << "Tib RV I/O type " <<
		static_cast<int>(io_type) << "=" << IOTypeToString(io_type);

	return(out_string.str());
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace RvUtilX

} // namespace MLB

