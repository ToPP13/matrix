cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(matrix VERSION 0.0.1)
endif ()

# Load settings for an external project.
find_package (GTest REQUIRED)
find_package (Threads REQUIRED)

include_directories (
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Copy a file to another location and modify its contents.
configure_file(version.h.in version.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
file (GLOB MAIN_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        )
file (GLOB MAIN_TEST
        ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp
        )
file (GLOB MAIN_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*
        )


source_group("src" FILES ${MAIN_SRC})
source_group("test" FILES ${MAIN_TEST})
source_group("include" FILES ${MAIN_INCLUDES})


# Add an executable to the project using the specified source files.
add_executable(matrix_cli src/matrix.cpp )
# Add a library to the project using the specified source files.
add_library(matrix src/lib.cpp )
add_executable(gtest test/gtest.cpp)


# Set propertiess to a target.
set_target_properties(matrix_cli matrix gtest PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Add include directories to a target.
# CMAKE_BINARY_DIR - The path to the top level of the build tree.
target_include_directories(matrix PRIVATE "${CMAKE_BINARY_DIR}" )

# Add include directories to the build.
include_directories(${GTEST_INCLUDE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set_target_properties(gtest PROPERTIES
    INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(matrix_cli PRIVATE matrix)
target_link_libraries(gtest ${GTEST_LIBRARIES} matrix ${GTEST_MAIN_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Add compile options to a target.
if (MSVC)
    target_compile_options(matrix_cli PRIVATE
        /W4
    )
    target_compile_options(matrix PRIVATE
        /W4
    )
    target_compile_options(gtest PRIVATE
        /W4
    )
else ()    
    target_compile_options(matrix_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(gtest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



# Load and run CMake code from a file or module.
install(TARGETS matrix_cli RUNTIME DESTINATION bin)

# Set a CMake, cache or environment variable to a given value.
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT martynovich@protei.ru)

include(CPack)

# Enable testing for current directory and below.
enable_testing()

# Add a test to the project to be run by ctest(1).
add_test(gtest gtest)

