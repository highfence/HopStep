#pragma once
#include "Core\CoreExport.h"

namespace HopStep
{
	/**
	 * 현재 모듈의 Type을 보관하고, 접근할 수 있도록 하는 인터페이스
	 */
	class HTypeLibrary final
	{
	public:

		~HTypeLibrary();

		static HTypeLibrary* GetPropertyPtr();

	protected:
	};
}
