cmake_minimum_required(VERSION 3.28)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(img2ascii VERSION 0.0 LANGUAGES C)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.c)
add_executable(img2ascii ${sources})

target_include_directories(img2ascii PRIVATE include)
target_link_libraries(img2ascii PRIVATE -lm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

install(TARGETS img2ascii RUNTIME DESTINATION bin)
