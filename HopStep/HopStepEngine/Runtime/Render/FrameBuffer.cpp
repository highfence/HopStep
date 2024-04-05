#include "HopStep.h"
#include "FrameBuffer.h"

namespace HopStep
{
	HFrameBuffer::HFrameBuffer(const int32 InWidth, const int32 InHeight)
		: Width(InWidth), Height(InHeight)
	{
		const int32 TotalSize = Width * Height;
		Canvas.resize(TotalSize, 0);
		DepthBuffer.resize(TotalSize, 10.0f);
	}

	void HFrameBuffer::ClearBuffers()
	{
		HGenericMemory::MemSet(&Canvas[0], 0, Canvas.size() * sizeof(uint32));
		for (size_t i = 0; i < DepthBuffer.size(); ++i)
		{
			DepthBuffer[i] = 10.0f;
		}
	}
}
