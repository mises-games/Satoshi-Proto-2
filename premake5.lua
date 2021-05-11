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
        "%{prj.name}/vendor/spdlog/include"
    }

    links
    {
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        defines
        {
            "ST_PLATFORM_MSDOS"
        }

        links
        {
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
        "Satoshi/vendor"
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