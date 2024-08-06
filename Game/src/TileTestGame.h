#pragma once
#include "FallingSandEngine.h"
class TileTestGame : public FallingSandEngine::Layer
{
public:
	TileTestGame();
	virtual ~TileTestGame() {};
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(FallingSandEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(FallingSandEngine::Event& e) override;
private:
	FallingSandEngine::OrthographicCameraController m_CameraController;
	FallingSandEngine::Ref<FallingSandEngine::Texture2D> m_TileTextureSheet;
	FallingSandEngine::Ref<FallingSandEngine::SubTexture2D> m_SubTexture, m_waterTexture,m_dirtTexture;
	FallingSandEngine::Ref<FallingSandEngine::Framebuffer> m_Framebuffer;

	std::unordered_map<char, FallingSandEngine::Ref<FallingSandEngine::SubTexture2D>> s_TextureMap;
};