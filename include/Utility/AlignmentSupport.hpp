// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for data type alignment.

	Revision History	:	1992-09-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////


#ifndef HH__MLB__Utility__AlignmentSupport_hpp__HH

#define HH__MLB__Utility__AlignmentSupport_hpp__HH	1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
	\file 	AlignmentSupport.hpp

	\brief	Logic to support of proper data type alignment.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility.hpp>

#if defined(__GNUC__) && (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 7)
# include <stddef.h>
#endif // #if defined(__GNUC__) && (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 7)

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

namespace ImplementationPrivate {
// ////////////////////////////////////////////////////////////////////////////
struct API_UTILITY SomeStruct {
	char datum_;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DataType>
	struct AlignmentRequirement {
	char     char_;
	DataType data_;
};
// ////////////////////////////////////////////////////////////////////////////
} // namespace ImplementationPrivate

// ////////////////////////////////////////////////////////////////////////////
template <typename DataType>
	unsigned int GetAlignmentRequirement()
{
	return(offsetof(ImplementationPrivate::AlignmentRequirement<DataType>,
		data_));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DataType>
	unsigned int GetAlignmentRequirement(const DataType &)
{
	return(GetAlignmentRequirement<DataType>());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
inline API_UTILITY unsigned int GetAlignmentRequirementStructure()
{
	return(GetAlignmentRequirement<ImplementationPrivate::SomeStruct>());
}
// ////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename DataType>
	DataType GranularRoundDown(DataType datum, DataType granularity)
{
	if ((datum < static_cast<DataType>(1)) ||
		(granularity < static_cast<DataType>(1)))
		return(0);

	return((datum / granularity) * granularity);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename DataType>
	DataType GranularRoundUp(DataType datum, DataType granularity)
{
	DataType tmp_datum = GranularRoundDown(datum, granularity);

	return(((!datum) || (datum % granularity)) ?
		(tmp_datum + granularity) : tmp_datum);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
template <typename DataType>
	DataType GranularRound(DataType datum, DataType granularity)
{
	DataType tmp_datum = GranularRoundDown(datum, granularity);

	return(((!datum) || (!(datum % granularity))) ? tmp_datum :
		(tmp_datum + granularity));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__AlignmentSupport_hpp__HH

