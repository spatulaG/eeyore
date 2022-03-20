workspace "Eeyore"
	architecture "x64"

	configurations
	{
	"Debug",
	"Release",
	"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Eeyore\\vendor\\GLFW\\include"

include "Eeyore\\vendor\\GLFW"

project "Eeyore"
	location "Eeyore"
	kind "SharedLib"
	language"C++"

	targetdir ("bin\\" ..outputdir .. "\\%{prj.name}") 
	objdir ("bin-int\\" ..outputdir .. "\\%{prj.name}") 

	pchsource "Eeyore/src/erpch.cpp"
	pchheader "erpch.h"

	files
	{
		"%{prj.name}\\src\\**.h",
		"%{prj.name}\\src\\**.cpp"
	}

	includedirs
	{
		"%{prj.name}\\vendor\\spdlog\\include",
		"%{prj.name}\\src",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter"system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines{
		"ER_PLATFORM_WINDOWS",
		"ER_BUILD_DLL"
	}

	postbuildcommands
	{
		"{COPY} %{cfg.buildtarget.relpath} ..\\bin\\" .. outputdir .. "\\Sandbox"
	}

	filter "configurations:Debug"
		defines "ER_DEBUG"
		buildoptions "/MDd" -- Multi threaded debug, so not static alloc
		symbols "On"
	
	filter "configurations:Release"
		defines "ER_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "ER_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language"C++"

	targetdir ("bin\\" ..outputdir .. "\\%{prj.name}") 
	objdir ("bin-int\\" ..outputdir .. "\\%{prj.name}") 

	files
	{
		"%{prj.name}\\src\\**.h",
		"%{prj.name}\\src\\**.cpp"
	}

	includedirs 
	{
		"Eeyore\\vendor\\spdlog\\include",
		"Eeyore\\src"
	}
	links
	{
	"Eeyore"
	}

	filter"system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"ER_PLATFORM_WINDOWS",
	}

	filter "configurations:Debug"
		defines "ER_DEBUG"
		buildoptions "/MDd"--why?
		symbols "On"
	
	filter "configurations:Release"
		defines "ER_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "ER_DIST"
		buildoptions "/MD"
		optimize "On"