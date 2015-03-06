// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	VFast Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Definition of the ExcContextInfo class.

	Revision History	:	2008-11-24 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2008 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__VFast__ExcContextInfo_hpp__HH

#define HH__MLB__VFast__ExcContextInfo_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace VFast {

// ////////////////////////////////////////////////////////////////////////////
/**
	\brief Provides some general information of use in the construction of
	instances of the \c ExcContext class.
*/
struct ExcContextInfo {
	explicit ExcContextInfo(bool implicit_scp_120 = false)
		:implicit_scp_120_(implicit_scp_120)
	{
	}

	/**
		Returns the value of the \e implicit_scp_120_ member.
	*/
	inline bool SupportsImplicitSCP120() const
	{
		return(implicit_scp_120_);
	}

	bool implicit_scp_120_;
};
// ////////////////////////////////////////////////////////////////////////////

} // namespace VFast

} // namespace MLB

#endif // #ifndef HH__MLB__VFast__ExcContextInfo_hpp__HH

