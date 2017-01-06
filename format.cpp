#include "narf/format.h"

// From http://stackoverflow.com/a/8098080
std::string narf::util::format(const std::string fmt_str, va_list argp) {
	int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
	std::string str;
	std::unique_ptr<char[]> formatted;
	va_list ap;
	while(1) {
		formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
		strcpy(&formatted[0], fmt_str.c_str());
		va_copy(ap, argp);
		final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
		va_end(ap);
		if (final_n < 0 || final_n >= n)
			n += abs(final_n - n + 1);
		else
			break;
	}
	return std::string(formatted.get());
}

std::string narf::util::format(const std::string fmt_str, ...) {
	va_list argp;
	va_start(argp, fmt_str);
	auto ret = narf::util::format(fmt_str, argp);
	va_end(argp);
	return ret;
}
