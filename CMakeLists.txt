cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(zappy)

# Use pthreads if possible
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads)

if(CMAKE_USE_PTHREADS_INIT)
	set(CMAKE_THREAD_LIBS_INIT "pthread")
endif()

# Disable developer warnings for CMake
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")

# The default name of the generated component
set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME "default")

# Export all the compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# If ccache is installed, use to speed up the build
find_program(CCACHE_FOUND ccache HINTS /bin /usr/bin)
if(CCACHE_FOUND)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

add_compile_options(-Wall
	-Wextra
	-Wpedantic
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

add_subdirectory(src)
