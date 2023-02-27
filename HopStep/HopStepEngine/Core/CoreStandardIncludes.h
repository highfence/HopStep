#pragma once

// standard library
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <mutex>
#include <wchar.h>
#include <optional>
#include <iostream>
#include <cstddef>
#include <string_view>
#include <cstddef>
#include <any>
#include <concepts>
#include <filesystem>
#include <type_traits>
#include <atomic>
#include <functional>
#include <format>

#include "HopStepDefine.h"

// define-dependency includes
#if HopStep_On_Windows
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#endif

#if !HopStep_On_CustomContainer
#include <tuple>
#include <unordered_map>
#include <stack>
#include <vector>
#endif
