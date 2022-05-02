#pragma once

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

		std::vector<class HStruct*> GetTypes();

		void RegisterNewType(class HStruct* InType);

	protected:

		std::vector<class HStruct*> Types;
	};
}
