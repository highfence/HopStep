#pragma once

namespace HopStep::CoreObject::Reflection
{
	/**
	 * ���� ����� Type�� �����ϰ�, ������ �� �ֵ��� �ϴ� �������̽�
	 */
	class HMetadataLibrary final
	{
	public:

		~HMetadataLibrary();

		static HMetadataLibrary* Get();

		std::vector<class HType*> GetTypes();

		void RegisterNewType(class HType* InType);

	protected:

		std::vector<class HType*> Types;
	};
}
