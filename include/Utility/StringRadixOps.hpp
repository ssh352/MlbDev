// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	StringRadixOps.hpp

	File Description	:	Include file for the new, yet-to-be-fully-implemented,
								string <---> integer radix functions.

	Revision History	:	1995-10-10 --- Portions of original logic from
													MlbDev/Utility/IntToString.cpp.
									Michael L. Brock
								2016-08-07 --- Base-62 specific logic first-cut.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__StringRadixOps_hpp__HH

#define HH__MLB__Utility__StringRadixOps_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file 	StringRadixOps.hpp

	\brief	String <--> radix functions.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility.hpp>

#include <mbtypes.h>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
void GetCharMapRadixSafe64(std::size_t &low_index, std::size_t &high_index,
	const unsigned char *&char_map);
void GetCharMapRadixPem64(std::size_t &low_index, std::size_t &high_index,
	const unsigned char *&char_map);
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix(std::size_t radix, const char *begin_ptr,
	const char *end_ptr, const char **last_ptr = NULL,
	bool *overflow_flag = NULL, std::size_t low_index = 0,
	std::size_t high_index = 0, const unsigned char *char_map = NULL);
Native_UInt64 StringToUIntRadix(std::size_t radix, std::size_t src_len,
	const char *src_ptr, const char **last_ptr = NULL,
	bool *overflow_flag = NULL, std::size_t low_index = 0,
	std::size_t high_index = 0, const unsigned char *char_map = NULL);
Native_UInt64 StringToUIntRadix(std::size_t radix, const char *src_ptr,
	const char **last_ptr = NULL, bool *overflow_flag = NULL,
	std::size_t low_index = 0, std::size_t high_index = 0,
	const unsigned char *char_map = NULL);
Native_UInt64 StringToUIntRadix(std::size_t radix, const std::string &src,
	std::size_t *last_offset = NULL, bool *overflow_flag = NULL,
	std::size_t low_index = 0, std::size_t high_index = 0,
	const unsigned char *char_map = NULL);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__StringRadixOps_hpp__HH

