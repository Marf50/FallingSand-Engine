#pragma once
#define ImGuiEnabled 1
#include "FallingSandEngine.h"
#include "Panels/SceneHierarchyPanel.h"
namespace FallingSandEngine
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() {};

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnEvent(Event& e) override;



		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;

	private:

		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void SaveSceneAs();
		void OpenScene();


		Ref<Scene> m_ActiveScene;
		bool m_PrimaryCamera = false;
		OrthographicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;
		bool m_ViewPortFocused;
		bool m_ViewPortHovered;
		glm::vec2 m_ViewPortSize;


		// Panels
		SceneHierarchyPanel m_ScenehierarchyPanel;
	};
}