cmake_minimum_required(VERSION 3.16)
project(ResourceExample C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(ResourceExample main.c ${CMAKE_CURRENT_BINARY_DIR}/resources.c)
target_link_libraries(ResourceExample ${GTK3_LIBRARIES})

set(GLIB_FLAGS --target=resources.c)
set(GLIB_FLAGS ${GLIB_FLAGS} --generate-source)
set(GLIB_FLAGS ${GLIB_FLAGS} --sourcedir=${PROJECT_SOURCE_DIR})

add_custom_command(
        OUTPUT resources.c
        COMMAND glib-compile-resources ${PROJECT_SOURCE_DIR}/example.gresource.xml ${GLIB_FLAGS}
        DEPENDS example.gresource.xml
        resource.txt
)

add_custom_target(generate_resources DEPENDS resources.c)
add_dependencies(${PROJECT_NAME} generate_resources)
