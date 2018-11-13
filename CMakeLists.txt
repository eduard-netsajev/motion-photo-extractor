cmake_minimum_required (VERSION 3.12)
project ("Motion Photo Extractor"
         LANGUAGES CXX
         VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(mpe mpe.cpp)

install(TARGETS mpe RUNTIME DESTINATION bin)