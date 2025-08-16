cmake_minimum_required(VERSION 3.10)
project(AlgorithmVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/usr/local" ${CMAKE_PREFIX_PATH})

find_package(SFML COMPONENTS Graphics Window REQUIRED)

message(STATUS "Found SFML version: ${SFML_VERSION}")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML::Graphics
    SFML::Window
)

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

file(GLOB FONT_FILES "${CMAKE_SOURCE_DIR}/*.ttf" "${CMAKE_SOURCE_DIR}/*.otf" "${CMAKE_SOURCE_DIR}/*.ttc")
foreach(FONT_FILE ${FONT_FILES})
    get_filename_component(FONT_NAME ${FONT_FILE} NAME)
    configure_file(${FONT_FILE} ${CMAKE_BINARY_DIR}/${FONT_NAME} COPYONLY)
    message(STATUS "Copying font: ${FONT_NAME}")
endforeach()

if(EXISTS "${CMAKE_SOURCE_DIR}/DejaVuSans.ttf")
    file(COPY ${CMAKE_SOURCE_DIR}/DejaVuSans.ttf DESTINATION ${CMAKE_BINARY_DIR})
    message(STATUS "✅ DejaVuSans.ttf copied to build directory")
else()
    message(WARNING "❌ DejaVuSans.ttf not found in source directory")
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/arial.ttf")
    file(COPY ${CMAKE_SOURCE_DIR}/arial.ttf DESTINATION ${CMAKE_BINARY_DIR})
    message(STATUS "✅ arial.ttf copied to build directory")
endif()

message(STATUS "Build directory: ${CMAKE_BINARY_DIR}")
message(STATUS "Source directory: ${CMAKE_SOURCE_DIR}")