// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	29 West LBM API Wrapper Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the LbmTopicRcv class.

	Revision History	:	2008-08-16 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2008 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <LbmWrapper/LbmAttrSupport.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace LbmWrapper {

//	////////////////////////////////////////////////////////////////////////////
LbmTopicRcv::LbmTopicRcv(LbmContext &context, const char *topic_name,
	lbm_rcv_topic_attr_t *topic_attr)
	:LbmObjectBase<lbm_topic_t>()
	,topic_name_(topic_name)
{
	Initialize(context, topic_attr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmTopicRcv::LbmTopicRcv(LbmContext &context, const std::string &topic_name,
	lbm_rcv_topic_attr_t *topic_attr)
	:LbmObjectBase<lbm_topic_t>()
	,topic_name_(topic_name)
{
	Initialize(context, topic_attr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmTopicRcv::LbmTopicRcv(LbmContext &context, const char *topic_name,
	LbmAttrTopicRcv &topic_attr)
	:LbmObjectBase<lbm_topic_t>()
	,topic_name_(topic_name)
{
	Initialize(context, topic_attr.GetObjectPtr());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmTopicRcv::LbmTopicRcv(LbmContext &context, const std::string &topic_name,
	LbmAttrTopicRcv &topic_attr)
	:LbmObjectBase<lbm_topic_t>()
	,topic_name_(topic_name)
{
	Initialize(context, topic_attr.GetObjectPtr());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
/*
	CODE NOTE: Question for Mark Robbie: Is there a way to get the topic name
	from a lbm_topic_t *?
*/
LbmTopicRcv::LbmTopicRcv(lbm_topic_t *topic_attr)
	:LbmObjectBase<lbm_topic_t>(topic_attr)
	,topic_name_()
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void LbmTopicRcv::Initialize(LbmContext &context,
	lbm_rcv_topic_attr_t *attr_ptr)
{
	lbm_topic_t *tmp_ptr;

	WRAP29_LBM_THROW_IF_NE_ZERO(
		::lbm_rcv_topic_lookup,
		(&tmp_ptr, context.GetObjectPtr(), topic_name_.c_str(), attr_ptr));

	//	Topic objects are deleted automagically by LBM...
	object_sptr_.reset(tmp_ptr, MyNullDeleter());
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace LbmWrapper

} // namespace MLB

