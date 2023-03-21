cmake_minimum_required(VERSION 3.20)
project(wordappcpp C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS} "/usr/include/gtkmm-3.0")
link_directories(${GTKMM_LIBRARY_DIRS})

set(SOURCE_FILES src/main.cpp src/common/utils.cpp src/common/utils.hpp src/comps/MainWindow.cpp src/comps/MainWindow.hpp src/comps/CsvGrid.cpp src/comps/CsvGrid.hpp src/common/parser.cpp src/common/parser.hpp src/common/picker.cpp src/common/picker.hpp src/common/logger.cpp src/common/logger.hpp src/common.hpp src/comps/SessionWindow.cpp src/comps/SessionWindow.hpp src/common/structs.hpp src/common/structs.cpp src/comps/SessionClock.cpp src/comps/SessionClock.hpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})
