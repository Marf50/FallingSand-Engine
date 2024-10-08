#pragma once
namespace FallingSandEngine
{
	class FreeCam : public ScriptableEntity
	{
	public:
		void OnCreate() override
		{

		}
		void OnUpdate(Timestep ts) override
		{

			auto& transformComponent = GetComponent<TransformComponent>();
			if (Input::IsKeyPressed(KeyCode::W))
				transformComponent.Translation.y += (m_CameraSpeed * ts);

			if (Input::IsKeyPressed(KeyCode::S))
				transformComponent.Translation.y -= (m_CameraSpeed * ts);
			
			if (Input::IsKeyPressed(KeyCode::A))
				transformComponent.Translation.x -= (m_CameraSpeed * ts);

			if (Input::IsKeyPressed(KeyCode::D))
				transformComponent.Translation.x += (m_CameraSpeed * ts);
			
			
		}
		

		void OnDestroy() override
		{

		}
	private:
		float m_CameraSpeed = 75.0f;
	};
}