//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	SockLibX Portable Socket Library Source Module
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the AddressIP class.

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

#include <Utility/StringSupport.hpp>

#include <algorithm>

#include <memory.h>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace SockLibX {

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP() :
	host_name_()
{
	memset(ip_address, '\0', sizeof(ip_address));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP(long in_address) :
	host_name_()
{
	SetAddress(in_address);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP(unsigned long in_address) :
	host_name_()
{
	SetAddress(in_address);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP(const unsigned char *in_address) :
	host_name_()
{
	SetAddress(in_address);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP(const char *in_address) :
	host_name_()
{
	SetAddress(in_address);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP(const std::string &in_address) :
	host_name_()
{
	SetAddress(in_address.c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP(const char *in_address, bool is_raw_ip_flag) :
	host_name_()
{
	SetAddress(in_address, is_raw_ip_flag);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP(const std::string &in_address, bool is_raw_ip_flag) :
	host_name_()
{
	SetAddress(in_address.c_str(), is_raw_ip_flag);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP(const char *in_host_name, const char *in_address) :
	host_name_(in_host_name)
{
	SetAddress(in_address);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP(const std::string &in_host_name,
	const std::string &in_address) :
	host_name_(in_host_name)
{
	SetAddress(in_address.c_str());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP::AddressIP(const AddressIP &other) :
	host_name_(other.host_name_)
{
	memcpy(ip_address, other.ip_address, sizeof(ip_address));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
AddressIP & AddressIP::operator = (const AddressIP &other)
{
	AddressIP tmp_datum(other);

	swap(tmp_datum);

	return(*this);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void AddressIP::swap(AddressIP &other)
{
	host_name_.swap(other.host_name_);

	unsigned char tmp_ip_address[4];

	memcpy(tmp_ip_address, ip_address, sizeof(ip_address));
	memcpy(ip_address, other.ip_address, sizeof(ip_address));
	memcpy(other.ip_address, tmp_ip_address, sizeof(ip_address));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void AddressIP::SetAddress(long in_address)
{
	memcpy(ip_address, &in_address, sizeof(ip_address));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void AddressIP::SetAddress(unsigned long in_address)
{
	memcpy(ip_address, &in_address, sizeof(ip_address));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void AddressIP::SetAddress(const unsigned char *in_address)
{
	memcpy(ip_address, in_address, sizeof(ip_address));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void AddressIP::SetAddress(const char *in_address, bool is_raw_ip_flag)
{
	if (!is_raw_ip_flag) {
		struct in_addr tmp_in_addr;
		char           tmp_host_name[MLB::Utility::MaxHostNameLength + 1];
		char           npsl_error_text[NPSL_MAX_ERROR_TEXT];
		if (NPSL_ResolveHostBasic(in_address, tmp_host_name,
			&tmp_in_addr, NULL, NULL, npsl_error_text) != NPSL_SUCCESS)
			throw SockLibXException(npsl_error_text);
		host_name_ = tmp_host_name;
#ifdef MSC_VER
		::memcpy(&ip_address, &tmp_in_addr.S_un.S_un_b, sizeof(ip_address));
#else
		::memcpy(&ip_address, &tmp_in_addr, sizeof(ip_address));
#endif // #ifdef MSC_VER
	}
	else
		SetAddress(INetToAddr(in_address));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void AddressIP::SetAddress(const std::string &in_address, bool is_raw_ip_flag)
{
	SetAddress(in_address.c_str(), is_raw_ip_flag);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void AddressIP::SetHostName(const std::string &in_host_name)
{
	host_name_ = in_host_name;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string AddressIP::GetHostIPAddress() const
{
	return(MLB::Utility::AnyToString(ip_address[0]) + "." +
		MLB::Utility::AnyToString(ip_address[1]) + "." +
		MLB::Utility::AnyToString(ip_address[2]) + "." +
		MLB::Utility::AnyToString(ip_address[3]));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string AddressIP::GetHostIPAddressZeroFilled() const
{
	return(MLB::Utility::ZeroFill(ip_address[0], 3) + "." +
		MLB::Utility::ZeroFill(ip_address[1], 3) + "." +
		MLB::Utility::ZeroFill(ip_address[2], 3) + "." +
		MLB::Utility::ZeroFill(ip_address[3], 3));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string AddressIP::GetHostId() const
{
	return((!host_name_.empty()) ? host_name_ : GetHostIPAddress());;
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string AddressIP::GetHostName() const
{
	return(host_name_);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
struct in_addr AddressIP::GetInAddr() const
{
	struct in_addr tmp_addr;

	::memset(&tmp_addr, '\0', sizeof(tmp_addr));
#ifdef _MSC_VER
	::memcpy(&tmp_addr.S_un.S_un_b, ip_address, sizeof(tmp_addr.S_un.S_un_b));
#else
	::memcpy(&tmp_addr, ip_address, sizeof(tmp_addr));
#endif // #ifdef _MSC_VER

	return(tmp_addr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSockAddr_In AddressIP::GetSockaddrIn() const
{
	NativeSockAddr_In tmp_addr;

	memset(&tmp_addr, '\0', sizeof(tmp_addr));

	tmp_addr.sin_addr = GetInAddr();

	return(tmp_addr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSockAddr_In AddressIP::GetSockaddrIn(AddressFamily address_family) const
{
	NativeSockAddr_In tmp_addr;

	memset(&tmp_addr, '\0', sizeof(tmp_addr));

	tmp_addr.sin_addr = GetInAddr();
	tmp_addr.sin_family = static_cast<short>(address_family);

	return(tmp_addr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSockAddr AddressIP::GetSockaddr() const
{
	NativeSockAddr_In tmp_sockaddr_in = GetSockaddrIn();
	NativeSockAddr    tmp_sockaddr;

	memset(&tmp_sockaddr, '\0', sizeof(tmp_sockaddr));
	memcpy(&tmp_sockaddr, &tmp_sockaddr_in,
		std::min(sizeof(tmp_sockaddr), sizeof(tmp_sockaddr_in)));

	return(tmp_sockaddr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
NativeSockAddr AddressIP::GetSockaddr(AddressFamily address_family) const
{
	NativeSockAddr tmp_sockaddr = GetSockaddr();

	tmp_sockaddr.sa_family = static_cast<unsigned short>(address_family);

	return(tmp_sockaddr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string AddressIP::ToString() const
{
	return(GetHostId());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool AddressIP::operator <  (const AddressIP &other) const
{
	return(Compare(this, &other) <  0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool AddressIP::operator >  (const AddressIP &other) const
{
	return(Compare(this, &other) >  0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool AddressIP::operator <= (const AddressIP &other) const
{
	return(Compare(this, &other) <= 0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool AddressIP::operator >= (const AddressIP &other) const
{
	return(Compare(this, &other) >= 0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool AddressIP::operator == (const AddressIP &other) const
{
	return(Compare(this, &other) == 0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool AddressIP::operator != (const AddressIP &other) const
{
	return(Compare(this, &other) != 0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int AddressIP::Compare(const AddressIP &other) const
{
	return(Compare(this, &other));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int AddressIP::Compare(const AddressIP *ptr_1, const AddressIP *ptr_2)
{
	return(memcmp(ptr_1->ip_address, ptr_2->ip_address,
		sizeof(ptr_1->ip_address)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str,
	const AddressIP &datum)
{
	o_str <<
		datum.ToString();

	return(o_str);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void swap(AddressIP &arg_1, AddressIP &arg_2)
{
	arg_1.swap(arg_2);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace SockLibX

} // namespace MLB

