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
	commands = [[copy /Y "$(TargetDir)$(ProjectName).dll" "$(SolutionDir)Game\$(ProjectName).dll"]]

	-- Include directories relative to root folder (sol dir)
	IncludeDir = {}
	IncludeDir["GLFW"] = "FallingSandEngine/Vendor/GLFW/include"
	IncludeDir["Glad"] = "FallingSandEngine/Vendor/Glad/include"
	IncludeDir["ImGui"] = "FallingSandEngine/Vendor/ImGui"
	IncludeDir["glm"] = "FallingSandEngine/Vendor/glm"

	group "Dependencies"
		include "FallingSandEngine/Vendor/GLFW"
		include "FallingSandEngine/Vendor/Glad"
		include "FallingSandEngine/Vendor/imgui"
		
	group ""
	

project "FallingSandEngine"
	location "FallingSandEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fsepch.h"
	pchsource "FallingSandEngine/src/fsepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{	
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}
	


	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"FSE_PLATFORM_WINDOWS",
			"FSE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			commands 
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
	staticruntime "Off"
	
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
		"%{IncludeDir.glm}"
	}

	links
	{
		"FallingSandEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
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