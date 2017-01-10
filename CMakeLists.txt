cmake_minimum_required(VERSION 2.8)

project(FGETOPTCC)

find_package(Threads)

if (CMAKE_COMPILER_IS_GNUCC)
    set(MY_C_FLAGS "-Wall -I../ -I../src/")
    set(CMAKE_C_FLAGS "-O0 ${MY_C_FLAGS}")
else ()
    message(FATAL_ERROR, "Cannot build on non Unix systems")
endif ()

add_library(fgetoptcc STATIC src/fgetopt.c)

if (build_share_lib)
    add_library(fgetopt SHARED src/fgetopt.c)
    install(TARGETS fgetopt DESTINATION lib)
endif ()

if (build_examples_c)
    add_executable(use_fgetopt_c examples/use_fgetopt_c.c)
    add_executable(use_fgetopt_alias_c examples/use_fgetopt_alias_c.c)
    if (build_share_lib)
        target_link_libraries(use_fgetopt_c fgetopt)
        target_link_libraries(use_fgetopt_alias_c fgetopt)
    else ()
        target_link_libraries(use_fgetopt_c fgetoptcc)
        target_link_libraries(use_fgetopt_alias_c fgetoptcc)
    endif ()
endif ()

if (build_examples_cxx)
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(MY_CXX_FLAGS "-Wall -I../ -I../src/")
        set(CMAKE_CXX_FLAGS "-O0 ${MY_CXX_FLAGS}")
    else ()
        message(FATAL_ERROR, "Cannot build on non Unix systems")
    endif ()

    add_executable(use_fgetopt_cpp examples/use_fgetopt_cpp.cc)
    add_executable(use_fgetopt_alias_cpp examples/use_fgetopt_alias_cpp.cc)
    if (build_share_lib)
        target_link_libraries(use_fgetopt_cpp fgetopt)
        target_link_libraries(use_fgetopt_alias_cpp fgetopt)
    else ()
        target_link_libraries(use_fgetopt_cpp fgetoptcc)
        target_link_libraries(use_fgetopt_alias_cpp fgetoptcc)
    endif ()
endif ()

install(TARGETS fgetoptcc DESTINATION lib)
install(FILES src/fgetopt.h DESTINATION include)

################################
# Testing
################################
if (test)
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(MY_CXX_FLAGS "-Wall -I../ -I../src/")
        set(CMAKE_CXX_FLAGS "-O0 ${MY_CXX_FLAGS}")
    else ()
        message(FATAL_ERROR, "Cannot build on non Unix systems")
    endif ()

    if (DEFINED ENV{GTEST_ROOT})
        message("... using gtest found in $ENV{GTEST_ROOT}")
        # This adds another subdirectory, which has 'project(gtest)'.
        add_subdirectory($ENV{GTEST_ROOT} ${CMAKE_CURRENT_BINARY_DIR}/extrn)
 
        enable_testing()

        # Include the gtest library. gtest_SOURCE_DIR is available due to
        # 'project(gtest)' above.
        include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    else ()
        message("GTEST_ROOT is not defined. Download source code Google Tests...")

        # This adds another subdirectory, which has 'project(gtest)'.
        include(CMakeLists-ExternalProjects.txt)

        # Global link directories
        link_directories(${CMAKE_BINARY_DIR}/GoogleTest-prefix/src/GoogleTest-build)

        enable_testing()

        # Include the gtest library. gtest_SOURCE_DIR is available due to
        # 'project(gtest)' above.
        include_directories(${CMAKE_BINARY_DIR}/gtest/include ${CMAKE_BINARY_DIR}/gtest)

    endif ()

    ##############
    # Unit Tests
    ##############
    add_executable(runUnitTests tests/unittests/fgetopt_unittest.cc)

    # Standard linking to gtest stuff.
    target_link_libraries(runUnitTests gtest gtest_main)

    # Extra linking for the project.
    target_link_libraries(runUnitTests fgetoptcc)

    target_link_libraries(runUnitTests ${CMAKE_THREAD_LIBS_INIT})

    # This is so you can do 'make test' to see all your tests run, instead of
    # manually running the executable runUnitTests to see those specific tests.
    add_test(NAME that-test-I-made COMMAND runUnitTests)
 
    # You can also omit NAME and COMMAND. The second argument could be some other
    # test executable.
    add_test(that-other-test-I-made runUnitTests)
endif()
