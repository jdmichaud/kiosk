cmake_minimum_required(VERSION 3.5.1)

project(kiosk)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run rcc automatically for inclusion of the resource files
# in the generated executable
set(CMAKE_AUTORCC ON)


# Find the QtWebView library
find_package(Qt5WebView REQUIRED)

# Tell CMake to create the kiosk executable
add_executable(kiosk 
  resources.qrc
  src/main.cpp
)

# Use the Widgets module from Qt 5.
target_link_libraries(kiosk Qt5::WebView)
