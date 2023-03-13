# CMakeList.txt: main 项目文件

project ("delegate_constructor")

# set output oath of library
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# add include directory
# include_directories(${PROJECT_SOURCE_DIR}/inc)

# get source list of the directory
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

# message(${CMAKE_CURRENT_SOURCE_DIR})

# message(${SRC_LIST})

# add source to this project's library
add_executable(${PROJECT_NAME} ${SRC_LIST})
