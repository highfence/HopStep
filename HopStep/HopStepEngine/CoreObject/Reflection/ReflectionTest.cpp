#include "ReflectionTest.h"

using namespace HopStep::CoreObject::Reflection;

int32 HFunctionTestObject::Add(int32 A, int32 B)
{
    return A + B;
}

int32 HFunctionTestObject::AddBC()
{
    return B + C;
}

void HFunctionTestObject::AddWithParamter(int32& OutParam)
{
    OutParam = B + C;
}
