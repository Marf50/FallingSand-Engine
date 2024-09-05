#pragma once
#include "entt.hpp"
#include "FallingSandEngine/Core/Timestep.h"

namespace FallingSandEngine
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();

		//todo make entity type
		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);
		void OnUpdate(Timestep ts);
		void ResizeBounds(uint32_t width, uint32_t height);
		void ListAllEntitesAndComponents();
		uint32_t GetViewportWidth() { return m_ViewportWidth; }
		uint32_t GetViewportHeight() { return m_ViewportHeight; }
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		
		uint32_t m_ViewportWidth = 0;
		uint32_t m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}