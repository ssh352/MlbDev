//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Google Protocol Buffers Support Library
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	GpbElementInfo.hpp

	File Description	:	Definition of the GpbElementInfo class.

	Revision History	:	2015-06-20 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2015 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////

#ifndef HH___MLB__ProtoBuf__GpbElementInfo_hpp___HH

#define HH___MLB__ProtoBuf__GpbElementInfo_hpp___HH	1

//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Include necessary header files...
//	////////////////////////////////////////////////////////////////////////////

#include <ProtoBuf/GpbElementInfoMaxLengths.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace ProtoBuf {

//	////////////////////////////////////////////////////////////////////////////
enum GpbDatumType {
	GpbDatumType_SInt32      = ::google::protobuf::FieldDescriptor::CPPTYPE_INT32,
	GpbDatumType_SInt64      = ::google::protobuf::FieldDescriptor::CPPTYPE_INT64,
	GpbDatumType_UInt32      = ::google::protobuf::FieldDescriptor::CPPTYPE_UINT32,
	GpbDatumType_UInt64      = ::google::protobuf::FieldDescriptor::CPPTYPE_UINT64,
	GpbDatumType_Double      = ::google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE,
	GpbDatumType_Float       = ::google::protobuf::FieldDescriptor::CPPTYPE_FLOAT,
	GpbDatumType_Bool        = ::google::protobuf::FieldDescriptor::CPPTYPE_BOOL,
	GpbDatumType_Enum        = ::google::protobuf::FieldDescriptor::CPPTYPE_ENUM,
	GpbDatumType_String      = ::google::protobuf::FieldDescriptor::CPPTYPE_STRING,
	GpbDatumType_Message     = ::google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE,
	GpbDatumType_Repeated    = ::google::protobuf::FieldDescriptor::MAX_CPPTYPE + 1,
	GpbDatumType_RepeatedPtr,
	GpbDatumType_Minimum     = GpbDatumType_SInt32,
	GpbDatumType_Maximum     = GpbDatumType_RepeatedPtr,
	GpbDatumType_Count       = (GpbDatumType_Maximum - GpbDatumType_Minimum) + 1
};
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
struct GpbElementInfoDescriptors {
	const ::google::protobuf::Descriptor      *descriptor_;
	const ::google::protobuf::FieldDescriptor *field_descriptor_;
	const ::google::protobuf::FileDescriptor  *file_descriptor_;
	const ::google::protobuf::EnumDescriptor  *enum_descriptor_;
};
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
class GpbElementInfo {
	typedef ::google::protobuf::Descriptor      GPB_Descriptor;
	typedef ::google::protobuf::FieldDescriptor GPB_FieldDescriptor;
	typedef ::google::protobuf::FileDescriptor  GPB_FileDescriptor;
	typedef ::google::protobuf::EnumDescriptor  GPB_EnumDescriptor;
	typedef ::google::protobuf::Reflection      GPB_Reflection;
public:
	typedef std::vector<GpbElementInfo>               GpbElementInfoVector_I;
	typedef std::pair<GpbElementInfo, GpbElementInfo> GpbElementInfoPair_I;
	typedef std::vector<GpbElementInfoPair_I>         GpbElementInfoPairVector_I;

	explicit GpbElementInfo();
	explicit GpbElementInfo(const GPB_Descriptor &descriptor);
	explicit GpbElementInfo(const GPB_Descriptor *descriptor);
	explicit GpbElementInfo(const std::string &message_name);

	inline std::size_t GetDepth() const
	{
		return(depth_);
	}

	inline int         GetMemberIndex() const
	{
		return(member_index_);
	}

	inline std::size_t GetMaxDepth() const
	{
		return(max_depth_);
	}

	inline ::google::protobuf::FieldDescriptor::CppType GetCppType() const
	{
		return(cpp_type_);
	}

	inline GpbDatumType GetDatumType() const
	{
		return(datum_type_);
	}

	const char *GetTypeNameFull() const;

	const char *GetTypeName() const;

	const char *GetMemberName() const;

	const char *GetName() const;

	const char *GetNameFull() const;

	const char *GetTypeFileName() const;

	const char *GetMemberFileName() const;

	const char *GetFileName() const;

	const char *GetLabelName() const;

	::google::protobuf::FieldDescriptor::Label GetLabel() const;

	bool GetSourceLocationType(
		::google::protobuf::SourceLocation &dst) const;

	::google::protobuf::SourceLocation GetSourceLocationType() const;

