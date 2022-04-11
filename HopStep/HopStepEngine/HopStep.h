#pragma once

// standard library
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>
#include <mutex>
#include <wchar.h>

#include "PrimitiveTypeDefines.h"
#include "MetadataLibrary.h"
#include "Type.h"
#include "Object.h"
#include "ReflectionMarco.h"

#if defined(_WIN64)
#define HopStep_Windows64 1
#elif defined(_WIN32)
#define HopStep_Windows32 1
#endif

#define HopStep_On_Windows HopStep_Windows64 | HopStep_Windows32

#if HopStep_On_Windows
#include <Windows.h>
#endif
