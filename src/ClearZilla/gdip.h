#pragma once

#include "pch.h"

extern "C" {
	Gdiplus::GpStatus WINGDIPAPI
		GdipSetTextRenderingHint(Gdiplus::GpGraphics* graphics, Gdiplus::TextRenderingHint mode);
}