#pragma once
#include "TypeGenerator.h"
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
	friend class HType; \
	using This = Class; \
	inline static constexpr HopStep::HStringView FriendlyName = L ## #Class; \
\
	static class HType* StaticClass(); \
\
private: 
	

#define IMPLEMENT_CLASS_BODY(Class, ...) \
	HType* Class::StaticClass() \
	{ \
		static HType ClassType = HType(HTypeGenerator<This>(FriendlyName)); \
		return &ClassType; \
	}
