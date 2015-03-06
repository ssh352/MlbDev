// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	MLB LSFWrapper Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Support for LSF functionality 'ls_rtaske()'.

	Revision History	:	1998-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////


// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/C_StringSupport.hpp>

#include <LSFWrapper/LSFWrapper.hpp>

#if defined(_Windows) && defined(_DEBUG)
# include "CRTDBG.h"
#endif // #if defined(_Windows) && defined(_DEBUG)

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace LSFWrapper {

//	////////////////////////////////////////////////////////////////////////////
int LSF_rtaske(const char *host, char **argv, int options, char **envp)
{
	if (host == NULL)
		throw LSFException("The 'ls_rtaske()' host name is 'NULL'.");

	if (!(*host))
		throw LSFException("The 'ls_rtaske()' host name is an empty string.");

	if (argv == NULL)
		throw LSFException("The 'ls_rtaske()' argument list pointer is 'NULL'.");

	if (argv[0] == NULL)
		throw LSFException("The 'ls_rtaske()' first argument list pointer is "
			"'NULL' --- minimally, the name of the command to execute must be "
			"specified.");

	if (!(*argv[0]))
		throw LSFException("The 'ls_rtaske()' first argument list pointer is "
			"an empty string--- minimally, the name of the command to execute "
			"must be specified.");
		
	int result;

#if defined(_Windows) && defined(_DEBUG)
	//	Get the old CRT debug flags...
	int old_mem_debug_flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	//	Turn them all off for this operation...
	_CrtSetDbgFlag(_CRTDBG_CHECK_DEFAULT_DF);
#endif // #if defined(_Windows) && defined(_DEBUG)

	//	Make the call to Platform LSF...
	result = ls_rtaske(const_cast<char *>(host), argv, options, envp);

#if defined(_Windows) && defined(_DEBUG)
	//	Restore the original CRT debug flags...
	_CrtSetDbgFlag(old_mem_debug_flag);
#endif // #if defined(_Windows) && defined(_DEBUG)

	//	Throw if necessary...
	if (result < 0) {
		std::ostringstream error_text;
		error_text << "Invocation of 'ls_rtaske()' on host '" << host <<
			"' failed with a negative return code (" << result << ").";
		ThrowLSFStatus(lserrno, error_text);
	}

	return(result);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int RTaskE(const std::string &host_name, const ArgvList &argument_list,
	int rtask_options, const EnvpList &environment_list)
{
	//	Construct the NULL pointer terminated char** array for argv...
	MLB::Utility::C_ListTypeString<unsigned int> argv_list;
	argv_list.FromContainer(argument_list,
		"Invocation of Platform/LSF function 'ls_rtaske()' for argv_list");
	argv_list.AppendEmpty(
		"Invocation of Platform/LSF function 'ls_rtaske()' for argv_list");

	//	Construct the NULL pointer terminated char** array for envp...
	MLB::Utility::C_ListTypeString<unsigned int> envp_list;
	envp_list.FromContainer(environment_list,
		"Invocation of Platform/LSF function 'ls_rtaske()' for envp list");
	envp_list.AppendEmpty(
		"Invocation of Platform/LSF function 'ls_rtaske()' for envp list");

	return(LSF_rtaske(host_name.c_str(), argv_list.GetList(), rtask_options,
		envp_list.GetList()));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int RTaskE(const std::string &host_name, const std::string &argument_0,
	int rtask_options, const EnvpList &environment_list)
{
	return(RTaskE(host_name, ArgvList(1, argument_0), rtask_options,
		environment_list));
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace LSFWrapper

} // namespace MLB

#ifdef TEST_MAIN

#include <Utility/Sleep.hpp>

#include <iomanip>

using namespace MLB::LSFWrapper;

//	////////////////////////////////////////////////////////////////////////////
struct TEST_RTaskEInfo {
	TEST_RTaskEInfo(const std::string &host_name, bool rtask_done,
		int process_id, const std::string &error_text = "") :
		host_name_(host_name)
		,rtask_done_(rtask_done)
		,process_id_(process_id)
		,error_text_(error_text) { }

	std::string host_name_;
	bool        rtask_done_;
	int         process_id_;
	std::string error_text_;
};
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
struct TestArgs {
	TestArgs() :
		 node_count_(1)
		,sleep_time_(0)
		,resource_spec_()
		,rtask_options_(0)
		,init_rex_ports_(1)
		,node_acquisition_sleep_(0)
		,permit_duplicate_nodes_(false)
		,node_name_()
		,restrict_set_()
		,argv_list_() {
	}

	unsigned int            node_count_;
	unsigned int            sleep_time_;
	std::string             resource_spec_;
	int                     rtask_options_;
	unsigned int            init_rex_ports_;
	unsigned int            node_acquisition_sleep_;
	bool                    permit_duplicate_nodes_;
	std::string             node_name_;
	MLB::Utility::StringSet restrict_set_;
	ArgvList                argv_list_;
};
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void TEST_RTaskE(TestArgs &argv_control)
{
	//	Need to set up before calling RTaskE()...
	RexInitDoneContext rex_context(argv_control.init_rex_ports_);

	HostList host_list;

	if (argv_control.node_count_ > 1) {
		host_list = PlaceReq(argv_control.resource_spec_,
		argv_control.node_count_ * 8, OK_ONLY);
		std::sort(host_list.begin(), host_list.end());
	}
	else if (argv_control.node_name_.empty())
		host_list = PlaceReq(argv_control.resource_spec_, 1, OK_ONLY);
	else
		host_list.push_back(argv_control.node_name_);

	std::cout << "PlaceReq() result        : " <<
		static_cast<unsigned int>(host_list.size()) << std::endl;

	if (!argv_control.permit_duplicate_nodes_) {
		MLB::Utility::StringSet tmp_set(host_list.begin(), host_list.end());
		HostList                tmp_list(tmp_set.begin(), tmp_set.end());
		host_list.swap(tmp_list);
		std::cout << "PlaceReq() result (final): " <<
			static_cast<unsigned int>(host_list.size()) << std::endl;
	}

	ArgvList tmp_argv_list;

	if (!argv_control.argv_list_.empty())
		tmp_argv_list = argv_control.argv_list_;
	else {
#ifdef _Windows
		tmp_argv_list = ArgvList(1, "C:\\WinNT\\system32\\hostname.exe");
#else
		tmp_argv_list = ArgvList(1, "hostname");
#endif // #ifdef _Windows
	}

	std::deque<TEST_RTaskEInfo> rtask_info;
//	EnvpList                    envp_list = MLB::Utility::GetEnvironment();
EnvpList envp_list;

	EnvpList::const_iterator iter_b(envp_list.begin());
	EnvpList::const_iterator iter_e(envp_list.end());

	std::cout << std::setfill('=') << std::setw(78) << "" <<
		std::setfill(' ') << std::endl;
	std::cout << "Environment Variables:" << std::endl;
	std::cout << std::setfill('-') << std::setw(78) << "" <<
		std::setfill(' ') << std::endl;
	while (iter_b != iter_e)
		std::cout << "[" << *iter_b++ << "]" << std::endl;
	std::cout << std::setfill('=') << std::setw(78) << "" <<
		std::setfill(' ') << std::endl;

	unsigned int count_1 = 0;

	iter_b = host_list.begin();
	iter_e = host_list.end();

	while (iter_b != iter_e) {
		if (argv_control.restrict_set_.find(
			MLB::Utility::ConvertHostNameToCanonical(*iter_b)) ==
			argv_control.restrict_set_.end()) {
			int process_id = -1;
			try {
				std::cout << std::setw(5) << count_1 << ": [" <<
					std::setw(20) << *iter_b << "] = " << std::flush;
				process_id = RTaskE(*iter_b, tmp_argv_list,
					argv_control.rtask_options_, envp_list);
				std::cout << "PID " << std::setw(5) << process_id << std::endl;
				++count_1;
				rtask_info.push_back(TEST_RTaskEInfo(*iter_b, true, process_id));
			}
			catch (const std::exception &except) {
				rtask_info.push_back(TEST_RTaskEInfo(*iter_b, false, 0,
					except.what()));
				std::cout << "ERROR A: " << except.what() << std::endl;
			}
			MLB::Utility::SleepMilliSecs(argv_control.node_acquisition_sleep_);
try {
	LSF_RWaitResult wait_result;
	if (MLB::LSFWrapper::RWait(wait_result, LSF_WNOHANG, true))
		rtask_info.push_back(TEST_RTaskEInfo(*iter_b, false, process_id));
}
catch (const std::exception &except) {
	rtask_info.push_back(TEST_RTaskEInfo(*iter_b, false, 0, except.what()));
	std::cout << "ERROR B: " << except.what() << std::endl;
}
		}
		++iter_b;
	}

	std::cout << "Sleeping for 10 seconds..." << std::endl;

	MLB::Utility::SleepMilliSecs(10000);

	for (count_1 = 0; count_1 < rtask_info.size(); ++count_1) {
		try {
			LSF_RWaitResult wait_result;
			std::cout << std::setw(5) << count_1 << ": " <<
				std::setw(20) << rtask_info[count_1].host_name_ << ": " <<
				std::flush;
			if (rtask_info[count_1].rtask_done_) {
				std::cout << "PID = " << std::setw(5) <<
					rtask_info[count_1].process_id_ << ": " << std::flush;
				RWaitTid(rtask_info[count_1].process_id_, wait_result, 0x0);
				std::cout << " Process exit code = " << std::setw(6) <<
					wait_result.process_status_ << std::endl;
			}
			else
				std::cout << "ERROR C: " << rtask_info[count_1].error_text_ <<
					std::endl;
		}
		catch (const std::exception &except) {
			std::cout << "ERROR D: " << except.what() << std::endl;
		}
	}
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
//	Get the command line parameters...
void GetParameters(int argc, char **argv, TestArgs &argv_control)
{
	unsigned int count_1;
	std::string  tmp_name;

	for (count_1 = 1; count_1 < static_cast<unsigned int>(argc); ++count_1) {
		if (LSFParseCmdLineArg::ParseCmdLineNumeric<unsigned int>(
			"-NODE_COUNT", count_1, argc, argv, argv_control.node_count_, 1))
			;
		else if (LSFParseCmdLineArg::ParseCmdLineFollowing(
			"-HOST_NAME", count_1, argc, argv, argv_control.node_name_) ||
			MLB::Utility::ParseCmdLineArg::ParseCmdLineFollowing(
			"-NODE_NAME", count_1, argc, argv, argv_control.node_name_))
			;
		else if (LSFParseCmdLineArg::ParseCmdLineNumeric<unsigned int>(
			"-SLEEP_TIME", count_1, argc, argv, argv_control.sleep_time_))
			;
		else if (LSFParseCmdLineArg::ParseLSFResourceSpec(count_1, argc,
			argv, argv_control.resource_spec_))
			;
		else if (LSFParseCmdLineArg::ParseCmdLineNumeric<int>(
			"-RTASK_OPTIONS", count_1, argc, argv, argv_control.rtask_options_))
			;
		else if (LSFParseCmdLineArg::ParseLSFResourceSpec(count_1,
			argc, argv, argv_control.resource_spec_))
			;
		else if (LSFParseCmdLineArg::ParseCmdLineInitRexPorts(count_1,
			argc, argv, argv_control.init_rex_ports_))
			;
		else if (LSFParseCmdLineArg::ParseCmdLineNodeAcquisitionSleep(
			count_1, argc, argv, argv_control.node_acquisition_sleep_))
			;
		else if (LSFParseCmdLineArg::ParseCmdLinePermitDuplicateNodes(
			count_1, argc, argv, argv_control.permit_duplicate_nodes_))
			;
		else if (LSFParseCmdLineArg::ParseCmdLineFollowing(
			"-RESTRICT_HOST", count_1, argc, argv, tmp_name) ||
			MLB::Utility::ParseCmdLineArg::ParseCmdLineFollowing(
			"-RESTRICT_NODE", count_1, argc, argv, tmp_name))
			argv_control.restrict_set_.insert(
				MLB::Utility::ConvertHostNameToCanonical(tmp_name));
		else if (LSFParseCmdLineArg::ParseCmdLineAndRemainder(
			"-EXECUTE", count_1, argc, argv, argv_control.argv_list_))
			;
		else
			LSFParseCmdLineArg::InvalidArgument(argv[count_1]);
	}
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	int      return_code = EXIT_SUCCESS;
	TestArgs argv_control;

	std::cout << "Test of function 'RTaskE()'" << std::endl;
	std::cout << "---- -- -------- ----------" << std::endl;

	// //////////////////////////////////////////////////////////////////////
	// //////////////////////////////////////////////////////////////////////
	//	Help may have been requested on the command line...
	// //////////////////////////////////////////////////////////////////////
	if (MLB::Utility::ParseCmdLineArg::HasCmdLineHelp(argc, argv, 1)) {
		std::cout << "USAGE: " << std::endl <<
			"   " << argv[0] << " " <<
			"[ -node_count <number-of-nodes> ( = " <<
				argv_control.node_count_ << " ) ] " <<
			"[ -host_name <name-of-host-node-on-which-to-execute> ( = " <<
				argv_control.node_name_ << ") ] " <<
			"[ -sleep_time <sleep-milliseconds-between-rtaske-calls> ( = " <<
				argv_control.sleep_time_ << " ) ] " <<
			"[ -resource_spec <LSF-resource-specification-string> ( = " <<
				argv_control.resource_spec_ << " ) ] " <<
			"[ -rtask_options <rtask-option-flags> ( = " <<
				argv_control.rtask_options_ << " ) ] " <<
			"[ -init_rex_ports <number-of-initrex-ports> ] " <<
			"[ -node_acquisition_sleep <sleep-milliseconds-between-rtasks> ] " <<
			"[ -permit_duplicate_nodes <boolean> ( = OFF ) ] " <<
			"[ -restrict_host <host-name> ] " <<
			"[ -execute <program-name> [ <args> ... ] ] " << std::endl <<
			" *** NOTE: The '-execute' parameter (and its associated " <<
			"parameters which follow it) must be last on the command line." <<
			std::endl << std::endl;
		exit(EXIT_SUCCESS);
	}
	// //////////////////////////////////////////////////////////////////////

	try {
		GetParameters(argc, argv, argv_control);
		TEST_RTaskE(argv_control);
	}
	catch (const std::exception &except) {
		std::cout << std::endl << "ERROR: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
//	////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

