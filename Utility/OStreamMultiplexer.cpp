//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	MLB Utility Library Module File
//	////////////////////////////////////////////////////////////////////////////
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementatio of the OStreamMultiplexer and related
								classes.

	Revision History	:	2006-11-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2006 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
//	////////////////////////////////////////////////////////////////////////////
 
//	////////////////////////////////////////////////////////////////////////////
//	////////////////////////////////////////////////////////////////////////////
//	Required include files...
//	////////////////////////////////////////////////////////////////////////////

#include <Utility/OStreamMultiplexer.hpp>
#include <Utility/Utility_Exception.hpp>

//	////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

//	////////////////////////////////////////////////////////////////////////////
OStreamPortList::OStreamPortList()
	:the_lock_()
	,ostream_port_set_()
{
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OStreamPortList::~OStreamPortList()
{
	try {
		RemoveAll();
	}
	catch (const std::exception &) {
	}
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void OStreamPortList::AddOStream(std::ostream *ostream_ptr)
{
	CheckNullPtrArg(ostream_ptr);

	ScopedLockType my_lock(the_lock_);

	ostream_port_set_.insert(ostream_ptr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void OStreamPortList::RemoveOStream(std::ostream *ostream_ptr)
{
	CheckNullPtrArg(ostream_ptr);

	ScopedLockType my_lock(the_lock_);

	ostream_port_set_.erase(ostream_ptr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void OStreamPortList::RemoveAll()
{
	ScopedLockType my_lock(the_lock_);

	ostream_port_set_.clear();
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void OStreamPortList::RemoveAllExcept(std::ostream *ostream_ptr)
{
	CheckNullPtrArg(ostream_ptr);

	ScopedLockType my_lock(the_lock_);

	if (ostream_port_set_.find(ostream_ptr) == ostream_port_set_.end())
		ostream_port_set_.clear();
	else {
		ostream_port_set_.clear();
		ostream_port_set_.insert(ostream_ptr);
	}
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int OStreamPortList::DoPutChar(int chr)
{
	ScopedLockType     my_lock(the_lock_);
	OStreamPortSetIter iter_b(ostream_port_set_.begin());
	OStreamPortSetIter iter_e(ostream_port_set_.end());

	for ( ; iter_b != iter_e; ++iter_b)
		**iter_b << static_cast<char>(chr);

	return(0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int OStreamPortList::DoSync()
{
	ScopedLockType     my_lock(the_lock_);
	OStreamPortSetIter iter_b(ostream_port_set_.begin());
	OStreamPortSetIter iter_e(ostream_port_set_.end());

	for ( ; iter_b != iter_e; ++iter_b)
		**iter_b << std::flush;

	return(0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void OStreamPortList::CheckNullPtrArg(std::ostream *ostream_ptr) const
{
	if (ostream_ptr == NULL)
		MLB::Utility::ThrowInvalidArgument("Pointer to 'std::ostream' "
			"instance is 'NULL'.");
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OStreamMultiplexerBuffer::OStreamMultiplexerBuffer(
	OStreamPortList &ostream_port_list)
	:std::streambuf()
	,ostream_port_list_(ostream_port_list)
{
	setp(0, 0);
	setg(0, 0, 0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::streambuf::int_type OStreamMultiplexerBuffer::overflow(int c)
{
     if (c != EOF)
		return(ostream_port_list_.DoPutChar(c));

	return(0);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int OStreamMultiplexerBuffer::sync()
{
	return(ostream_port_list_.DoSync());
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OStreamMultiplexer::OStreamMultiplexer(std::ostream *ostream_ptr)
	:std::ostream(new OStreamMultiplexerBuffer(GetOStreamPortListRef()))
	,ostream_port_list_()
{
	if (ostream_ptr != NULL)
		AddOStream(ostream_ptr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void OStreamMultiplexer::AddOStream(std::ostream *ostream_ptr)
{
	ostream_port_list_.AddOStream(ostream_ptr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void OStreamMultiplexer::RemoveOStream(std::ostream *ostream_ptr)
{
	ostream_port_list_.RemoveOStream(ostream_ptr);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
OStreamPortList &OStreamMultiplexer::GetOStreamPortListRef()
{
	return(ostream_port_list_);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#ifdef TEST_MAIN

using namespace MLB::Utility;

const char TEST_FileNameBase[] = "OStreamMultiplexer.Test_";

//	////////////////////////////////////////////////////////////////////////////
void TEST_OpenOutputFile(const std::string &file_name,
	std::ofstream &file_stream)
{
	file_stream.open(file_name.c_str(), std::ios_base::out);

   if (!file_stream.rdbuf()->is_open())
		MLB::Utility::ThrowSystemError("Attempt to open file " + file_name +
			"for writing failed");
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
int main()
{
	int return_code = EXIT_SUCCESS;

	try {
		OStreamMultiplexer my_mos(&std::cout);
		std::ofstream      file_stream_1;
		std::ofstream      file_stream_2;
		TEST_OpenOutputFile("./OStreamMultiplexer.Test_001.txt", file_stream_1);
		TEST_OpenOutputFile("./OStreamMultiplexer.Test_002.txt", file_stream_2);
		my_mos.AddOStream(&file_stream_1);
		my_mos.AddOStream(&file_stream_2);
		my_mos << "Line 1: This is a test!!!" << std::endl;
		my_mos << "Line 2: This is a test: " << std::setw(10) << 666 << ": OK!!!" <<
			std::endl;
		my_mos << "Line 3: About to remove file '" <<
			"./OStreamMultiplexer.Test_001.txt'..." << std::endl;
		my_mos.RemoveOStream(&file_stream_1);
		my_mos << "Line 4: Have removed file '" <<
			"./OStreamMultiplexer.Test_001.txt'..." << std::endl;
		my_mos << "Line 5: ---> Done!!!" << std::endl;
	}
	catch (const std::exception &except) {
		std::cerr << "ERROR: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
//	////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

