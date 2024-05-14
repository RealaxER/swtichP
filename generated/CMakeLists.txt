cmake_minimum_required(VERSION 3.5)
project(panel)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)


message("Cmake from Bui Dinh Hien")
# set path
set(PATH_LIB /home/bhien/work/screen_ssd202d/ssd2xx-demo/4.littlevgl/)
set(PATH_CUSTOM /home/bhien/GUI-Guider-Projects/Panel/custom/)
# set path lib lumi
# set(PATH_LIB_LUMI /home/bhien/lib_lumi)
# set(TARGET /home/bhien/work/ssd202d.host/host/arm-buildroot-linux-gnueabihf/sysroot)


set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
# Set compiler
set(CMAKE_CXX_COMPILER /home/bhien/work/ssd202d.host/host/bin/arm-linux-gnueabihf-g++)
set(CMAKE_C_COMPILER /home/bhien/work/ssd202d.host/host/bin/arm-linux-gnueabihf-gcc)

# set(CMAKE_C_FLAGS "-march=armv7-a -mfpu=neon -mfloat-abi=hard --sysroot=${TARGET}")
# set(CMAKE_CXX_FLAGS "-march=armv7-a -mfpu=neon -mfloat-abi=hard --sysroot=${TARGET}")

# Suppress warnings for GCC
if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 7.1)
    add_compile_options(-Wno-psabi)
endif()

# Adjust the default behaviour of the find commands:
# Search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# Search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)


# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PATH_CUSTOM}
    ${PATH_LIB}
    ${PATH_LIB}/lvgl/
    ${PATH_LIB}/lv_drivers/
    # ${PATH_LIB_LUMI}
)

# Include and set lib for Lib Lumi
# include_directories(${PATH_LIB_LUMI}/Libraries/Atomic)
# include_directories(${PATH_LIB_LUMI}/Libraries/Crypto)
# include_directories(${PATH_LIB_LUMI}/Libraries/Functors)
# include_directories(${PATH_LIB_LUMI}/Libraries/Log)
# include_directories(${PATH_LIB_LUMI}/Libraries/Signal)
# include_directories(${PATH_LIB_LUMI}/Libraries/ThirdParty)
# include_directories(${PATH_LIB_LUMI}/Libraries/Thread)
# include_directories(${PATH_LIB_LUMI}/Libraries/Timer)
# include_directories(${PATH_LIB_LUMI}/Libraries/Type)
# include_directories(${PATH_LIB_LUMI}/Libraries/Utils)
# include_directories(${PATH_LIB_LUMI}/Libraries/Values)
# include_directories(${PATH_LIB_LUMI}/Sources/Atomic)
# include_directories(${PATH_LIB_LUMI}/Sources/Crypto)
# include_directories(${PATH_LIB_LUMI}/Sources/JsonConfigure)
# include_directories(${PATH_LIB_LUMI}/Sources/Log)
# include_directories(${PATH_LIB_LUMI}/Sources/ThirdParty)
# include_directories(${PATH_LIB_LUMI}/Sources/Thread)
# include_directories(${PATH_LIB_LUMI}/Sources/Timer)
# include_directories(${PATH_LIB_LUMI}/Sources/Utils)
# include_directories(${PATH_LIB_LUMI}/Sources/Values)

# link_libraries(pthread crypto ssl rt dl mosquitto)

add_definitions(-DUSE_LOG_FILE)

message(STATUS "HOME:=$ENV{HOME}")
message(STATUS "CMAKE_BUILD_TYPE:=${CMAKE_BUILD_TYPE}")
message(STATUS "PLATFORM:=${PLATFORM}")


# Set sources
file(GLOB_RECURSE IMAGE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/images/*.c)
file(GLOB_RECURSE FONT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/guider_fonts/*.c)
# file(GLOB_RECURSE SOURCES_LUMI
#         "${PATH_LIB_LUMI}/Libraries/Atomic/*"
#         "${PATH_LIB_LUMI}/Libraries/Crypto/*"
#         "${PATH_LIB_LUMI}/Libraries/Functors/*"
#         "${PATH_LIB_LUMI}/Libraries/Log/*"
#         "${PATH_LIB_LUMI}/Libraries/Signal/*"
#         "${PATH_LIB_LUMI}/Libraries/ThirdParty/*"
#         "${PATH_LIB_LUMI}/Libraries/Thread/*"
#         "${PATH_LIB_LUMI}/Libraries/Timer/*"
#         "${PATH_LIB_LUMI}/Libraries/Type/*"
#         "${PATH_LIB_LUMI}/Libraries/Utils/*"
#         "${PATH_LIB_LUMI}/Libraries/Values/*"
#         "${PATH_LIB_LUMI}/Sources/Atomic/*"
#         "${PATH_LIB_LUMI}/Sources/Crypto/*"
#         "${PATH_LIB_LUMI}/Sources/JsonConfigure/*"
#         "${PATH_LIB_LUMI}/Sources/Log/*"
#         "${PATH_LIB_LUMI}/Sources/ThirdParty/*"
#         "${PATH_LIB_LUMI}/Sources/Thread/*"
#         "${PATH_LIB_LUMI}/Sources/Timer/*"
#         "${PATH_LIB_LUMI}/Sources/Utils/*"
#         "${PATH_LIB_LUMI}/Sources/Values/*"
# )

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/setup_scr_screen.c
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/gui_guider.c
    ${CMAKE_CURRENT_SOURCE_DIR}/events_init.c
)



# Library sources
file(GLOB_RECURSE LIB_SOURCES ${PATH_LIB}/lvgl/*.c)
file(GLOB_RECURSE LIB_SOURCES_DRIVER ${PATH_LIB}/lv_drivers/*.c)

# Build libraries
add_library(lvgl STATIC ${LIB_SOURCES})
add_library(lv_drivers STATIC ${LIB_SOURCES_DRIVER})
#add_library(lumi STATIC ${SOURCES_LUMI})


# Build executable
add_executable(panel main.cc ${SOURCES} ${IMAGE_SOURCES} ${FONT_SOURCES})

# Link libraries
target_link_libraries(panel pthread lvgl lv_drivers)
#install(TARGETS panel RUNTIME DESTINATION bin)
