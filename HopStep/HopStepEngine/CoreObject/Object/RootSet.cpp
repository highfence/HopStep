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

    void HRootSet::GetGCProperties(TArray<IGCObject*>& OutList)
    {
        HObject::GetGCProperties(OutList);
        OutList.append_range(Childs);
    }
}