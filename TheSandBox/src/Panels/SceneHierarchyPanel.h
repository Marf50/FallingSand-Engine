#pragma once
#include "FallingSandEngine/Scene/Scene.h"
#include "FallingSandEngine/Core/Core.h"
#include "FallingSandEngine/Core/Log.h"
#include "FallingSandEngine/Scene/Entity.h"
#include "FallingSandEngine/Scene/Components.h"
namespace FallingSandEngine
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:

		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}