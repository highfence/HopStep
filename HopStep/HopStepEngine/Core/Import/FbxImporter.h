#pragma once
#include "..\HopStepOverrides.h"
#include "..\PrimitiveTypeDefines.h"
#include "..\..\ThirdParty\FBX\2020.2\include\fbxsdk.h"

#pragma comment(lib, "libfbxsdk.lib")
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libfbxsdk-mt.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "libxml2-mt.lib")
#pragma comment(lib, "zlib-md.lib")
#pragma comment(lib, "zlib-mt.lib")

namespace HopStep 
{
	struct HFBXImportOptions
	{

	};

	class HFbxImporter
	{
	public:

		virtual ~HFbxImporter();

		bool Initialize();

		bool OpenFile(const HString& Filename);

		void CleanUp();

	protected:

		::FbxManager* SDKManager = nullptr;
		TUniquePtr<HFBXImportOptions> ImportOptions = nullptr;
		::FbxImporter* Importer = nullptr;
		

	};
}