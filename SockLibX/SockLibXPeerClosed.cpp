//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	SockLibX Portable Socket Library Source Module
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the SockLibXPeerClosed class.

	Revision History	:	2002-01-26 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2002 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Include necessary header files . . .
//	////////////////////////////////////////////////////////////////////////////

#include <SockLibX.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace SockLibX {

//	////////////////////////////////////////////////////////////////////////////
SockLibXPeerClosed::SockLibXPeerClosed(const char *except_string)
	:SockLibXExceptionError(false, SocketError_None,
		GetPeerClosedString(except_string))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SockLibXPeerClosed::SockLibXPeerClosed(const std::string &except_string)
	:SockLibXExceptionError(false, SocketError_None,
		GetPeerClosedString(except_string.c_str()))
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SockLibXPeerClosed::~SockLibXPeerClosed() MBCOMPAT_EXCEPT_NOTHROW
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SockLibXPeerClosed::Rethrow(const char *except_string) const
{
	SockLibXPeerClosed tmp_except(*this);

	tmp_except.SetWhat(except_string);

	throw tmp_except;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool SockLibXPeerClosed::IsPeerConnectShutdown() const
{
	return(true);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string SockLibXPeerClosed::GetPeerClosedString(const char *other_text)
{
	return(((other_text != NULL) && *other_text) ?
		("Socket closed by peer: " + std::string(other_text)) :
		"Socket closed by peer.");
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace SockLibX

} // namespace MLB

