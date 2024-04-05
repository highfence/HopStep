#include "Scene.h"
#include "Runtime/Render/FrameBuffer.h"
#include "Runtime/Render/Renderer.h"
#include "Runtime/Engine/PrimitiveComponent.h"

namespace HopStep
{
	HScene::HScene()
		: HSceneInterface()
	{
	}

	void HScene::AddPrimitive(HPrimitiveComponent* Primitive)
	{
	}

	void HScene::RemovePrimitive(HPrimitiveComponent* Primitive)
	{
	}

	void HScene::Render() const
	{
		auto Renderer = IRenderer::CreateRenderer();
		HCheck(!Renderer);

		// Todo: change below global client size
		auto FrameBuffer = HFrameBuffer(HopStep::ClientWidth, HopStep::ClientHeight);
		Renderer->RenderScene(this, FrameBuffer);


		
	}
}
