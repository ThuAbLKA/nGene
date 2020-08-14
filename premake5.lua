workspace "nGene"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "nGene"
	location "nGene"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
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
			"NGN_PLATFORM_WINDOWS",
			"NGN_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "NGN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NGN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NGN_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs 
	{
		"nGene/vendor/spdlog/include",
		"nGene/src"
	}

	links 
	{
		"nGene"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"NGN_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "NGN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NGN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NGN_DIST"
		optimize "On"