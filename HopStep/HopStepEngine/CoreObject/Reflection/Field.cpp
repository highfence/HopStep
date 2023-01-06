#include "TypeLibrary.h"
#include "Field.h"

namespace HopStep
{
    HField::~HField()
    {
        if (FieldClassPrivate != nullptr)
        {
            delete FieldClassPrivate;
            FieldClassPrivate = nullptr;
        }
    }
}
