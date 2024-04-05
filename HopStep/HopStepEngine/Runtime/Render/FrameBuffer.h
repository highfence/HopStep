#pragma once
#include "Core/CoreExport.h"

namespace HopStep
{
	class HFrameBuffer
	{
	public:
		HFrameBuffer(const int32 InWidth, const int32 InHeight);

		void ClearBuffers();

	private:

		int32 Width;
		int32 Height;

		TArray<uint32> Canvas;
		TArray<float> DepthBuffer;
	};
}