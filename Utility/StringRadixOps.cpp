// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	StringRadixOps.cpp

	File Description	:	Implementation of the new, yet-to-be-fully-implemented,
								string <---> integer radix functions.

	Revision History	:	1993-10-10 --- Portions of original logic from
													MlbDev/Utility/IntToString.cpp.
									Michael L. Brock
								2016-08-07 --- Base-62 specific logic first-cut.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/StringRadixOps.hpp>

#include <cstring>
#include <stdexcept>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

namespace {

// ////////////////////////////////////////////////////////////////////////////
template <typename DstType, DstType SrcRadix>
	DstType StringToUIntRadix_ORIG(const char *begin_ptr, const char *end_ptr,
		const char **last_ptr = NULL)
{
	const char *curr_ptr = begin_ptr;

	while ((curr_ptr < end_ptr) && ::isspace(*curr_ptr))
		++curr_ptr;

	while ((curr_ptr < end_ptr) && (*curr_ptr == '0'))
		++curr_ptr;

	DstType old_dst_value = 0;
	DstType dst_value     = 0;

	while (curr_ptr < end_ptr) {
		DstType tmp_value;
		if (::isdigit(*curr_ptr))
			tmp_value = static_cast<DstType>(*curr_ptr - '0');
		else if (::isupper(*curr_ptr))
			tmp_value = static_cast<DstType>((*curr_ptr - 'A') + 10);
		else if (::islower(*curr_ptr))
			tmp_value = static_cast<DstType>((*curr_ptr - 'a') + 10 + 26);
		else
			break;
		if (tmp_value >= SrcRadix)
			break;
		old_dst_value  = dst_value;
		dst_value     *= static_cast<DstType>(SrcRadix);
		dst_value     += tmp_value;
		if (dst_value < old_dst_value) {
			/*
				We over-flowed.

				If last_ptr is not NULL, we'll set it to point to the offending
				character. Caller detects the overflow because that character is
				a valid character for the radix.

				Otherwise, we throw.
			*/
			if (last_ptr) {
				dst_value = old_dst_value;
				break;
			}
			std::ostringstream o_str;
			o_str << "Conversion of the string '" <<
				std::string(begin_ptr, end_ptr) << "' failed at index " <<
				(curr_ptr - begin_ptr) << " ('" << *curr_ptr << " = ASCII " <<
				static_cast<unsigned int>(static_cast<unsigned char>(*curr_ptr)) <<
				").";
			throw std::overflow_error(o_str.str());
		}
		++curr_ptr;
	}

	if (last_ptr)
		*last_ptr = curr_ptr;

	return(dst_value);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DstType, DstType SrcRadix>
	DstType StringToUIntRadix_ORIG(std::size_t src_len, const char *src_ptr,
		const char **last_ptr = NULL)
{
	return(StringToUIntRadix_ORIG<DstType, SrcRadix>(src_ptr,
		src_ptr + src_len, last_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DstType, DstType SrcRadix>
	DstType StringToUIntRadix_ORIG(const char *src_ptr,
		const char **last_ptr = NULL)
{
	return(StringToUIntRadix_ORIG<DstType, SrcRadix>(::strlen(src_ptr), src_ptr,
		last_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename DstType, DstType SrcRadix>
	DstType StringToUIntRadix_ORIG(const std::string &src,
		std::size_t *last_offset = NULL)
{
	DstType     return_value;
	const char *last_ptr;

	return_value = StringToUIntRadix_ORIG<DstType, SrcRadix>(src.size(),
		src.c_str(), &last_ptr);

	if (last_offset)
		*last_offset = static_cast<std::size_t>(last_ptr - src.c_str());

	return(return_value);
}
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous  namespace

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix62(const char *begin_ptr, const char *end_ptr,
	const char **last_ptr)
{
	return(StringToUIntRadix_ORIG<Native_UInt64, 62>(begin_ptr, end_ptr, last_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix62(std::size_t src_len, const char *src_ptr,
	const char **last_ptr)
{
	return(StringToUIntRadix_ORIG<Native_UInt64, 62>(src_len, src_ptr, last_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix62(const char *src_ptr,
	const char **last_ptr)
{
	return(StringToUIntRadix_ORIG<Native_UInt64, 62>(src_ptr, last_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix62(const std::string &src,
	std::size_t *last_offset)
{
	return(StringToUIntRadix_ORIG<Native_UInt64, 62>(src, last_offset));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

// ////////////////////////////////////////////////////////////////////////////
//	****************************************************************************
//	****************************************************************************
//	****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

namespace {

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Machine-generated by CreateRadixCharMaps.pl
// ////////////////////////////////////////////////////////////////////////////
const std::size_t   MyCharMap_Safe64__CharLow   = 45;
const std::size_t   MyCharMap_Safe64__CharHigh  = 122;
const unsigned char MyCharMap_Safe64__MapData[] = {
     62 /* - */,   0 /* . */,   0 /* / */,   0 /* 0 */,
      1 /* 1 */,   2 /* 2 */,   3 /* 3 */,   4 /* 4 */,
      5 /* 5 */,   6 /* 6 */,   7 /* 7 */,   8 /* 8 */,
      9 /* 9 */,   0 /* : */,   0 /* ; */,   0 /* < */,
      0 /* = */,   0 /* > */,   0 /* ? */,   0 /* @ */,
     10 /* A */,  11 /* B */,  12 /* C */,  13 /* D */,
     14 /* E */,  15 /* F */,  16 /* G */,  17 /* H */,
     18 /* I */,  19 /* J */,  20 /* K */,  21 /* L */,
     22 /* M */,  23 /* N */,  24 /* O */,  25 /* P */,
     26 /* Q */,  27 /* R */,  28 /* S */,  29 /* T */,
     30 /* U */,  31 /* V */,  32 /* W */,  33 /* X */,
     34 /* Y */,  35 /* Z */,   0 /* [ */,   0 /* \ */,
      0 /* ] */,   0 /* ^ */,  63 /* _ */,   0 /* ` */,
     36 /* a */,  37 /* b */,  38 /* c */,  39 /* d */,
     40 /* e */,  41 /* f */,  42 /* g */,  43 /* h */,
     44 /* i */,  45 /* j */,  46 /* k */,  47 /* l */,
     48 /* m */,  49 /* n */,  50 /* o */,  51 /* p */,
     52 /* q */,  53 /* r */,  54 /* s */,  55 /* t */,
     56 /* u */,  57 /* v */,  58 /* w */,  59 /* x */,
     60 /* y */,  61 /* z */
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Machine-generated by CreateRadixCharMaps.pl
// ////////////////////////////////////////////////////////////////////////////
const std::size_t   MyCharMap_Pem64__CharLow   = 43;
const std::size_t   MyCharMap_Pem64__CharHigh  = 122;
const unsigned char MyCharMap_Pem64__MapData[] = {
     62 /* + */,   0 /* , */,   0 /* - */,   0 /* . */,
     63 /* / */,   0 /* 0 */,   1 /* 1 */,   2 /* 2 */,
      3 /* 3 */,   4 /* 4 */,   5 /* 5 */,   6 /* 6 */,
      7 /* 7 */,   8 /* 8 */,   9 /* 9 */,   0 /* : */,
      0 /* ; */,   0 /* < */,   0 /* = */,   0 /* > */,
      0 /* ? */,   0 /* @ */,  10 /* A */,  11 /* B */,
     12 /* C */,  13 /* D */,  14 /* E */,  15 /* F */,
     16 /* G */,  17 /* H */,  18 /* I */,  19 /* J */,
     20 /* K */,  21 /* L */,  22 /* M */,  23 /* N */,
     24 /* O */,  25 /* P */,  26 /* Q */,  27 /* R */,
     28 /* S */,  29 /* T */,  30 /* U */,  31 /* V */,
     32 /* W */,  33 /* X */,  34 /* Y */,  35 /* Z */,
      0 /* [ */,   0 /* \ */,   0 /* ] */,   0 /* ^ */,
      0 /* _ */,   0 /* ` */,  36 /* a */,  37 /* b */,
     38 /* c */,  39 /* d */,  40 /* e */,  41 /* f */,
     42 /* g */,  43 /* h */,  44 /* i */,  45 /* j */,
     46 /* k */,  47 /* l */,  48 /* m */,  49 /* n */,
     50 /* o */,  51 /* p */,  52 /* q */,  53 /* r */,
     54 /* s */,  55 /* t */,  56 /* u */,  57 /* v */,
     58 /* w */,  59 /* x */,  60 /* y */,  61 /* z */
};
// ////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
void GetCharMapSafe64(std::size_t &low_index, std::size_t &high_index,
	const unsigned char *&char_map)
{
	low_index  = MyCharMap_Safe64__CharLow;
	high_index = MyCharMap_Safe64__CharHigh;
	char_map   = MyCharMap_Safe64__MapData;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void GetCharMapPem64(std::size_t &low_index, std::size_t &high_index,
	const unsigned char *&char_map)
{
	low_index  = MyCharMap_Pem64__CharLow;
	high_index = MyCharMap_Pem64__CharHigh;
	char_map   = MyCharMap_Pem64__MapData;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix(std::size_t low_index, std::size_t high_index,
	const unsigned char *char_map, std::size_t radix, const char *begin_ptr,
	const char *end_ptr, const char **last_ptr = NULL)
{
	if (radix < 2)
		throw std::invalid_argument("Radix value is less than 2.");
	else if ((radix < 65) && (!low_index) && (!high_index) && (!char_map))
		GetCharMapSafe64(low_index, high_index, char_map);
	else if (low_index >= high_index)
		throw std::invalid_argument("The low character index is not less than "
			"the high character index.");
	else if (!char_map)
		throw std::invalid_argument("The character map parameter is NULL.");

	std::size_t map_size = (high_index - low_index) + 1;

	if (map_size > (std::numeric_limits<unsigned char>::max() + 1))
		throw std::invalid_argument("The size of the character map exceeds the "
			"number of distinct unsigned char values.");
	else if (radix > map_size)
		throw std::invalid_argument("The specified radix is greater than the "
			"size of the character map.");

	const char *curr_ptr = begin_ptr;

	while ((curr_ptr < end_ptr) && ::isspace(*curr_ptr))
		++curr_ptr;

	Native_UInt64 old_dst_value = 0;
	Native_UInt64 dst_value     = 0;

	while (curr_ptr < end_ptr) {
		if ((static_cast<unsigned char>(*curr_ptr) < low_index) ||
			 (static_cast<unsigned char>(*curr_ptr) > high_index))
			break;
		Native_UInt64 tmp_value;
		if (*curr_ptr == '0')
			tmp_value = 0;
		else {
			tmp_value = char_map[*curr_ptr - low_index];
			if ((!tmp_value) || (tmp_value >= radix))
				break;
		}
		old_dst_value  = dst_value;
		dst_value     *= static_cast<Native_UInt64>(radix);
		dst_value     += tmp_value;
		if (dst_value < old_dst_value) {
			/*
				We over-flowed.

				If last_ptr is not NULL, we'll set it to point to the offending
				character. Caller detects the overflow because that character is
				a valid character for the radix.

				Otherwise, we throw.
			*/
			if (last_ptr) {
				dst_value = old_dst_value;
				break;
			}
			std::ostringstream o_str;
			o_str << "Conversion of the string '" <<
				std::string(begin_ptr, end_ptr) << "' overflowed at index " <<
				(curr_ptr - begin_ptr) << " ('" << *curr_ptr << " = ASCII " <<
				static_cast<unsigned int>(static_cast<unsigned char>(*curr_ptr)) <<
				").";
			throw std::overflow_error(o_str.str());
		}
		++curr_ptr;
	}

	if (last_ptr)
		*last_ptr = curr_ptr;

	return(dst_value);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix(std::size_t low_index, std::size_t high_index,
	const unsigned char *char_map, std::size_t radix, std::size_t src_len,
	const char *src_ptr, const char **last_ptr = NULL)
{
	return(StringToUIntRadix(low_index, high_index, char_map, radix,
		src_ptr, src_ptr + src_len, last_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix(std::size_t low_index, std::size_t high_index,
	const unsigned char *char_map, std::size_t radix, const char *src_ptr,
	const char **last_ptr = NULL)
{
	return(StringToUIntRadix(low_index, high_index, char_map, radix,
		::strlen(src_ptr), src_ptr, last_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix(std::size_t low_index, std::size_t high_index,
	const unsigned char *char_map, std::size_t radix, const std::string &src,
	std::size_t *last_offset = NULL)
{
	const char    *last_ptr;
	Native_UInt64  return_value = StringToUIntRadix(low_index, high_index,
		char_map, radix, src.size(), src.c_str(), &last_ptr);

	if (last_offset)
		*last_offset = static_cast<std::size_t>(last_ptr - src.c_str());

	return(return_value);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix(std::size_t radix, const char *begin_ptr,
	const char *end_ptr, const char **last_ptr = NULL)
{
	return(StringToUIntRadix(0, 0, NULL, radix, begin_ptr, end_ptr, last_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix(std::size_t radix, std::size_t src_len,
	const char *src_ptr, const char **last_ptr = NULL)
{
	return(StringToUIntRadix(0, 0, NULL, radix, src_len, src_ptr, last_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix(std::size_t radix, const char *src_ptr,
	const char **last_ptr = NULL)
{
	return(StringToUIntRadix(0, 0, NULL, radix, src_ptr, last_ptr));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
Native_UInt64 StringToUIntRadix(std::size_t radix, const std::string &src,
	std::size_t *last_offset = NULL)
{
	return(StringToUIntRadix(0, 0, NULL, radix, src, last_offset));
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

// ////////////////////////////////////////////////////////////////////////////
//	****************************************************************************
//	****************************************************************************
//	****************************************************************************
// ////////////////////////////////////////////////////////////////////////////

#ifdef TEST_MAIN

#include <cstdlib>

using namespace MLB::Utility;

// ////////////////////////////////////////////////////////////////////////////
template <std::size_t SrcRadix>
struct TypeToSizeT {
	static const std::size_t value = SrcRadix;
};
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <std::size_t SrcRadix>
	void TEST_RunTestHelper_ORIG(const char *src_ptr)
{
	const char *last_ptr;

	std::cout << std::right << std::setw(3) <<
		TypeToSizeT<SrcRadix>::value << " " << std::left << std::setw(64) <<
		src_ptr << "=";
	Native_UInt64 result =
		StringToUIntRadix_ORIG<Native_UInt64, SrcRadix>(src_ptr, &last_ptr);
	std::cout << std::right << std::setw(20) << result << '[' << last_ptr <<
		']' << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_RunTest_ORIG()
{
	TEST_RunTestHelper_ORIG<10>("123AG");
	TEST_RunTestHelper_ORIG<16>("123AG");
	TEST_RunTestHelper_ORIG<62>("47");
	TEST_RunTestHelper_ORIG<62>("H31");
	TEST_RunTestHelper_ORIG<62>("LygHa16AHYF");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_RunTestHelper(std::size_t radix, const char *src_ptr)
{
	const char *last_ptr;

	std::cout << std::right << std::setw(3) << radix << " " << std::left <<
		std::setw(64) << src_ptr << "=";
	Native_UInt64 result = StringToUIntRadix(radix, src_ptr, &last_ptr);
	std::cout << std::right << std::setw(20) << result << '[' << last_ptr <<
		']' << std::endl;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void TEST_RunTest()
{
	TEST_RunTestHelper(10, "123AG");
	TEST_RunTestHelper(16, "123AG");
	TEST_RunTestHelper(62, "47");
	TEST_RunTestHelper(62, "H31");
	TEST_RunTestHelper(62, "LygHa16AHYF");
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		TEST_RunTest_ORIG();
		TEST_RunTest();
	}
	catch (const std::exception &except) {
		std::cout << std::endl;
		std::cout << "Regression test error: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

