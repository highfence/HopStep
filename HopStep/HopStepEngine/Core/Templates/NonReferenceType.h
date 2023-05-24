#pragma once

#include "..\CoreStandardIncludes.h"

template <class TType>
concept NonReferenceType = !std::is_reference_v<TType>;
