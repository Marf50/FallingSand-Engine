#pragma once
#include <glm/glm.hpp>

namespace FallingSandEngine
{
	class Camera
	{
	public:
		Camera(const glm::mat4& projectionMatrix)
			:m_ProjectionMatrix(projectionMatrix) {}

		Camera() = default;

		virtual ~Camera() = default;
		

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		

		
		// TODO:
		// SetPerspective/SetOrtho

	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	};
}