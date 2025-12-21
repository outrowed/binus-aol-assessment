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

    set(target_output_dir "${CMAKE_BINARY_DIR}/${comp_dir}")
    set_target_properties("${comp_dir}" PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${target_output_dir}"
    )

    set(prepare_output_script "${CMAKE_BINARY_DIR}/cmake/prepare_${comp_dir}_output.cmake")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/cmake")
    file(WRITE "${prepare_output_script}"
      "if(EXISTS \"${target_output_dir}\" AND NOT IS_DIRECTORY \"${target_output_dir}\")\n"
      "  file(REMOVE \"${target_output_dir}\")\n"
      "endif()\n"
      "file(MAKE_DIRECTORY \"${target_output_dir}\")\n"
    )

    add_custom_command(TARGET "${comp_dir}" PRE_LINK
      COMMAND "${CMAKE_COMMAND}" -P "${prepare_output_script}"
    )

    add_custom_command(TARGET "${comp_dir}" POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy_directory
              "${CMAKE_SOURCE_DIR}/${comp_dir}"
              "${target_output_dir}"
      COMMENT "Copying ${comp_dir} assets to ${target_output_dir}"
    )
  endif()
endforeach()
