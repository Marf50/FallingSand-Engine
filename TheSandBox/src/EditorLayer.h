#pragma once

#include "FallingSandEngine.h"

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
		OrthographicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;

		glm::vec2 m_ViewPortSize;
	};
}