// xll_regex.cpp - regular expressions
#include <regex>
#include "xll_regex.h"

using namespace xll;

using xchar = traits<XLOPERX>::xchar;
using xcstr = traits<XLOPERX>::xcstr;

AddIn xai_regex_search(
	Function(XLL_LPOPER, "xll_regex_search", "REGEX.SEARCH")
	.Arguments({
		Arg(XLL_CSTRING, "re", "is a regular expression."),
		Arg(XLL_CSTRING, "string", "is a string."),
		})
	.Category("Regex")
	.FunctionHelp("")
);
LPOPER WINAPI xll_regex_search(xcstr regex, xcstr str)
{
#pragma XLLEXPORT
	static OPER o;

	try {
		o = ErrNA;

		std::match_results<xcstr> mr;
		std::basic_regex<xchar> re(regex);
		if (std::regex_search(str, mr, re)) {
			o = Nil;
			for (const auto& m : mr) {
				o.push_back(OPER(m.first, (xchar)(m.second - m.first)));
			}
		}

	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return &o;
}

#ifdef _DEBUG

#define XLL_REGEX_TEST(X) \
	X(_T(".*"), _T("abc"), _T("abc")) \

int xll_regex_test()
{
	try {
#define RE_TEST(a, b, ...) ensure(*xll_regex_search(a, b) == OPER::make(__VA_ARGS__));
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