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

#include <Utility/ValueToStringRadix.hpp>
#include <Utility/Utility_Exception.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace OSSupport {

// ////////////////////////////////////////////////////////////////////////////
char *OS_GetModuleBaseName(HANDLE process_handle, HMODULE module_handle,
	char *module_name, DWORD module_name_length)
{
	typedef COMPAT_FN_TYPE(BOOL (WINAPI *OS_FPtr_GetModuleBaseNameA),
		(HANDLE, HMODULE, LPSTR, DWORD));

	HMODULE psapi_module_handle = EnsureLoadedLibrary("psapi", true);

#pragma warning(disable:4191)
	OS_FPtr_GetModuleBaseNameA proc_addr =
		reinterpret_cast<OS_FPtr_GetModuleBaseNameA>(OS_GetProcAddress(
		psapi_module_handle, "GetModuleBaseNameA", true));
#pragma warning(default:4191)

	if ((*proc_addr)(process_handle, module_handle, module_name,
		module_name_length) == 0)
		MLB::Utility::ThrowSystemError("Call to 'GetModuleBaseNameA()' for "
			"process " + MLB::Utility::ValueToStringHex(process_handle) +
			", module " + MLB::Utility::ValueToStringHex(module_handle) + " with "
			"a module name buffer located at " +
			MLB::Utility::ValueToStringHex(module_name) + " and a module name "
			"buffer length of " +
			MLB::Utility::AnyToString(module_name_length) + " failed");

	return(module_name);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &OS_GetModuleBaseName(HANDLE process_handle, HMODULE module_handle,
	std::string &module_name)
{
	char tmp_buffer[(MLB::Utility::MaxPathNameLength * 2) + 1];

	return(module_name.assign(OS_GetModuleBaseName(process_handle,
		module_handle, tmp_buffer, sizeof(tmp_buffer) - 1)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string OS_GetModuleBaseName(HANDLE process_handle, HMODULE module_handle)
{
	std::string module_name;

	return(OS_GetModuleBaseName(process_handle, module_handle, module_name));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace OSSupport

} // namespace MLB

#ifdef TEST_MAIN

using namespace MLB::OSSupport;

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		std::cout << "Test OS_GetModuleBaseName():" << std::endl;
		HANDLE  process_handle = ::GetCurrentProcess();
		HMODULE module_handle  = OS_GetModuleHandle("ntdll.dll", true);
		std::cout << "   OS_GetModuleHandle(\"ntdll.dll\", true)"
			"                 : " <<
			MLB::Utility::ValueToStringHex(module_handle) << std::endl;
		std::cout << "   OS_GetModuleBaseName(" <<
			MLB::Utility::ValueToStringHex(process_handle) << ", " <<
			MLB::Utility::ValueToStringHex(module_handle) << "): " <<
			OS_GetModuleBaseName(process_handle, module_handle) << std::endl;
	}
	catch (const std::exception &except) {
		std::cerr << "REGRESSION TEST FAILURE: " <<
			"OSSupport/Win/OS_GetModuleBaseName.cpp: " << except.what() <<
			std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif /* #ifdef TEST_MAIN */

