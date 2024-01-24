cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

project(sortVisualiser)

set(BUBBLE_SOURCE
    bubbleSort.cpp)

add_executable(bubbleSort ${BUBBLE_SOURCE})

target_link_libraries(
  bubbleSort PRIVATE
  /Library/Frameworks/SDL2.framework/Versions/A/SDL2
)

target_include_directories(
  bubbleSort PRIVATE
  /Library/Frameworks/SDL2.framework/Versions/A/Headers
)

set(INSERTION_SOURCE
    insertionSort.cpp)

add_executable(insertionSort ${INSERTION_SOURCE})

target_link_libraries(
  insertionSort PRIVATE
  /Library/Frameworks/SDL2.framework/Versions/A/SDL2
)

target_include_directories(
  insertionSort PRIVATE
  /Library/Frameworks/SDL2.framework/Versions/A/Headers
)
