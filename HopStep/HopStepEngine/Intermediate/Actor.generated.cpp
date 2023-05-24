#include "HopStep.h"
#include "Runtime\Engine\Actor.h"

using namespace HopStep;

void HActor::__Fill_Class_Property_HActor(HClass* InStaticClass)
{
	HStructBuilder::AddProperty<HActor, HSceneComponent*, HClassProperty>(InStaticClass, TEXT("RootComponent"), &HActor::RootComponent);
	HStructBuilder::SetSuper<HObject>(InStaticClass);
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execGetLocation, TEXT("GetLocation"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execSetLocation, TEXT("SetLocation"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execGetRotation, TEXT("GetRotation"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execSetRotation, TEXT("SetRotation"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execGetScale, TEXT("GetScale"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execSetScale, TEXT("SetScale"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execSetTransform, TEXT("SetTransform"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execGetTransform, TEXT("GetTransform"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execGetActorLocation, TEXT("GetActorLocation"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execSetActorLocation, TEXT("SetActorLocation"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execGetActorRotation, TEXT("GetActorRotation"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execSetActorRotation, TEXT("SetActorRotation"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execGetActorScale, TEXT("GetActorScale"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execSetActorScale, TEXT("SetActorScale"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execSetActorTransform, TEXT("SetActorTransform"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execGetActorTransform, TEXT("GetActorTransform"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execGetRootComponent, TEXT("GetRootComponent"));
	HStructBuilder::AddNativeFunction((HClass*)InStaticClass, &HActor::execGetActorQuat, TEXT("GetActorQuat"));
}

DEFINE_FUNCTION(HActor::execGetLocation)
{
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->GetLocation());
}
DEFINE_FUNCTION(HActor::execSetLocation)
{
	HFUNC_GET_FROM_FRAME(const HVector&, HFunc_Param_NewLocation);
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->SetLocation(HFunc_Param_NewLocation));
}
DEFINE_FUNCTION(HActor::execGetRotation)
{
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->GetRotation());
}
DEFINE_FUNCTION(HActor::execSetRotation)
{
	HFUNC_GET_FROM_FRAME(const HRotator&, HFunc_Param_NewRotation);
	HFUNC_THIS->SetRotation(HFunc_Param_NewRotation);
}
DEFINE_FUNCTION(HActor::execGetScale)
{
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->GetScale());
}
DEFINE_FUNCTION(HActor::execSetScale)
{
	HFUNC_GET_FROM_FRAME(const HVector&, HFunc_Param_NewScale);
	HFUNC_THIS->SetScale(HFunc_Param_NewScale);
}
DEFINE_FUNCTION(HActor::execSetTransform)
{
	HFUNC_GET_FROM_FRAME(const HTransform&, HFunc_Param_NewTransform);
	HFUNC_THIS->SetTransform(HFunc_Param_NewTransform);
}
DEFINE_FUNCTION(HActor::execGetTransform)
{
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->GetTransform());
}
DEFINE_FUNCTION(HActor::execGetActorLocation)
{
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->GetActorLocation());
}
DEFINE_FUNCTION(HActor::execSetActorLocation)
{
	HFUNC_GET_FROM_FRAME(const HVector&, HFunc_Param_NewLocation);
	HFUNC_THIS->SetActorLocation(HFunc_Param_NewLocation);
}
DEFINE_FUNCTION(HActor::execGetActorRotation)
{
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->GetActorRotation());
}
DEFINE_FUNCTION(HActor::execSetActorRotation)
{
	HFUNC_GET_FROM_FRAME(const HRotator&, HFunc_Param_NewRotation);
	HFUNC_THIS->SetActorRotation(HFunc_Param_NewRotation);
}
DEFINE_FUNCTION(HActor::execGetActorScale)
{
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->GetActorScale());
}
DEFINE_FUNCTION(HActor::execSetActorScale)
{
	HFUNC_GET_FROM_FRAME(const HVector&, HFunc_Param_NewScale);
	HFUNC_THIS->SetActorScale(HFunc_Param_NewScale);
}
DEFINE_FUNCTION(HActor::execSetActorTransform)
{
	HFUNC_GET_FROM_FRAME(const HTransform&, HFunc_Param_NewTransform);
	HFUNC_THIS->SetActorTransform(HFunc_Param_NewTransform);
}
DEFINE_FUNCTION(HActor::execGetActorTransform)
{
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->GetActorTransform());
}
DEFINE_FUNCTION(HActor::execGetRootComponent)
{
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->GetRootComponent());
}
DEFINE_FUNCTION(HActor::execGetActorQuat)
{
	*HFUNC_RESULT_PARAM = HFUNC_RESULT_TYPECAST(HFUNC_THIS->GetActorQuat());
}

IMPLEMENT_CLASS(HActor);
