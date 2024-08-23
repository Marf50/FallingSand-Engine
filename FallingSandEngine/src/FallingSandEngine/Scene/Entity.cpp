#include "fsepch.h"
#include "Entity.h"
	
namespace FallingSandEngine
{
	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene)
	{

	}
}