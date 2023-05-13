#
# Created by tim4ukys on 13.05.2023.
#
cmake_minimum_required(VERSION 3.10)

project(MapConstructor)

find_package(SFML REQUIRED window)
find_package(ImGui-SFML)

include_directories(${SFML_INCLUDE_DIR})
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ImGui-SFML::ImGui-SFML sfml-graphics ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/Nonogram/map-constructor)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/resource/roboto.ttf
            ${OUTPUT_DIR}/roboto.ttf
        )
