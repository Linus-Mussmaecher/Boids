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

# Add source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/code/src/*")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/code/src/")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

# link raylib
target_link_libraries(boids PRIVATE raylib)

#copy resources folder into build folder
add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:boids>/resources)

add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/dll/ $<TARGET_FILE_DIR:boids>)
