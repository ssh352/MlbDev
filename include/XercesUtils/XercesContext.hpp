// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Xerces-C Utilities Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Definition of the XercesContext class.

	Revision History	:	2005-01-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2005 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__XercesUtils__XercesContext_hpp__HH

#define HH__MLB__XercesUtils__XercesContext_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <XercesUtils/XercesUtils.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace XercesUtils {

// ////////////////////////////////////////////////////////////////////////////
struct API_XERCESUTILS XercesContext {
	XercesContext();
	//**	Virtual to permit use as a base class to guarantee first construction.
	virtual ~XercesContext();
	/**
		Must have copy ctor to increment internal Xerces reference count, but
		the compiler-generated assignment operator is sufficient...
	*/
	XercesContext(const XercesContext &other);
};
// ////////////////////////////////////////////////////////////////////////////

} // namespace XercesUtils

} // namespace MLB

#endif // #ifndef HH__MLB__XercesUtils__XercesContext_hpp__HH

