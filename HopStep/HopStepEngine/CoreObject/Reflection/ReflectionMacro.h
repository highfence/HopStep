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

