//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of Boost serialization for the class
								VersionNumber.

	Revision History	:	2006-12-21 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2006 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////
 
//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Required include files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility/VersionNumber.hpp>
#include <Utility/Boost/Serialization/BoostSerialization.ipp>

//	////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Use macros to get declarations and forced instantiations done...
// ////////////////////////////////////////////////////////////////////////////

	//	Declare the template functions...
MLB_BOOSTX_SERIAL_TEMPLATE_SPLIT(MLB::Utility::VersionNumber)

	//	The binary archive save() and load() functions both have explicit
	//	instantiations, so we force instantiate only the serialize functions...
MLB_BOOSTX_SERIAL_DECL_Serialize_binary(MLB::Utility::VersionNumber)

	//	Force instantiation of text functions...
MLB_BOOSTX_SERIAL_DECL_Split_text(MLB::Utility::VersionNumber)

	//	Force instantiation of the xml functions...
MLB_BOOSTX_SERIAL_DECL_Split_xml(MLB::Utility::VersionNumber)

	// Force instantiation of the Serialize{Load|Save}{Binary|Text|Xml} funcs.
MLB_BOOSTX_SerializeLoadSave(MLB::Utility::VersionNumber)

// ////////////////////////////////////////////////////////////////////////////

namespace boost {

namespace serialization {

// ////////////////////////////////////////////////////////////////////////////
//	Specialization for binary serialization (save)...
template <>
	void save(boost::archive::binary_oarchive &s_archive,
	const MLB::Utility::VersionNumber &datum, const unsigned int)
{
	s_archive
		& datum.version_[0]
		& datum.version_[1]
		& datum.version_[2]
		& datum.version_[3];
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
//	Specialization for binary serialization (load)...
template <>
	void load(boost::archive::binary_iarchive &s_archive,
	MLB::Utility::VersionNumber &datum, const unsigned int)
{
	s_archive
		& datum.version_[0]
		& datum.version_[1]
		& datum.version_[2]
		& datum.version_[3];
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename SArchive>
	void save(SArchive &s_archive, const MLB::Utility::VersionNumber &datum,
		const unsigned int)
{
	std::string tmp_datum = datum.ToString();

	s_archive
		& boost::serialization::make_nvp("versionNumber", tmp_datum);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename SArchive>
	void load(SArchive &s_archive, MLB::Utility::VersionNumber &datum,
		const unsigned int)
{
	std::string tmp_datum;

	s_archive
		& boost::serialization::make_nvp("versionNumber", tmp_datum);

	datum = MLB::Utility::VersionNumber::FromString(tmp_datum);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
template <typename SArchive>
	void serialize(SArchive &s_archive, MLB::Utility::VersionNumber &datum,
		const unsigned int o_version)
{
	boost::serialization::split_free(s_archive, datum, o_version);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace serialization

} // namespace boost

#ifdef TEST_MAIN

using namespace MLB::Utility;

//	////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	std::cout <<
		"Test routine for Boost Serialization of class 'VersionNumber'" <<
		std::endl;
	std::cout <<
		"---- ------- --- ----- ------------- -- ----- ---------------" <<
		std::endl;

	try {
		VersionNumber test_datum;
		TEST_Serialization(test_datum, "VersionNumber");
	}
	catch (const std::exception &except) {
		std::cout << std::endl << std::endl;
		std::cout << "ERROR: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
//	////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

