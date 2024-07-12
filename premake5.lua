workspace "FallingSandGame"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "FallingSandGame"
	location "FallingSandGame"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FSG_PLATFORM_WINDOWS",
			"FSG_BUILD_DLL"	
		}

		postbuildcommands
		{
			
		}

		filter "configurations:Debug"
			defines "FSG_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "FSG_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "FSG_DIST"
			optimize "On"

	project "Game"
		location "Game"
		kind "ConsoleApp"
		language"C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"FallingSandGame/vendor/spdlog/include",
		"FallingSandGame/src"
	}

	links
	{
		"FallingSandGame"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FSG_PLATFORM_WINDOWS"	
		}

		filter "configurations:Debug"
			defines "FSG_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "FSG_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "FSG_DIST"
			optimize "On"