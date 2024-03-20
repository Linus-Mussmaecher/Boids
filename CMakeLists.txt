cmake_minimum_required(VERSION 3.21)
project(boids)

set(CMAKE_CXX_STANDARD 20)



# Allow fetching content from repos
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Fetch raylib
FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

add_executable(boids code/src/main.cpp code/src/boids2D/boids.h code/src/boids2D/boid.cpp code/src/ray_extend/ray_extend.h code/src/ray_extend/ray_extend.cpp code/src/boids2D/obstacle.cpp code/src/boids2D/boids.cpp)

# link raylib
target_link_libraries(boids PRIVATE raylib)

#copy resources folder into build folder
add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:boids>/resources)

add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/dll/ $<TARGET_FILE_DIR:boids>)
