#include "..\HopStepEngine\Core\HopStepCore.h"
#include "NamePool.h"
#include "NameHelper.h"

namespace HopStep
{
    HString HNameEntry::GetString() const
    {
        const Internal::HNamePool& NamePool = Internal::HNamePool::GetNamePool();
        return NamePool.FindString(Id.GetValue());
    }
}
