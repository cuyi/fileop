include_directories(${PROJECT_SOURCE_DIR}/src/)

aux_source_directory(read SRC_LIST)
aux_source_directory(write SRC_LIST)

add_executable(fileop main.c common.c ${SRC_LIST})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)