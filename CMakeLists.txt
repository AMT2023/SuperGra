cmake_minimum_required(VERSION 3.21)
project(PassarattiRacing LANGUAGES CXX)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_executable(PassarattiRacing src/main.cpp)
target_link_libraries(PassarattiRacing PRIVATE sfml-graphics)
target_compile_features(PassarattiRacing PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET PassarattiRacing POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:PassarattiRacing> $<TARGET_FILE_DIR:PassarattiRacing> COMMAND_EXPAND_LISTS)
endif()
# #file(CREATE_LINK ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets SYMBOLIC)
install(TARGETS PassarattiRacing)
