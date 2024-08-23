workspace "FallingSandEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Game"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to root folder (sol dir)
	IncludeDir = {}
	IncludeDir["GLFW"] = "FallingSandEngine/Vendor/GLFW/include"
	IncludeDir["Glad"] = "FallingSandEngine/Vendor/Glad/include"
	IncludeDir["ImGui"] = "FallingSandEngine/Vendor/ImGui"
	IncludeDir["glm"] = "FallingSandEngine/Vendor/glm"
	IncludeDir["stb_image"] = "FallingSandEngine/Vendor/stb_image"
	IncludeDir["entt"] = "FallingSandEngine/Vendor/entt/include"
	IncludeDir["yaml"] = "FallingSandEngine/Vendor/yaml/include"

	group "Dependencies"
		include "FallingSandEngine/Vendor/GLFW"
		include "FallingSandEngine/Vendor/Glad"
		include "FallingSandEngine/Vendor/imgui"
		include "FallingSandEngine/Vendor/yaml"
		
	group ""
	

project "FallingSandEngine"
	location "FallingSandEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fsepch.h"
	pchsource "FallingSandEngine/src/fsepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/Vendor/stb_image/**.cpp",
		"%{prj.name}/Vendor/stb_image/**.h"
	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	includedirs
	{	
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml}"

	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib",
		"yaml-cpp"
	}
	


	filter "system:windows"
		
		systemversion "latest"

		defines
		{
			"FSE_PLATFORM_WINDOWS",
			"FSE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		filter "configurations:Debug"
			defines "FSE_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "FSE_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "FSE_DIST"
			runtime "Release"
			optimize "On"

project "TheSandBox"
	location "TheSandBox"
	kind "ConsoleApp"
	language"C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"FallingSandEngine/vendor/spdlog/include",
		"FallingSandEngine/src",
		"FallingSandEngine/Vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"FallingSandEngine"
	}

	filter "system:windows"
		
		systemversion "latest"

		defines
		{
			"FSE_PLATFORM_WINDOWS"	
		}

		filter "configurations:Debug"
			defines "FSE_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "FSE_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "FSE_DIST"
			runtime "Release"
			optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language"C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"FallingSandEngine/vendor/spdlog/include",
		"FallingSandEngine/src",
		"FallingSandEngine/Vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"FallingSandEngine"
	}

	filter "system:windows"
		
		systemversion "latest"

		defines
		{
			"FSE_PLATFORM_WINDOWS"	
		}

		filter "configurations:Debug"
			defines "FSE_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "FSE_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "FSE_DIST"
			runtime "Release"
			optimize "On"