// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	IsEolChar.hpp

	File Description	:	Include file for end-of-line determination.

	Revision History	:	2016-05-09 --- Modified for C++.
									Michael L. Brock
								1986-10-27 --- Original C language version from
													strfuncs library.
									Michael L. Brock

		Copyright Michael L. Brock 2016 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////


#ifndef HH___MLB__Utility__IsEolChar_hpp___HH

#define HH___MLB__Utility__IsEolChar_hpp___HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <cstddef>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
inline bool IsEolChar(int datum)
{
	return((datum == '\r') || (datum == '\n'));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
inline bool IsEolChar(char datum)
{
	return(IsEolChar(static_cast<int>(datum)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
inline int IsEolChar(const char *datum_ptr)
{
	return((!IsEolChar(*datum_ptr)) ? 0 :
		((IsEolChar(datum_ptr[1]) && (*datum_ptr != datum_ptr[1])) ? 2 : 1));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
inline int IsEolChar(const char *datum_ptr, std::size_t datum_length)
{
	return((datum_length < 1) ? 0 : ((datum_length == 1) ?
		IsEolChar(*datum_ptr) : IsEolChar(datum_ptr)));
}
// ////////////////////////////////////////////////////////////////////////////


} // namespace Utility

} // namespace MLB

#endif // #ifndef HH___MLB__Utility__IsEolChar_hpp___HH

