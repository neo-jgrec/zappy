add_executable(server_unit_tests)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.c
)

foreach(source ${SOURCES})
    file(READ ${source} contents)
    string(FIND "${contents}" "int main" main_found)
    if(main_found EQUAL -1)
        list(APPEND FILTERED_SOURCES ${source})
    endif()
endforeach()

file(GLOB_RECURSE TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

target_sources(server_unit_tests PRIVATE
    ${FILTERED_SOURCES}
    ${TEST_SOURCES}
)

target_include_directories(server_unit_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

target_link_libraries(server_unit_tests PRIVATE
    criterion
    gcov
    uuid
    m
)

target_compile_options(server_unit_tests PRIVATE
    --coverage
    -fprofile-arcs
    -ftest-coverage
)

target_include_directories(server_unit_tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../includes
        ${CMAKE_SOURCE_DIR}/../includes
		${UUID_INCLUDE_DIRS}
)

install(TARGETS server_unit_tests
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
