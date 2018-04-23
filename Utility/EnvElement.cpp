//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the EnvElement class.

	Revision History	:	1993-10-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////
 
//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Required include files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility/GetEnvironment.hpp>
#include <Utility/C_StringSupport.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
EnvElement::EnvElement()
	:env_name_()
	,env_value_()
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
EnvElement::EnvElement(const std::string &env_string)
	:env_name_(env_string, 0, GetEnvStringSeparatorIndex(env_string))
	,env_value_(env_string, GetEnvStringSeparatorIndex(env_string) + 1,
		std::string::npos)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
EnvElement::EnvElement(const std::string &env_name,
	const std::string &env_value)
	:env_name_(env_name)
	,env_value_(env_value)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool EnvElement::operator < (const EnvElement &other) const
{
	return(Utility_stricmp(env_name_.c_str(), other.env_name_.c_str()) < 0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string &EnvElement::ToString(std::string &out_string) const
{
	out_string = env_name_ + "=" + env_value_;

	return(out_string);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string EnvElement::ToString() const
{
	std::string out_string;

	return(ToString(out_string));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str, const EnvElement &datum)
{
	o_str << datum.ToString();

	return(o_str);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

