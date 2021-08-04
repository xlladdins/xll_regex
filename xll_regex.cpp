// xll_regex.cpp - regular expressions
#include <regex>
#include "xll_regex.h"

using namespace xll;

using xchar = traits<XLOPERX>::xchar;
using xcstr = traits<XLOPERX>::xcstr;

#define REGEX_FLAG_TYPE(a,b,c) XLL_CONST(LONG, REGEX_SYNTAX_ ## a, std::regex_constants:: ## b, c, CATEGORY, REGEX_CONSTANTS_TOPIC)
REGEX_CONSTANTS_SYNTAX(REGEX_FLAG_TYPE)
#undef REGEX_FLAG_TYPE

#define REGEX_MATCH_TYPE(a,b,c) XLL_CONST(LONG, REGEX_MATCH_ ## a, std::regex_constants:: ## b, c, CATEGORY, REGEX_CONSTANTS_TOPIC)
REGEX_CONSTANTS_MATCH(REGEX_MATCH_TYPE)
#undef REGEX_MATCH_TYPE

AddIn xai_regex_(
	Function(XLL_HANDLEX, "xll_regex_", "\\REGEX")
	.Arguments({
		Arg(XLL_CSTRING, "regex", "is a regular expression."),
		Arg(XLL_LONG, "flags", "are optional flags from REGEX_FLAG_*.")
		})
		.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to a compiled regular expression.")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/standard-library/basic-regex-class")
	.Documentation(R"xyzyx()xyzyx")
);
HANDLEX WINAPI xll_regex_(xcstr re, std::regex_constants::syntax_option_type flags)
{
#pragma XLLEXPORT
	HANDLEX h = INVALID_HANDLEX;

	handle<std::basic_regex<xchar>> re_(new std::basic_regex<xchar>(re, flags));
	if (re_) {
		h = re_.get();
	}

	return h;
}

AddIn xai_regex_search(
	Function(XLL_LPOPER, "xll_regex_search", "REGEX.SEARCH")
	.Arguments({
		Arg(XLL_LPOPER, "regex", "is a regular expression or handle."),
		Arg(XLL_CSTRING, "string", "is a string."),
		Arg(XLL_LONG, "flags", "are optional flags from REGEX_MATCH_*")
		})
	.Category("Regex")
	.FunctionHelp("Search for a regular expression match.")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/standard-library/regex-functions#regex_search")
	.Documentation(R"(
Search <code>string</code> for matching results of
regular expression <code>regex</code>. Return <code>FALSE</code>
if there is no match or a one column array of all sub matches.
)")
);
LPOPER WINAPI xll_regex_search(const LPOPER pre, xcstr str, std::regex_constants::match_flag_type flags)
{
#pragma XLLEXPORT
	static OPER o;

	try {
		o = false;

		std::match_results<xcstr> mr;
		if (pre->is_num()) {
			handle<std::basic_regex<xchar>> re_(pre->as_num());
			if (re_) {
				o = std::regex_search(str, mr, *re_, flags);
			}
		}
		else if (pre->is_str()) {
			std::basic_regex<xchar> re(pre->val.str + 1, pre->val.str[0]);
			o = std::regex_search(str, mr, re, flags);
		}
		else {
			o = ErrValue;
		}

		if (o) {
			o = Nil;
			for (const auto& m : mr) {
				o.push_back(OPER(m.first, (xchar)(m.second - m.first)));
			}
		}

	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = ErrNA;
	}

	return &o;
}

#ifdef _DEBUG

#define XLL_REGEX_TEST(X) \
	X(_T(".*"), _T("abc"), _T("abc")) \
	X(_T(".(b)."), _T("abc"), _T("abc"), _T("b")) \

int xll_regex_test()
{
	try {
#define RE_TEST(a, b, ...) { OPER _a(a); ensure(*xll_regex_search(&_a, b, std::regex_constants::match_default) == OPER::make(__VA_ARGS__)); }
		XLL_REGEX_TEST(RE_TEST)
#undef RE_TEST
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return FALSE;
	}

	return TRUE;
}
Auto<OpenAfter> xaoa_regex_test(xll_regex_test);

#endif // _DEBUG