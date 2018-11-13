cmake_minimum_required (VERSION 3.12)
project ("Motion Photo Extractor"
         LANGUAGES CXX
         VERSION 0.1)

add_executable(mpe mpe.cpp)

install(TARGETS mpe RUNTIME DESTINATION bin)