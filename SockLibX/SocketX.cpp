//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	SockLibX Portable Socket Library Source Module
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation file for class SocketX.

	Revision History	:	2002-01-26 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2002 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Include necessary header files . . .
//	////////////////////////////////////////////////////////////////////////////

#include <SockLibX/SocketX.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace SockLibX {

//	////////////////////////////////////////////////////////////////////////////
SocketX::SocketX(NativeSocketHandle in_socket_handle,
	const NativeSockAddr &in_end_point, AddressFamily in_address_family,
	SocketType in_socket_type, ProtocolType in_protocol_type)
	:address_family(in_address_family)
	,socket_type(in_socket_type)
	,protocol_type(in_protocol_type)
	,socket_handle(NPSL_INVALID_SOCKET)
	,end_point(in_end_point)
	,is_connected(false)
{
	if (in_socket_handle != NPSL_INVALID_SOCKET) {
		socket_handle  = in_socket_handle;
		is_connected   = true;
		end_point_addr = GetSockaddr();
	}
	else
		Connect(end_point);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SocketX::SocketX(NativeSocketHandle in_socket_handle,
	const NativeSockAddr_In &in_end_point, AddressFamily in_address_family,
	SocketType in_socket_type, ProtocolType in_protocol_type)
	:address_family(in_address_family)
	,socket_type(in_socket_type)
	,protocol_type(in_protocol_type)
	,socket_handle(NPSL_INVALID_SOCKET)
	,end_point(in_end_point)
	,is_connected(false)
{
	if (in_socket_handle != NPSL_INVALID_SOCKET) {
		socket_handle  = in_socket_handle;
		is_connected   = true;
		end_point_addr = GetSockaddr();
	}
	else
		Connect(end_point);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SocketX::SocketX(NativeSocketHandle in_socket_handle,
	const EndPointIP &in_end_point, AddressFamily in_address_family,
	SocketType in_socket_type, ProtocolType in_protocol_type)
	:address_family(in_address_family)
	,socket_type(in_socket_type)
	,protocol_type(in_protocol_type)
	,socket_handle(NPSL_INVALID_SOCKET)
	,end_point(in_end_point)
	,is_connected(false)
{
	if (in_socket_handle != NPSL_INVALID_SOCKET) {
		socket_handle  = in_socket_handle;
		is_connected   = true;
		end_point_addr = GetSockaddr();
	}
	else
		Connect(in_end_point);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SocketX::SocketX(const EndPointIP &in_end_point, AddressFamily in_address_family,
	SocketType in_socket_type, ProtocolType in_protocol_type)
	:address_family(in_address_family)
	,socket_type(in_socket_type)
	,protocol_type(in_protocol_type)
	,socket_handle(NPSL_INVALID_SOCKET)
	,end_point()
	,is_connected(false)
{
	Connect(in_end_point);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SocketX::SocketX(AddressFamily in_address_family, SocketType in_socket_type,
	ProtocolType in_protocol_type)
	:address_family(in_address_family)
	,socket_type(in_socket_type)
	,protocol_type(in_protocol_type)
	,socket_handle(NPSL_INVALID_SOCKET)
	,end_point()
	,is_connected(false)
{
	Create();
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SocketX::~SocketX()
{
	Close();
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SocketX::SocketX(const SocketX &other)
{
	address_family = other.address_family;
	socket_type    = other.socket_type;
	protocol_type  = other.protocol_type;
	socket_handle  = other.socket_handle;
	end_point      = other.end_point;
	end_point_addr = other.end_point_addr;
	is_connected   = other.is_connected;

	if (other.socket_handle != NPSL_INVALID_SOCKET) {
		const_cast<SocketX &>(other).socket_handle = NPSL_INVALID_SOCKET;
		const_cast<SocketX &>(other).is_connected  = false;
	}
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SocketX & SocketX::operator = (const SocketX &other)
{
	address_family = other.address_family;
	socket_type    = other.socket_type;
	protocol_type  = other.protocol_type;
	socket_handle  = other.socket_handle;
	end_point      = other.end_point;
	end_point_addr = other.end_point_addr;
	is_connected   = other.is_connected;

	if (other.socket_handle != NPSL_INVALID_SOCKET) {
		const_cast<SocketX &>(other).socket_handle = NPSL_INVALID_SOCKET;
		const_cast<SocketX &>(other).is_connected  = false;
	}

	return(*this);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::Create()
{
	CheckNotCreated();

	socket_handle = Socket(address_family, socket_type, protocol_type);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::Connect()
{
	Connect(end_point);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::Connect(const EndPointIP &in_end_point)
{
	if (!IsCreated())
		Create();

	CheckNotConnected();

	MLB::SockLibX::Connect(socket_handle, in_end_point);

	end_point      = in_end_point;
	end_point_addr = GetSockaddr();
	is_connected   = true;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
// Notes:
//		1) No harm is done if this method is called on a socket instance
//			which has not been created or connected.
//		2)	Any exceptions are suppressed until after the socket close.
void SocketX::Close()
{
	if (!IsCreated())
		return;

	std::string error_string;

	// If we are at present connected, we must first disconnect the socket.
	//	We'll catch any exception for later reporting...
	if (IsConnected()) {
		try {
			Disconnect();
		}
		catch (std::exception &except) {
			error_string += except.what();
		}
	}

	// Now close the socket... Capture and concatenate error messages...
	try {
		MLB::SockLibX::CloseSocket(socket_handle);
	}
	catch (const std::exception &except) {
		error_string += ((error_string.empty()) ? "E" : ": Additional e") +
			std::string("rror(s) on socket close: ") + except.what();
	}

	//	Invalidate the socket handle...
	socket_handle = NPSL_INVALID_SOCKET;

	// Finally, (re-)throw an exception if an error occurred...
	if (!error_string.empty())
		throw SockLibXException(error_string);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
// Notes:
//		1) No harm is done if this method is called on a socket instance
//			which has not been connected.
//		2)	Any exceptions are suppressed until after the socket has
//			been disconnected.
void SocketX::Disconnect()
{
	if (IsConnected()) {
		try {
			ShutDown(ShutDownHow_Both);
		}
		catch (const std::exception &except) {
			// Some kind of problem... Indicate no connection.
			is_connected = false;
			MLB::Utility::Rethrow(except, "Error(s) on socket shut-down: " +
				std::string(except.what()));
		}
	}
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SocketX SocketX::Accept()
{
	SocketX tmp_client_socket;

	return(Accept(tmp_client_socket));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SocketX &SocketX::Accept(SocketX &client_socket)
{
	EndPointIP         client_end_point;
	NativeSocketHandle client_native_handle = Accept(client_end_point);
	SocketX            tmp_client_socket(client_native_handle,
		client_end_point, address_family, socket_type, protocol_type);

	client_socket = tmp_client_socket;

	return(client_socket);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSocketHandle SocketX::Accept(EndPointIP &end_point)
{
	CheckNotConnected();

	return(MLB::SockLibX::Accept(socket_handle, end_point));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSocketHandle SocketX::Accept(NativeSockAddr_In &addr)
{
	CheckNotConnected();

	return(MLB::SockLibX::Accept(socket_handle, addr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSocketHandle SocketX::Accept(NativeSockAddr &addr,
	NativeSockLen_T &addr_length)
{
	CheckNotConnected();

	return(MLB::SockLibX::Accept(socket_handle, addr, addr_length));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSocketHandle SocketX::Accept(NativeSockAddr *addr,
	NativeSockLen_T *addr_length) const
{
	CheckNotConnected();

	return(MLB::SockLibX::Accept(socket_handle, addr, addr_length));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::Bind(const EndPointIP &end_point) const
{
	NativeSockAddr_In addr = end_point.GetSockaddrIn();

	return(Bind(reinterpret_cast<const NativeSockAddr *>(&addr), sizeof(addr)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::Bind(const NativeSockAddr_In &addr) const
{
	Bind(reinterpret_cast<const NativeSockAddr *>(&addr), sizeof(addr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::Bind(const NativeSockAddr &addr) const
{
	Bind(&addr, sizeof(addr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::Bind(const NativeSockAddr *addr, NativeSockLen_T addrlen) const
{
	CheckNotConnected();

	CheckCreated();

	MLB::SockLibX::Bind(socket_handle, addr, addrlen);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::CloseSocket()
{
	Close();
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
EndPointIP SocketX::GetPeerName()
{
	CheckConnected();

	return(MLB::SockLibX::GetPeerName(socket_handle));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
EndPointIP SocketX::GetSockName()
{
	return(MLB::SockLibX::GetSockName(socket_handle));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::GetSockOpt(int opt_level, int opt_name, void *opt_value,
	int *opt_length)
{
	CheckCreated();

	MLB::SockLibX::GetSockOpt(socket_handle, opt_level, opt_name, opt_value,
		opt_length);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::GetSockOpt(int opt_level, int opt_name, bool &opt_value)
{
	CheckCreated();

	MLB::SockLibX::GetSockOpt(socket_handle, opt_level, opt_name, opt_value);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::GetSockOpt(int opt_level, int opt_name, int &opt_value)
{
	CheckCreated();

	MLB::SockLibX::GetSockOpt(socket_handle, opt_level, opt_name, opt_value);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::Listen(unsigned int backlog_count) const
{
	CheckNotConnected();

	MLB::SockLibX::Listen(socket_handle, backlog_count);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::Recv(std::string &buffer, unsigned int buffer_length,
	int flags) const
{
	CheckConnected();

	return(MLB::SockLibX::Recv(socket_handle, buffer, buffer_length, flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::Recv(char *buffer_ptr, unsigned int buffer_length,
	int flags) const
{
	CheckConnected();

	return(MLB::SockLibX::Recv(socket_handle, buffer_ptr, buffer_length, flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
//	The version which takes a 'char *' argument matches most closely the BSD
//	library function, so this 'void *' version invokes it instead of the other
//	way around...
unsigned int SocketX::Recv(void *buffer_ptr, unsigned int buffer_length,
	int flags) const
{
	return(MLB::SockLibX::Recv(socket_handle, static_cast<char *>(buffer_ptr),
		buffer_length, flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::RecvAppend(std::string &buffer, int flags) const
{
	CheckConnected();

	return(MLB::SockLibX::RecvAppend(socket_handle, buffer, flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::RecvFrom(char *buffer_ptr, unsigned int buffer_length,
	int flags, NativeSockAddr *addr, NativeSockLen_T *addrlen) const
{
	CheckCreated();

	return(MLB::SockLibX::RecvFrom(socket_handle, buffer_ptr, buffer_length,
		flags, addr, addrlen));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
//	The version which takes a 'char *' argument matches most closely the BSD
//	library function, so this 'void *' version invokes it instead of the other
//	way around...
unsigned int SocketX::RecvFrom(void *buffer_ptr, unsigned int buffer_length,
	int flags, NativeSockAddr *addr, NativeSockLen_T *addrlen) const
{
	CheckCreated();

	return(MLB::SockLibX::RecvFrom(socket_handle, buffer_ptr, buffer_length,
		flags, addr, addrlen));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::RecvFrom(void *buffer_ptr, unsigned int buffer_length,
	int flags, EndPointIP &end_point) const
{
	CheckCreated();

	return(MLB::SockLibX::RecvFrom(socket_handle, buffer_ptr, buffer_length,
		flags, end_point));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::RecvFrom(std::string &buffer, unsigned int buffer_length,
	int flags, NativeSockAddr &addr, NativeSockLen_T &addr_length)
{
	CheckCreated();

	return(MLB::SockLibX::RecvFrom(socket_handle, buffer, buffer_length, flags,
		addr, addr_length));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::RecvFrom(std::string &buffer, unsigned int buffer_length,
	int flags, NativeSockAddr_In &addr)
{
	CheckCreated();

	return(MLB::SockLibX::RecvFrom(socket_handle, buffer, buffer_length, flags,
		addr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::RecvFrom(std::string &buffer, unsigned int buffer_length,
	int flags, EndPointIP &end_point)
{
	CheckCreated();

	return(MLB::SockLibX::RecvFrom(socket_handle, buffer, buffer_length, flags,
		end_point));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::Select(NativeFDSet_T *read_fd_set,
	NativeFDSet_T *write_fd_set, NativeFDSet_T *error_fd_set,
	const struct timeval *time_out_ptr) const
{
	CheckCreated();

	return(MLB::SockLibX::Select(socket_handle, read_fd_set, write_fd_set,
		error_fd_set, time_out_ptr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectRead(const struct timeval *time_out_ptr) const
{
	NativeFDSet_T tmp_fd_set = GetFDSet();

	return(Select(&tmp_fd_set, NULL, NULL, time_out_ptr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectRead(const struct timeval &time_out_ref) const
{
	return(SelectRead(&time_out_ref));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectRead(unsigned int wait_usecs) const
{
	return(SelectRead(
		MLB::Utility::TimeVal(wait_usecs / 1000000, wait_usecs % 1000000)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectWrite(const struct timeval *time_out_ptr) const
{
	NativeFDSet_T tmp_fd_set = GetFDSet();

	return(Select(NULL, &tmp_fd_set, NULL, time_out_ptr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectWrite(const struct timeval &time_out_ref) const
{
	return(SelectWrite(&time_out_ref));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectWrite(unsigned int wait_usecs) const
{
	return(SelectWrite(
		MLB::Utility::TimeVal(wait_usecs / 1000000, wait_usecs % 1000000)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectError(const struct timeval *time_out_ptr) const
{
	NativeFDSet_T tmp_fd_set = GetFDSet();

	return(Select(NULL, NULL, &tmp_fd_set, time_out_ptr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectError(const struct timeval &time_out_ref) const
{
	return(SelectError(&time_out_ref));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectError(unsigned int wait_usecs) const
{
	return(SelectError(
		MLB::Utility::TimeVal(wait_usecs / 1000000, wait_usecs % 1000000)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::Send(const std::ostringstream &buffer, int flags) const
{
	return(Send(buffer.str(), flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::Send(const std::string &buffer, int flags) const
{
	return(Send(buffer.c_str(), static_cast<unsigned int>(buffer.size()),
		flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::Send(const char *buffer_ptr, unsigned int buffer_length,
	int flags) const
{
	CheckConnected();

	return(MLB::SockLibX::Send(socket_handle, buffer_ptr, buffer_length, flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
//	The version which takes a 'const char *' argument matches most closely the
//	BSD library function, so this 'const void *' version invokes it instead of
//	the other way around...
unsigned int SocketX::Send(const void *buffer_ptr, unsigned int buffer_length,
	int flags) const
{
	return(Send(static_cast<const char *>(buffer_ptr), buffer_length, flags));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SendTo(const std::ostringstream &buffer, int flags,
	const NativeSockAddr *addr, NativeSockLen_T addrlen) const
{
	return(SendTo(buffer.str(), flags, addr, addrlen));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SendTo(const std::string &buffer, int flags,
	const NativeSockAddr &addr) const
{
	CheckConnected();

	return(MLB::SockLibX::SendTo(socket_handle, buffer, flags, addr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SendTo(const std::string &buffer, int flags,
	const NativeSockAddr_In &addr) const
{
	CheckConnected();

	return(MLB::SockLibX::SendTo(socket_handle, buffer, flags, addr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SendTo(const std::string &buffer, int flags,
	const EndPointIP &end_point) const
{
	CheckConnected();

	return(MLB::SockLibX::SendTo(socket_handle, buffer, flags, end_point));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SendTo(const std::string &buffer, int flags,
	const NativeSockAddr *addr, NativeSockLen_T addrlen) const
{
	return(SendTo(buffer.c_str(), static_cast<unsigned int>(buffer.size()),
		flags, addr, addrlen));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SendTo(const char *buffer_ptr, unsigned int buffer_length,
	int flags, const NativeSockAddr *addr, NativeSockLen_T addrlen) const
{
	CheckCreated();

	return(MLB::SockLibX::SendTo(socket_handle, buffer_ptr, buffer_length,
	  flags, addr, addrlen));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::SetSockOpt(int opt_level, int opt_name, const void *opt_value,
	int opt_length)
{
	CheckCreated();

	MLB::SockLibX::SetSockOpt(socket_handle, opt_level, opt_name, opt_value,
		opt_length);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::SetSockOpt(int opt_level, int opt_name, bool opt_value)
{
	SetSockOpt(opt_level, opt_name, &opt_value, sizeof(opt_value));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::SetSockOpt(int opt_level, int opt_name, int opt_value)
{
	SetSockOpt(opt_level, opt_name, &opt_value, sizeof(opt_value));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::ShutDown(ShutDownHow shut_down_how)
{
	CheckConnected();

	MLB::SockLibX::ShutDown(socket_handle, shut_down_how);

	is_connected = false;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectWait(NativeFDSet_T *read_fd_set,
	NativeFDSet_T *write_fd_set, NativeFDSet_T *error_fd_set,
	const struct timeval *time_out_ptr) const
{
	return(Select(read_fd_set, write_fd_set, error_fd_set, time_out_ptr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectWaitOnRead(
	const struct timeval *time_out_ptr) const
{
	NativeFDSet_T read_fd_set  = GetFDSet();

	return(Select(&read_fd_set, NULL, NULL, time_out_ptr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectWaitOnWrite(
	const struct timeval *time_out_ptr) const
{
	NativeFDSet_T write_fd_set = GetFDSet();

	return(Select(NULL, &write_fd_set, NULL, time_out_ptr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectWaitOnError(
	const struct timeval *time_out_ptr) const
{
	NativeFDSet_T error_fd_set = GetFDSet();

	return(Select(NULL, NULL, &error_fd_set, time_out_ptr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::SelectWaitOnAny(
	const struct timeval *time_out_ptr) const
{
	NativeFDSet_T read_fd_set  = GetFDSet();
	NativeFDSet_T write_fd_set = GetFDSet();
	NativeFDSet_T error_fd_set = GetFDSet();

	return(Select(&read_fd_set, &write_fd_set, &error_fd_set, time_out_ptr));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::GetRecvBufferSize()
{
	CheckCreated();

	return(MLB::SockLibX::GetRecvBufferSize(socket_handle));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int SocketX::GetSendBufferSize()
{
	CheckCreated();

	return(MLB::SockLibX::GetSendBufferSize(socket_handle));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::SetRecvBufferSize(unsigned int buffer_size)
{
	CheckCreated();

	MLB::SockLibX::SetRecvBufferSize(socket_handle, buffer_size);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::SetSendBufferSize(unsigned int buffer_size)
{
	CheckCreated();

	MLB::SockLibX::SetSendBufferSize(socket_handle, buffer_size);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeFDSet_T SocketX::GetFDSet() const
{
	CheckCreated();

	return(MLB::SockLibX::GetFDSet(socket_handle));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeFDSet_T &SocketX::AppendToFDSet(NativeFDSet_T &in_fd_set) const
{
	CheckCreated();

	return(MLB::SockLibX::AppendToFDSet(socket_handle, in_fd_set));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::SetBlockingMode(bool blocking_mode_flag) const
{
	CheckCreated();

	MLB::SockLibX::SetBlockingMode(socket_handle, blocking_mode_flag);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::SetBlockingModeOn() const
{
	SetBlockingMode(true);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::SetBlockingModeOff() const
{
	SetBlockingMode(false);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool SocketX::IsCreated() const
{
	return(socket_handle != NPSL_INVALID_SOCKET);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool SocketX::IsConnected() const
{
	return(IsCreated() && is_connected);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool SocketX::IsReadyReadOrWrite() const
{
	NativeFDSet_T  read_fd_set  = GetFDSet();
	NativeFDSet_T  write_fd_set = GetFDSet();
	struct timeval time_out     = { 0, 0 };

	return(IsConnected() && Select(&read_fd_set, &write_fd_set, NULL,
		&time_out));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool SocketX::IsReadyRead() const
{
	struct timeval time_out = { 0, 0 };

	return(IsConnected() && SelectRead(&time_out));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool SocketX::IsReadyWrite() const
{
	struct timeval time_out = { 0, 0 };

	return(IsConnected() && SelectWrite(&time_out));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::CheckCreated() const
{
	if (!IsCreated())
		throw SockLibXException("Socket has not been created.");
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::CheckConnected() const
{
	CheckCreated();

	if (!IsConnected())
		throw SockLibXException("Socket has not been connected.");
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::CheckNotCreated() const
{
	if (IsCreated())
		throw SockLibXException("Socket is already created.");
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::CheckNotConnected() const
{
	if (IsConnected())
		throw SockLibXException("Socket has already been connected.");
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSocketHandle SocketX::GetSocket() const
{
	return(socket_handle);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressFamily SocketX::GetAddressFamily() const
{
	return(address_family);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
SocketType SocketX::GetSocketType() const
{
	return(socket_type);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
ProtocolType SocketX::GetProtocolType() const
{
	return(protocol_type);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string SocketX::GetHostIPAddress() const
{
	return(end_point.GetHostIPAddress());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string SocketX::GetHostIPAddressZeroFilled() const
{
	return(end_point.GetHostIPAddressZeroFilled());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string SocketX::GetHostName() const
{
	return(end_point.GetHostName());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int SocketX::GetPort() const
{
	return(end_point.GetPort());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
EndPointIP SocketX::GetEndPointIP() const
{
	return(end_point);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSockAddr_In  SocketX::GetSockaddrIn() const
{
	return(end_point.GetSockaddrIn(address_family));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSockAddr  SocketX::GetSockaddr() const
{
	return(end_point.GetSockaddr(address_family));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void SocketX::Invalidate()
{
	socket_handle = NPSL_INVALID_SOCKET;
	is_connected  = false;
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace SockLibX

} // namespace MLB

#ifdef TEST_MAIN

# include <iostream>

using namespace MLB::SockLibX;

//	////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	int         return_code = EXIT_SUCCESS;
	const char *host;
	const char *port;

	host = (argc > 1) ? argv[1] : "localhost";
	port = (argc > 2) ? argv[2] : "7777";

	try {
		SockLibXContext socket_lib;
		std::cout << "Attempting to connect to [" << host << ":" << port <<
			"]..." << std::flush;
		SocketX my_socket(EndPointIP(AddressIP(host), port));
		std::cout << " done!!!" << std::endl;
		std::cout << "Local  endpoint: [" << my_socket.GetSockName() << "]" <<
			std::endl;
		std::cout << "Remote endpoint: [" << my_socket.GetPeerName() << "]" <<
			std::endl;
		my_socket.Disconnect();
		my_socket.Close();
	}
	catch (std::exception &except) {
		std::cout << std::endl << "MLB::SockLibX::SocketX error: " <<
			except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	std::cout << "Test completed." << std::endl;

	return(return_code);
}
//	////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

