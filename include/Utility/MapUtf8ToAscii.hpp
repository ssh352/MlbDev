// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	MapUtf8ToAscii.hpp

	File Description	:	Include file for the logic to map UTF-8 sequences
								within strings to single characters.

	Revision History	:	2018-05-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2018 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__MapUtf8ToAscii_hpp__HH

#define HH__MLB__Utility__MapUtf8ToAscii_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file 	MapUtf8ToAscii.hpp

	\brief	UTF-8 mapping support.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
typedef std::pair<const char *, const char *> Utf8MapEntry;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY std::string &MapUtf8ToAsciiInPlace(const std::size_t map_count,
	const Utf8MapEntry *map_list,  std::string &src);
API_UTILITY std::string  MapUtf8ToAscii(const std::size_t map_count,
	const Utf8MapEntry *map_list,  const std::string &src);

API_UTILITY std::string &MapUtf8ToAscii7InPlace(std::string &src);
API_UTILITY std::string  MapUtf8ToAscii7(const std::string &src);

API_UTILITY std::string &MapUtf8ToAscii8InPlace(std::string &src);
API_UTILITY std::string  MapUtf8ToAscii8(const std::string &src);
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__MapUtf8ToAscii_hpp__HH

