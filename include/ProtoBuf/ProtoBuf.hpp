//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Google Protocol Buffers Support Library
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	ProtoBuf.hpp

	File Description	:	Basic MLB ProtoBuf include file.

	Revision History	:	2016-06-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2016 - 2017.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////

#ifndef HH___MLB__ProtoBuf__ProtoBuf_hpp___HH

#define HH___MLB__ProtoBuf__ProtoBuf_hpp___HH	1

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Include necessary header files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility.hpp>

#include <mbtypes.h>

#include <memory>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4100 4127 4365 4512 4625 4626)
#endif // #ifdef _MSC_VER

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/Message.h>

#ifdef _MSC_VER
# pragma warning(pop)
#endif // #ifdef _MSC_VER

#include <boost/shared_ptr.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace ProtoBuf {

//	////////////////////////////////////////////////////////////////////////////
typedef boost::shared_ptr< ::google::protobuf::Message > GpbMessageSPtr;
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
#if (__cplusplus < 201103L)
typedef std::auto_ptr< ::google::protobuf::Message >   GpbMessageUPtr;
#else
typedef std::unique_ptr< ::google::protobuf::Message > GpbMessageUPtr;
#endif // #if (__cplusplus < 201103L)
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
typedef std::vector<GpbMessageSPtr>          GpbMessageSPtrVector;
typedef GpbMessageSPtrVector::iterator       GpbMessageSPtrVectorIter;
typedef GpbMessageSPtrVector::const_iterator GpbMessageSPtrVectorIterC;
//	////////////////////////////////////////////////////////////////////////////

} // namespace ProtoBuf

} // namespace MLB

#endif // #ifndef HH___MLB__ProtoBuf__GpbElementInfo_hpp___HH

