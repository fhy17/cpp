project(regex)

# add include directory
include_directories(${CMAKE_SOURCE_DIR}/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# get source list of the directory
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
# message(${CMAKE_CURRENT_SOURCE_DIR})

# message(${SRC_LIST})


# if(MSVC)
#     set(VERSIONINFO_RC "${PROJECT_SOURCE_DIR}/version_info.rc")
#     configure_file("${PROJECT_SOURCE_DIR}/version_info.rc.in" "${VERSIONINFO_RC}")
# endif()

# add source to this project's library dll
# add_library(${PROJECT_NAME} STATIC ${SRC_LIST} ${VERSIONINFO_RC})
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
