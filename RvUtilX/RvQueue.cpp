// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	TibCo/Rendezvous Support Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Wrapper functions for the TibrvQueue class.

	Revision History	:	2001-10-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2017.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <RvUtilX.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace RvUtilX {

//	////////////////////////////////////////////////////////////////////////////
TibrvQueue &QueueCreate(TibrvQueue &queue_ref)
{
	RvUtilX_THROW_TIBRV_STATUS_IF(queue_ref.create,
		());

	return(queue_ref);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void QueueDestroy(TibrvQueue &queue_ref)
{
	RvUtilX_THROW_TIBRV_STATUS_IF(queue_ref.destroy,
		());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void QueueDispatch(TibrvQueue &queue_ref)
{
	RvUtilX_THROW_TIBRV_STATUS_IF(queue_ref.dispatch,
		());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
unsigned int QueueGetCount(TibrvQueue &queue_ref)
{
	tibrv_u32 event_count;

	RvUtilX_THROW_TIBRV_STATUS_IF(queue_ref.getCount,
		(event_count));

	return(event_count);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
tibrvQueue QueueGetHandle(TibrvQueue &queue_ref)
{
	return(queue_ref.getHandle());
}
//	////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void QueueGetLimitPolicy(TibrvQueue &queue_ref, tibrvQueueLimitPolicy &policy,
	unsigned int &max_events, unsigned int &discard_amount)
{
	tibrv_u32 tmp_max_events     = max_events;
	tibrv_u32 tmp_discard_amount = discard_amount;

	RvUtilX_THROW_TIBRV_STATUS_IF(queue_ref.getLimitPolicy,
		(policy, tmp_max_events, tmp_discard_amount));

	max_events         = tmp_max_events;
	tmp_discard_amount = tmp_discard_amount;
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const char *QueueGetNamePtr(TibrvQueue &queue_ref)
{
	const char *tmp_ptr = NULL;

	RvUtilX_THROW_TIBRV_STATUS_IF(queue_ref.getName,
		(tmp_ptr));

	return(tmp_ptr);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string QueueGetName(TibrvQueue &queue_ref)
{
	return(QueueGetNamePtr(queue_ref));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
unsigned int QueueGetPriority(TibrvQueue &queue_ref)
{
	tibrv_u32 priority;
		
	RvUtilX_THROW_TIBRV_STATUS_IF(queue_ref.getPriority,
		(priority));

	return(priority);
}
// ////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool QueueIsDefault(const TibrvQueue *queue_ptr)
{
	return(queue_ptr == GetDefaultQueue());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool QueueIsDefault(const TibrvQueue &queue_ref)
{
	return(QueueIsDefault(&queue_ref));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool QueuePoll(TibrvQueue &queue_ref)
{

	TibrvStatus rv_status = queue_ref.poll();

	if (rv_status == TIBRV_OK)
		return(true);
	else if (rv_status != TIBRV_TIMEOUT)
		ThrowTibrvStatus(rv_status, "TibrvQueue.poll() failed.");

	return(false);
}
//	////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void QueueSetLimitPolicy(TibrvQueue &queue_ref, tibrvQueueLimitPolicy policy,
	unsigned int max_events, unsigned int discard_amount)
{
	tibrv_u32 tmp_max_events     = max_events;
	tibrv_u32 tmp_discard_amount = discard_amount;

	RvUtilX_THROW_TIBRV_STATUS_IF(queue_ref.setLimitPolicy,
		(policy, tmp_max_events, tmp_discard_amount));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void QueueSetName(TibrvQueue &queue_ref, const char *queue_name)
{
	RvUtilX_THROW_TIBRV_STATUS_IF(queue_ref.setName,
		(queue_name));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void QueueSetName(TibrvQueue &queue_ref, const std::string &queue_name)
{
	QueueSetName(queue_ref, queue_name.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void QueueSetPriority(TibrvQueue &queue_ref, unsigned int priority)
{
	RvUtilX_THROW_TIBRV_STATUS_IF(queue_ref.setPriority,
		(priority));
}
// ////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool QueueTimedDispatch(TibrvQueue &queue_ref, double time_out)
{
	TibrvStatus rv_status = queue_ref.timedDispatch(time_out);

	if (rv_status == TIBRV_OK)
		return(true);
	else if (rv_status != TIBRV_TIMEOUT)
		ThrowTibrvStatus(rv_status, "TibrvQueue.timedDispatch() failed.");

	return(false);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace RvUtilX

} // namespace MLB

