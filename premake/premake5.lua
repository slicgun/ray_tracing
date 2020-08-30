workspace "cod zombies"
	configurations {"Debug", "Release"}
	location "../"

project "cod zombies"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	objdir "bin-int/%{cfg.buildcfg}"

	files 
	{
		"../src/**.h",
		"../src/**.cpp",
	}

	includedirs
	{
		"../vendor/glm",
		"../vendor/SFML/include"
	}

	libdirs
	{
		"../vendor/SFML/lib"
	} 

	links
	{
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