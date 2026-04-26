cmake_minimum_required(VERSION 3.18)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SKIA_LIB ${CMAKE_SOURCE_DIR}/third_party/lib/skia/Debug/skia.lib)
else()
    set(SKIA_LIB ${CMAKE_SOURCE_DIR}/third_party/lib/skia/Release/skia.lib)
endif()

project(PhiVideo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_SYSTEM_VERSION 10.0.19041.0 CACHE STRING "" FORCE)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/third_party/include
    ${CMAKE_SOURCE_DIR}/third_party/include/skia
)

find_package(OpenGL REQUIRED)

add_executable (PhiVideo 
    src/Log/Log.h
    src/Log/Log.cpp

	src/Base/Base.h
    src/Base/Base.cpp
    src/Base/Maths.h
    src/Base/Maths.cpp

    src/Framebuffer/Texture.h 
    src/Framebuffer/Texture.cpp
    src/Framebuffer/Framebuffer.h
    src/Framebuffer/Framebuffer.cpp

    src/Application/Application.h
    src/Application/Application.cpp

	src/Main.cpp

    third_party/src/glad/glad.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    ${PROJECT_SOURCE_DIR}/third_party/lib/glfw/glfw3.lib
    ${SKIA_LIB}
    d3d12.lib
    dxgi.lib
    d3dcompiler.lib
    dxguid.lib
    user32.lib
)
