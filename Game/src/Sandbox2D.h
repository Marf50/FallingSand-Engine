#pragma once
#include "FallingSandEngine.h"
class Sandbox2D : public FallingSandEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() {};
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(FallingSandEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(FallingSandEngine::Event& e) override;
private:
	FallingSandEngine::OrthographicCameraController m_CameraController;
	FallingSandEngine::Ref<FallingSandEngine::Texture2D> m_TileTexture;
};