// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Operating System Support (OSSupport) Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the amount of physical memory in use by a
								process.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <OSSupport.h>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace OSSupport {

//	////////////////////////////////////////////////////////////////////////////
MLB::Utility::MemorySizeType GetPhysicalMemoryInUse()
{
#ifdef _Windows
	PROCESS_MEMORY_COUNTERS datum;

	OS_GetProcessMemoryInfo(datum);

	return(datum.WorkingSetSize);
#else
# error "Compilation of 'OSSupport/GetPhysicalMemoryInUse.cpp' is not yet supported under this operating system."
#endif // #ifdef _Windows
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace OSSupport

} // namespace MLB

