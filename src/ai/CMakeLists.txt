add_executable(zappy_ai)

# Set the default C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# If in debug mode, enable debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_options(-O0 -g3)
	add_compile_definitions(DEBUG)
endif()

# Enable glibc assertions
add_definitions(-D_GLIBCXX_ASSERTIONS)

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

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
)

target_sources(zappy_ai
        PRIVATE
        ${SOURCES}
)

target_include_directories(zappy_ai
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

install(TARGETS zappy_ai
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(tests)
