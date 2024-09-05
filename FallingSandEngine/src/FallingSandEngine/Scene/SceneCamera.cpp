#include "fsepch.h"
#include "SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace FallingSandEngine
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjectionMatrix();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		//m_ProjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
		RecalculateProjectionMatrix();
	}
	void SceneCamera::SetPerspective(float fov, float nearClip, float farClip)
	{
		//m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveFOV = fov;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;
		RecalculateProjectionMatrix();
	}
	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjectionMatrix();
	}

	void SceneCamera::RecalculateProjectionMatrix()
	{
		if (m_ProjectionType == ProjectionType::Orthographic)
		{
			float orthoLeft = -0.5f * m_AspectRatio * m_OrthographicSize;
			float orthoRight = 0.5 * m_AspectRatio * m_OrthographicSize;
			float orthoTop = 0.5f * m_OrthographicSize;
			float orthoBottom = -0.5f * m_OrthographicSize;

			m_ProjectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
		}
		if (m_ProjectionType == ProjectionType::Perspective)
		{
			m_ProjectionMatrix = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
	}
	
	glm::vec3 SceneCamera::ScreenToWorld(const glm::vec2& screenPos, const glm::mat4& viewMatrix, const glm::vec4& viewport) const
	{
		glm::vec3 screenPos3D(screenPos.x, viewport.w - screenPos.y, 0.0f);
		return glm::unProject(screenPos3D, viewMatrix, m_ProjectionMatrix, viewport);
	}
}