#pragma once
#include "..\HopStepOverrides.h"

namespace HopStep 
{
	class HAssetImporter
	{
	public:

		bool OpenFile(const HString& Filename);

	private:

		const class aiScene* LoadAISceneFromFile(const HString& Filename) const;

	};
}