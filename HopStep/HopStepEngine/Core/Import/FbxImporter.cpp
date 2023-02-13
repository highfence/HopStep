#include "FbxImporter.h"

namespace HopStep
{
	HFbxImporter::~HFbxImporter()
	{
		CleanUp();
	}

	bool HFbxImporter::Initialize()
	{
		SDKManager = ::FbxManager::Create();
		::FbxIOSettings* IOSetting = ::FbxIOSettings::Create(SDKManager, IOSROOT);
		SDKManager->SetIOSettings(IOSetting);

		ImportOptions = std::make_unique<HFBXImportOptions>();
		return false;
	}

	bool HFbxImporter::OpenFile(const HString& Filename)
	{
		Importer = ::FbxImporter::Create(SDKManager, "");

		int SDKMajor = 0;
		int SDKMinor = 0;
		int SDKRevision = 0;
		::FbxManager::GetFileFormatVersion(SDKMajor, SDKMinor, SDKRevision);

		return false;
	}

	void HFbxImporter::CleanUp()
	{
		if (SDKManager)
		{
			SDKManager->Destroy();
			SDKManager = nullptr;
		}
	}
}