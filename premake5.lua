workspace "qsql"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    startproject "qsql-tests"

    IncludeDir = {}
    IncludeDir["QTL"] = "dependencies/qtl"

    LibDir = {}
    LibDir["QTL"] = "dependencies/qtl"

    BinDir = {}

project "qsql"
    location "qsql"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/include/**.h", 
        "%{prj.name}/src/**.cpp", 
        "dependencies/qtl/qtl.natvis"
    }

    includedirs 
    {
        "%{prj.name}/include",
        "%{IncludeDir.QTL}"
    }

    libdirs
    {
        "dependencies/qtl"
    }

    links
    {
        "qtlDEBUGx64"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    disablewarnings
	{
		"4005"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        ignoredefaultlibraries
        {
            "LIBCMT",
            "LIBCMTD"
        }

        linkoptions
        {
            "/ignore:4006",
            "/ignore:4221",
            "/ignore:4099",
            "/ignore:4075"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/qsql-tests")
        }

    filter "system:linux"
        buildoptions
        {
            "-std=c++17",
            "-fPIC"
        }

        filter "configurations:Debug"
        defines 
        { 
            "QSQL_DEBUG",
            "QSQL_ENABLE_ASSERTS"
        }

        staticruntime "Off"
        runtime "Debug"

        symbols "On"

    filter "configurations:Release"
        defines 
        { 
            "QSQL_RELEASE" 
        }

        staticruntime "Off"
        runtime "Release"

        optimize "On"

    filter "configurations:Dist"
        defines
        {
            "QSQL_DIST"
        }

        staticruntime "Off"
        runtime "Release"

        optimize "On"

project "qsql-tests"
    location "qsql-tests"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    dependson
    {
        "qsql"
    }

    files 
    { 
        "%{prj.name}/include/**.h", 
        "%{prj.name}/src/**.cpp",
        "dependencies/qtl/qtl.natvis"
    }

    includedirs
    {
        "qsql/include",
        "%{prj.name}/include",
        "%{IncludeDir.QTL}"
    }

    libdirs
    {
        "dependencies/qtl"
    }

    links
    {
        "qtlDEBUGx64"
    }

    flags
    {
        "MultiProcessorCompile"
    }

	disablewarnings
	{
		"4005"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        linkoptions
        {
            "/ignore:4006",
            "/ignore:4221",
            "/ignore:4099",
            "/ignore:4075"
        }

    filter "system:linux"
        buildoptions 
        { 
            "-std=c++17", 
            "-fPIC" 
        }

    filter "configurations:Debug"
        defines 
        {
            "QSQL_DEBUG",
            "QSQL_ENABLE_ASSERTS"
        }

        staticruntime "Off"
        runtime "Debug"
        
        symbols "On"

    filter "configurations:Release"
        defines 
        {
            "QSQL_RELEASE"
        }

        staticruntime "Off"
        runtime "Release"

        optimize "On"

    filter "configurations:Dist"
        defines 
        {
            "QSQL_DIST"
        }

        staticruntime "Off"
        runtime "Release"

        optimize "On"