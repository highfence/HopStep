#pragma once
#include "Core\HopStepCore.h"

namespace HopStep::CoreObject::Reflection
{
	/**
	 * ���� ����� Type�� �����ϰ�, ������ �� �ֵ��� �ϴ� �������̽�
	 */
	class HTypeLibrary final
	{
	public:

		~HTypeLibrary();

		static HTypeLibrary* Get();

		HArray<class HType*> GetTypes();

		void RegisterNewType(class HType* InType);

	protected:

		std::vector<class HType*> Types;
	};
}
