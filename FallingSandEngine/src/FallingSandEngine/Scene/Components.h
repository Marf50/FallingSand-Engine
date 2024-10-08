#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "FallingSandEngine/Renderer/Camera.h"
#include "SceneCamera.h"
#include "ScriptableEntity.h"




namespace FallingSandEngine
{
	enum class ElementType : uint16_t;
	class ElementInterface;
	typedef uint64_t CellData;

	struct TagComponent
	{
		std::string Tag;

		TagComponent() {}
		TagComponent(const TagComponent&) {}
		TagComponent(const std::string& tag)
			:Tag(tag) {}
	};
	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
		

		TransformComponent() {}
		TransformComponent(const TransformComponent&) {}
		TransformComponent(const glm::vec3& translation)
			:Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1,0,0 })
								*glm::rotate(glm::mat4(1.0f), Rotation.y, { 0,1,0 })
								*glm::rotate(glm::mat4(1.0f), Rotation.z, { 0,0,1 });
			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};
	struct SpriteRendererComponent
	{
		glm::vec4 Color = glm::vec4(1.0f);

		SpriteRendererComponent() {}
		SpriteRendererComponent(const SpriteRendererComponent&) {}
		SpriteRendererComponent(const glm::vec4& color)
			:Color(color) {}
	};
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		std::function<ScriptableEntity* ()> InstantiateScript;  // Change from function pointer to std::function
		std::function<void(NativeScriptComponent*)> DestroyScript;

		template<typename T, typename... Args>
		void Bind(Args&&... args)
		{
			// Heap Allocation Stinky "new" bad
			InstantiateScript = [args...]() mutable {
				T* script = new T(std::forward<Args>(args)...);  // Construct the script
				return static_cast<ScriptableEntity*>(script);
				};
			DestroyScript = [](NativeScriptComponent* nsc) {
				delete nsc->Instance;
				nsc->Instance = nullptr;
				};
		}
	};
	struct ChunkComponent
	{
		ChunkComponent(const ChunkComponent&) = delete;
		ChunkComponent& operator=(const ChunkComponent&) = delete;

		// Default constructor and destructor
		ChunkComponent() = default;
		~ChunkComponent() = default;

		int64_t ChunkCoords[2];
		CellData Cells[64][64];
		bool IsAwake = false;
		ChunkComponent* Neighbors[8];
		bool RandomNumber = false;

		std::unordered_map<ElementType, Scope<ElementInterface>> ElementCache;
	};
}
