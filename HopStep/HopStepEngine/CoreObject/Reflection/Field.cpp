#include "TypeLibrary.h"
#include "FieldClass.h"
#include "Field.h"

namespace HopStep
{
    inline HField::HField(const HString& InName, HFieldClass* FieldClass)
        : TypeFlag(static_cast<uint64>(HTypeFlag::None))
        , FieldClassPrivate(FieldClass)
        , FieldName(InName)
    {
    }

    HField::~HField()
    {
        if (FieldClassPrivate != nullptr)
        {
            delete FieldClassPrivate;
            FieldClassPrivate = nullptr;
        }
    }

    HFieldClass* HField::StaticClass()
    {
        return nullptr;
    }

    inline constexpr uint64 HField::StaticClassCastFlagsPrivate()
    {
        return static_cast<uint64>(EClassCastFlags::CastFlag_Field);
    }

    inline constexpr uint64 HField::StaticClassCastFlags()
    {
        return static_cast<uint64>(EClassCastFlags::CastFlag_Field);
    }

    inline const HName& HField::GetName() const
    {
        return FieldName;
    }
}
