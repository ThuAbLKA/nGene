workspace "nGene"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "nGene/vendor/GLFW/include"
IncludeDir["Glad"] = "nGene/vendor/Glad/include"
IncludeDir["ImGui"] = "nGene/vendor/imgui"
IncludeDir["glm"] = "nGene/vendor/glm"

include "nGene/vendor/GLFW"
include "nGene/vendor/Glad"
include "nGene/vendor/imgui"

group "Dependancies"
	include "nGene/vendor/GLFW"
	include "nGene/vendor/Glad"
	include "nGene/vendor/imgui"

group ""

project "nGene"
	location "nGene"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ngpch.h"
	pchsource "nGene/src/ngpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
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
		"Glad",
		"GLFW",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NGN_PLATFORM_WINDOWS",
			"NGN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "NGN_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NGN_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NGN_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"nGene/vendor/spdlog/include",
		"nGene/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"nGene"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NGN_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "NGN_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NGN_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NGN_DIST"
		runtime "Release"
		optimize "On"