// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the atomic types.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////


#ifndef HH__MLB__Utility__AtomicTypes_hpp__HH

#define HH__MLB__Utility__AtomicTypes_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file AtomicTypes.h

	\brief	The atomic types header file.

	Contains atomic type definitions and function prototypes.
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
// ////////////////////////////////////////////////////////////////////////////
//	Specifies the type capable of atomic test-and-set on the platform. To be
//	defined per-platform...
//	////////////////////////////////////////////////////////////////////////////
#ifdef _Windows
typedef long AtomicValue;
#elif __GNUC__
typedef long AtomicValue;
#else
# error "Utility/AtomicTypes.hpp: No atomic exchange/compare value defined for this platform."
#endif // #ifdef _Windows
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
API_UTILITY inline AtomicValue AtomicValueSet(
	volatile AtomicValue *atomic_value_ptr, AtomicValue new_value)
{
#ifdef _Windows
	// Needed for MinGW gcc 3.4.5
# ifdef __MINGW32__
	return(::InterlockedExchange(const_cast<long int *>(atomic_value_ptr),
		new_value));
# else
	return(::InterlockedExchange(atomic_value_ptr, new_value));
# endif // # ifdef __MINGW32__
#else
	return(__sync_lock_test_and_set(atomic_value_ptr, new_value));
#endif // #ifdef _Windows
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
API_UTILITY inline AtomicValue AtomicValueIncrement(
	volatile AtomicValue *atomic_value_ptr)
{
#ifdef _Windows
	// Needed for MinGW gcc 3.4.5
# ifdef __MINGW32__
	return(::InterlockedIncrement(const_cast<long int *>(atomic_value_ptr)));
# else
	return(::InterlockedIncrement(atomic_value_ptr));
# endif // # ifdef __MINGW32__
#else
	return(__sync_add_and_fetch(atomic_value_ptr, 1));
#endif // #ifdef _Windows
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
API_UTILITY inline AtomicValue AtomicValueDecrement(
	volatile AtomicValue *atomic_value_ptr)
{
#ifdef _Windows
	// Needed for MinGW gcc 3.4.5
# ifdef __MINGW32__
	return(::InterlockedDecrement(const_cast<long int *>(atomic_value_ptr)));
# else
	return(::InterlockedDecrement(atomic_value_ptr));
# endif // # ifdef __MINGW32__
#else
	return(__sync_sub_and_fetch(atomic_value_ptr, 1));
#endif // #ifdef _Windows
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
API_UTILITY inline AtomicValue AtomicValueGet(
	const volatile AtomicValue *atomic_value_ptr)
{
#ifdef _Windows
	return(::InterlockedCompareExchange(
		const_cast<AtomicValue *>(atomic_value_ptr), 0, 0));
#else
	return(__sync_val_compare_and_swap(
		const_cast<AtomicValue *>(atomic_value_ptr), 0, 0));
#endif // #ifdef _Windows
}
//	////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
typedef AtomicValue AtomicFlag;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
inline API_UTILITY void AtomicFlagClear(volatile AtomicFlag *atomic_flag_ptr)
{
	AtomicValueSet(atomic_flag_ptr, static_cast<AtomicValue>(0));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY inline bool AtomicFlagTest(volatile AtomicFlag *atomic_flag_ptr)
{
	return(AtomicValueGet(atomic_flag_ptr) != 0);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY inline void AtomicFlagSet(volatile AtomicFlag *atomic_flag_ptr)
{
	AtomicValueSet(atomic_flag_ptr, 1);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__AtomicTypes_hpp__HH

