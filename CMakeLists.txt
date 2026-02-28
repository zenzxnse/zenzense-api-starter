cmake_minimum_required(VERSION 3.20)

project(ZENZENSE_API_STARTER LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Packages (via vcpkg manifest: vcpkg.json) ----
find_package(Drogon CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# Cassandra C++ driver (vcpkg: cassandra-cpp-driver)
# Depending on port, this is usually Cassandra::cassandra
find_package(Cassandra CONFIG REQUIRED)

# ---- App target ----
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${APP_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Drogon::Drogon
  Cassandra::cassandra
)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- Tests ----
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
)

if(TEST_SOURCES)
  add_executable(unit_tests ${TEST_SOURCES})

  target_include_directories(unit_tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
  )

  target_link_libraries(unit_tests PRIVATE
    Catch2::Catch2WithMain
    Drogon::Drogon
    Cassandra::cassandra
  )

  enable_testing()
  add_test(NAME UnitTests COMMAND unit_tests)
endif()