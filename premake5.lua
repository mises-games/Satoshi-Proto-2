workspace "Satoshi"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Satoshi/vendor/GLFW/include"
IncludeDir["GLAD_GL"] = "Satoshi/vendor/GLAD_GL/include"

group "Dependencies"

    include "Satoshi/vendor/GLFW"
    include "Satoshi/vendor/GLAD_GL"

group ""

project "Satoshi"
    location "Satoshi"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.inl",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.glsl",
        "%{prj.name}/src/**.hlsl"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD_GL}",
        "%{prj.name}/src"
    }

    links
    {
        "GLFW",
        "GLAD_GL"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        defines
        {
            "ST_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

        links
        {
            "opengl32.lib",
            "d3d11.lib",
            "d3dcompiler.lib"
        }
    
    filter "configurations:Debug"
        defines "ST_DEBUG"
        symbols "on"
    
    filter "configurations:Release"
        defines "ST_RELEASE"
        optimize "on"    
    
    filter "configurations:Dist"
        defines "ST_DIST"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Satoshi/src",
        "Satoshi/vendor/spdlog/include"
    }

    links
    {
        "Satoshi"
    }
    
    filter "system:windows"
        systemversion "latest"

        defines
        {
            "ST_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "ST_DEBUG"
        symbols "on"
    
    filter "configurations:Release"
        defines "ST_RELEASE"
        optimize "on"    
    
    filter "configurations:Dist"
        defines "ST_DIST"
        optimize "on"