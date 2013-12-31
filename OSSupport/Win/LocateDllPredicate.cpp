// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Operating System Support (OSSupport) Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the LocateDllPredicate class.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <OSSupport_Win.h>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace OSSupport {

// ////////////////////////////////////////////////////////////////////////////
LocateDllPredicate::LocateDllPredicate()
	:candidate_count_(0)
	,best_match_("", MLB::Utility::VersionNumber::GetMinimumValue())
	,candidate_list_()
	,matched_list_()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
LocateDllPredicate::~LocateDllPredicate()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::SearchStartUpDir() const
{
	return(true);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::SearchCurrentDir() const
{
	return(true);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::SearchSystemDir() const
{
	return(true);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::SearchWindowsDir() const
{
	return(true);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::IsGlobalPredicate() const
{
	return(IsGlobalPredicateInternal());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::IsVersionMatch(const std::string &full_name) const
{
	return(IsVersionMatchImpl(full_name));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::IsVersionMatch(const std::string &full_name,
	MLB::Utility::VersionNumber &this_version) const
{
	return(IsVersionMatchImpl(full_name, this_version));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::IsMatchingDll(const std::string &full_name)
{
	++candidate_count_;

	return(IsMatchingDllInternal(full_name));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
DllMatchItem LocateDllPredicate::GetBestMatch() const
{
	return(GetBestMatchInternal());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string LocateDllPredicate::GetBestMatchName() const
{
	return(GetBestMatch().file_name_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
MLB::Utility::VersionNumber LocateDllPredicate::GetBestMatchVersion() const
{
	return(GetBestMatch().version_number_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string LocateDllPredicate::DescribePredicate() const
{
	return("any matching DLL");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::IsGlobalPredicateInternal() const
{
	return(false);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::IsVersionMatchImpl(const std::string &full_name) const
{
	return(IsVersionMatchImpl(full_name));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::IsVersionMatchImpl(const std::string &,
	MLB::Utility::VersionNumber &) const
{
	return(true);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool LocateDllPredicate::IsMatchingDllInternal(const std::string &full_name)
{
	MLB::Utility::VersionNumber this_version;

	DetermineProductVersion(full_name).swap(this_version);

	candidate_list_.push_back(DllMatchItem(full_name, this_version));
	matched_list_.push_back(DllMatchItem(full_name, this_version));

	if (matched_list_.size() == 1)
		best_match_ = matched_list_.front();

	return(true);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
DllMatchItem LocateDllPredicate::GetBestMatchInternal() const
{
	return(best_match_);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace OSSupport

} // namespace MLB

#ifdef TEST_MAIN

using namespace MLB::OSSupport;

// ////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	int return_code = EXIT_SUCCESS;

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif /* #ifdef TEST_MAIN */

