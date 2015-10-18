#pragma once
#include "TinyVisual.h"

namespace TinyUI
{
	namespace Windowless
	{
		/// <summary>
		/// 布局器接口
		/// </summary>
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
		/// <summary>
		/// 容器类布局器
		/// </summary>
		class TinyLayout : public ILayout
		{
		public:
			virtual void Install(TinyVisual* host) override;
			virtual void Uninstall(TinyVisual* host) override;
			virtual void Layout() override;
			virtual void OnAdding(TinyVisual* host, TinyVisual* view) override;
			virtual void OnAdd(TinyVisual* host, TinyVisual* view) override;
			virtual void OnRemoving(TinyVisual* host, TinyVisual* view) override;
			virtual void OnRemove(TinyVisual* host, TinyVisual* view) override;
		protected:
			TinyArray<TinyVisual*> m_visuals;
		};
	}
}



