workspace "FallingSandEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	commands = [[copy /Y "$(TargetDir)$(ProjectName).dll" "$(SolutionDir)Game\$(ProjectName).dll"]]

	-- Include directories relative to root folder (sol dir)
	IncludeDir = {}
	IncludeDir["GLFW"] = "FallingSandEngine/Vendor/GLFW/include"
	IncludeDir["Glad"] = "FallingSandEngine/Vendor/Glad/include"
	IncludeDir["ImGui"] = "FallingSandEngine/Vendor/ImGui"
	
	include "FallingSandEngine/Vendor/GLFW"
	include "FallingSandEngine/Vendor/Glad"
	include "FallingSandEngine/Vendor/imgui"

project "FallingSandEngine"
	location "FallingSandEngine"
	kind "SharedLib"
	language "C++"

	
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
		"%{IncludeDir.ImGui}"
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
		staticruntime "On"
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
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "FSE_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "FSE_DIST"
			buildoptions "/MD"
			optimize "On"



project "Game"
	location "Game"
	kind "ConsoleApp"
	language"C++"
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
		"FallingSandEngine/src"
	}

	links
	{
		"FallingSandEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FSE_PLATFORM_WINDOWS"	
		}

		filter "configurations:Debug"
			defines "FSE_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "FSE_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "FSE_DIST"
			buildoptions "/MD"
			optimize "On"