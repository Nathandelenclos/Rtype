cmake_minimum_required(VERSION 3.25)
project(r-type_server)

set(CMAKE_CXX_STANDARD 17)


add_executable(r-type_server_network
        shared/USocket.hpp
        server/ServerSocket.cpp
        server/ServerSocket.hpp
        server/main.cpp
)
if(WIN32)
    target_link_libraries(r-type_server_network ws2_32)
endif()

add_executable(r-type_client_network
        shared/USocket.hpp
        client/ClientSocket.cpp
        client/ClientSocket.hpp
        client/main.cpp)
if(WIN32)
    target_link_libraries(r-type_client_network ws2_32)
endif()
