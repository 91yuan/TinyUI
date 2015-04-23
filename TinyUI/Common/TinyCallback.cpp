#include "../stdafx.h"
#include "TinyObject.h"
#include "TinyCallback.h"

namespace TinyUI
{
	bool CallbackBase::is_null() const
	{
		return invoker_storage_.Ptr() == NULL;
	}

	void CallbackBase::Reset()
	{
		invoker_storage_ = NULL;
		polymorphic_invoke_ = NULL;
	}

	bool CallbackBase::Equals(const CallbackBase& other) const
	{
		return invoker_storage_.Ptr() == other.invoker_storage_.Ptr() &&
			polymorphic_invoke_ == other.polymorphic_invoke_;
	}

	CallbackBase::CallbackBase(InvokeFuncStorage polymorphic_invoke,
		TinyScopedReferencePtr<InvokerStorageBase>* invoker_storage)
		: polymorphic_invoke_(polymorphic_invoke)
	{
		if (invoker_storage)
		{
			invoker_storage_.Swap(*invoker_storage);
		}
	}

	CallbackBase::~CallbackBase() {}
};
