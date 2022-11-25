#include "..\..\Core\CoreExport.h"
#include "RootSet.h"

namespace HopStep
{
    HRootSet::~HRootSet()
    {
        Childs.clear();
    }

    void HRootSet::AddToRoot(HObject* Object)
    {
        HCheck(Object != nullptr);
        Childs.emplace_back(Object);
    }

    TArray<IGCObject*> HRootSet::GetGCProperties()
    {
        auto Result = HObject::GetGCProperties();

        Result.insert(Result.begin(), Childs.begin(), Childs.end());

        return Result;
    }
}