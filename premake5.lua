workspace "SlopDAW"
    configurations { "Debug", "Release" }
    architecture "x86_64"

project "DAW"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"

    -- Set the target output directory (for the final executable)
    targetname "SlopDAW"
    location "build"

    filter "toolset:g++"
        buildoptions { "-fconstexpr-ops-limit=500000000",
                       "-fconcepts-diagnostics-depth=5" }

    -- Debug configuration settings
    filter "configurations:Debug"
        targetdir "build/bin/Debug"  -- Output directory for Debug
        objdir "build/obj/Debug"     -- Object files for Debug

        buildoptions { "-O0" }       -- Debug flags: no optimization, debug info
        symbols "On"               -- Enable symbols for Debug
        entrypoint "mainCRTStartup"  -- Explicitly set entry point to "main" for Debug configuration

        -- Link libraries (common across configurations)
        libdirs { "libraries/lib/" }
        links {"glfw3", "opengl32"}

        -- Source and header files
        files {
        "libraries/include/imgui/**.h",
        "libraries/include/imgui/**.cpp",
        "libraries/include/GLFW/**.h",
        "src/**.cpp",   -- All .cpp files in src and subdirectories
        "src/**.hpp",   -- All .hpp files in src and subdirectories
        "src/**.h"      -- All .h files in src and subdirectories
        }

        -- Include directories (common across configurations)
        includedirs {
        "libraries/include/",
        "libraries/include/imgui",
        "libraries/include/GLFW",
        "src/gui/include",
        "src/task/include",
        "src/utils/include",
        "src/datapool/include",
        "src/messages/include",
        "src/os/include"
        }

    -- Release configuration settings
    filter "configurations:Release"
        targetdir "build/bin/Release"  -- Output directory for Release
        objdir "build/obj/Release"     -- Object files for Release

        buildoptions { 
            "-O3",               -- As agro as possible optimization without allowing undefined behaviour.
            "-flto",             -- Link time optimization 
            "-ftree-vectorize",  -- SIMD where possible 
            "-march=native",     -- Windows specific code (for now)
            "-ffast-math",       -- Risky, but worth it.
            "-fno-math-errno",   -- No worthless errno in std::cmath
            "-mavx2",            -- Even more SIMD where possible
            "-fconcepts-diagnostics-depth=5"}

        optimize "On"  -- Enable optimization for Release
        symbols "Off"  -- Disable symbols for Release

        -- Link libraries (common across configurations)
        libdirs { "libraries/lib/" }
        links {"glfw3", "opengl32"}

        -- Files 
        files {
            "libraries/include/imgui/**.h",
            "libraries/include/imgui/**.cpp",
            "libraries/include/GLFW/**.h",
            "src/**.cpp",   -- All .cpp files in src and subdirectories
            "src/**.hpp",   -- All .hpp files in src and subdirectories
            "src/**.h"      -- All .h files in src and subdirectories
        }

        -- Include directories (common across configurations)
        includedirs {
            "libraries/include/",
            "libraries/include/imgui",
            "libraries/include/GLFW",
            "src/gui/include",
            "src/task/include",
            "src/utils/include",
            "src/datapool/include",
            "src/messages/include",
            "src/os/include"
        }

    -- Reset filter to avoid unintended configuration inheritance
    filter {}
