cmake_minimum_required(VERSION 3.10)

project(TallerImagenes)

find_package(OpenCV REQUIRED)

include_directories(include)

add_executable(taller
    src/main.cpp
    src/filtros.cpp
)

target_link_libraries(taller ${OpenCV_LIBS})