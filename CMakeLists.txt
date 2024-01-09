cmake_minimum_required(VERSION 3.25)
project(r-type)

include_directories(include)

include(src/client/CMakeLists.txt)

include(src/lib/r_type/CMakeLists.txt)

include(src/server/CMakeLists.txt)
