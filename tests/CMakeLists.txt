cmake_minimum_required(VERSION 3.20)
project(drogon_playground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This is the key for clangd IntelliSense:
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # or pass -DCMAKE_EXPORT_COMPILE_COMMANDS=ON :contentReference[oaicite:2]{index=2}

find_package(Drogon CONFIG REQUIRED)

add_executable(server src/main.cpp)
target_link_libraries(server PRIVATE Drogon::Drogon)
