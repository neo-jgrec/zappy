add_executable(zappy_server)

# If in debug mode, enable debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_options(-O0 -g3)
	add_compile_definitions(DEBUG)
endif()

# Enable fortify by default but not in debug mode
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 12)
		# GCC 12 supports automatically initializing variables to zero
		add_compile_options(-ftrivial-auto-var-init=zero -O)

		# First we need to undef _FORTIFY_SOURCE as some systems
		# or libraries might have it set it previously.
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 ")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 ")
	else()
		add_definitions(-D_FORTIFY_SOURCE=2)
	endif()
endif()

find_package(PkgConfig REQUIRED)
pkg_search_module(UUID REQUIRED uuid)

find_library(MATH_LIB m)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

target_sources(zappy_server
        PRIVATE
        ${SOURCES}
)

target_include_directories(zappy_server
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_SOURCE_DIR}/includes
		${UUID_INCLUDE_DIRS}
)

target_link_libraries(zappy_server ${UUID_LIBRARIES} ${MATH_LIB})

install(TARGETS zappy_server)

add_subdirectory(tests)
