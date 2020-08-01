cmake_minimum_required(VERSION 3.0)
project(proc-mtn-view)

add_executable(proc-mtn-view
		${CMAKE_CURRENT_SOURCE_DIR}/src/common/perlin_noise

		${CMAKE_CURRENT_SOURCE_DIR}/src/pixel
		${CMAKE_CURRENT_SOURCE_DIR}/src/image
		${CMAKE_CURRENT_SOURCE_DIR}/src/layer
		${CMAKE_CURRENT_SOURCE_DIR}/src/main)
