cmake_minimum_required(VERSION 3.20)

project(cpp-raylib-platformer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------
# Sources
# -------------------------
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

add_executable(${PROJECT_NAME} ${GAME_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/src"
)

# -------------------------
# Find raylib (3-step fallback)
# 1) find_package(raylib CONFIG)
# 2) pkg-config (common on macOS with brew)
# 3) manual RAYLIB_DIR (common on Windows zip/prebuilt)
# -------------------------
set(RAYLIB_DIR "" CACHE PATH "Path to raylib install root (contains include/ and lib/)")

# --- 1) Try raylib config package
find_package(raylib CONFIG QUIET)

if (raylib_FOUND)
    message(STATUS "Found raylib via find_package(raylib CONFIG)")
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
else()
    # --- 2) Try pkg-config
    find_package(PkgConfig QUIET)
    if (PkgConfig_FOUND)
        pkg_check_modules(RAYLIB QUIET raylib)
    endif()

    if (RAYLIB_FOUND)
        message(STATUS "Found raylib via pkg-config")
        target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_INCLUDE_DIRS})
        target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARY_DIRS})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARIES})
    else()
        # --- 3) Manual RAYLIB_DIR
        if (NOT RAYLIB_DIR)
            message(FATAL_ERROR
                "raylib not found.\n"
                "Set -DRAYLIB_DIR=... (a folder containing include/raylib.h and lib/...)"
            )
        endif()

        message(STATUS "Using manual raylib from: ${RAYLIB_DIR}")
        target_include_directories(${PROJECT_NAME} PRIVATE "${RAYLIB_DIR}/include")
        target_link_directories(${PROJECT_NAME} PRIVATE "${RAYLIB_DIR}/lib")

        if (WIN32)
            # Most raylib builds on Windows need these system libs
            target_link_libraries(${PROJECT_NAME} PRIVATE raylib opengl32 gdi32 winmm)
        elseif (APPLE)
            # raylib on macOS typically needs frameworks
            target_link_libraries(${PROJECT_NAME} PRIVATE raylib
                "-framework Cocoa"
                "-framework IOKit"
                "-framework OpenGL"
                "-framework CoreVideo"
            )
        else()
            # Linux (just in case)
            target_link_libraries(${PROJECT_NAME} PRIVATE raylib m pthread dl rt X11)
        endif()
    endif()
endif()

# -------------------------
# Copy assets next to the executable after build
# So you can load with: "assets/texture/xxx.png"
# -------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)

# Nice-to-have for MSVC: set startup to correct working dir when using VS
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)
