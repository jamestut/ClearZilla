#pragma once

void dprintf(const char* format, ...);

#define dlogp(fmt, ...) dprintf("[ClearZilla] " __FUNCTION__ "(" fmt ")\n", __VA_ARGS__)
