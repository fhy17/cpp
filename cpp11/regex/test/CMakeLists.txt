cmake_minimum_required (VERSION 3.8)

project ("regex_test")

include_directories(
	${CMAKE_SOURCE_DIR}/inc
	${CMAKE_SOURCE_DIR}/external_dependencies/googletest/include
	${CMAKE_CURRENT_SOURCE_DIR}/../include
)

link_directories(
	${CMAKE_SOURCE_DIR}/lib
	${GOOGLE_TEST_LIB_PATH}
)

# get source list of the directory
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}  SRC_LIST)

# message(${SRC_LIST})


# add source to this project's library
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PUBLIC
	regex
	gtest
	gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})