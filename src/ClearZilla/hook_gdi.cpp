#include "pch.h"
#include "hooksdecl.h"

fn_CreateFontA Orig_CreateFontA;
fn_CreateFontW Orig_CreateFontW;
fn_CreateFontIndirectA Orig_CreateFontIndirectA;
fn_CreateFontIndirectW Orig_CreateFontIndirectW;
fn_CreateFontIndirectExA Orig_CreateFontIndirectExA;
fn_CreateFontIndirectExW Orig_CreateFontIndirectExW;

static BYTE ChangeGdiFontQuality(BYTE iQuality)
{
    switch (iQuality)
    {
    case CLEARTYPE_NATURAL_QUALITY:
    case CLEARTYPE_QUALITY:
        return ANTIALIASED_QUALITY;
    }
    return iQuality;
}

HFONT WINAPI My_CreateFontA(_In_ int cHeight, _In_ int cWidth, _In_ int cEscapement, _In_ int cOrientation, _In_ int cWeight, _In_ DWORD bItalic,
    _In_ DWORD bUnderline, _In_ DWORD bStrikeOut, _In_ DWORD iCharSet, _In_ DWORD iOutPrecision, _In_ DWORD iClipPrecision,
    _In_ DWORD iQuality, _In_ DWORD iPitchAndFamily, _In_opt_ LPCSTR pszFaceName)
{
    return Orig_CreateFontA(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet,
        iOutPrecision, iClipPrecision, ChangeGdiFontQuality((BYTE)iQuality), iPitchAndFamily, pszFaceName);
}

HFONT WINAPI My_CreateFontW(_In_ int cHeight, _In_ int cWidth, _In_ int cEscapement, _In_ int cOrientation, _In_ int cWeight, _In_ DWORD bItalic,
    _In_ DWORD bUnderline, _In_ DWORD bStrikeOut, _In_ DWORD iCharSet, _In_ DWORD iOutPrecision, _In_ DWORD iClipPrecision,
    _In_ DWORD iQuality, _In_ DWORD iPitchAndFamily, _In_opt_ LPCWSTR pszFaceName)
{
    return Orig_CreateFontW(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet,
        iOutPrecision, iClipPrecision, ChangeGdiFontQuality((BYTE)iQuality), iPitchAndFamily, pszFaceName);
}

template<typename T, typename F>
inline HFONT My_CreateFontIndirect_template(CONST T* lplf, F f)
{
    BYTE newQual = ChangeGdiFontQuality(lplf->lfQuality);
    if (newQual != lplf->lfQuality) {
        T localStruct;
        memcpy(&localStruct, lplf, sizeof(localStruct));
        localStruct.lfQuality = newQual;
        return f(&localStruct);
    }
    return f(lplf);
}

HFONT WINAPI My_CreateFontIndirectA(_In_ CONST LOGFONTA* lplf)
{
    return My_CreateFontIndirect_template<LOGFONTA, fn_CreateFontIndirectA>(lplf, Orig_CreateFontIndirectA);
}

HFONT WINAPI My_CreateFontIndirectW(_In_ CONST LOGFONTW* lplf)
{
    return My_CreateFontIndirect_template<LOGFONTW, fn_CreateFontIndirectW>(lplf, Orig_CreateFontIndirectW);
}

template<typename T, typename F>
inline HFONT My_CreateFontIndirectEx_template(CONST T* lplf, F f)
{
    BYTE oldQual = lplf->elfEnumLogfontEx.elfLogFont.lfQuality;
    BYTE newQual = ChangeGdiFontQuality(oldQual);
    if (oldQual != newQual) {
        T localStruct;
        memcpy(&localStruct, lplf, sizeof(localStruct));
        localStruct.elfEnumLogfontEx.elfLogFont.lfQuality = newQual;
        return f(&localStruct);
    }
    return f(lplf);
}

HFONT WINAPI My_CreateFontIndirectExA(_In_ CONST ENUMLOGFONTEXDVA* lplf)
{
    return My_CreateFontIndirectEx_template<ENUMLOGFONTEXDVA, fn_CreateFontIndirectExA>(lplf, Orig_CreateFontIndirectExA);
}

HFONT WINAPI My_CreateFontIndirectExW(_In_ CONST ENUMLOGFONTEXDVW* lplf)
{
    return My_CreateFontIndirectEx_template<ENUMLOGFONTEXDVW, fn_CreateFontIndirectExW>(lplf, Orig_CreateFontIndirectExW);
}
