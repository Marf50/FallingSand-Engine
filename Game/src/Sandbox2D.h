#pragma once
#include "FallingSandEngine.h"
#include "FallingSandEngine/Scene/SceneSerailizer.h"


#include "Base.h"
namespace FallingSandEngine
{
	class Sandbox2D : public Layer
	{
	public:
		Sandbox2D();
		virtual ~Sandbox2D() {};
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& e) override;
		void OnSettingsUpdate();

	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseClicked(MouseButtonPressedEvent& e);
		Entity m_MainCamera;


		Ref<Scene> m_ActiveScene;
		Ref<Framebuffer> m_Framebuffer;
		Ref<ChunkManager> m_ChunkManager;
	};
}