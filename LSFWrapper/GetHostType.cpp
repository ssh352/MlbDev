// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB LSFWrapper Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Support for LSF functionality 'ls_gethosttype()'.

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

#include <LSFWrapper/LSFWrapper.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace LSFWrapper {

//	////////////////////////////////////////////////////////////////////////////
char *LSF_gethosttype(const char *host_name)
{
	char *result;

	LSFWrapper_THROW_IF_NULL(result, ls_gethosttype,
		(const_cast<char *>(host_name)));

	if (!(*result))
		throw LSFException("Platform/LSF function 'ls_gethosttype()' returned "
			"an empty string.");

	return(result);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string GetHostType(const std::string &host_name)
{
	return(LSF_gethosttype(host_name.c_str()));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace LSFWrapper

} // namespace MLB

#include <iomanip>

#ifdef TEST_MAIN

using namespace MLB::LSFWrapper;

//	////////////////////////////////////////////////////////////////////////////
static void TEST_GetHostType()
{
	LSF_HostInfoVector host_info_list = GetHostInfo();

	LSF_HostInfoVector::const_iterator iter_b(host_info_list.begin());
	LSF_HostInfoVector::const_iterator iter_e(host_info_list.end());

	while (iter_b != iter_e) {
		std::cout << "Host type for " << std::left << std::setw(63) <<
			iter_b->hostName << ": " << GetHostType(iter_b->hostName) <<
			std::endl;
		++iter_b;
	}
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	std::cout << "Test of function 'GetHostType()'" << std::endl;
	std::cout << "---- -- -------- ---------------" << std::endl;

	try {
		TEST_GetHostType();
	}
	catch (const std::exception &except) {
		std::cout << std::endl << "ERROR: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
//	////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

