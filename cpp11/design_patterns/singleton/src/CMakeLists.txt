cmake_minimum_required (VERSION 3.8)

project(singleton VERSION 1.0.0.1)

# add include directory
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../include
	${CMAKE_SOURCE_DIR}/inc
)

# add link directory
link_directories(
	${CMAKE_SOURCE_DIR}/lib
)


# get source list of the directory
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
# message(${SRC_LIST})

# if(MSVC)
#     set(VERSIONINFO_RC "${CMAKE_CURRENT_SOURCE_DIR}/version_info.rc")
#     configure_file("${CMAKE_CURRENT_SOURCE_DIR}/version_info.rc.in" "${VERSIONINFO_RC}")
# endif()

# add source to this project's executable
# add_executable(${PROJECT_NAME} ${SRC_LIST} ${VERSIONINFO_RC})
add_executable(${PROJECT_NAME} ${SRC_LIST})