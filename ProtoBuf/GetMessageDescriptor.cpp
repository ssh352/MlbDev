//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Google Protocol Buffers Support Library
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	GetMessageDescriptor.cpp

	File Description	:	Implementation of logic to determine, given a string,
								the Google ProtoBuf message descriptor.

	Revision History	:	2016-06-05 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2016 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Include necessary header files...
//	////////////////////////////////////////////////////////////////////////////

#include <ProtoBuf/GetMessageDescriptor.hpp>

#include <Utility/Utility_Exception.hpp>

#include <sstream>

#include <boost/algorithm/string.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace ProtoBuf {

//	////////////////////////////////////////////////////////////////////////////
const ::google::protobuf::Descriptor *GetMessageDescriptor(
	const std::string &msg_name,
	const ::google::protobuf::DescriptorPool *descriptor_pool_ptr,
	bool throw_if_not_found)
{
	if (!descriptor_pool_ptr)
		MLB::Utility::ThrowInvalidArgument("The pointer to the '::google::"
			"protobuf::DescriptorPool' to be used is NULL.");

	const ::google::protobuf::Descriptor *descriptor_ptr =
		descriptor_pool_ptr->FindMessageTypeByName(msg_name);

	if (!descriptor_ptr) {
		std::string::size_type position;
		if ((position = msg_name.find_first_of(':')) !=
			std::string::npos) {
			std::string tmp_name((msg_name.substr(0, 2) == "::") ?
				msg_name.substr(2) : msg_name);
			boost::replace_all(tmp_name, "::", ".");
			descriptor_ptr = descriptor_pool_ptr->FindMessageTypeByName(tmp_name);
		}
	}

	if ((!descriptor_ptr) && throw_if_not_found) {
		std::ostringstream o_str;
		o_str << "Unable to locate message name '" << msg_name <<
			"' within the pool of " << ((descriptor_pool_ptr ==
			::google::protobuf::DescriptorPool::generated_pool()) ? "generated " :
			"") << "descriptors.";
		MLB::Utility::ThrowInvalidArgument(o_str.str());
	}

	return(descriptor_ptr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
const ::google::protobuf::Descriptor *GetMessageDescriptor(
	const std::string &msg_name, bool throw_if_not_found)
{
	return(GetMessageDescriptor(msg_name,
		::google::protobuf::DescriptorPool::generated_pool(),
		throw_if_not_found));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace ProtoBuf

} // namespace MLB

