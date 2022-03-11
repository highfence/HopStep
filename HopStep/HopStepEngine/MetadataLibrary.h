#pragma once

namespace HopStep::Reflection
{
	/**
	 * ���� ����� Type�� �����ϰ�, ������ �� �ֵ��� �ϴ� �������̽�
	 */
	class HMetadataLibrary
	{
	public:

		std::vector<class HType*> GetTypes();

	protected:

		std::vector<class HType*> Types;
	};
}

