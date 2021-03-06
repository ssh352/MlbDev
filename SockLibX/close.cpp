/* *********************************************************************** */
/* *********************************************************************** */
/*	Network Programming Support Library (NPSL) Source Module						*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes a socket.

	Revision History	:	1993-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */
 
#include <string.h>

#include "npsli.h"

#if defined(__linux__) && defined(__GNUC__)
# include <unistd.h>
#endif // #if defined(__linux__) && defined(__GNUC__)

/* *********************************************************************** */

/* *********************************************************************** */
int NPSL_CloseSocket(NPSL_SOCKET_HANDLE socket_handle, char *error_text)
{
	int         return_code;
	const char *function_name;

#ifdef _Windows
	function_name = "closesocket";

	if (closesocket(socket_handle) == NPSL_SOCKET_ERROR) {
#else
	function_name = "close";

	if (close(socket_handle) == NPSL_SOCKET_ERROR) {
#endif // #ifdef _Windows
		if (error_text != NULL)
			NPSL_AppendLastErrorString(0, NPSL_MAX_ERROR_TEXT,
				strcat(strcat(strcpy(error_text,
				"Attempt to close a socket connection with '"),
				function_name), "()' failed: "));
		return_code = NPSL_SUPP_MapLastError();
	}
	else
		return_code = NPSL_SUCCESS;

	return(return_code);
}
/* *********************************************************************** */

