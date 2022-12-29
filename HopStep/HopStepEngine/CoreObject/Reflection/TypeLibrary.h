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

		TArray<class HField*> GetTypes();

		void RegisterNewType(class HField* InType);

	protected:

		std::vector<class HField*> Types;
	};
}
