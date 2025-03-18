cmake_minimum_required(VERSION 3.20)

project(sdl_dekstop_pet VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set( CMAKE_CXX_FLAGS "-g" )

# Set source directory
set( SDL_TTRL_SRC src/*.cpp )
set( FONT_DIR res/fonts/DejaVuSansMono )
set(FREETYPE_INCLUDE_DIRS "D:/msys64/mingw64/include/freetype2")
set(FREETYPE_LIBRARY "D:/msys64/mingw64/lib/libfreetype.dll.a")

string(ASCII 27 Esc)
set(ColourReset "${Esc}[0m")
set(ColourBold  "${Esc}[1m")
set(Red         "${Esc}[31m")
set(Green       "${Esc}[32m")
set(Yellow      "${Esc}[33m")
set(Blue        "${Esc}[34m")
set(Magenta     "${Esc}[35m")
set(Cyan        "${Esc}[36m")
set(White       "${Esc}[37m")
set(BoldRed     "${Esc}[1;31m")
set(BoldGreen   "${Esc}[1;32m")
set(BoldYellow  "${Esc}[1;33m")

find_package(fmt REQUIRED)
if(fmt_FOUND)
  message(STATUS "fmt found")
endif()
find_package(spdlog REQUIRED)
if (spdlog_FOUND)
  message( STATUS "spdlog Found")
  message(STATUS "Spdlog include dir : ${spdlog_DIR}")
else()
  message( STATUS "spdlog Not Found")
endif()
include( FetchContent )

FetchContent_Declare(
  microsoft-gsl
  GIT_REPOSITORY "https://github.com/microsoft/GSL.git"
  GIT_TAG "v4.1.0"
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(microsoft-gsl)

FetchContent_Declare(
  json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Collect source files
file( GLOB_RECURSE SOURCES "src/*.cpp" )
set(SDL3_DIR "C:/Program Files/SDL-3.2.6/lib/cmake/SDL3")
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_ttf REQUIRED CONFIG REQUIRED SDL3_ttf-shared)
find_package(SDL3_image REQUIRED CONFIG REQUIRED SDL3_image-shared)
find_package(flecs REQUIRED)
message(STATUS "${Magenta}SDL3 Version: ${ColourReset}${SDL3_VERSION}")
message(STATUS "${Magenta}SDL3_ttf Version: ${ColourReset}${SDL3_ttf_VERSION}")
message(STATUS "${Magenta}SDL3_image Version: ${ColourReset}${SDL3_image_VERSION}")
message(STATUS "${Blue}SDL3 Dir: ${ColourReset}${SDL3_DIR}")
message(STATUS "${Blue}SDL3_ttf Dir: ${ColourReset}${SDL3_ttf_DIR}")
message(STATUS "${Blue}SDL3_image Dir: ${ColourReset}${SDL3_image_DIR}")
message(STATUS "${Blue}SDL3 DLL: ${ColourReset}${SDL3_DIR}/../../bin/SDL3.dll")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

include_directories( "src/" )
include_directories( "src/vendor" )

# Add include directory
target_include_directories(${PROJECT_NAME} PRIVATE 
  ${SRC_DIR}
)

target_compile_options(
  ${PROJECT_NAME} PRIVATE -Wall
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE SDL3::SDL3
  PRIVATE SDL3_ttf::SDL3_ttf
  PRIVATE SDL3_image::SDL3_image
  PRIVATE Microsoft.GSL::GSL
  PRIVATE flecs::flecs
  PRIVATE nlohmann_json::nlohmann_json
  PRIVATE spdlog
  PRIVATE fmt::fmt
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/asset.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/src/asset.hpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
)

# add_custom_command(TARGET sdl_dekstop_pet POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         "${SDL3_DIR}/../../../bin/SDL3.dll"
#         "${SDL3_image_DIR}/../../../bin/SDL3_image.dll"
# #         "C:/Program Files/flecs/bin/flecs.dll"
#         $<TARGET_FILE_DIR:sdl_dekstop_pet>
# )
#
