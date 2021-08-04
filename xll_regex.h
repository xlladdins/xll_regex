// xll_regex.h - <regex>
#pragma once

#include "xll/xll/xll.h"

#ifndef CATEGORY
#define CATEGORY "Regex"
#endif

#define REGEX_CONSTANTS_TOPIC "https://docs.microsoft.com/en-us/cpp/standard-library/regex-constants-class"

#define REGEX_CONSTANTS_SYNTAX(X) \
X(AWK, awk, "compile as awk") \
X(BASIC, basic, "compile as BRE") \
X(ECMASCRIPT, ECMAScript, "compile as ECMAScript") \
X(EGREP, egrep, "compile as egrep") \
X(EXTENDED, extended, "compile as ERE") \
X(GREP, grep, "compile as grep") \
X(ICASE, icase, "make matches case") \
X(NOSUBS, nosubs, "the implementaton need not keep track of the contents of capture groups") \
X(OPTIMIZE, optimize, "the implementation should emphasize speed of matching rather than speed of regular expression compilation") \

#define REGEX_CONSTANTS_MATCH(X) \
X(FORMAT_DEFAULT, format_default, "use ECMAScript format rules") \
X(FORMAT_FIRST_ONLY, format_first_only, "do not search for matches after the first one") \
X(FORMAT_NO_COPY, format_no_copy, "do not copy text that does not match the regular expression") \
X(FORMAT_SED, format_sed, "use sed format rules") \
X(MATCH_ANY, match_any, "if more than one match is possible any match is acceptable") \
X(MATCH_CONTINUOUS, match_continuous, "do not search for matches other than at the beginning of the target sequence") \
X(MATCH_DEFAULT, match_default, " ") \
X(MATCH_NOT_BOL, match_not_bol, "do not treat the first position in the target sequence as the beginning of a line") \
X(MATCH_NOT_BOW, match_not_bow, "do not treat the first position in the target sequence as the beginning of a word") \
X(MATCH_NOT_EOL, match_not_eol, "do not treat the past the end position in the target sequence as the end of a line") \
X(MATCH_NOT_EOW, match_not_eow, "do not treat the past the end position in the target sequence as the end of a word") \
X(MATCH_NOT_NULL, match_not_null, "do not treat an empty subsequence as a match") \
X(MATCH_PREV_AVAIL, match_prev_avail, "first is a valid iterator; ignore match_not_bol and match_not_bow if set") \

// REGEX_CONSTANTS_ERROR