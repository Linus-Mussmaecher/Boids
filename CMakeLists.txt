cmake_minimum_required(VERSION 3.21)
project(boids)

set(CMAKE_CXX_STANDARD 20)


#raylib
find_package(raylib REQUIRED)
include_directories(${RAYLIB_INCLUDE_DIRS})

add_executable(boids code/src/main.cpp code/src/basic/basic.h code/src/basic/boid.cpp code/src/ray_extend/ray_extend.h code/src/ray_extend/ray_extend.cpp code/src/basic/obstacle.cpp code/src/basic/basic.cpp code/src/teams/teams.h code/src/teams/teamboid.cpp code/src/teams/teams.cpp)

target_link_libraries(boids ${RAYLIB_LIBRARIES})

#copy resources folder into build folder
add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:boids>/resources)

add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/dll/ $<TARGET_FILE_DIR:boids>)