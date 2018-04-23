//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support formatting of binary data in
								hexadecimal.

	Revision History	:	2008-11-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2008 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////
 
//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Required include files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility/ToHexString.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

namespace {
// ////////////////////////////////////////////////////////////////////////////
const char HexChars[] = "0123456789abcdef";
// ////////////////////////////////////////////////////////////////////////////
} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
char *ToHexString(std::size_t data_length, const char *data_ptr,
   char *out_ptr, int fill_char)
{
	if (data_length) {
		char *original_out_ptr = out_ptr;
		while (data_length--) {
			*out_ptr++ =
				HexChars[(static_cast<unsigned char>(*data_ptr) & 0xf0) >> 4];
			*out_ptr++ = HexChars[static_cast<unsigned char>(*data_ptr) & 0x0f];
			if (data_length)
				*out_ptr++ = static_cast<char>(fill_char);
			++data_ptr;
		}
		*out_ptr = '\0';
		return(original_out_ptr);
	}
	else
		*out_ptr = '\0';

	return(out_ptr);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &ToHexString(std::size_t data_length, const char *data_ptr,
   std::string &out_string, int fill_char)
{
	//	... 'cause I can...
	if (!data_length)
		out_string.clear();
	else {
		out_string.resize((data_length * 2) + (data_length - 1));
		ToHexString(data_length, data_ptr,
			const_cast<char *>(out_string.c_str()), fill_char);
	}
	
	return(out_string);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string ToHexString(std::size_t data_length, const char *data_ptr,
   int fill_char)
{
	std::string out_string;

	return(ToHexString(data_length, data_ptr, out_string, fill_char));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *ToHexString(std::size_t data_length, const void *data_ptr,
   char *out_ptr, int fill_char)
{
	return(ToHexString(data_length, static_cast<const char *>(data_ptr),
		out_ptr, fill_char));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &ToHexString(std::size_t data_length, const void *data_ptr,
   std::string &out_string, int fill_char)
{
	return(ToHexString(data_length, static_cast<const char *>(data_ptr),
		out_string, fill_char));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string ToHexString(std::size_t data_length, const void *data_ptr,
   int fill_char)
{
	return(ToHexString(data_length, static_cast<const char *>(data_ptr),
		fill_char));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *ToHexString(const std::string &in_string, char *out_ptr, int fill_char)
{
	return(ToHexString(in_string.size(), in_string.data(), out_ptr, fill_char));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &ToHexString(const std::string &in_string, std::string &out_string,
	int fill_char)
{
	return(ToHexString(in_string.size(), in_string.data(), out_string,
		fill_char));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string ToHexString(const std::string &in_string, int fill_char)
{
	return(ToHexString(in_string.size(), in_string.data(), fill_char));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

