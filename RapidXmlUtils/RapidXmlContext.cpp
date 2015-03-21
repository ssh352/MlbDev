// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB RapidXml Utilities Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the RapidXmlContext class.

	Revision History	:	2015-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2005 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <RapidXmlUtils/RapidXmlContext.hpp>

#include <Utility/Utility_Exception.hpp>

//#error "!!!"

/*
#if defined(_Windows) && !defined(__MINGW32__)
# pragma warning(push)
# pragma warning(disable:4217 4275 4625 4626)
# if _MSC_VER >= 1500
#  pragma warning(disable:4061 4242 4244 4365 4640)
# endif // # if _MSC_VER >= 1500
#endif // #if defined(_Windows) && !defined(__MINGW32__)

#error "!!!"
#include <boost/thread/mutex.hpp>

#if defined(_Windows) && !defined(__MINGW32__)
# pragma warning(pop)
#endif // #if defined(_Windows) && !defined(__MINGW32__)
*/

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace RapidXmlUtils {

// ////////////////////////////////////////////////////////////////////////////
RapidXmlContext::RapidXmlContext()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
RapidXmlContext::~RapidXmlContext()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
RapidXmlContext::RapidXmlContext(const RapidXmlContext &)
{
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace RapidXmlUtils

} // namespace MLB

