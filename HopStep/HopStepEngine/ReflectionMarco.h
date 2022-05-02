#pragma once
#include "HopStepOverrides.h"

using namespace HopStep::CoreObject::Reflection;

#define HPROPERTY(...)

#define DECLARE_TYPEHASH \
	size_t GetTypeHash() const \
	{ \
		static size_t UniquePointer; \
		return reinterpret_cast<size_t>(&UniquePointer); \
	}							

#define DECLARE_CLASS_BODY(Class, ...) \
public: \
	DECLARE_TYPEHASH \
\
	friend class HStruct; \
	using This = Class; \
	inline static constexpr HopStep::HStringView FriendlyName = L ## #Class; \
\
	static class HStruct* StaticClass(); \
\
private: 
	

#define IMPLEMENT_CLASS_BODY(Class, ...) \
	HStruct* Class::StaticClass() \
	{ \
		static HStruct ClassType(FriendlyName.data()); \
		return &ClassType; \
	}
