#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGDI.h"
#include "TinyVisual.h"

namespace TinyUI
{
	namespace Windowless
	{
		/// <summary>
		/// ¹ö¶¯Ìõ
		/// </summary>
		class TinyScroll : public TinyVisual
		{
			DECLARE_DYNAMIC(TinyScroll);
			DISALLOW_COPY_AND_ASSIGN(TinyScroll);
		public:
			TinyScroll();
			virtual ~TinyScroll();
		};
	}
}



