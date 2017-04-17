// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	SocketIo Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the PacketSocketAsync class.

	Revision History	:	2010-11-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2010 - 2017.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <SocketIo/PacketSocketAsync.hpp>

#include <Utility/ValueToStringRadix.hpp>
#include <Utility/Utility_Exception.hpp>

#include <boost/bind.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace SocketIo {

// ////////////////////////////////////////////////////////////////////////////
PacketSocketAsync::PacketSocketAsync(std::size_t buffer_size,
	boost::shared_ptr<char> &buffer_sptr, boost::asio::io_service &io_service,
	const std::string &mc_group, IpPortType ip_port,
	const std::string &host_interface, bool is_broadcast, bool bind_local)
	:PacketSocket(io_service, mc_group, ip_port, host_interface, is_broadcast,
		bind_local)
	,is_running_(false)
	,sender_endpoint_()
	,buffer_(buffer_size, buffer_sptr)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
PacketSocketAsync::PacketSocketAsync(std::size_t buffer_size,
	boost::shared_ptr<char> &buffer_sptr, boost::asio::io_service &io_service,
	const std::string &mc_group, const std::string &ip_port,
	const std::string &host_interface, bool is_broadcast, bool bind_local)
	:PacketSocket(io_service, mc_group, ip_port, host_interface, is_broadcast,
		bind_local)
	,is_running_(false)
	,sender_endpoint_()
	,buffer_(buffer_size, buffer_sptr)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
PacketSocketAsync::PacketSocketAsync(std::size_t buffer_size,
	boost::shared_ptr<char> &buffer_sptr, boost::asio::io_service &io_service,
	const SocketSpec &socket_spec, bool is_broadcast, bool bind_local)
	:PacketSocket(io_service, socket_spec, is_broadcast, bind_local)
	,is_running_(false)
	,sender_endpoint_()
	,buffer_(buffer_size, buffer_sptr)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
PacketSocketAsync::PacketSocketAsync(std::size_t buffer_size,
	char *buffer_ptr, boost::asio::io_service &io_service,
	const std::string &mc_group, IpPortType ip_port,
	const std::string &host_interface, bool is_broadcast, bool bind_local)
	:PacketSocket(io_service, mc_group, ip_port, host_interface, is_broadcast,
		bind_local)
	,is_running_(false)
	,sender_endpoint_()
	,buffer_(buffer_size, buffer_ptr)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
PacketSocketAsync::PacketSocketAsync(std::size_t buffer_size,
	char *buffer_ptr, boost::asio::io_service &io_service,
	const std::string &mc_group, const std::string &ip_port,
	const std::string &host_interface, bool is_broadcast, bool bind_local)
	:PacketSocket(io_service, mc_group, ip_port, host_interface, is_broadcast,
		bind_local)
	,is_running_(false)
	,sender_endpoint_()
	,buffer_(buffer_size, buffer_ptr)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
PacketSocketAsync::PacketSocketAsync(std::size_t buffer_size,
	char *buffer_ptr, boost::asio::io_service &io_service,
	const SocketSpec &socket_spec, bool is_broadcast, bool bind_local)
	:PacketSocket(io_service, socket_spec, is_broadcast, bind_local)
	,is_running_(false)
	,sender_endpoint_()
	,buffer_(buffer_size, buffer_ptr)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
PacketSocketAsync::PacketSocketAsync(std::size_t buffer_size,
	boost::asio::io_service &io_service, const std::string &mc_group,
	IpPortType ip_port, const std::string &host_interface, bool is_broadcast,
	bool bind_local)
	:PacketSocket(io_service, mc_group, ip_port, host_interface, is_broadcast,
		bind_local)
	,is_running_(false)
	,sender_endpoint_()
	,buffer_(buffer_size)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
PacketSocketAsync::PacketSocketAsync(std::size_t buffer_size,
	boost::asio::io_service &io_service, const std::string &mc_group,
	const std::string &ip_port, const std::string &host_interface,
	bool is_broadcast, bool bind_local)
	:PacketSocket(io_service, mc_group, ip_port, host_interface, is_broadcast,
		bind_local)
	,is_running_(false)
	,sender_endpoint_()
	,buffer_(buffer_size)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
PacketSocketAsync::PacketSocketAsync(std::size_t buffer_size,
	boost::asio::io_service &io_service, const SocketSpec &socket_spec,
	bool is_broadcast, bool bind_local)
	:PacketSocket(io_service, socket_spec, is_broadcast, bind_local)
	,is_running_(false)
	,sender_endpoint_()
	,buffer_(buffer_size)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
PacketSocketAsync::~PacketSocketAsync()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool PacketSocketAsync::IsRunning() const
{
	return(is_running_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool PacketSocketAsync::Run()
{
	if (!RunImpl())
		return(false);

	if (!is_running_)
		Schedule();

	return(true);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool PacketSocketAsync::RecvFromAsync(
	const boost::system::error_code &error, std::size_t bytes_received)
{
	if (RecvFromAsyncImpl(error, bytes_received)) {
		Schedule();
		return(true);
	}

	return(false);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool PacketSocketAsync::RunImpl()
{
	return(true);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool PacketSocketAsync::RecvFromAsyncImpl(
	const boost::system::error_code & /* error */,
	std::size_t /* bytes_received */)
{
	return(true);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void PacketSocketAsync::Schedule()
{
	socket_.async_receive_from(
		boost::asio::buffer(buffer_.GetPtr(), buffer_.GetSize()),
		sender_endpoint_, boost::bind(&PacketSocketAsync::RecvFromAsync,
		this, boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));

	is_running_ = true;
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace SocketIo

} // namespace MLB

#ifdef TEST_MAIN

using namespace MLB::SocketIo;

// ////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	int return_code = EXIT_SUCCESS;

	try {
		std::string ip_address("239.255.1.46");
		std::string ip_port("8612");
		std::string host_interface;
		if (argc > 1) {
			ip_address = argv[1];
			if (argc > 2) {
				ip_port = argv[2];
				if (argc > 3)
					host_interface = argv[3];
			}
		}
		boost::asio::io_service io_service;
		PacketSocketAsync       test_socket(1000000, io_service, ip_address,
			ip_port, host_interface);
		//	Send
		//	Receive
		boost::asio::ip::udp::endpoint src_endpoint;
		std::string packet_data;
		test_socket.RecvFrom(packet_data, src_endpoint);
		std::cout << "First message of three  : " << packet_data << std::endl;
		test_socket.RecvFrom(packet_data, src_endpoint);
		std::cout << "Second message of three : " << packet_data << std::endl;
		test_socket.RecvFrom(packet_data, src_endpoint);
		std::cout << "Third message of three  : " << packet_data << std::endl;
	}
	catch (const std::exception &except) {
		std::cerr << std::endl << "ERROR: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

