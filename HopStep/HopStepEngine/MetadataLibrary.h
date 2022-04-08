#pragma once

/**
 * ���� ����� Type�� �����ϰ�, ������ �� �ֵ��� �ϴ� �������̽�
 */
class HMetadataLibrary
{
public:

	static HMetadataLibrary& Get();

	std::vector<class HType*> GetTypes();

	void RegisterNewType(class HType* InType);

protected:

	std::vector<class HType*> Types;
};

