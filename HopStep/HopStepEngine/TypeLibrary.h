#pragma once

namespace HopStep::CoreObject::Reflection
{
	/**
	 * 현재 모듈의 Type을 보관하고, 접근할 수 있도록 하는 인터페이스
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
