// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	TibCo/Rendezvous Support Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for boost serialization support for
								class and structures in the RvUtilX library.

	Revision History	:	2005-02-18 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2005 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__RvUtilX_BoostSerialization_hpp__HH

#define HH__MLB__RvUtilX_BoostSerialization_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/Boost/Serialization/BoostSerialization.hpp>
#include <RvUtilX.hpp>

// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
BOOST_CLASS_IMPLEMENTATION(MLB::RvUtilX::SNDSpec,
	boost::serialization::object_serializable)
BOOST_CLASS_IMPLEMENTATION(MLB::RvUtilX::FtSpec,
	boost::serialization::object_serializable)
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
MLB_BOOSTX_SERIAL_TEMPLATE(MLB::RvUtilX::SNDSpec)
MLB_BOOSTX_SERIAL_TEMPLATE(MLB::RvUtilX::FtSpec)
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifndef HH__MLB__RvUtilX_BoostSerialization_hpp__HH

