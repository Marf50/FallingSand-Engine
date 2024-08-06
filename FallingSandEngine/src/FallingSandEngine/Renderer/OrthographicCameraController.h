#pragma once
#include "FallingSandEngine/Renderer/OrthographicCamera.h"
#include "FallingSandEngine/Core/Timestep.h"

#include "FallingSandEngine/Events/Events.h"
#include "FallingSandEngine/Events/ApplicationEvents.h"	
#include "FallingSandEngine/Events/MouseEvents.h"

namespace FallingSandEngine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		void ResizeBounds(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; CalculateView(); }

	private:

		void CalculateView();

		bool OnMouseScrolled(MouseScrollEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		bool m_Rotation = false;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 90.0f;


		OrthographicCamera m_Camera;
		
	};
}