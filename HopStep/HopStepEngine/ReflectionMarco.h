#pragma once
#include "TypeGenerator.h"

#define DECLARE_TYPEHASH \
	size_t GetTypeHash() const \
	{ \
		static size_t UniquePointer; \
		return reinterpret_cast<size_t>(&UniquePointer); \
	}							

#define DECLARE_CLASS_BODY(Class, ...) \
	DECLARE_TYPEHASH \
	friend class HType; \
	using This = Class; \
	static class HType* StaticClass(); \
	inline static constexpr std::wstring_view FriendlyName = L ## #Class; \

#define IMPLEMENT_CLASS_BODY(Class, ...) \
	HType* Class::StaticClass() \
	{ \
		static HType ClassType = HType(HTypeGenerator<This>(FriendlyName)); \
		return &ClassType; \
	}
