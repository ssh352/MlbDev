//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for enumeration flag operations.

	Revision History	:	1996-04-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////
 
#ifndef HH__MLB__Utility__EnumFlagOps_hpp__HH

#define HH__MLB__Utility__EnumFlagOps_hpp__HH	1

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Required include files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
template <typename EnumType>
	EnumType EnumFlagAnd(EnumType base_value, EnumType other_value)
{
	return(static_cast<EnumType>(static_cast<int>(base_value) &
		static_cast<int>(other_value)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename EnumType>
	EnumType EnumFlagOr(EnumType base_value, EnumType other_value)
{
	return(static_cast<EnumType>(static_cast<int>(base_value) |
		static_cast<int>(other_value)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename EnumType>
	EnumType EnumFlagXor(EnumType base_value, EnumType other_value)
{
	return(static_cast<EnumType>(static_cast<int>(base_value) ^
		static_cast<int>(other_value)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename EnumType>
	EnumType EnumValueAdd(EnumType base_value, int other_value)
{
	return(static_cast<EnumType>(static_cast<int>(base_value) + other_value));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename EnumType>
	EnumType EnumValueSubtract(EnumType base_value, int other_value)
{
	return(static_cast<EnumType>(static_cast<int>(base_value) - other_value));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename EnumType>
	EnumType EnumValueIncrement(EnumType base_value)
{
	return(EnumValueAdd(base_value, 1));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename EnumType>
	EnumType EnumValueDecrement(EnumType base_value)
{
	return(EnumValueSubtract(base_value, 1));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename EnumType>
	EnumType EnumFlagSet(EnumType base_value, EnumType other_value)
{
	return(static_cast<EnumType>(static_cast<int>(base_value) |
		static_cast<int>(other_value)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename EnumType>
	EnumType EnumFlagClear(EnumType base_value, EnumType other_value)
{
	return(static_cast<EnumType>(static_cast<int>(base_value) &
		(~static_cast<int>(other_value))));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__EnumFlagOps_hpp__HH

