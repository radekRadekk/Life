cmake_minimum_required(VERSION 3.10)
project(Life C)

set(CMAKE_C_STANDARD 99)

add_executable(Life main.c cell.c cell.h field.c field.h game.c game.h)