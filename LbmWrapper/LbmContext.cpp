// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	29 West LBM API Wrapper Library Module File
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the LbmContext class.

	Revision History	:	2008-08-16 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2008 - 2016.
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
LbmContext::LbmContext()
	:LbmObjectBase<lbm_context_t>()
{
	Initialize(NULL);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmContext::LbmContext(LbmAttrContext &context_attr)
	:LbmObjectBase<lbm_context_t>()
{
	Initialize(context_attr.GetObjectPtr());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmContext::LbmContext(lbm_context_t *context_attr)
	:LbmObjectBase<lbm_context_t>(context_attr)
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void LbmContext::Initialize(lbm_context_attr_t *attr_ptr)
{
	lbm_context_t *tmp_ptr;

	WRAP29_LBM_THROW_IF_NE_ZERO(
		::lbm_context_create,
		(&tmp_ptr, attr_ptr, NULL, NULL));

	object_sptr_.reset(tmp_ptr, ::lbm_context_delete);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int LbmContext::ScheduleTimer(lbm_timer_cb_proc proc, void *clientd,
	lbm_event_queue_t *evq, lbm_ulong_t delay)
{
	return(LbmScheduleTimer(GetObjectPtr(), proc, clientd, evq, delay));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int LbmContext::ScheduleTimerRecurring(lbm_timer_cb_proc proc, void *clientd,
	lbm_event_queue_t *evq, lbm_ulong_t delay)
{
	return(LbmScheduleTimerRecurring(GetObjectPtr(), proc, clientd, evq, delay));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void LbmContext::Dump(int *size, lbm_config_option_t *opts)
{
	ConfigDumpHelper<lbm_context_t>::DumpConfig(::lbm_context_dump,
		GetObjectPtr(), size, opts);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmConfigOptionList &LbmContext::Dump(LbmConfigOptionList &out_list)
{
	return(ConfigDumpHelper<lbm_context_t>::DumpConfig(::lbm_context_dump,
		GetObjectPtr(), out_list));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
LbmConfigOptionList LbmContext::Dump()
{
	LbmConfigOptionList out_list;

	return(Dump(out_list));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace LbmWrapper

} // namespace MLB

