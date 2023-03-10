cmake_minimum_required (VERSION 3.8)

project ("automatic_derivation")

include_directories(
	${CMAKE_SOURCE_DIR}/inc
	${CMAKE_CURRENT_SOURCE_DIR}/../include
)

link_directories(
	${CMAKE_SOURCE_DIR}/lib
)

# get source list of the directory
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}  SRC_LIST)
# message(${SRC_LIST})

# add source to this project's library
add_executable(${PROJECT_NAME} ${SRC_LIST})