#include "pch.h"
#include "hooksdecl.h"

fn_GdipSetTextRenderingHint Orig_GdipSetTextRenderingHint;

Gdiplus::Status WINGDIPAPI My_GdipSetTextRenderingHint(Gdiplus::GpGraphics* graphics, Gdiplus::TextRenderingHint mode)
{
	return Orig_GdipSetTextRenderingHint(graphics, mode);
}
