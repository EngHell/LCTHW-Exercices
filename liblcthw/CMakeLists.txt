cmake_minimum_required(VERSION 3.9)
project(lcthw)
set(CMAKE_C_FLAGS "-g -std=c11 -Wall -Wextra -Du_char='unsigned char'")
set(CMAKE_C_FLAGS_RELEASE "-O2")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
#set(CMAKE_VERBOSE_MAKEFILE  1)

include_directories(${CMAKE_SOURCE_DIR}/src)

#lIBRARY BUILD

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
add_library(lcthw STATIC ${SOURCES})
target_link_libraries(lcthw bsd)
#target_compile_definitions(lcthw PRIVATE u_char="unsigned char")

# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
# file( GLOB APP_SOURCES RELATIVE app/*.cxx )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/tests )
file( GLOB_RECURSE TESTS RELATIVE ${CMAKE_SOURCE_DIR} "tests/*_tests.c")
foreach( testsourcefile ${TESTS} )
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".c" "" testname ${testsourcefile} )
        string(REPLACE "tests/" "" testname ${testname})
    add_executable( ${testname} ${testsourcefile})
    # Make sure YourLib is linked to each app
    target_link_libraries( ${testname} lcthw )
endforeach( testsourcefile ${APP_SOURCES} )

#Those lines helps us to run the tests
add_custom_command ( OUTPUT tests.sh
        POST_BUILD
        COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/tests/runtests.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/)

# sadly i couldn't get this to work in the first build, you have to run cmake all again but no worries as nothing
# has changed it won't build the files again
# but just exec our .sh file
add_custom_target(
        runtests ALL
        DEPENDS tests.sh
)