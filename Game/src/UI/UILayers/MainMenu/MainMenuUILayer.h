#pragma once
#include "FallingSandEngine.h"
#include "UI/UI.h"
#include "AssetManagement/AssetManager.h"
#include "AssetManagement/SettingsManager.h"
#include "Sandbox2D.h"

namespace FallingSandEngine
{
	class MainMenuUILayer : public Layer
	{
	public:
		MainMenuUILayer();
		virtual ~MainMenuUILayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& e) override;


		bool MainMenuUILayer::OnKeyPressed(KeyPressedEvent& e);
		bool MainMenuUILayer::OnWindowResize(WindowResizeEvent& e);
	private:
		UI m_UI;
		OrthographicCamera m_Camera;
		UIStyle m_Style;
		bool m_ShouldOpenGame = false;
	};
}