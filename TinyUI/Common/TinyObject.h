#pragma once
#include "TinyCommon.h"

namespace TinyUI
{
#define DECLARE_DYNAMIC(class_name) \
public: \
	virtual LPCTSTR class_name::GetClassName() const \
	{ \
	return #class_name; \
};
	/// <summary>
	/// �������,���������͸�ֵ
	/// </summary>
	class TinyObject
	{
	protected:
		TinyObject();
	public:
		virtual ~TinyObject();
		virtual LPCTSTR GetClassName() const = 0;
		DISALLOW_COPY_AND_ASSIGN(TinyObject);
	};
};

