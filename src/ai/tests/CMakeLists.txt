add_executable(ai_unit_tests)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp
)

foreach(source ${SOURCES})
    file(READ ${source} contents)
    string(FIND "${contents}" "int main" main_found)
    if(main_found EQUAL -1)
        list(APPEND FILTERED_SOURCES ${source})
    endif()
endforeach()

file(GLOB_RECURSE TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

target_sources(ai_unit_tests PRIVATE
    ${FILTERED_SOURCES}
    ${TEST_SOURCES}
)

target_include_directories(ai_unit_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

target_link_libraries(ai_unit_tests PRIVATE
    criterion
    gcov
)

target_compile_options(ai_unit_tests PRIVATE
    --coverage
    -fprofile-arcs
    -ftest-coverage
)

install(TARGETS ai_unit_tests
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
