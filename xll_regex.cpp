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