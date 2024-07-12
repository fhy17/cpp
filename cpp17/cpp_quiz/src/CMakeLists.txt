cmake_minimum_required (VERSION 3.8)

project ("cpp_quiz")

include_directories(
	${CMAKE_SOURCE_DIR}/inc
	${CMAKE_CURRENT_SOURCE_DIR}/../include
#	${CMAKE_SOURCE_DIR}/../extern/boost/include/boost-1_77
	# D:/Apps/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.39.33519/include
)

link_directories(
	${CMAKE_SOURCE_DIR}/lib
)

# get source list of the directory
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}  SRC_LIST)
# message(${SRC_LIST})

# add source to this project's library
add_executable(${PROJECT_NAME} ${SRC_LIST})