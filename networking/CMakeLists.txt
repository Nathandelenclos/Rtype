cmake_minimum_required(VERSION 3.25)
project(r-type_server)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(r-type_server_network
        shared/USocket.hpp
)

add_executable(r-type_client
        shared/USocket.hpp
)
