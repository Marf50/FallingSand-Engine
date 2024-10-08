#pragma once
#include "FallingSandEngine.h"
#include "UI/UI.h"
#include "AssetManagement/AssetManager.h"
#include "AssetManagement/SettingsManager.h"
#include "UI/UILayers/MainMenu/MainMenuUILayer.h"

namespace FallingSandEngine
{
	class EscMenuUILayer : public Layer
	{
	public:
		EscMenuUILayer();
		virtual ~EscMenuUILayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& e) override;
		

		bool EscMenuUILayer::OnKeyPressed(KeyPressedEvent& e);
		bool EscMenuUILayer::OnWindowResize(WindowResizeEvent& e);
	private:
		UI m_UI;
		OrthographicCamera m_Camera;
		UIStyle m_Style;
		bool m_ShouldClose = false;
		bool m_ShouldCloseToMainMenu = false;
		float m_ChunkRenderDistance = SettingsManager::GetSetting<float>("ChunkRenderDistance");
		float m_CameraZoom = SettingsManager::GetSetting<float>("CameraZoom");
		bool m_OptionsOpen = false;

		
	};
}