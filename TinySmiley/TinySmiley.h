#pragma once
//COM´´½¨²Î http://www.codeproject.com/Articles/8679/Building-a-LOCAL-COM-Server-and-Client-A-Step-by-S
//http://www.cppblog.com/mzty/archive/2007/05/28/25007.html
#include "smiley_h.h"

namespace Tiny
{
	class TinySmileySource : public ISmileySource
	{
	public:
		virtual HRESULT STDMETHODCALLTYPE LoadStream(
			/* [in] */ LPSTREAM pStm) = 0;

		virtual HRESULT STDMETHODCALLTYPE LoadFile(
			/* [in] */ LPCSTR pszFilePath) = 0;

		virtual HRESULT STDMETHODCALLTYPE SaveAs(
			/* [in] */ LPSTREAM pStm) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetFile(
			/* [out] */ BSTR *bstrFile) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetFrameCount(
			/* [out] */ int *pFrameCount) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetFrameDelay(
			/* [in] */ int iFrame,
			/* [out] */ int *pFrameDelay) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetSize(
			/* [out] */ LPSIZE pSize) = 0;

		virtual HRESULT STDMETHODCALLTYPE Draw(
			/* [in] */ HDC hdc,
			/* [in] */ LPCRECT pRect,
			/* [in] */ int iFrame) = 0;

	};
}



