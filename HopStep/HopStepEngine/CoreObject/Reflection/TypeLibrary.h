#pragma once
#include "Core\CoreExport.h"

namespace HopStep
{
	/**
	 * ���� ����� Type�� �����ϰ�, ������ �� �ֵ��� �ϴ� �������̽�
	 */
	class HTypeLibrary final
	{
	public:

		~HTypeLibrary();

		static HTypeLibrary* GetPropertyPtr();

		HArray<class HType*> GetTypes();

		void RegisterNewType(class HType* InType);

	protected:

		std::vector<class HType*> Types;
	};
}
