cmake_minimum_required(VERSION 3.18)
project(PhiVideo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_SYSTEM_VERSION 10.0.19041.0 CACHE STRING "" FORCE)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (PhiVideo 
	
	"src/PhiVideo/Main.cpp"

)
