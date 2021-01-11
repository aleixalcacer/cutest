#
# Created by Aleix Alcacer Sales on 08/01/2021.
#


cmake_minimum_required(VERSION 3.17)
project(cutest C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES example_*.c)

foreach (source ${SOURCES})
    get_filename_component(target_name ${source} NAME_WE)
    set(target cutest_${target_name})
    add_executable(${target} ${target_name}.c)
endforeach (source)
