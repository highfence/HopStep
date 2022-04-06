#pragma once
#include "TypeGenerator.h"

namespace HopStep::Reflection
{
#define DECLARE_TYPEHASH \
	size_t GetTypeHash() const \
	{ \
		static size_t UniquePointer; \
		return reinterpret_cast<size_t>(&UniquePointer); \
	}							


#define GENERATED_CLASS_BODY(Class, ...) \
	friend class HType; \
	using This = Class; \
	\
	inline static HType* StaticClass(); \
	inline static constexpr std::wstring_view FriendlyName = L ## #Class; \


#define GENERATE_BODY(Class, ...) \
	HType* Class::StaticClass() \
	{ \
		static HType ClassType(HTypeGenerator<Class>(FriendlyName)); \
		return &ClassType; \
	}
}
