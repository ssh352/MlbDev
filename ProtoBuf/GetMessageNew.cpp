//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Google Protocol Buffers Support Library
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	GetMessageNew.cpp

	File Description	:	Implementation of logic to create a copy of the
								prototype instance of a Google ProtoBuf message by
								name.

	Revision History	:	2016-06-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2016 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Include necessary header files...
//	////////////////////////////////////////////////////////////////////////////

#include <ProtoBuf/GetMessageNew.hpp>
#include <ProtoBuf/GetMessagePrototype.hpp>

#include <Utility/C_StringSupport.hpp>

#include <sstream>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace ProtoBuf {

//	////////////////////////////////////////////////////////////////////////////
GpbMessageSPtr GetMessageNew(const std::string &msg_name,
	::google::protobuf::MessageFactory *msg_factory_ptr)
{
	GpbMessageSPtr msg_sptr;

	try {
		msg_sptr.reset(GetMessagePrototype(msg_name, msg_factory_ptr)->New());
	}
	catch (const std::exception &except) {
		std::ostringstream o_str;
		o_str << "Unable to create a new Google ProtoBuf message of type '" <<
			msg_name << "' from its prototypical form: " << except.what();
		MLB::Utility::Rethrow(except, o_str.str());
	}

	return(msg_sptr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
GpbMessageSPtr GetMessageNew(const std::string &msg_name)
{
	return(GetMessageNew(msg_name, NULL));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace ProtoBuf

} // namespace MLB
