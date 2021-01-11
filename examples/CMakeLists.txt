#
# Created by Aleix Alcacer Sales on 08/01/2021.
#


file(GLOB SOURCES example_*.c)

foreach (source ${SOURCES})
    get_filename_component(target_name ${source} NAME_WE)
    set(target cutest_${target_name})
    add_executable(${target} ${target_name}.c)
endforeach (source)
