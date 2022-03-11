#pragma once

namespace HopStep::Reflection
{
	/**
	 * 현재 모듈의 Type을 보관하고, 접근할 수 있도록 하는 인터페이스
	 */
	class HMetadataLibrary
	{
	public:

		std::vector<class HType*> GetTypes();

	protected:

		std::vector<class HType*> Types;
	};
}

