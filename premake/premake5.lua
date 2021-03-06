workspace "ray_tracing"
	configurations {"Debug", "Release"}
	location "../"
	startproject "ray_tracing"

include "../vendor/Glad"

project "ray_tracing"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir "../bin/%{cfg.buildcfg}"
	objdir "../bin-int"

	files 
	{
		"../src/**.h",
		"../src/**.cpp",
	}

	includedirs
	{
		"../src",
		"../vendor/glm",
		"../vendor/SFML/include",
		"../vendor/Glad/include",
		"../vendor/spdlog/include",
		"../vendor/stb",
		"../vendor/tinyobjloader",
		"../vendor/pcg/include",
	}

	libdirs
	{
		"../vendor/SFML/lib"
	} 

	links
	{
		"Glad",
		"opengl32.lib"
	}

	filter "configurations:Debug"
		defines {""}
		symbols "on"

		links
		{
			"sfml-system-d.lib",
			"sfml-window-d.lib",
			"sfml-graphics-d.lib",
			"sfml-audio-d.lib",
			"sfml-network-d.lib"
		}

	filter "configurations:Release"
		defines {""}
		optimize "on"

		links
		{
			"sfml-system.lib",
			"sfml-window.lib",
			"sfml-graphics.lib",
			"sfml-audio.lib",
			"sfml-network.lib"
		}
