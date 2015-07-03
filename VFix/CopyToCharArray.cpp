// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	VFix Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	CopyToCharArray.hpp

	File Description	:	Implementation of the CopyToCharArray() function.

	Revision History	:	2015-07-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2015 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <VFix/CopyToCharArray.hpp>

#include <Utility/Utility_Exception.hpp>

#include <sstream>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace VFix {

// ////////////////////////////////////////////////////////////////////////////
const char *CopyToCharArray(std::size_t src_len, const char *src_str,
	std::size_t dst_len, char *dst_str, bool can_truncate_flag)
{
	if (src_len <= dst_len)
		::strcpy(dst_str, src_str);
	else if (!can_truncate_flag){
		std::ostringstream o_str;
		o_str << "Unable to copy a source string of length " << src_len <<
			" because it exceeds the maximum destination string length of " <<
			dst_len << ".";
		MLB::Utility::ThrowInvalidArgument(o_str.str());
	}
	else
		MLB::Utility::nstrcpy(dst_str, src_str, dst_len);

	return(dst_str);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const char *CopyToCharArray(const char *src_str, std::size_t dst_len,
	char *dst_str, bool can_truncate_flag)
{
	return(CopyToCharArray(::strlen(src_str), src_str, dst_len, dst_str,
		can_truncate_flag));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const char *CopyToCharArray(const std::string &src_str, std::size_t dst_len,
	char *dst_str, bool can_truncate_flag)
{
	return(CopyToCharArray(src_str.size(), src_str.c_str(), dst_len, dst_str,
		can_truncate_flag));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace VFix

} // namespace MLB
