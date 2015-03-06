// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	ODBC Wrapper Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the GetInfoTypeDatum class.

	Revision History	:	2001-10-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <OdbcWrapper/OdbcWrapper.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace OdbcWrapper {

// ////////////////////////////////////////////////////////////////////////////
GetInfoTypeDatum::GetInfoTypeDatum()
	:GetInfoTypeDatumValue()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
GetInfoTypeDatum::GetInfoTypeDatum(
	const GetInfoTypeDatumRaw &descriptor_raw,
	const GetInfoTypeDatumValue &descriptor_val)
	:GetInfoTypeDatumValue(descriptor_val)
	,info_type_name_(descriptor_raw.info_type_name_)
	,data_type_name_(descriptor_raw.data_type_name_)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
GetInfoTypeDatum::GetInfoTypeDatum(SQLUSMALLINT info_type)
	:GetInfoTypeDatumValue()
{
	info_type_ = info_type;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
GetInfoTypeDatum::~GetInfoTypeDatum()
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool GetInfoTypeDatum::operator < (
	const GetInfoTypeDatum &other) const
{
	return(info_type_ < other.info_type_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
GetInfoTypeDatum &GetInfoTypeDatum::swap(GetInfoTypeDatum &other)
{
	GetInfoTypeDatumValue::swap(other);

	info_type_name_.swap(other.info_type_name_);
	data_type_name_.swap(other.data_type_name_);

	return(*this);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &GetInfoTypeDatum::ToString(std::string &out_string) const
{
	std::string(info_type_name_ + "=" +
		GetInfoTypeDatumValue::ToString()).swap(out_string);

	return(out_string);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string GetInfoTypeDatum::ToString() const
{
	std::string out_string;

	return(ToString(out_string));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &GetInfoTypeDatum::ToStringPadded(
	std::string &out_string, std::streamsize padding_width) const
{
	std::ostringstream o_str;
	std::string        tmp_string;

	o_str
		<< std::left << std::setw(padding_width) << info_type_name_
		<<	std::right << ": "
		<< GetInfoTypeDatumValue::ToStringPadded(tmp_string);

	return(out_string.assign(o_str.str()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string GetInfoTypeDatum::ToStringPadded(
	std::streamsize padding_width) const
{
	std::string out_string;

	return(ToStringPadded(out_string, padding_width));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str,
	const GetInfoTypeDatum &datum)
{
	std::string out_string;

	o_str
		<< datum.ToString(out_string);

	return(o_str);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace OdbcWrapper

} // namespace MLB

