#pragma once

namespace HopStep
{
	/**
	 * �𸮾� �������� FPrimitiveSceneProxy�� ������ �ý��ۿ� ����Ǵ� �⺻ ��ü�� ��ǥ�ϴ� Ŭ�����Դϴ�. �� Ŭ������ ���� ������� ���� ������ ���̿� �ִ� ��ü�� �����ϸ�, �������� ���� �����Ϳ� �޼��带 �����մϴ�.
	 * FPrimitiveSceneProxy�� �ֿ� ������ ������ �����ϴ�:
	 * ������ ����: FPrimitiveSceneProxy�� �������� ���� �ʿ��� �����͸� �����ϰ� �����մϴ�. �� �����Ϳ��� �޽�, ���̴�, �ؽ�ó, ����, �׸��� �����ð� ���õ� ���� ���� ���Ե˴ϴ�.
	 * ������ ���� ����: FPrimitiveSceneProxy�� DrawDynamicElements �޼��带 ���� ������ ������ �����մϴ�. �� �޼���� �������� �⺻ ��ü�� �ν��Ͻ�ȭ�ϰ�, ���� Ŀ�ǵ带 �����Ͽ� ������ ť�� �߰��ϴ� ������ �����մϴ�.
	 * ������ ���� ����: FPrimitiveSceneProxy�� ������ ���¸� �����ϰ�, ����� ���¸� ������Ʈ�մϴ�. �̸� ���� ������ ����ȭ�� �����մϴ�.
	 * �������� �ø�: FPrimitiveSceneProxy�� �������� �ø��� �����Ͽ� ī�޶� �þ� ���� ��ü�� ���������� �������ν� ������ ����ȭ�մϴ�.
	 * LOD(���� ���� ������) ����: FPrimitiveSceneProxy�� ��ü�� �Ÿ��� ���� LOD�� �����Ͽ�, �ָ� ������ ��ü�� ���� �����Ϸ� �������ǰ� ����� ��ü�� ���ػ󵵷� �������ǵ��� �մϴ�. �̸� ���� ������ ������ �����մϴ�.
	 * FPrimitiveSceneProxy�� ����Ͽ� �𸮾� �������� ������ ���μ����� ���� ȿ�������� ������ �� ������, ������ ������������ Ŀ����ȭ�ϰ� ����ȭ�� �� �ֽ��ϴ�.
	 */
	class HPrimitiveSceneProxy
	{
	public:
		HPrimitiveSceneProxy() = default;
		virtual ~HPrimitiveSceneProxy() = default;
	};
}