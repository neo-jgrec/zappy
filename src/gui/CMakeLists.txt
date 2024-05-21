add_executable(zappy_gui)

# Set the default C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Set compilation flags
add_compile_options(-Wall
	-Wextra
	-pedantic-errors
	-fexceptions
	-ffunction-sections
	-fdata-sections
	-fasynchronous-unwind-tables
	-fno-delete-null-pointer-checks
	-fno-common
	-fno-omit-frame-pointer
	-fno-strict-aliasing
	-fno-semantic-interposition
	-fstack-protector-strong
	-fstack-clash-protection
	-flto=auto
	-fdiagnostics-color=auto
	-grecord-gcc-switches
	-pipe
	-pthread
)

# If in debug mode, enable debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_options(-O0 -g3 -DDEBUG)
endif()

# Enable glibc assertions
add_definitions(-D_GLIBCXX_ASSERTIONS)

# Enable fortify by default
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

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

target_sources(zappy_gui
        PRIVATE
        ${SOURCES}
)

target_include_directories(zappy_gui
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/includes
)

target_link_libraries(zappy_gui
	PRIVATE
		sfml-graphics
		sfml-audio
		sfml-network
)

install(TARGETS zappy_gui)
