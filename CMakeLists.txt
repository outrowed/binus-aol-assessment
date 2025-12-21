cmake_minimum_required(VERSION 3.16)

project(azza_proj C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(GLOB COMP_DIRS RELATIVE "${CMAKE_SOURCE_DIR}" "COMP*")

foreach(comp_dir ${COMP_DIRS})
  if(NOT IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${comp_dir}")
    continue()
  endif()

  file(GLOB comp_sources CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/${comp_dir}/*.c")
  set(main_source "${CMAKE_SOURCE_DIR}/${comp_dir}/main.c")

  if(EXISTS "${main_source}")
    add_executable("${comp_dir}" ${comp_sources})
    target_include_directories("${comp_dir}" PRIVATE "${CMAKE_SOURCE_DIR}/${comp_dir}")
  endif()
endforeach()
