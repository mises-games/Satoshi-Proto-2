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
IncludeDir["GLAD_GL"] = "Satoshi/vendor/GLAD_GL/include"
IncludeDir["ImGui"] = "Satoshi/vendor/ImGui"
IncludeDir["yaml_cpp"] = "Satoshi/vendor/yaml_cpp/include"

group "Dependencies"

    include "Satoshi/vendor/GLAD_GL"
    include "Satoshi/vendor/ImGui"
    include "Satoshi/vendor/yaml_cpp"

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
        "%{IncludeDir.GLAD_GL}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.yaml_cpp}",
        "%{prj.name}/src"
    }

    links
    {
        "ImGui",
        "yaml_cpp",
        "GLAD_GL"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        defines
        {
            "ST_PLATFORM_WINDOWS"
        }

        links
        {
            "opengl32.lib",
            "d3d11.lib",
            "d3dcompiler.lib",
            "Ws2_32.lib"
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
        "%{prj.name}/**.yaml",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Satoshi/src",
        "Satoshi/vendor/ImGui",
        "Satoshi/vendor/spdlog/include",
        "Satoshi/vendor/yaml_cpp/include"
    }

    links
    {
        "Satoshi"
    }

    filter "files:**.yaml"
        buildaction "Resource"


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