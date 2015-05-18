cmake_minimum_required(VERSION 2.6)
project(AnimatedSortingAlgorithms)

add_definitions(-std=c++11)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Set version information in a config.h file
set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SFML_ROOT C:/SFML/SFML-2.3)

#add_subdirectory(src)
#add_subdirectory(lib)

# Define sources and executable
set(EXECUTABLE_NAME "SortingAlgorithms")
set(PROJ_SRCS Bar.cpp bubblesort.cpp handle.cpp heapsort.cpp insertionsort.cpp mergesort.cpp quicksort.cpp randomtoolkit.cpp selectionsort.cpp Source.cpp)
add_executable(${EXECUTABLE_NAME} ${PROJ_SRCS})

# Bar.hpp bubblesort.hpp handle.hpp heapsort.hpp insertionsort.hpp mergesort.hpp quicksort.hpp randomtoolkit.hpp selectionsort.hpp

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# # Install target
# install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# # CPack packaging
# include(InstallRequiredSystemLibraries)
# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
# set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
# set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
# include(CPack)