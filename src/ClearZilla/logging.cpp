#include "logging.h"
#include "pch.h"
#include <varargs.h>
#include <stdio.h>

void dprintf(const char* format, ...)
{
	static char dprintf_msg[66000];
	va_list args;
	va_start(args, format);
	*dprintf_msg = 0;
	auto len = vsnprintf_s(dprintf_msg, sizeof(dprintf_msg), format, args);
	for (; len > 1; len--)
	{
		auto& ch = dprintf_msg[len - 1];
		if (ch == '\r' || ch == '\n')
			ch = '\0';
		else
			break;
	}
	OutputDebugStringA(dprintf_msg);
}