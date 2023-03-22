cmake_minimum_required(VERSION 3.21)
project(PassarattiRacing LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(PassarattiRacing src/main.cpp)
target_link_libraries(PassarattiRacing PRIVATE sfml-graphics)
target_compile_features(PassarattiRacing PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET PassarattiRacing POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:PassarattiRacing> $<TARGET_FILE_DIR:PassarattiRacing> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS PassarattiRacing)
