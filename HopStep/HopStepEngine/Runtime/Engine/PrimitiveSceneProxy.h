#pragma once

namespace HopStep
{
	/**
	 * 언리얼 엔진에서 FPrimitiveSceneProxy는 렌더링 시스템에 적용되는 기본 객체를 대표하는 클래스입니다. 이 클래스는 게임 스레드와 렌더 스레드 사이에 있는 개체를 중재하며, 렌더링을 위한 데이터와 메서드를 제공합니다.
	 * FPrimitiveSceneProxy의 주요 역할은 다음과 같습니다:
	 * 데이터 제공: FPrimitiveSceneProxy는 렌더링을 위해 필요한 데이터를 수집하고 전달합니다. 이 데이터에는 메시, 셰이더, 텍스처, 재질, 그리고 라이팅과 관련된 정보 등이 포함됩니다.
	 * 렌더링 로직 정의: FPrimitiveSceneProxy는 DrawDynamicElements 메서드를 통해 렌더링 로직을 정의합니다. 이 메서드는 렌더링할 기본 객체를 인스턴스화하고, 렌더 커맨드를 생성하여 렌더링 큐에 추가하는 과정을 포함합니다.
	 * 렌더링 상태 관리: FPrimitiveSceneProxy는 렌더링 상태를 관리하고, 변경된 상태를 업데이트합니다. 이를 통해 렌더링 최적화를 지원합니다.
	 * 프러스텀 컬링: FPrimitiveSceneProxy는 프러스텀 컬링을 지원하여 카메라 시야 밖의 객체를 렌더링하지 않음으로써 성능을 최적화합니다.
	 * LOD(레벨 오브 디테일) 관리: FPrimitiveSceneProxy는 객체의 거리에 따른 LOD를 관리하여, 멀리 떨어진 객체는 낮은 디테일로 렌더링되고 가까운 객체는 고해상도로 렌더링되도록 합니다. 이를 통해 렌더링 성능을 개선합니다.
	 * FPrimitiveSceneProxy를 사용하여 언리얼 엔진에서 렌더링 프로세스를 보다 효율적으로 관리할 수 있으며, 렌더링 파이프라인을 커스텀화하고 최적화할 수 있습니다.
	 */
	class HPrimitiveSceneProxy
	{
	public:
		HPrimitiveSceneProxy() = default;
		virtual ~HPrimitiveSceneProxy() = default;
	};
}