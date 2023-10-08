cmake_minimum_required(VERSION 3.17)
project(GameLife)

set(CMAKE_CXX_STANDARD 20)

add_executable(${CMAKE_PROJECT_NAME}
       main.cpp
)

set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)


find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} sfml-audio sfml-network sfml-graphics sfml-window sfml-system)