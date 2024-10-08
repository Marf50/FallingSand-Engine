#include "fsepch.h"
#include "Scene.h"

#include "Components.h"
#include "FallingSandEngine/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"
#include "ElementInterface.h"


namespace FallingSandEngine
{
	
	
	Scene::Scene()
	{
		
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
		
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Update Scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					// TODO: Move to Scene::OnScenePlay should happen when scene is played
					if (!nsc.Instance)
					{
						//FSE_CORE_INFO("Instantiating script for entity {0}", (uint32_t)entity);
						nsc.Instance = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity{entity, this};
						nsc.Instance->OnCreate();

					}
					//FSE_CORE_INFO("Updating script for entity {0}", (uint32_t)entity);
					nsc.Instance->OnUpdate(ts);	
				});
		}




		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			{
				auto view = m_Registry.view<TransformComponent, CameraComponent>();
				for (auto entity : view)
				{
					auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
					if (camera.Primary)
					{
						mainCamera = &camera.Camera;
						cameraTransform = transform.GetTransform();
						break;
					}
				} 
			}
			
		}
		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, cameraTransform);
			//chunks
			auto view = m_Registry.view<TransformComponent, ChunkComponent>();
			for (auto entity : view)
			{
				FSE_PROFILE_SCOPE("Drawing Chunks");
				//FSE_INFO("chunk found with id {0}", (void*)&entity);
				auto [transformComponent, chunkComponent] = view.get<TransformComponent, ChunkComponent>(entity);
				auto translation = transformComponent.Translation;
				//FSE_INFO("Updating Chunk scene {0}", (void*)&chunkComponent);
				for (int x = 0; x < 64; ++x)
				{
					for (int y = 0; y < 64; ++y)
					{
						FSE_PROFILE_SCOPE("Drawing Cell");
						ElementType cellType = ElementInterface::GetElementType(chunkComponent.Cells[x][y]);
						if ((uint16_t)cellType == 0U || (uint16_t)cellType == 1U)
							continue;
						//FSE_CORE_INFO("Found Element in chunk {0}", (uint16_t)cellType);
						
						auto it = chunkComponent.ElementCache.find(cellType);
						if (it != chunkComponent.ElementCache.end())
						{
							Scope<ElementInterface>& element = it->second;
							
							if (element)
							{
								FSE_PROFILE_SCOPE("Rendering Cell");
								glm::vec4 color = element->GetColor();

								glm::vec3 cellPosition = translation + glm::vec3(x + (64 * chunkComponent.ChunkCoords[0]), y + (64 * chunkComponent.ChunkCoords[1]), 0.0f);
								glm::mat4 cellTransform = glm::translate(glm::mat4(1.0f), cellPosition);
								Renderer2D::DrawQuad(cellTransform, color);
								//FSE_CORE_INFO("Drawing Cell at ({0}, {1}) Color = ({2}, {3}, {4}, {5}", cellPosition.x, cellPosition.y, color[0], color[1], color[2], color[3]);
							}
						}

					}
				}

				
			}
			//sprites
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::ResizeBounds(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		// Resize non-FixedAspectRatio Cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}
	// For Debug
	void Scene::ListAllEntitesAndComponents()
	{
		// Iterate through all entities in the registry by using the view
		auto view = m_Registry.view<TransformComponent, TagComponent>(); // A general view, add/remove components as needed
		for (auto entityID : view)
		{
			Entity entity{ entityID, this }; // Wrap entity in your Entity class
			auto& tag = entity.GetComponent<TagComponent>().Tag; // Get the entity's tag for easy identification
			FSE_INFO("Entity ID: {0}, Tag: {1}", (uint32_t)(entt::entity)entityID, tag);

			// Check if the entity has specific components and print information
			if (entity.HasComponent<TransformComponent>())
			{
				auto& transform = entity.GetComponent<TransformComponent>();
				FSE_INFO("  - TransformComponent: Translation({0}, {1}, {2})",
					transform.Translation.x, transform.Translation.y, transform.Translation.z);
			}

			if (entity.HasComponent<CameraComponent>())
			{
				FSE_INFO("  - CameraComponent");
			}

			if (entity.HasComponent<ChunkComponent>())
			{
				auto& chunkComponent = entity.GetComponent<ChunkComponent>();
				FSE_INFO("  - ChunkComponent at address: {0}, ChunkCoords: ({1}, {2})",
					(void*)&chunkComponent, chunkComponent.ChunkCoords[0], chunkComponent.ChunkCoords[1]);

				// List all neighbors
				static const char* neighborNames[8] = { "North", "North-East", "East", "South-East", "South", "South-West", "West", "North-West" };
				for (int i = 0; i < 8; ++i)
				{
					if (chunkComponent.Neighbors[i] != nullptr)
					{
						FSE_INFO("    - {0} Neighbor at ({1}, {2})",
							neighborNames[i], chunkComponent.Neighbors[i]->ChunkCoords[0], chunkComponent.Neighbors[i]->ChunkCoords[1]);
					}
					else
					{
						FSE_INFO("    - {0} Neighbor: NULL", neighborNames[i]);
					}
				}
			}

			if (entity.HasComponent<NativeScriptComponent>())
			{
				FSE_INFO("  - NativeScriptComponent with script at address: {0}", (void*)entity.GetComponent<NativeScriptComponent>().Instance);
			}

			if (entity.HasComponent<SpriteRendererComponent>())
			{
				FSE_INFO("  - SpriteRendererComponent");
			}

			// Add more components here if needed
		}
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}
	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}
	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<ChunkComponent>(Entity entity, ChunkComponent& component)
	{
		//FSE_CORE_INFO("ChunkComponent added {0}", (void*)&component);
	}
}

