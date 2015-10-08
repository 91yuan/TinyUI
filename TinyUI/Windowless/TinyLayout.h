#pragma once
#include "TinyVisual.h"

namespace TinyUI
{
	namespace Windowless
	{
		class ILayout
		{
		public:
			virtual void Install(TinyVisual* host) = 0;
			virtual void Uninstall(TinyVisual* host) = 0;
			virtual void Layout() = 0;
			virtual void OnAdding(TinyVisual* host, TinyVisual* view)= 0;
			virtual void OnAdd(TinyVisual* host, TinyVisual* view) = 0;
			virtual void OnRemoving(TinyVisual* host, TinyVisual* view) = 0;
			virtual void OnRemove(TinyVisual* host, TinyVisual* view) = 0;
		};
	}
}



