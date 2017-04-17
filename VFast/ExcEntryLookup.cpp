// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	VFast Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the ExcEntryLookup class.

	Revision History	:	2008-11-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2008 - 2017.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <VFast/ExcEntryLookup.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace VFast {

// ////////////////////////////////////////////////////////////////////////////
void ExcEntryLookup::PopulateExcEntryLookupList(unsigned int entry_count,
	const ExcEntry *entry_list, unsigned int item_count,
	ExcEntryLookup *lookup_list)
{
	::memset(lookup_list, '\0', item_count * sizeof(lookup_list[0]));

	for (unsigned int count_1 = 0; count_1 < entry_count;
		++count_1, ++entry_list) {
		if (!lookup_list[entry_list->item_index_].count_++)
			lookup_list[entry_list->item_index_].first_ = count_1;
		lookup_list[entry_list->item_index_].last_ = count_1;
	}
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace VFast

} // namespace MLB

