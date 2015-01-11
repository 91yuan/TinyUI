#pragma once
#include "TinyGraphics.h"

namespace TinyUI
{
#define CLR_TO_RGBA(c) c | 0xFF000000
#define RGB_TO_RGBA(r, g, b) CLR_TO_RGBA(RGB(r, g, b))
#define _RGBA(r, g, b, a) RGB(r, g, b) | (a << 24)
	/// <summary>
	/// Render–Èª˘¿‡
	/// </summary>
	class TinyGraphicsRender
	{
	public:
		TinyGraphicsRender(TinyDC& dc);
		~TinyGraphicsRender();

	/*	BOOL DrawShadow(TinyRectangle rect,
			INT nDepth,
			INT iMinBrightness = 100,
			INT iMaxBrightness = 50,
			TinyBitmap* pBmpSaveBottom = NULL,
			TinyBitmap* pBmpSaveRight = NULL,
			COLORREF clrBase = (COLORREF)-1,
			BOOL bRightShadow = TRUE);

		BOOL HighlightRect(TinyRectangle rect,
			int nPercentage = -1,
			COLORREF clrTransparent =
			(COLORREF)-1,
			int nTolerance = 0,
			COLORREF clrBlend = (COLORREF)-1);

		void FillGradient(TinyRectangle rect,
			COLORREF colorStart,
			COLORREF colorFinish,
			BOOL bHorz = TRUE,
			int nStartFlatPercentage = 0,
			int nEndFlatPercentage = 0);

		void FillGradient2(TinyRectangle rect,
			COLORREF colorStart,
			COLORREF colorFinish,
			int nAngle = 0);

		void Fill4ColorsGradient(TinyRectangle rect,
			COLORREF colorStart1,
			COLORREF colorFinish1,
			COLORREF colorStart2,
			COLORREF colorFinish2,
			BOOL bHorz = TRUE,
			int nPercentage = 50);

		BOOL GrayRect(TinyRectangle rect,
			int nPercentage = -1,
			COLORREF clrTransparent =
			(COLORREF)-1,
			COLORREF clrDisabled =
			(COLORREF)-1);

		void MirrorRect(TinyRectangle rect, BOOL bHorz = TRUE);

		BOOL DrawGradientRing(TinyRectangle rect,
			COLORREF colorStart, COLORREF colorFinish,
			COLORREF colorBorder,
			int nAngle,
			int nWidth,
			COLORREF clrFace = (COLORREF)-1);

		void DrawLine(int x1, int y1, int x2, int y2, COLORREF clrLine, int nPenStyle = PS_SOLID);
		void DrawLineA(double x1, double y1, double x2, double y2, COLORREF clrLine, int nPenStyle = PS_SOLID);
		void DrawEllipse(const TinyRectangle& rect, COLORREF clrFill, COLORREF clrLine, int nPenStyle = PS_SOLID);
		void DrawRect(const TinyRectangle& rect, COLORREF clrFill, COLORREF clrLine);
		void DrawArc(const TinyRectangle& rect, double dblStartAngle, double dblFinishAngle, BOOL bIsClockwise, COLORREF clrLine, int nPenStyle = PS_SOLID);
		void DrawFocusRect(const TinyRectangle& rectFocus);

		static void DrawAlpha(TinyDC* pDstDC, const TinyRectangle& rectDst, TinyDC* pSrcDC, const TinyRectangle& rectSrc, BYTE nOpacity = 255);

		void FillAlpha(const TinyRectangle& rect, BYTE bValue = 255);
		void DrawRotated(TinyRectangle rectDest, TinyDC& dcSrc, BOOL bClockWise);

		static COLORREF PixelAlpha(COLORREF srcPixel, int percent);
		static COLORREF PixelAlpha(COLORREF srcPixel, double percentR, double percentG, double percentB);
		static COLORREF PixelAlpha(COLORREF srcPixel, COLORREF dstPixel, int percent);
		static void SetAlphaPixel(COLORREF* pBits, TinyRectangle rect, int x, int y, int percent, int iShadowSize, COLORREF clrBase = (COLORREF)-1, BOOL bIsRight = TRUE);
		static void SetPixel(COLORREF* pBits, int cx, int cy, int x, int y, COLORREF color);

		static double HuetoRGB(double m1, double m2, double h);
		static BYTE HueToRGB(float rm1, float rm2, float rh);
		static COLORREF HLStoRGB_ONE(double H, double L, double S);
		static COLORREF HLStoRGB_TWO(double H, double L, double S);
		static void RGBtoHSL(COLORREF rgb, double *H, double *S, double *L);
		static double MakeHue_ONE(double H);
		static double MakeHue_TWO(double H);

		static BOOL IsDarkColor(COLORREF clr);
		static BOOL IsLightColor(COLORREF clr);
		static BOOL IsPaleColor(COLORREF clr);
		static COLORREF ColorMakeLighter(COLORREF clr, double dblRatio = .1);
		static COLORREF ColorMakeDarker(COLORREF clr, double dblRatio = .1);
		static COLORREF ColorMakePale(COLORREF clr, double dblLum = .97);
		static COLORREF GetInterlaceColor(COLORREF clr);

		static void RGBtoHSV(COLORREF rgb, double *H, double *S, double *V);
		static COLORREF HSVtoRGB(double H, double S, double V);

		static COLORREF SmartMixColors(COLORREF color1, COLORREF color2, double dblLumRatio = 1., int k1 = 1, int k2 = 1);

		static COLORREF MixColors(COLORREF clr1, COLORREF clr2, double dblRatio);

		static HBITMAP CreateBitmap_24(const TinySize& size, void** pBits);
		static HBITMAP CreateBitmap_24(HBITMAP bitmap);

		static HBITMAP CreateBitmap_32(const TinySize& size, void** pBits);
		static HBITMAP CreateBitmap_32(HBITMAP bitmap, COLORREF clrTransparent = -1);

		static HBITMAP PrepareShadowMask(int nDepth,
			COLORREF clrBase,
			int iMinBrightness = 0,
			int iMaxBrightness = 100,
			double dblSmooth = 1.0,
			double dblDarkRatio = 0.25);

		static void DrawGlassButtonBorder(TinyDC& dc, TinyRectangle rect,COLORREF clrGlow1, COLORREF clrGlow2, COLORREF clrDark1, COLORREF clrDark2);
		static void DrawGlassButtonBackround(TinyDC& dc, TinyRectangle rect,COLORREF clrGlow1, COLORREF clrGlow2, COLORREF clrDark1, COLORREF clrDark2);
		static void FillAlpha(const TinyRectangle& rect, HBITMAP hBmp, BYTE bValue);
		static void FillTransparentAlpha(const TinyRectangle& rect, HBITMAP hBmp, COLORREF clrTransparent);*/
	private:
		TinyDC&	m_dc;
	};
}


