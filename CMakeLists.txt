cmake_minimum_required(VERSION 3.21)
project(boids)

set(CMAKE_CXX_STANDARD 20)


#raylib
find_package(raylib REQUIRED)
include_directories(${RAYLIB_INCLUDE_DIRS})

add_executable(boids code/src/main.cpp code/src/boids2D/boids.h code/src/boids2D/boid.cpp code/src/ray_extend/ray_extend.h code/src/ray_extend/ray_extend.cpp code/src/boids2D/obstacle.cpp code/src/boids2D/boids.cpp code/src/boids3D/boids3D.h code/src/boids3D/boids3D.cpp code/src/boids3D/boid3D.cpp code/src/boids3D/obstacle3D.cpp)

target_link_libraries(boids ${RAYLIB_LIBRARIES})

#copy resources folder into build folder
add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:boids>/resources)

add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/dll/ $<TARGET_FILE_DIR:boids>)