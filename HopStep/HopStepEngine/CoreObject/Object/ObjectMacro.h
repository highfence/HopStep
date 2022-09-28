#pragma once
#include "ObjectBase.h"
#include "..\Reflection\Class.h"
#include "..\Reflection\StructBuilder.h"

// writing class implement in Class.generated.cpp
#define IMPLEMENT_CLASS(TClass) \
	static HStaticClassRegister<TClass> __Auto_Initialize_##TClass(); \
	HClass* TClass::StaticClass() \
	{ \
		static HClass* PrivateStaticClass = nullptr; \
		if (PrivateStaticClass == nullptr) \
		{ \
			PrivateStaticClass = new HClass(TClass::FriendlyName.data()); \
			__Fill_Class_Property_##TClass(PrivateStaticClass); \
		} \
		return PrivateStaticClass; \
	}

