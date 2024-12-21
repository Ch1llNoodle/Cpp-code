cmake_minimum_required(VERSION 3.10...3.22)
project(MyProject LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置CMAKE_PREFIX_PATH
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};D:/Scoop/apps/vcpkg/current/installed/x64-windows")

# Find packages
find_package(CURL CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

# Add executable
add_executable(exchange exchange.cpp)

# Link libraries
target_link_libraries(exchange PRIVATE
  CURL::libcurl
  jsoncpp_lib
)