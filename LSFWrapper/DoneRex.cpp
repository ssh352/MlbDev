// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB LSFWrapper Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Support for LSF functionality 'ls_donerex()'.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2017.
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
int LSF_donerex()
{
	int result;

	if ((result = ls_donerex()) != 0) {
		std::ostringstream error_text;
		error_text << "Invocation of 'ls_donerex()' returned " << result << ".";
		throw MLB::LSFWrapper::LSFExceptionStatus(lserrno,	error_text);
	}

	return(result);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int DoneRex()
{
	return(LSF_donerex());
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace LSFWrapper

} // namespace MLB

#include <iomanip>

#ifdef TEST_MAIN

using namespace MLB::LSFWrapper;

//	////////////////////////////////////////////////////////////////////////////
static void TEST_DoneRex()
{
	std::cout << "InitRex(1, 0): " << InitRex(1) << std::endl;
	std::cout << "DoneRex()    : " << DoneRex()  << std::endl;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	std::cout << "Test of function 'DoneRex()'" << std::endl;
	std::cout << "---- -- -------- -----------" << std::endl;

	try {
		TEST_DoneRex();
	}
	catch (const std::exception &except) {
		std::cout << std::endl << "ERROR: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
//	////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

