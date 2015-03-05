#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
	/// <summary>
	/// 树节点
	/// </summary>
	template<class T>
	class TinyTreeNode
	{
	public:
		TinyTreeNode();
		TinyTreeNode(const T&);
		~TinyTreeNode();
	};
	/// <summary>
	/// 自绘树控件
	/// </summary>
	template<class T>
	class TinyTreeBox
	{

	};
};