	bool GetSourceLocationMember(
		::google::protobuf::SourceLocation &dst) const;

	::google::protobuf::SourceLocation GetSourceLocationMember() const;

	const GPB_FieldDescriptor *GetFieldDescriptor() const
	{
		return(field_descriptor_);
	}

	GpbElementInfoDescriptors GetDescriptors() const;

	const GpbElementInfoVector_I &GetMemberList() const
	{
		return(member_list_);
	}

	GpbElementInfoMaxLengths  GetMaxLengths() const;
	GpbElementInfoMaxLengths &GetMaxLengths(
		GpbElementInfoMaxLengths &max_lengths) const;

	GpbElementInfoVector_I SetIntersection(const GpbElementInfo &other) const;
	GpbElementInfoVector_I SetDifference(const GpbElementInfo &other) const;

	GpbElementInfoPairVector_I SetIntersectionPair(
		const GpbElementInfo &other) const;

	std::ostream &EmitTabular(
		GpbEmitFlags::EmitFlags emit_flags = GpbEmitFlags::Default,
		std::ostream &o_str = std::cout) const;
	std::ostream &EmitCsv(
		GpbEmitFlags::EmitFlags emit_flags = GpbEmitFlags::Default,
		std::ostream &o_str = std::cout) const;

	static std::string SourceLocationToString(
		const ::google::protobuf::SourceLocation &datum);

	template <typename DerivedMessageType>
		static GpbElementInfo GetInstance()
	{
		return(GpbElementInfo(DerivedMessageType::descriptor(), 0));
	}

	void TestFileName() const;

private:
	const GPB_Descriptor                         *descriptor_;
	const GPB_FieldDescriptor                    *field_descriptor_;
	const GPB_FileDescriptor                     *file_descriptor_;
	const GPB_EnumDescriptor                     *enum_descriptor_;
	::google::protobuf::FieldDescriptor::CppType  cpp_type_;
	GpbDatumType                                  datum_type_;
	std::size_t                                   depth_;
	int                                           member_index_;
	std::size_t                                   max_depth_;
	GpbElementInfoVector_I                        member_list_;

	explicit GpbElementInfo(const GPB_Descriptor *descriptor,
		std::size_t depth);
	explicit GpbElementInfo(const GPB_Descriptor *descriptor,
		const GPB_FieldDescriptor *field_descriptor,
		std::size_t depth, int member_index);

	std::ostream &EmitTabular(const GpbElementInfoMaxLengths &max_lengths,
		GpbEmitFlags::EmitFlags emit_flags = GpbEmitFlags::Default,
		std::ostream &o_str = std::cout) const;
	std::ostream &EmitCsv(bool /* disambiguation */,
		GpbEmitFlags::EmitFlags emit_flags = GpbEmitFlags::Default,
		std::ostream &o_str = std::cout) const;

	static const GPB_FileDescriptor *DetermineFileDescriptorPtr(
		const GPB_Descriptor *descriptor,
		const GPB_FieldDescriptor *field_descriptor);

	template <typename DescriptorType>
		static bool GetSourceLocationHelper(const DescriptorType &descriptor,
			::google::protobuf::SourceLocation &dst)
	{
		return((descriptor) ? descriptor->GetSourceLocation(&dst) : false);
	}

	static const char *GetLabelName(
		::google::protobuf::FieldDescriptor::Label label);

	//	Really just to support debugging...
	static void ClearSourceLocation(::google::protobuf::SourceLocation &datum);

	friend std::ostream & operator << (std::ostream &o_str,
		const GpbElementInfo &data);
};
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
typedef GpbElementInfo::GpbElementInfoVector_I GpbElementInfoVector;
typedef GpbElementInfoVector::iterator         GpbElementInfoVectorIter;
typedef GpbElementInfoVector::const_iterator   GpbElementInfoVectorIterC;
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
typedef GpbElementInfo::GpbElementInfoPair_I     GpbElementInfoPair;
typedef std::vector<GpbElementInfoPair>          GpbElementInfoPairVector;
typedef GpbElementInfoPairVector::iterator       GpbElementInfoPairVectorIter;
typedef GpbElementInfoPairVector::const_iterator GpbElementInfoPairVectorIterC;
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str, const GpbElementInfo &data);
//	////////////////////////////////////////////////////////////////////////////

} // namespace ProtoBuf

} // namespace MLB

#endif // #ifndef HH___MLB__ProtoBuf__GpbElementInfo_hpp___HH
