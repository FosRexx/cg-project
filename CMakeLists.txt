# Set the cmake minimum version to 3.5.1
cmake_minimum_required(VERSION 3.5.1)

# Define the project name
project(cg-project)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Add all c++ source files under the src directory
file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add compiler errors/warnings flags
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX /O2>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -g -O2>)

# Setting to automatically generate compile_commands required by linters
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Link math.h
target_link_libraries(${PROJECT_NAME} m)
# Linking dl
target_link_libraries(${PROJECT_NAME} dl)

# Add SDL2 library
# If windows use SDL libraries provided in .sdl2
IF (WIN32)
	set(SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2" CACHE BOOL "" FORCE)
	set(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2/include" "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2/include/SDL2" CACHE BOOL "" FORCE)
ENDIF()
# Else for anything else use system's SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_image library
# If windows use SDL libraries provided in .sdl2
IF (WIN32)
	set(SDL2_IMAGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2" CACHE BOOL "" FORCE)
	set(SDL2_IMAGE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2/include" "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2/include/SDL2" CACHE BOOL "" FORCE)
ENDIF()
# Else for anything else use system's SDL2
find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Image)

# Add SDL2_ttf library
# If windows use SDL libraries provided in .sdl2
IF (WIN32)
	set(SDL2_TTF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2" CACHE BOOL "" FORCE)
	set(SDL2_TTF_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2/include" "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2/include/SDL2" CACHE BOOL "" FORCE)
ENDIF()
# Else for anything else use system's SDL2
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Net)

# Add SDL2_mixer library
# If windows use SDL libraries provided in .sdl2
IF (WIN32)
	set(SDL2_MIXER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2" CACHE BOOL "" FORCE)
	set(SDL2_MIXER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2/include" "${CMAKE_CURRENT_SOURCE_DIR}/.sdl2/include/SDL2" CACHE BOOL "" FORCE)
ENDIF()
# Else for anything else use system's SDL2
find_package(SDL2_mixer REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

# Add SDL2_gfx library
#find_package(SDL2_gfx REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::GFX)
