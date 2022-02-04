cmake_minimum_required(VERSION 3.21)
project(boids)

set(CMAKE_CXX_STANDARD 20)


#raylib
find_package(raylib REQUIRED)
include_directories(${RAYLIB_INCLUDE_DIRS})

add_executable(boids code/src/boids.cpp code/include/boids.h code/src/boid.cpp code/include/ray_extend.h code/src/ray_extend.cpp)

target_link_libraries(boids ${RAYLIB_LIBRARIES})

#copy resources folder into build folder
add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:boids>/resources)

add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/dll/ $<TARGET_FILE_DIR:boids>)