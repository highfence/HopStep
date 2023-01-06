#include "..\..\Core\CoreExport.h"


namespace HopStep
{
	namespace Internal
	{
		struct HObjectHandleInternal
		{
			intptr_t PointerOrRef;
		};
	}

	using HObjectHandle = Internal::HObjectHandleInternal;

	inline bool operator==(HObjectHandle LHS, HObjectHandle RHS);
	inline bool operator!=(HObjectHandle LHS, HObjectHandle RHS);
	inline HObjectHandle MakeObjectHandle(class HObject*);
	inline class HObject* ResolveObjectHandle(const HObjectHandle& InHandle);

	struct HObjectPtr
	{
	public:

		HObjectPtr()
			: Handle(MakeObjectHandle(nullptr))
		{

		}

		HObjectPtr(class HObject* InObject)
			: Handle(MakeObjectHandle(InObject))
		{

		}

		class HObject* Get() const
		{
			return ResolveObjectHandle(Handle);
		}

	private:

		HObjectHandle Handle;
	};

	template <typename TClass> requires std::derived_from<TClass, HObject>
	struct TObjectPtr
	{
		using ElementType = TClass;

	public:

		TObjectPtr()
			: ObjectPtr()
		{

		}

		TObjectPtr(TClass&& InObject)
			: ObjectPtr(InObject)
		{

		}

	private:

		HObjectPtr ObjectPtr;
	};
}