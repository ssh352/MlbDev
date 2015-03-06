// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Operating System Support (OSSupport) Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of GetStartUpDirectory().

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

#include <OSSupport_Win.h>

#include <Utility/PathName.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace OSSupport {

// ////////////////////////////////////////////////////////////////////////////
std::string &GetStartUpDirectory(std::string &out_dir)
{
	return(out_dir.assign(MLB::Utility::GetDirNamePortion(
		DetermineProcessImageFileName())));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string GetStartUpDirectory()
{
	std::string out_dir;

	return(GetStartUpDirectory(out_dir));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace OSSupport

} // namespace MLB

#ifdef TEST_MAIN

using namespace MLB::OSSupport;

// ////////////////////////////////////////////////////////////////////////////
int main(int, char **argv)
{
	int return_code = EXIT_SUCCESS;

	try {
		std::cout << "Test GetStartUpDirectory(): " << std::endl;
		std::cout << "   argv[0]               = [" <<
			argv[0] << "]" <<  std::endl;
		std::cout << "   GetStartUpDirectory() = [" <<
			GetStartUpDirectory() << "]" << std::endl;
	}
	catch (const std::exception &except) {
		std::cerr << "REGRESSION TEST FAILURE: " <<
			"OSSupport/Win/GetStartUpDirectory.cpp: " << except.what() <<
			std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif /* #ifdef TEST_MAIN */

