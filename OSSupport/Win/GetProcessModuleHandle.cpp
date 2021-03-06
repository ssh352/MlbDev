// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Operating System Support (OSSupport) Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of wrappers to the Windows function
								GetModuleFileName().

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <OSSupport/Win/OSSupport_Win.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace OSSupport {

// ////////////////////////////////////////////////////////////////////////////
HMODULE GetProcessModuleHandle(HANDLE process_handle)
{
	HMODULE module_handle;

	//	First module is main EXE, so only need an array of one...
	OS_EnumProcessModules(process_handle, &module_handle, 1);

	return(module_handle);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
HMODULE GetProcessModuleHandle()
{
	return(GetProcessModuleHandle(::GetCurrentProcess()));
}
// ////////////////////////////////////////////////////////////////////////////
} // namespace OSSupport

} // namespace MLB

#ifdef TEST_MAIN

#include <Utility/ValueToStringRadix.hpp>

using namespace MLB::OSSupport;

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		HMODULE exe_module = GetProcessModuleHandle();
		std::cout << "Test GetProcessModuleHandle(): " <<
			MLB::Utility::ValueToStringHex(exe_module) << ": " <<
			OS_GetModuleFileName(exe_module) << std::endl;
	}
	catch (const std::exception &except) {
		std::cerr << "REGRESSION TEST FAILURE: " <<
			"OSSupport/Win/OS_GetModuleFileName.cpp: " << except.what() <<
			std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif /* #ifdef TEST_MAIN */

