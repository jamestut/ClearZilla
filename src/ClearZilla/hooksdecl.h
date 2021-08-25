#pragma once

#include "pch.h"
#include "gdip.h"

extern "C" {
    // typedef for the functions
    typedef HFONT(WINAPI* fn_CreateFontA)(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR);
    typedef HFONT(WINAPI* fn_CreateFontW)(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCWSTR);
    typedef HFONT(WINAPI* fn_CreateFontIndirectA)(CONST LOGFONTA*);
    typedef HFONT(WINAPI* fn_CreateFontIndirectW)(CONST LOGFONTW*);
    typedef HFONT(WINAPI* fn_CreateFontIndirectExA)(CONST ENUMLOGFONTEXDVA*);
    typedef HFONT(WINAPI* fn_CreateFontIndirectExW)(CONST ENUMLOGFONTEXDVW*);
    typedef Gdiplus::GpStatus(WINGDIPAPI* fn_GdipSetTextRenderingHint)(Gdiplus::GpGraphics*, Gdiplus::TextRenderingHint);

    // original function pointers
    extern fn_CreateFontA Orig_CreateFontA;
    extern fn_CreateFontW Orig_CreateFontW;
    extern fn_CreateFontIndirectA Orig_CreateFontIndirectA;
    extern fn_CreateFontIndirectW Orig_CreateFontIndirectW;
    extern fn_CreateFontIndirectExA Orig_CreateFontIndirectExA;
    extern fn_CreateFontIndirectExW Orig_CreateFontIndirectExW;
    extern fn_GdipSetTextRenderingHint Orig_GdipSetTextRenderingHint;

    // detour functions
    HFONT WINAPI My_CreateFontA(_In_ int cHeight, _In_ int cWidth, _In_ int cEscapement, _In_ int cOrientation, _In_ int cWeight, _In_ DWORD bItalic,
        _In_ DWORD bUnderline, _In_ DWORD bStrikeOut, _In_ DWORD iCharSet, _In_ DWORD iOutPrecision, _In_ DWORD iClipPrecision,
        _In_ DWORD iQuality, _In_ DWORD iPitchAndFamily, _In_opt_ LPCSTR pszFaceName);

    HFONT WINAPI My_CreateFontW(_In_ int cHeight, _In_ int cWidth, _In_ int cEscapement, _In_ int cOrientation, _In_ int cWeight, _In_ DWORD bItalic,
        _In_ DWORD bUnderline, _In_ DWORD bStrikeOut, _In_ DWORD iCharSet, _In_ DWORD iOutPrecision, _In_ DWORD iClipPrecision,
        _In_ DWORD iQuality, _In_ DWORD iPitchAndFamily, _In_opt_ LPCWSTR pszFaceName);

    HFONT WINAPI My_CreateFontIndirectA(_In_ CONST LOGFONTA* lplf);

    HFONT WINAPI My_CreateFontIndirectW(_In_ CONST LOGFONTW* lplf);

    HFONT WINAPI My_CreateFontIndirectExA(_In_ CONST ENUMLOGFONTEXDVA*);

    HFONT WINAPI My_CreateFontIndirectExW(_In_ CONST ENUMLOGFONTEXDVW*);

    Gdiplus::Status WINGDIPAPI My_GdipSetTextRenderingHint(Gdiplus::GpGraphics* graphics, Gdiplus::TextRenderingHint mode);
}