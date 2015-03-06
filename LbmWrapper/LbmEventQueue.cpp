// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	29 West LBM API Wrapper Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the LbmEventQueue class.

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
#include <LbmWrapper/LbmMiscSupport.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace LbmWrapper {

//	////////////////////////////////////////////////////////////////////////////
LbmEventQueue::LbmEventQueue(lbm_event_queue_t *event_queue_ptr)
	:LbmObjectBase<lbm_event_queue_t>(event_queue_ptr)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmEventQueue::LbmEventQueue(lbm_event_queue_monitor_proc call_back,
	void *user_data_ptr, lbm_event_queue_attr_t *attr_ptr)
	:LbmObjectBase<lbm_event_queue_t>()
{
	Initialize(call_back, user_data_ptr, attr_ptr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmEventQueue::LbmEventQueue(lbm_event_queue_monitor_proc call_back,
	void *user_data_ptr, LbmAttrEventQueue &attr)
	:LbmObjectBase<lbm_event_queue_t>()
{
	Initialize(call_back, user_data_ptr, attr.GetObjectPtr());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void LbmEventQueue::Initialize(lbm_event_queue_monitor_proc call_back,
	void *user_data_ptr, LbmAttrEventQueue &attr_ref)
{
	Initialize(call_back, user_data_ptr, attr_ref.GetObjectPtr());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void LbmEventQueue::Initialize(lbm_event_queue_monitor_proc call_back,
	void *user_data_ptr, lbm_event_queue_attr_t *attr_ptr)
{
	lbm_event_queue_t *tmp_ptr;

	WRAP29_LBM_THROW_IF_NE_ZERO(
		::lbm_event_queue_create,
		(&tmp_ptr, call_back, user_data_ptr, attr_ptr));

	object_sptr_.reset(tmp_ptr, ::lbm_event_queue_delete);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int LbmEventQueue::EventDispatch(lbm_ulong_t tmo)
{
	return(LbmEventDispatch(GetObjectPtr(), tmo));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void LbmEventQueue::EventDispatchUnblock()
{
	LbmEventDispatchUnblock(GetObjectPtr());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int LbmEventQueue::EventQueueSize()
{
	return(LbmEventQueueSize(GetObjectPtr()));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void LbmEventQueue::EventQueueShutdown()
{
	LbmEventQueueShutdown(GetObjectPtr());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void LbmEventQueue::Dump(int *size, lbm_config_option_t *opts)
{
	ConfigDumpHelper<lbm_event_queue_t>::DumpConfig(::lbm_event_queue_dump,
		GetObjectPtr(), size, opts);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmConfigOptionList &LbmEventQueue::Dump(LbmConfigOptionList &out_list)
{
	return(ConfigDumpHelper<lbm_event_queue_t>::DumpConfig(
		::lbm_event_queue_dump, GetObjectPtr(), out_list));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmConfigOptionList LbmEventQueue::Dump()
{
	LbmConfigOptionList out_list;

	return(Dump(out_list));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace LbmWrapper

} // namespace MLB

