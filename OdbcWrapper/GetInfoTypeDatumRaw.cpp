// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	ODBC Wrapper Library Module
// ////////////////////////////////////////////////////////////////////////////
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implementation of the GetInfoTypeDatumRaw class.

	Revision History	:	2001-10-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
//	Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <OdbcWrapper/OdbcWrapper.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace OdbcWrapper {

// ////////////////////////////////////////////////////////////////////////////
#define ODBCWRAPPER_GETINFO_TYPE(info_type, info_name, data_type, is_str,	\
	is_small, is_mask, is_flag, is_handle, is_2way_)								\
	{	info_type, info_name, #data_type, is_str, is_small, is_mask, is_flag,\
		is_handle, is_2way_	}

#define ODBCWRAPPER_GETINFO_TYPE_String(info_type)									\
	ODBCWRAPPER_GETINFO_TYPE(info_type, #info_type, std::string,  true,  false, false, false, false, false)
#define ODBCWRAPPER_GETINFO_TYPE_USmallInt(info_type)								\
	ODBCWRAPPER_GETINFO_TYPE(info_type, #info_type, SQLUSMALLINT, false, true,  false, false, false, false)
#define ODBCWRAPPER_GETINFO_TYPE_Bitmask(info_type)								\
	ODBCWRAPPER_GETINFO_TYPE(info_type, #info_type, SQLUINTEGER,  false, false, true, false,  false, false)
#define ODBCWRAPPER_GETINFO_TYPE_Flag(info_type)									\
	ODBCWRAPPER_GETINFO_TYPE(info_type, #info_type, SQLUINTEGER,  false, false, false, true,  false, false)
#define ODBCWRAPPER_GETINFO_TYPE_Value(info_type)									\
	ODBCWRAPPER_GETINFO_TYPE(info_type, #info_type, SQLUINTEGER,  false, false, false, false, false, false)
#define ODBCWRAPPER_GETINFO_TYPE_Handle(info_type)									\
	ODBCWRAPPER_GETINFO_TYPE(info_type, #info_type, SQLUINTEGER,  false, false, false, false,  true, false)
#define ODBCWRAPPER_GETINFO_TYPE_Handle2Way(info_type)							\
	ODBCWRAPPER_GETINFO_TYPE(info_type, #info_type, SQLUINTEGER,  false, false, false, false,  true,  true)
// ////////////////////////////////////////////////////////////////////////////

namespace {
// ////////////////////////////////////////////////////////////////////////////
const GetInfoTypeDatumRaw GetInfoTypeRawList[] = {
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_ACCESSIBLE_PROCEDURES),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_ACCESSIBLE_TABLES),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_ACTIVE_ENVIRONMENTS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_ACTIVE_ENVIRONMENTS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_ALTER_DOMAIN),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_ALTER_TABLE),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_ASYNC_MODE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_BATCH_ROW_COUNT),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_BATCH_SUPPORT),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_BOOKMARK_PERSISTENCE),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_CATALOG_LOCATION),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_CATALOG_NAME),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_CATALOG_NAME_SEPARATOR),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_CATALOG_TERM),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CATALOG_USAGE),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_COLLATION_SEQ),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_COLUMN_ALIAS),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_CONCAT_NULL_BEHAVIOR),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_BIGINT),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_BINARY),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_BIT),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_CHAR),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_GUID),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_DATE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_DECIMAL),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_DOUBLE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_FLOAT),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_INTEGER),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_INTERVAL_YEAR_MONTH),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_INTERVAL_DAY_TIME),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_LONGVARBINARY),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_LONGVARCHAR),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_NUMERIC),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_REAL),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_SMALLINT),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_TIME),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_TIMESTAMP),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_TINYINT),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_VARBINARY),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_VARCHAR),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CONVERT_FUNCTIONS),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_CORRELATION_NAME),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CREATE_ASSERTION),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CREATE_CHARACTER_SET),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CREATE_COLLATION),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CREATE_DOMAIN),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CREATE_SCHEMA),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CREATE_TABLE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CREATE_TRANSLATION),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_CREATE_VIEW),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_CURSOR_COMMIT_BEHAVIOR),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_CURSOR_ROLLBACK_BEHAVIOR),
#ifdef SQL_CURSOR_ROLLBACK_SQL_CURSOR_SENSITIVITY
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_CURSOR_ROLLBACK_SQL_CURSOR_SENSITIVITY),
#endif // #ifdef SQL_CURSOR_ROLLBACK_SQL_CURSOR_SENSITIVITY
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_DATA_SOURCE_NAME),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_DATA_SOURCE_READ_ONLY),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_DATABASE_NAME),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DATETIME_LITERALS),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_DBMS_NAME),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_DBMS_VER),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_DDL_INDEX),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_DEFAULT_TXN_ISOLATION),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_DESCRIBE_PARAMETER),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_DM_VER),
	ODBCWRAPPER_GETINFO_TYPE_Handle(SQL_DRIVER_HDBC),
	ODBCWRAPPER_GETINFO_TYPE_Handle(SQL_DRIVER_HENV),
	ODBCWRAPPER_GETINFO_TYPE_Handle2Way(SQL_DRIVER_HDESC),
	ODBCWRAPPER_GETINFO_TYPE_Handle(SQL_DRIVER_HLIB),
	ODBCWRAPPER_GETINFO_TYPE_Handle2Way(SQL_DRIVER_HSTMT),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_DRIVER_NAME),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_DRIVER_ODBC_VER),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_DRIVER_VER),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DROP_ASSERTION),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DROP_CHARACTER_SET),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DROP_COLLATION),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DROP_DOMAIN),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DROP_SCHEMA),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DROP_TABLE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DROP_TRANSLATION),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DROP_VIEW),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DYNAMIC_CURSOR_ATTRIBUTES1),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_DYNAMIC_CURSOR_ATTRIBUTES2),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_EXPRESSIONS_IN_ORDERBY),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_GETDATA_EXTENSIONS),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_GROUP_BY),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_IDENTIFIER_CASE),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_IDENTIFIER_QUOTE_CHAR),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_INDEX_KEYWORDS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_INFO_SCHEMA_VIEWS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_INSERT_STATEMENT),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_INTEGRITY),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_KEYSET_CURSOR_ATTRIBUTES1),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_KEYSET_CURSOR_ATTRIBUTES2),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_KEYWORDS),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_LIKE_ESCAPE_CLAUSE),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_MAX_ASYNC_CONCURRENT_STATEMENTS),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_MAX_BINARY_LITERAL_LEN),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_CATALOG_NAME_LEN),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_MAX_CHAR_LITERAL_LEN),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_COLUMN_NAME_LEN),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_COLUMNS_IN_GROUP_BY),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_COLUMNS_IN_INDEX),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_COLUMNS_IN_ORDER_BY),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_COLUMNS_IN_SELECT),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_COLUMNS_IN_TABLE),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_CONCURRENT_ACTIVITIES),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_CURSOR_NAME_LEN),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_DRIVER_CONNECTIONS),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_IDENTIFIER_LEN),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_MAX_INDEX_SIZE),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_PROCEDURE_NAME_LEN),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_MAX_ROW_SIZE),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_MAX_ROW_SIZE_INCLUDES_LONG),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_SCHEMA_NAME_LEN),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_MAX_STATEMENT_LEN),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_TABLE_NAME_LEN),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_TABLES_IN_SELECT),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_MAX_USER_NAME_LEN),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_MULT_RESULT_SETS),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_MULTIPLE_ACTIVE_TXN),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_NEED_LONG_DATA_LEN),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_NON_NULLABLE_COLUMNS),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_NULL_COLLATION),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_NUMERIC_FUNCTIONS),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_ODBC_INTERFACE_CONFORMANCE),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_ODBC_VER),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_OJ_CAPABILITIES),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_ORDER_BY_COLUMNS_IN_SELECT),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_PARAM_ARRAY_ROW_COUNTS),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_PARAM_ARRAY_SELECTS),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_PROCEDURE_TERM),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_PROCEDURES),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_POS_OPERATIONS),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_QUOTED_IDENTIFIER_CASE),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_ROW_UPDATES),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_SCHEMA_TERM),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SCHEMA_USAGE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SCROLL_OPTIONS),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_SEARCH_PATTERN_ESCAPE),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_SERVER_NAME),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_SPECIAL_CHARACTERS),
	ODBCWRAPPER_GETINFO_TYPE_Value(SQL_SQL_CONFORMANCE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_DATETIME_FUNCTIONS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_FOREIGN_KEY_DELETE_RULE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_FOREIGN_KEY_UPDATE_RULE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_GRANT),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_NUMERIC_VALUE_FUNCTIONS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_PREDICATES),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_RELATIONAL_JOIN_OPERATORS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_REVOKE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_ROW_VALUE_CONSTRUCTOR),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_STRING_FUNCTIONS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SQL92_VALUE_EXPRESSIONS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_STANDARD_CLI_CONFORMANCE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_STATIC_CURSOR_ATTRIBUTES1),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_STATIC_CURSOR_ATTRIBUTES2),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_STRING_FUNCTIONS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SUBQUERIES),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_SYSTEM_FUNCTIONS),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_TABLE_TERM),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_TIMEDATE_ADD_INTERVALS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_TIMEDATE_DIFF_INTERVALS),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_TIMEDATE_FUNCTIONS),
	ODBCWRAPPER_GETINFO_TYPE_USmallInt(SQL_TXN_CAPABLE),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_TXN_ISOLATION_OPTION),
	ODBCWRAPPER_GETINFO_TYPE_Bitmask(SQL_UNION),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_USER_NAME),
	ODBCWRAPPER_GETINFO_TYPE_String(SQL_XOPEN_CLI_YEAR)
};
const unsigned int          GetInfoTypeRawCount  =
	sizeof(GetInfoTypeRawList) / sizeof(GetInfoTypeRawList[0]);
