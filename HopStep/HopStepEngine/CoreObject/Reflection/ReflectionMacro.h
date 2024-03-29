#pragma once
#include "Core\CoreExport.h"
#include "Class.h"
#include "ScriptMacros.h"

using namespace HopStep;

/*
	Defines used by HeaderTool parsing.
	Ignore their inner contents before additional file generated.
*/
#define HCLASS(...)
#define HENUM(...)
#define HPROPERTY(...)
#define HFUNCTION(...)

#define DECLARE_TYPEHASH \
	size_t GetTypeHash() const \
	{ \
		static size_t UniquePointer; \
		return reinterpret_cast<size_t>(&UniquePointer); \
	}							

#define HEADERTOOL_STRING_CONCAT_INNER(A,B,C,D) A##B##C##D
#define HEADERTOOL_STRING_CONCAT(A,B,C,D) HEADERTOOL_STRING_CONCAT_INNER(A,B,C,D)
#define HEADERTOOL_DEFINE HEADERTOOL_STRING_CONCAT(CURRENT_FILE_ID,_,__LINE__,_Generated_Function_Declare);

#define BODY_DEFINE(Class) \
public: \
	DECLARE_TYPEHASH \
\
	using ThisClass = Class; \
	inline static constexpr HopStep::HStringView FriendlyName = L ## #Class; \
\
	static class HClass* StaticClass(); \
\
private: \
	static void __Fill_Class_Property_##Class(class HClass*); \
	friend class HStruct; \
	friend struct HStructBuilder;


#define DECLARE_CLASS_BODY(Class) HEADERTOOL_DEFINE \
BODY_DEFINE(Class) 

/*
	Using declare / define HFunction property in autogenerated boilerplate code.
*/
#define DECLARE_FUNCTION(func) static void func(void* Instance, HFunctionCallFrame& Frame, HFUNC_RESULT_DECL_INNER)
#define DEFINE_FUNCTION(func) void func(void* Instance, HFunctionCallFrame& Frame, HFUNC_RESULT_DECL_INNER)



/**
 * Field related defines
 */
#define DECLARE_FIELD(TClass, TSuperClass, TStaticFlags) \
public: \
	typedef TSuperClass Super; \
	typedef TClass ThisClass; \
	static FField* Construct(const HName&); \
	static FFieldClass* StaticClass(); \
	inline static constexpr uint64 StaticClassCastFlagsPrivate() { return static_cast<uint64>(TStaticFlags); } \
	inline static constexpr uint64 GetStaticCLassCastFlags() \
	{ \
		return static_cast<uint64>(TStaticFlags) | Super::StaticClassCastFlagsPrivate(); \
	} 

#define IMPLEMENT_FIELD(TClass) \
FField* TClass::Construct(const HName& InName) \
{ \
	return new TClass(InName, TClass::StaticClass()); \
} \
FFieldClass* TClass::StaticClass() \
{ \
	static FFieldClass StaticFieldClass(TEXT(#TClass), TClass::StaticClassCastFlagsPrivate(), TClass::StaticClassCastFlags(), TClass::Super::StaticClass(), &TClass::Construct); \
	return &StaticFieldClass; \
} \

