cmake_minimum_required(VERSION 3.20)

project(order_book)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(order_book
    app/main.cpp
)

target_include_directories(order_book
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
