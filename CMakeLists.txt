# Usage:
# Create a build folder, cd into it and just do: cmake <PATH_TO_THE_PROJECT>
# Use '-DCMAKE_BUILD_TYPE=Debug' to enable -ggdb3 flag.

cmake_minimum_required(VERSION 3.1.0)

project(kiosk)

# Search for libraries below /
set(CMAKE_PREFIX_PATH ~/Qt5.8.0/5.8/gcc_64/)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run rcc automatically for inclusion of the resource files
# in the generated executable
set(CMAKE_AUTORCC ON)

# Make GCC stop on first error
add_definitions(
  -Wfatal-errors
)

# Use the appropriate standard library depending on the compiler selected
# by the environement variable
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
# This is what we should do but because of this Ubuntu bug:
# https://bugs.launchpad.net/ubuntu/+source/libc++/+bug/1610168 ...
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
# ... we have to do this
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Find the QtWebView library
find_package(Qt5Gui REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5WebView REQUIRED)

# Tell CMake to create the kiosk executable
add_executable(kiosk
  resources/resources.qrc
  src/main.cpp
  src/Interpreter.cpp
  src/KioskContext.cpp
)

# Use the Widgets module from Qt 5.
target_link_libraries(kiosk
	Qt5::Gui
	Qt5::Quick
	Qt5::WebView
)
