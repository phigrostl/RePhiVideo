cmake_minimum_required(VERSION 3.18)
project(PhiVideo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_SYSTEM_VERSION 10.0.19041.0 CACHE STRING "" FORCE)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (PhiVideo 
	
	"src/PhiVideo/Main.cpp"

	"src/PhiVideo/Base/Base.h"
    "src/PhiVideo/Base/Base.cpp"
    "src/PhiVideo/Base/Maths.h"
    "src/PhiVideo/Base/Maths.cpp"

    "src/PhiVideo/Framebuffer/Texture.h"
    "src/PhiVideo/Framebuffer/Texture.cpp"
    "src/PhiVideo/Framebuffer/Framebuffer.h"
    "src/PhiVideo/Framebuffer/Framebuffer.cpp"

    "src/PhiVideo/Log/Log.h"
    "src/PhiVideo/Log/Log.cpp"

    "src/PhiVideo/stb/stb_image.cpp"
    "src/PhiVideo/stb/stb_truetype.cpp"
    "src/PhiVideo/stb/std_image_resize2.cpp"
    "src/PhiVideo/stb/stb_image_write.cpp"

)
