cmake_minimum_required(VERSION 3.23)
project(wordappcpp C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

set(SOURCE_FILES src/main.cpp src/utils.cpp src/utils.hpp src/comps/MainWindow.cpp src/comps/MainWindow.hpp src/comps/CsvGrid.cpp src/comps/CsvGrid.hpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})