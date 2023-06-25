cmake_minimum_required(VERSION 3.25)
project(learn_ssdeep C)

set(CMAKE_C_STANDARD 11)

add_executable(learn_ssdeep main.c fuzzy.c edit_dist.c)
