workspace "FallingSandEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "FallingSandEngine"
	location "FallingSandEngine"
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
			"FSE_PLATFORM_WINDOWS",
			"FSE_BUILD_DLL"	
		}

		postbuildcommands
		{
			
		}

		filter "configurations:Debug"
			defines "FSE_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "FSE_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "FSE_DIST"
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
			symbols "On"

		filter "configurations:Release"
			defines "FSE_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "FSE_DIST"
			optimize "On"