// ////////////////////////////////////////////////////////////////////////////
} // Anonymous namespace

// ////////////////////////////////////////////////////////////////////////////
const GetInfoTypeDatumRaw *GetInfoTypeDatumRaw::GetInfoTypeDatumPtr(
	SQLUSMALLINT info_type)
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < GetInfoTypeRawCount; ++count_1) {
		if (info_type == GetInfoTypeRawList[count_1].info_type_)
			return(GetInfoTypeRawList + count_1);
	}

	return(NULL);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
const GetInfoTypeDatumRaw *GetInfoTypeDatumRaw::GetInfoTypeDatumPtrChecked(
	SQLUSMALLINT info_type)
{
	const GetInfoTypeDatumRaw *found_ptr = GetInfoTypeDatumPtr(info_type);

	if (found_ptr == NULL)
		throw OdbcException("Unable to locate the '::SQLGetInfo()' information "
			"type descriptor entry for " + MLB::Utility::AnyToString(info_type) +
			".");

	return(found_ptr);
}
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
unsigned int GetInfoTypeDatumRaw::GetInfoTypeRawData(
	const GetInfoTypeDatumRaw *&list_ptr)
{
	list_ptr = GetInfoTypeRawList;

	return(GetInfoTypeRawCount);
}
// ////////////////////////////////////////////////////////////////////////////

} // namespace OdbcWrapper

} // namespace MLB

