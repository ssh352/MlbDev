// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	TibCo/Rendezvous Support Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the SubjectNameFlat class.

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

// ////////////////////////////////////////////////////////////////////////////
SubjectNameFlat::SubjectNameFlat()
	:element_count_(0)
	,is_pattern_(false)
{
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SubjectNameFlat::SubjectNameFlat(const std::string &subject_name)
	:element_count_(0)
	,is_pattern_(false)
{
	SetSubjectName(subject_name);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SubjectNameFlat::SubjectNameFlat(const char *subject_name)
	:element_count_(0)
	,is_pattern_(false)
{
	SetSubjectName(subject_name);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
SubjectNameFlat::SubjectNameFlat(const SubjectNameWork &subject_name)
	:element_count_(0)
	,is_pattern_(false)
{
	SetSubjectName(subject_name);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::SetSubjectName(const std::string &subject_name)
{
	SetSubjectName(subject_name.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::SetSubjectName(const char *subject_name)
{
	SetSubjectName(SubjectNameWork(subject_name));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::SetSubjectName(const SubjectNameWork &subject_name)
{
	unsigned int count_1;

	element_count_ = subject_name.element_count_;
	is_pattern_    = subject_name.is_pattern_;

	for (count_1 = 0; count_1 < subject_name.element_count_; ++count_1)
		strcpy(element_list_[count_1], subject_name.element_list_[count_1]);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::MatchSubjectName(const std::string &subject_name,
	unsigned int *failed_element) const
{
	return(MatchSubjectName(subject_name.c_str(), failed_element));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::MatchSubjectName(const char *subject_name,
	unsigned int *failed_element) const
{
	return(MatchSubjectName(SubjectNameFlat(subject_name), failed_element));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::MatchSubjectName(const SubjectNameFlat &subject_name,
	unsigned int *failed_element) const
{
	//	////////////////////////////////////////////////////////////////
	//	If the number of elements in the subject exceeds the number of
	//	elements in this pattern AND the last element in this pattern is
	//	not '>' then the match has failed.
	if ((subject_name.element_count_ > element_count_) &&
		(*element_list_[element_count_ - 1] != ElementLastChar)) {
		if (failed_element != NULL)
			*failed_element = element_count_;
		return(false);
	}

	//	////////////////////////////////////////////////////////////////
	//	If the number of elements in the subject is less than the
	//	number of elements in this pattern, the match has failed.
	if (subject_name.element_count_ < element_count_) {
		//	Note: In this case the failure is considered to have occurred
		//	beyond the end of the list of subject name elements.
		if (failed_element != NULL)
			*failed_element = subject_name.element_count_;
		return(false);
	}
	//	////////////////////////////////////////////////////////////////
	//	Otherwise, we need to look at each element...
	unsigned int count_1;
	for (count_1 = 0; count_1 < subject_name.element_count_; ++count_1) {
		//	If we've examined all of the pattern elements, then we don't
		//	have a match...
		if (count_1 >= element_count_)
			return(false);
		//	If we've gotten this far and the current element of the pattern
		//	is '>' then we have a match.
		if (*element_list_[count_1] == ElementLastChar)
			return(true);
		//	If the current element of the pattern is not '*' and the current
		//	element of the pattern does not match the current element of the
		//	subject name, the match has failed.
		if ((*element_list_[count_1] != ElementAnyChar) &&
			strcmp(element_list_[count_1], subject_name.element_list_[count_1])) {
			if (failed_element != NULL)
				*failed_element = count_1;
			return(false);
		}				
	}

	return(true);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::IsPattern() const
{
	return(is_pattern_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::IsFullName() const
{
	return(!IsPattern());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::IsReplyName() const
{
	char subject_name[MaxSubjectSize + 1];

	return(IsFullName() &&
		(strlen(ToString(subject_name)) <= MaxReplySubjectSize));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
unsigned int SubjectNameFlat::GetElementCount() const
{
	return(element_count_);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckPattern()
{
	if (!IsPattern()) {
		std::ostringstream error_text;
		error_text << "Subject name '" << ToString() <<
			"' is not an explicit Rendezvous subject name pattern.";
		//	CODE NOTE: Should throw RvBadSubjectException
		throw RvException(error_text);
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckFullName()
{
	if (!IsFullName()) {
		std::ostringstream error_text;
		error_text << "Subject name '" << ToString() <<
			"' is not a fully-qualified subject name.";
		//	CODE NOTE: Should throw RvBadSubjectException
		throw RvException(error_text);
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckReplyName()
{
	try {
		CheckFullName();
		if (!IsReplyName()) {
			//	CODE NOTE: Should throw RvBadSubjectException
			std::string subject_name(ToString());
			throw RvException("The length of subject name '" + subject_name +
				"' (" + MLB::Utility::AnyToString(subject_name.size()) +
				") exceeds the maximum permissible (" +
				MLB::Utility::AnyToString(MaxReplySubjectSize) + ").");
		}
	}
	catch (const std::exception &except) {
		MLB::Utility::Rethrow(except, "Not a valid Tib/Rendezvous reply "
			"subject: " + std::string(except.what()));
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string SubjectNameFlat::ToString() const
{
	std::string out_string;

	return(ToString(out_string));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::string &SubjectNameFlat::ToString(std::string &out_string) const
{
	char subject_name[MaxSubjectSize + 1];

	return(out_string.assign(ToString(subject_name)));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
char *SubjectNameFlat::ToString(char *out_string) const
{
	unsigned int  count_1;
	char         *tmp_ptr = out_string;

	for (count_1 = 0; count_1 < element_count_; ++count_1) {
		if (count_1)
			*tmp_ptr++ = '.';
		strcpy(tmp_ptr, element_list_[count_1]);
		tmp_ptr += strlen(tmp_ptr);
	}

	return(out_string);
}
// ////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string SubjectNameFlat::ToStringFromElements(unsigned int element_start,
	unsigned int element_end) const
{
	std::string out_string;

	return(ToStringFromElements(out_string, element_start, element_end));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
std::string &SubjectNameFlat::ToStringFromElements(std::string &out_string,
	unsigned int element_start, unsigned int element_end) const
{
	char subject_name[MaxSubjectSize + 1];

	return(out_string.assign(ToStringFromElements(subject_name, element_start,
		element_end)));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
char *SubjectNameFlat::ToStringFromElements(char *out_string,
	unsigned int element_start, unsigned int element_end) const
{
	if (element_start > element_end)
		std::swap(element_start, element_end);

	char *out_ptr = out_string;

	while ((element_start < element_count_) &&
		(element_start <= element_end)) {
		size_t element_length = strlen(element_list_[element_start]);
		::memcpy(out_ptr, element_list_[element_start++], element_length);
		if (out_ptr != out_string) {
			out_ptr[element_length] = '.';
			++out_ptr;
		}
		out_ptr += element_length;
	}

	*out_ptr = '\0';

	return(out_string);
}
//	////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::operator < (const SubjectNameFlat &other) const
{
	unsigned int min_count = std::min(element_count_, other.element_count_);
	unsigned int count_1;

	int          cmp;

	for (count_1 = 0; count_1 < min_count; ++count_1) {
		cmp = strcmp(element_list_[count_1], other.element_list_[count_1]);
		if (cmp < 0)
			return(true);
		else if (cmp > 0)
			return(false);
	}

	if (element_count_ != min_count)
		return(true);

	return(false);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::IsPatternSubjectName(const char *subject_name)
{
	try {
		SubjectNameFlat tmp_name(subject_name);
		return(tmp_name.IsPattern());
	}
	catch (...) {
	}

	return(false);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::IsPatternSubjectName(const std::string &subject_name)
{
	return(IsPatternSubjectName(subject_name.c_str()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::IsPatternSubjectName(
	const std::ostringstream &subject_name)
{
	return(IsPatternSubjectName(subject_name.str().c_str()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::IsFullNameSubjectName(const char *subject_name)
{
	try {
		SubjectNameFlat tmp_name(subject_name);
		return(tmp_name.IsFullName());
	}
	catch (const std::exception &) {
	}

	return(false);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::IsFullNameSubjectName(const std::string &subject_name)
{
	return(IsFullNameSubjectName(subject_name.c_str()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
bool SubjectNameFlat::IsFullNameSubjectName(
	const std::ostringstream &subject_name)
{
	return(IsFullNameSubjectName(subject_name.str().c_str()));
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckPatternSubjectName(const char *subject_name)
{
	if (!IsPatternSubjectName(subject_name)) {
		std::ostringstream error_text;
		error_text << "Subject name '" << subject_name <<
			"' is not an explicit Rendezvous subject name pattern.";
		//	CODE NOTE: Should throw RvBadSubjectException
		throw RvException(error_text);
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckPatternSubjectName(const std::string &subject_name)
{
	CheckPatternSubjectName(subject_name.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckPatternSubjectName(
	const std::ostringstream &subject_name)
{
	CheckPatternSubjectName(subject_name.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckFullNameSubjectName(const char *subject_name)
{
	if (!IsFullNameSubjectName(subject_name)) {
		std::ostringstream error_text;
		error_text << "Subject name '" << subject_name <<
			"' is not a fully-qualified subject name.";
		//	CODE NOTE: Should throw RvBadSubjectException
		throw RvException(error_text);
	}
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckFullNameSubjectName(const std::string &subject_name)
{
	CheckFullNameSubjectName(subject_name.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckFullNameSubjectName(
	const std::ostringstream &subject_name)
{
	CheckFullNameSubjectName(subject_name.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckReplySubjectName(const char *subject_name)
{
	SubjectNameFlat tmp_name(subject_name);

	tmp_name.CheckReplyName();
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckReplySubjectName(const std::string &subject_name)
{
	CheckReplySubjectName(subject_name.c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
void SubjectNameFlat::CheckReplySubjectName(
	const std::ostringstream &subject_name)
{
	CheckReplySubjectName(subject_name.str().c_str());
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream &o_str, const SubjectNameFlat &datum)
{
	char subject_name[MaxSubjectSize + 1];

	o_str <<
		datum.ToString(subject_name);

	return(o_str);
}
// ////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool IsPatternSubjectName(const char *subject_name)
{
	return(SubjectNameFlat::IsPatternSubjectName(subject_name));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool IsPatternSubjectName(const std::string &subject_name)
{
	return(SubjectNameFlat::IsPatternSubjectName(subject_name));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool IsPatternSubjectName(const std::ostringstream &subject_name)
{
	return(SubjectNameFlat::IsPatternSubjectName(subject_name));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool IsFullNameSubjectName(const char *subject_name)
{
	return(SubjectNameFlat::IsFullNameSubjectName(subject_name));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool IsFullNameSubjectName(const std::string &subject_name)
{
	return(SubjectNameFlat::IsFullNameSubjectName(subject_name));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
bool IsFullNameSubjectName(const std::ostringstream &subject_name)
{
	return(SubjectNameFlat::IsFullNameSubjectName(subject_name));
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void CheckPatternSubjectName(const char *subject_name)
{
	SubjectNameFlat::CheckPatternSubjectName(subject_name);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void CheckPatternSubjectName(const std::string &subject_name)
{
	SubjectNameFlat::CheckPatternSubjectName(subject_name);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void CheckPatternSubjectName(const std::ostringstream &subject_name)
{
	SubjectNameFlat::CheckPatternSubjectName(subject_name);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void CheckFullNameSubjectName(const char *subject_name)
{
	SubjectNameFlat::CheckFullNameSubjectName(subject_name);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void CheckFullNameSubjectName(const std::string &subject_name)
{
	SubjectNameFlat::CheckFullNameSubjectName(subject_name);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void CheckFullNameSubjectName(const std::ostringstream &subject_name)
{
	SubjectNameFlat::CheckFullNameSubjectName(subject_name);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void CheckReplySubjectName(const char *subject_name)
{
	SubjectNameFlat::CheckReplySubjectName(subject_name);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void CheckReplySubjectName(const std::string &subject_name)
{
	SubjectNameFlat::CheckReplySubjectName(subject_name);
}
//	////////////////////////////////////////////////////////////////////////////

//	////////////////////////////////////////////////////////////////////////////
void CheckReplySubjectName(const std::ostringstream &subject_name)
{
	SubjectNameFlat::CheckReplySubjectName(subject_name);
}
//	////////////////////////////////////////////////////////////////////////////

} // namespace RvUtilX

} // namespace MLB

#ifdef TEST_MAIN

using namespace MLB::RvUtilX;

// ////////////////////////////////////////////////////////////////////////////
//	CODE NOTE: This TEST_MAIN logic remains to be implemented.
int main(int argc, char **argv)
{
	int return_code = EXIT_SUCCESS;

	try {
		int count_1;
		for (count_1 = 1; count_1 < argc; ++count_1) {
			try {
				std::cout << "[" << argv[count_1] << "]:" << std::flush;
				SubjectNameFlat tmp_flat_1(argv[count_1]);
				SubjectNameFlat tmp_flat_2(tmp_flat_1);
				SubjectNameFlat tmp_flat_3;
				tmp_flat_3 = tmp_flat_1;
				if ((tmp_flat_1 < tmp_flat_2) || (tmp_flat_2 < tmp_flat_1))
					std::cout << " #1 AND #2 ARE NOT EQUAL!!! [" << tmp_flat_1 <<
						"] versus [" << tmp_flat_2 << "]";
				if ((tmp_flat_1 < tmp_flat_3) || (tmp_flat_3 < tmp_flat_1))
					std::cout << " #1 AND #3 ARE NOT EQUAL!!! [" << tmp_flat_1 <<
						"] versus [" << tmp_flat_3 << "]";
			}
			catch (const std::exception &except) {
				std::cout << "ERROR: " << except.what();
				return_code = EXIT_FAILURE;
			}
			std::cout << std::endl;
		}
		if (return_code != EXIT_SUCCESS)
			MLB::Utility::ThrowException("Inconsistencies detected in the "
				"operation of the SubjectNameFlat copy constructors, assignment "
				"operators and/or swap() methods.");
	}
	catch (const std::exception &except) {
		std::cerr << std::endl << "Error(s) in RvUtilX/SubjectNameFlat.cpp' "
			"regression test: " << except.what() << std::endl;
		return_code = EXIT_FAILURE;
	}

	return(return_code);
}
// ////////////////////////////////////////////////////////////////////////////

#endif // #ifdef TEST_MAIN

